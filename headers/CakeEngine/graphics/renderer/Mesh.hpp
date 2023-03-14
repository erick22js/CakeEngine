#ifndef cakengine_graphics_renderer_mesh_h
#define cakengine_graphics_renderer_mesh_h

#include "ShaderAttribs.hpp"



class CKMesh{
	
	friend class CKRenderer;
	
protected:
	GLuint vbo;
	GLuint ibo;
	
	Bool uses_indices = false;
	Uint8* vbuffer = nullptr;
	Int vertices = 0;
	Int vertices_offset = 0;
	Uint16* ibuffer = nullptr;
	Int indices = 0;
	Int indices_offset = 0;
	
	GLenum usage = GL_STATIC_DRAW;
	CKRenderMode renderMode = CK_RENDERMODE_TRIANGLES;
	
	CKShaderAttribs *attribs = nullptr;
	
	void initBuffers();
	void deleteBuffers();
	void dataBuffers();
	
	void loadVBuffer(Uint8* vbuffer, Int vertices);
	void loadIBuffer(Uint16* ibuffer, Int indices);
	
public:
	CKMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, CKRenderMode renderMode);
	CKMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, Uint16* ibufferm, Int indices, CKRenderMode renderMode);
	CKMesh(CKShaderAttribs *attribs, CKRenderMode renderMode);
	~CKMesh();
	
	void setVertices(void* vbuffer, Int vertices);
	void setIndices(Uint16* ibufferm, Int indices);
	
	void bindBuffers();
	void unbindBuffers();
	
	void* getVerticesBuffer();
	Uint16* getIndicesBuffer();
	
};

class CKStaticMesh:public CKMesh{
	
public:
	CKStaticMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, CKRenderMode renderMode);
	CKStaticMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, Uint16* ibufferm, Int indices, CKRenderMode renderMode);
	CKStaticMesh(CKShaderAttribs *attribs, CKRenderMode renderMode);
	
};

class CKDynamicMesh:public CKMesh{
	
public:
	CKDynamicMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, CKRenderMode renderMode);
	CKDynamicMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, Uint16* ibufferm, Int indices, CKRenderMode renderMode);
	CKDynamicMesh(CKShaderAttribs *attribs, CKRenderMode renderMode);
	
};

class CKStreamMesh:public CKMesh{
	
public:
	CKStreamMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, CKRenderMode renderMode);
	CKStreamMesh(CKShaderAttribs *attribs, void* vbuffer, Int vertices, Uint16* ibufferm, Int indices, CKRenderMode renderMode);
	CKStreamMesh(CKShaderAttribs *attribs, CKRenderMode renderMode);
	
};


#endif // cakengine_graphics_renderer_mesh_h
