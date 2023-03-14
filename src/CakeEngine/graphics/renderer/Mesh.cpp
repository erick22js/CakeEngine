#include <CakeEngine/graphics/renderer/Mesh.hpp>


/**
	MESH UTIL PRIVATE FUNCTIONS
*/

void CKMesh::initBuffers(){
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
}

void CKMesh::deleteBuffers(){
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void CKMesh::dataBuffers(){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, attribs->size*vertices, vbuffer, usage);
	
	if(uses_indices){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Uint16)*indices, ibuffer, usage);
	}
}

void CKMesh::loadVBuffer(Uint8* vbuffer, Int vertices){
	this->vertices = vertices;
	Int length = attribs->size*vertices;
	
	if(this->vbuffer){
		delete[] this->vbuffer;
	}
	this->vbuffer = new Uint8[length];
	
	do{
		length--;
		this->vbuffer[length] = vbuffer[length];
	}while(length);
}

void CKMesh::loadIBuffer(Uint16* ibuffer, Int indices){
	this->indices = indices;
	Int length = indices;
	
	if(this->ibuffer){
		delete[] this->ibuffer;
	}
	this->ibuffer = new Uint16[length];
	
	do{
		length--;
		this->ibuffer[length] = ibuffer[length];
	}while(length);
}


/**
	OBJECT INITIALIZATION
*/

CKMesh::CKMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, CKRenderMode renderMode){
	this->attribs = attribs;
	this->uses_indices = false;
	this->renderMode = renderMode;
	
	loadVBuffer((Uint8*)vbuffer, vertices);
	
	initBuffers();
	dataBuffers();
}

CKMesh::CKMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, Uint16* ibuffer, Int indices, CKRenderMode renderMode){
	this->attribs = attribs;
	this->uses_indices = true;
	this->renderMode = renderMode;
	
	loadVBuffer((Uint8*)vbuffer, vertices);
	loadIBuffer(ibuffer, indices);
	
	initBuffers();
	dataBuffers();
}

CKMesh::CKMesh(CKShaderAttribs *attribs, CKRenderMode renderMode){
	this->attribs = attribs;
	this->uses_indices = false;
	this->renderMode = renderMode;
	
	initBuffers();
}

CKMesh::~CKMesh(){
	deleteBuffers();
}


/**
	MESH PUBLIC FUNCTIONS
*/

void CKMesh::setVertices(void* vbuffer, Int vertices){
	loadVBuffer((Uint8*)vbuffer, vertices);
	dataBuffers();
}

void CKMesh::setIndices(Uint16* ibufferm, Int indices){
	this->uses_indices = true;
	loadIBuffer(ibuffer, indices);
	dataBuffers();
}

void CKMesh::bindBuffers(){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void CKMesh::unbindBuffers(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void *CKMesh::getVerticesBuffer(){
	return vbuffer;
}

Uint16 *CKMesh::getIndicesBuffer(){
	return ibuffer;
}


/**
	CUSTOM MESH OBJECTS
*/

CKStaticMesh::CKStaticMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, CKRenderMode renderMode): CKMesh(attribs, vbuffer, vertices, renderMode){
	usage = GL_STATIC_DRAW;
}

CKStaticMesh::CKStaticMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, Uint16* ibufferm, Int indices, CKRenderMode renderMode): CKMesh(attribs, vbuffer, vertices, ibufferm, indices, renderMode){
	usage = GL_STATIC_DRAW;
}

CKStaticMesh::CKStaticMesh(CKShaderAttribs *attribs, CKRenderMode renderMode): CKMesh(attribs, renderMode){
	usage = GL_STATIC_DRAW;
}

CKDynamicMesh::CKDynamicMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, CKRenderMode renderMode): CKMesh(attribs, vbuffer, vertices, renderMode){
	usage = GL_DYNAMIC_DRAW;
}

CKDynamicMesh::CKDynamicMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, Uint16* ibufferm, Int indices, CKRenderMode renderMode): CKMesh(attribs, vbuffer, vertices, ibufferm, indices, renderMode){
	usage = GL_DYNAMIC_DRAW;
}

CKDynamicMesh::CKDynamicMesh(CKShaderAttribs *attribs, CKRenderMode renderMode): CKMesh(attribs, renderMode){
	usage = GL_DYNAMIC_DRAW;
}

CKStreamMesh::CKStreamMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, CKRenderMode renderMode): CKMesh(attribs, vbuffer, vertices, renderMode){
	usage = GL_STREAM_DRAW;
}

CKStreamMesh::CKStreamMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, Uint16* ibufferm, Int indices, CKRenderMode renderMode): CKMesh(attribs, vbuffer, vertices, ibufferm, indices, renderMode){
	usage = GL_STREAM_DRAW;
}

CKStreamMesh::CKStreamMesh(CKShaderAttribs *attribs, CKRenderMode renderMode): CKMesh(attribs, renderMode){
	usage = GL_STREAM_DRAW;
}
