#include <CakeEngine/resources/g3d/ModelInstance.hpp>



/**
	MODEL
*/

CKModelMaterial *CKModelInstance::de_material = nullptr;
CKTexture *CKModelInstance::de_texture = nullptr;


CKModelInstance::CKModelInstance(CKMesh *mesh, CKShaderProgram *material): CKRenderable(mesh, material){
	if(de_texture==nullptr){
		Uint8* purplepixel= new Uint8[4]{0xff, 0xff, 0xff, 0xff};//new Uint8[4]{0xff, 0x44, 0xff, 0xff};
		de_texture = new CKTexture(purplepixel, 1, 1);
	}
	tex0 = de_texture;
}


CKModelInstance::~CKModelInstance(){
	
}


void CKModelInstance::render(CKRenderer *renderer, CKMat4 *mat){
	de_material->use();
	if(tex0){
		tex0->useTexture(0);
		glUniform1i(de_material->u_tex0, 0);
	}
	glUniformMatrix4fv(de_material->u_mat, 1, GL_FALSE, mat->values);
	renderer->render(this);
}


/**
	MODEL BUILDER
*/


CKModelBuilder::CKModelBuilder(){
	if(!CKModelInstance::de_material){
		CKModelInstance::de_material = new CKModelMaterial();
	}
	
	mesh_builder = new CKMeshBuilder(CKModelInstance::de_material->getAttribs());
}

CKModelBuilder::~CKModelBuilder(){
	
}


CKMeshBuilder *CKModelBuilder::getMeshBuilder(){
	return mesh_builder;
}


CKModelMaterial *CKModelBuilder::getMaterial(){
	return CKModelInstance::de_material;
}


CKModelInstance *CKModelBuilder::build(){
	if(!de_mesh){
		de_mesh = mesh_builder->createMesh();
	}
	de_mesh_ref++;
	
	return new CKModelInstance(de_mesh, CKModelInstance::de_material);
}
