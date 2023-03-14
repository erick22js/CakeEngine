#include <CakeEngine/util/formats/DaeHanddler.hpp>



/**
	IMPORTER
*/

Char* CKDaeImporter::translate_reference(Char* reference){
	return reference+1;
}

CKDae::Source *CKDaeImporter::locate_sourceById(std::vector<CKDae::Source*> *sources, Char* id){
	//std::cout << "Finding for '" << id << "'" << std::endl;
	for(Int i=0; i<sources->size(); i++){
		//std::cout << " * Option is '" << sources->at(i)->id << "'" << std::endl;
		if(CKString::isEqual(sources->at(i)->id, id)){
			//std::cout << "FOUND!!! '" << id << "'" << std::endl;
			return sources->at(i);
		}
	}
	return nullptr;
}
	

Int CKDaeImporter::decode_arrayFloat(Float* array, Char* str, Int length){
	//std::cout << std::endl;
	for(Int ai=0; ai<length; ai++){
		array[ai] = CKString::toFloat(str);
		//std::cout << array[ai] << " ";
		while((*str)&&((*str)!=' ')){
			str++;
		}
		str++;
	}
	//std::cout << std::endl;
	//std::cout << std::endl;
	return 0;
}

Int CKDaeImporter::decode_arrayUint16(Uint16* array, Char* str, Int length){
	//std::cout << std::endl;
	for(Int ai=0; ai<length; ai++){
		array[ai] = CKString::toInt(str);
		//std::cout << array[ai] << " ";
		while((*str)&&((*str)!=' ')){
			str++;
		}
		str++;
	}
	//std::cout << std::endl;
	//std::cout << std::endl;
	return 0;
}


Int CKDaeImporter::load_source(CKDae::Mesh *mesh, CKDae::Source *source, CKXmlNode *xmlsrc){
	CKXmlNode *xmlarray = nullptr;
	CKDae::Array array = {};
	
	source->id = xmlsrc->getProperty("id");
	source->name = xmlsrc->getProperty("name");
	
	/* Loads Float Array */
	xmlarray = xmlsrc->getFirstChildByName("float_array");
	
	array.id = xmlarray->getProperty("id");
	array.count = CKString::toInt(xmlarray->getProperty("count"));
	array.data = (void*)new Float[array.count];
	decode_arrayFloat((Float*)array.data, xmlarray->getContent(), array.count);
	
	source->array = array;
	
	return 0;
}

Int CKDaeImporter::load_triangles(CKDae::Triangles* triangles, CKDae::Mesh *mesh, CKXmlNode *xmltriangles){
	/* Loads the inputs inside triangles */
	std::vector<CKXmlNode*> xmlnodes_input = xmltriangles->getChildrenByName("input");
	Int attribs_count = 0;
	for(CKXmlNode *node:xmlnodes_input){
		CKDae::InputShared *input = new CKDae::InputShared{};
		if(CKString::isEqual(node->getProperty("semantic"), "VERTEX")){
			input->semantic = CKDae::VERTEX;
		}
		else if(CKString::isEqual(node->getProperty("semantic"), "NORMAL")){
			input->semantic = CKDae::NORMAL;
		}
		else if(CKString::isEqual(node->getProperty("semantic"), "TEXCOORD")){
			input->semantic = CKDae::TEXCOORD;
		}
		Char *referenceId = translate_reference(node->getProperty("source"));
		CKDae::SourceLookable* source = locate_sourceById(&mesh->c_src, referenceId);
		if(source==nullptr){
			//std::cout << "Now, comparing '" << referenceId << "' with the vertex attributes with id '"<< mesh->attribs.id << "'\n";
			if(CKString::isEqual(mesh->attribs.id, referenceId)){
				source = &mesh->attribs;
				//std::cout << "Its This!" << std::endl;
			}
		}
		input->src = source;
		mesh->c_inputs.push_back(input);
		attribs_count++;
	}
	
	/* Loads the indices */
	CKXmlNode *xmlindices = xmltriangles->getFirstChildByName("p");
	
	triangles->count = CKString::toInt(xmltriangles->getProperty("count"));
	triangles->indices_count = triangles->count*3*attribs_count;
	Uint16* indices = new Uint16[triangles->indices_count];
	decode_arrayUint16((Uint16*)indices, xmlindices->getContent(), triangles->indices_count);
	triangles->indices = indices;
	
	return 0;
}

Int CKDaeImporter::load_mesh(CKDae* dae, CKDae::Mesh *mesh, CKXmlNode *xmlmesh){
	/* Loads the Sources */
	std::vector<CKXmlNode*> xmlnodes_src = xmlmesh->getChildrenByName("source");
	for(CKXmlNode *node:xmlnodes_src){
		CKDae::Source *source = new CKDae::Source{};
		load_source(mesh, source, node);
		//std::cout << "@Pushing source with id '" << source->id << "'\n";
		mesh->c_src.push_back(source);
	}
	
	/* Loads the vertices Attributes */
	CKXmlNode *xmlvertices = xmlmesh->getFirstChildByName("vertices");
	mesh->attribs.id = xmlvertices->getProperty("id");
	std::vector<CKXmlNode*> xmlnodes_verticesinput = xmlvertices->getChildrenByName("input");
	for(CKXmlNode *node:xmlnodes_verticesinput){
		CKDae::InputUnshared *input = new CKDae::InputUnshared{};
		Char* referenceId = translate_reference(node->getProperty("source"));
		if(CKString::isEqual(node->getProperty("semantic"), "POSITION")){
			input->semantic = CKDae::POSITION;
			CKDae::Source* source = locate_sourceById(&mesh->c_src, referenceId);
			input->src = source;
		}
		mesh->attribs.inputs.push_back(input);
	}
	
	/* Loads the triangle */
	std::vector<CKXmlNode*> xmlnodes_trianglesinput = xmlmesh->getChildrenByName("triangles");
	for(CKXmlNode *node:xmlnodes_trianglesinput){
		//std::cout << "@ Loading Triangles\n";
		CKDae::Triangles *triangles = new CKDae::Triangles{};
		load_triangles(triangles, mesh, node);
		mesh->triangles.push_back(triangles);
	}
	
	return 0;
}

Int CKDaeImporter::build_mesh(CKDae* dae, CKDae::Mesh *mesh, CKXmlNode *xmlmesh){
	CKModelBuilder *mobuil = new CKModelBuilder();
	CKModelMaterial *momate = mobuil->getMaterial();
	CKMeshBuilder *mebuil = mobuil->getMeshBuilder();
	
	/* Setup the basis inputs to start the model builder */
	std::vector<CKDae::InputShared*> inputs = mesh->c_inputs;
	
	CKDae::InputShared
		*in_vertex = nullptr,
		*in_normal = nullptr,
		*in_texcoord = nullptr;
	
	for(CKDae::InputShared *input:inputs){
		switch(input->semantic){
			case CKDae::VERTEX:{
				in_vertex = input;
			}
			break;
			case CKDae::NORMAL:{
				in_normal = input;
			}
			break;
			case CKDae::TEXCOORD:{
				in_texcoord = input;
			}
			break;
			default:{
				//std::cout << "Found a non-valid semantic!" << std::endl;
			}
		}
	}
	
	CKDae::Triangles *triangles = mesh->triangles[0];
	
	Int ipv = (triangles->indices_count/triangles->count)/3;
	Int vpt = 3;
	Int count_indices = triangles->indices_count;
	
	struct Vertex{
		Float position[3];
		Float normal[3];
		Float texcoord[2];
	};
	
	std::vector<Vertex> vertices = std::vector<Vertex>(0);
	
	for(Int i=0; i<count_indices; i+=ipv*vpt){
		Int ibase = i;
		for(Int vi=0; vi<3; vi++){
			Int ivbase = ibase;
			Vertex vertex;
			if(in_vertex!=nullptr){
				vertex.position[0] = in_vertex->getFloat(triangles->indices[ibase + ipv*vi + in_vertex->offset]*3 + 0);
				vertex.position[1] = in_vertex->getFloat(triangles->indices[ibase + ipv*vi + in_vertex->offset]*3 + 1);
				vertex.position[2] = in_vertex->getFloat(triangles->indices[ibase + ipv*vi + in_vertex->offset]*3 + 2);
			}
			else{
				vertex.position[0] = 0;
				vertex.position[1] = 0;
				vertex.position[2] = 0;
			}
			if(in_normal!=nullptr){
				vertex.normal[0] = in_normal->getFloat(triangles->indices[ibase + ipv*vi + in_normal->offset]*3 + 0);
				vertex.normal[1] = in_normal->getFloat(triangles->indices[ibase + ipv*vi + in_normal->offset]*3 + 1);
				vertex.normal[2] = in_normal->getFloat(triangles->indices[ibase + ipv*vi + in_normal->offset]*3 + 2);
			}
			else{
				vertex.normal[0] = 0;
				vertex.normal[1] = 0;
				vertex.normal[2] = 0;
			}
			if(in_texcoord!=nullptr){
				vertex.texcoord[0] = in_texcoord->getFloat(triangles->indices[ibase + ipv*vi + in_texcoord->offset]*3 + 0);
				vertex.texcoord[1] = in_texcoord->getFloat(triangles->indices[ibase + ipv*vi + in_texcoord->offset]*3 + 1);
			}
			else{
				vertex.texcoord[0] = 0;
				vertex.texcoord[1] = 0;
			}
			vertices.push_back(vertex);
		}
	}
	
	Int count_vertex = vertices.size();
	for(Int pi = 0; pi<count_vertex; pi++){
		mebuil->addVertex();
		mebuil->setAttrib3v<Float>(momate->a_position,
			vertices[pi].position[0],
			vertices[pi].position[1],
			vertices[pi].position[2]);
		mebuil->setAttrib3v<Float>(momate->a_normal,
			vertices[pi].normal[0],
			vertices[pi].normal[1],
			vertices[pi].normal[2]);
		mebuil->setAttrib3v<Float>(momate->a_color, 1, 1, 1);
		mebuil->setAttrib2v<Float>(momate->a_tex0uv,
			vertices[pi].texcoord[0],
			vertices[pi].texcoord[1]);
	}
	
	/* TESTING AREA{ */
	/*
	mebuil->addVertex();
	mebuil->setAttrib3v<Float>(momate->a_position, -0.25, +0.25, -1.5f);
	mebuil->setAttrib3v<Float>(momate->a_normal, 0, 0, 1);
	mebuil->setAttrib3v<Float>(momate->a_color, 1, 1, 1);
	mebuil->setAttrib2v<Float>(momate->a_tex0uv, 0, 0);
	mebuil->addVertex();
	mebuil->setAttrib3v<Float>(momate->a_position, +0.25, +0.25, -1.5f);
	mebuil->setAttrib3v<Float>(momate->a_normal, 0, 0, 1);
	mebuil->setAttrib3v<Float>(momate->a_color, 1, 1, 1);
	mebuil->setAttrib2v<Float>(momate->a_tex0uv, 1, 0);
	mebuil->addVertex();
	mebuil->setAttrib3v<Float>(momate->a_position, +0.25, -0.25, -1.5f);
	mebuil->setAttrib3v<Float>(momate->a_normal, 0, 0, 1);
	mebuil->setAttrib3v<Float>(momate->a_color, 1, 1, 1);
	mebuil->setAttrib2v<Float>(momate->a_tex0uv, 1, 1);
	mebuil->addVertex();
	mebuil->setAttrib3v<Float>(momate->a_position, -0.25, -0.25, -1.5f);
	mebuil->setAttrib3v<Float>(momate->a_normal, 0, 0, 1);
	mebuil->setAttrib3v<Float>(momate->a_color, 1, 1, 1);
	mebuil->setAttrib2v<Float>(momate->a_tex0uv, 0, 1);
	mebuil->addIndices(0, 1, 2);
	mebuil->addIndices(0, 2, 3);
	*/
	/* }TESTING AREA */
	
	mesh->builder = mobuil;
	return 0;
}

Int CKDaeImporter::load_geometry(CKDae* dae, CKDae::Geometry *geometry, CKXmlNode *xmlgeo){
	CKXmlNode *xmlmesh = xmlgeo->getFirstChildByName("mesh");
	
	/* Loads up the mesh Object */
	CKDae::Mesh *mesh = new CKDae::Mesh{};
	
	load_mesh(dae, mesh, xmlmesh);
	build_mesh(dae, mesh, xmlmesh);
	
	geometry->builder = mesh->builder;
	geometry->mesh = mesh;
	
	return 0;
}

Int CKDaeImporter::load_libraries(CKDae* dae, CKXmlNode *xmldae){
	/* Loading geometries */
	CKXmlNode *lib_geometries = xmldae->getFirstChildByName("library_geometries");
	std::vector<CKXmlNode*> geometries = lib_geometries->getChildrenByName("geometry");
	
	for(CKXmlNode *node:geometries){
		CKDae::Geometry geometry;
		load_geometry(dae,  &geometry, node);
		dae->lib_geometries.push_back(geometry);
	}
	
	return 0;
}


CKScene3D *CKDaeImporter::import(CKReader *reader){
	CKXmlObject *xml = CKXmlDecoder::decodeFrom(reader);
	CKXmlNode *xmldae = xml->getFirstChildByName("COLLADA");
	
	CKDae dae;
	
	load_libraries(&dae, xmldae);
	
	CKScene3D *scene = new CKScene3D();
	for(CKDae::Geometry geometry:dae.lib_geometries){
		CKModelInstance *model = geometry.builder->build();
		scene->addChild(model);
	}
	/*
	for(CKDae::Geometry geo:dae.lib_geometries){
		CKModelInstance *model = geo.builder->build();
		scene->addChild(model);
	}
	*/
	delete xml;
	return scene;
}

#ifdef _

Int load_geometry_(Dae* dae, Geometry *geometry, CKXmlNode *xmlgeo){
	
	CKXmlNode *xmlmesh = xmlgeo->getFirstChildByName("mesh");
	
	/* Get triangles properties */
	CKXmlNode *xmltris = xmlmesh->getFirstChildByName("triangles");
	
	/* Get vertices attributes */
	std::vector<CKXmlNode*> xmlvert = xmlmesh->getFirstChildByName("vertices")->getChildren();
	CKXmlNode* xmlvert_pos = nullptr;
	
	for(CKXmlNode *node:xmlvert){
		if(strcmp(node->getProperty("semantic"), "POSITION")==0){
			xmlvert_pos = node;
			std::cout << "Found!" << std::endl;
			break;
		}
	}
	
	/* Get inputs */
	std::vector<CKXmlNode*> xmltrisinputs = xmltris->getChildrenByName("input");
	CKXmlNode *trinput_vertex = nullptr;
	CKXmlNode *trinput_normal = nullptr;
	CKXmlNode *trinput_map = nullptr;
	
	for(CKXmlNode *node:xmltrisinputs){
		if(strcmp(node->getProperty("semantic"), "VERTEX")){
			trinput_vertex = node;
		}
		if(strcmp(node->getProperty("semantic"), "NORMAL")){
			trinput_normal = node;
		}
		if(strcmp(node->getProperty("semantic"), "TEXCOORD")){
			trinput_map = node;
		}
	}
	
	/* Get attributes source */
	std::vector<CKXmlNode*> sources = xmlmesh->getChildrenByName("source");
	CKXmlNode *src_position = nullptr;
	CKXmlNode *src_normals = nullptr;
	CKXmlNode *src_map = nullptr;
	
	for(CKXmlNode *node:sources){
		if(strcmp(node->getProperty("id"), xmlvert_pos->getProperty("source")+1)==0){
			src_position = node;
		}/*
		if(strcmp(node->getProperty("id"), )==0){
			src_position = node;
		}*/
	}
	
	CKXmlNode* src_position_array = src_position->getFirstChildByName("float_array");
	
	// Decode positions
	Int position_vals_count = CKString::toInt(src_position_array->getProperty("count"));
	Char* position_vals_src = src_position_array->getContent();
	
	std::cout << position_vals_src << std::endl;
	
	Float* position = new Float[position_vals_count];
	
	for(Int pi=0; pi<position_vals_count; pi++){
		position[pi] = CKString::toFloat(position_vals_src);
		//std::cout << position[pi] << " ";
		while((*position_vals_src)&&((*position_vals_src)!=' ')){
			position_vals_src++;
		}
		position_vals_src++;
	}
	std::cout << std::endl;
	
	
	/* Retrieves the indices info */
	CKXmlNode *indices = xmltris->getFirstChildByName("p");
	
	// Decode indices
	Int ipv = xmltris->getChildrenByName("input").size(); //Indices for vertex
	Int vpt = 3; //Vertices for triangles
	Char* indice_vals_src = indices->getContent();
	Int indice_vals_count = CKString::toInt(xmltris->getProperty("count"))*ipv*vpt;
	
	std::cout << indice_vals_src << std::endl;
	
	Uint16* indice = new Uint16[indice_vals_count];
	
	for(Int pi=0; pi<indice_vals_count; pi++){
		indice[pi] = CKString::toInt(indice_vals_src);
		//std::cout << indice[pi] << " ";
		while((*indice_vals_src)&&((*indice_vals_src)!=' ')){
			indice_vals_src++;
		}
		indice_vals_src++;
	}
	std::cout << std::endl;
	
	
	CKModelBuilder *builder = new CKModelBuilder();
	CKModelMaterial *mate = builder->getMaterial();
	CKMeshBuilder *buil = builder->getMeshBuilder();
	
	
	Int pindex = 0;
	while(position_vals_count){
		buil->addVertex();
		buil->setAttrib3v<Float>(mate->a_position, position[0 + pindex*3], position[1 + pindex*3], position[2 + pindex*3]);
		buil->setAttrib3v<Float>(mate->a_normal, 0, 0, 1);
		buil->setAttrib3v<Float>(mate->a_color, 1, 1, 1);
		buil->setAttrib2v<Float>(mate->a_tex0uv, 0, 0);
		pindex++;
		position_vals_count -= 3;
	}
	Int iindex = 0;
	while(indice_vals_count){
		buil->addIndices(indice[ipv*0 + iindex*ipv*vpt], indice[ipv*1 + iindex*ipv*vpt], indice[ipv*2 + iindex*ipv*vpt]);
		iindex++;
		indice_vals_count -= ipv*vpt;
	}
	
	/* Setup Geometry Object */
	geometry->id = xmlgeo->getProperty("id");
	geometry->name = xmlgeo->getProperty("name");
	geometry->builder = builder;
	
	return 0;
}


CKScene3D *import_(CKReader *reader){
	CKXmlObject *xml = CKXmlDecoder::decodeFrom(reader);
	CKXmlNode *xmldae = xml->getFirstChildByName("COLLADA");
	
	Dae dae;
	
	load_libraries(&dae, xmldae);
	
	CKScene3D *scene = new CKScene3D();
	
	for(Geometry geo:dae.lib_geometries){
		CKModelInstance *model = geo.builder->build();
		scene->addChild(model);
	}
	
	delete xml;
	return scene;
}


#endif
