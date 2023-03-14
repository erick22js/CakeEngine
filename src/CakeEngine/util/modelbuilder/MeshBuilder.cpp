#include <CakeEngine/util/modelbuilder/MeshBuilder.hpp>



void* CKMeshBuilder::getVertex(){
	return (void*)(vertices.data()+attribs->getVertexSize()*(vindex-1));
}


CKMeshBuilder::CKMeshBuilder(CKShaderAttribs *attribs){
	this->attribs = attribs;
}

CKMeshBuilder::~CKMeshBuilder(){
	
}


Uint16 CKMeshBuilder::addVertex(){
	vertices.resize(vertices.size()+attribs->getVertexSize());
	return vindex++;
}

Uint16 CKMeshBuilder::addIndices(Uint16 v1, Uint16 v2, Uint16 v3){
	uses_index = true;
	indices.push_back(v1);
	indices.push_back(v2);
	indices.push_back(v3);
	return tindex++;
}


void* CKMeshBuilder::getVertices(){
	return (void*)vertices.data();
}

void* CKMeshBuilder::getIndices(){
	return (void*)indices.data();
}


CKMesh* CKMeshBuilder::createMesh(){
	if(uses_index){
		return new CKMesh(attribs, vertices.data(), vindex, indices.data(), tindex*3, CK_RENDERMODE_TRIANGLES);
	}
	else{
		return new CKMesh(attribs, vertices.data(), vindex, CK_RENDERMODE_TRIANGLES);
	}
}
