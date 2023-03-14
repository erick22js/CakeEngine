#ifndef cakengine_graphics_renderer_shaderattribs_h
#define cakengine_graphics_renderer_shaderattribs_h

#include <iostream>
#include <vector>

#include "../../api.hpp"
#include "../opengl/opengl.hpp"



typedef struct CKShaderAttrib{
	const Char* name;
	GLuint id;
	CKType type;
	Int length;
	void* offset;
}CKShaderAttrib;


class CKShaderAttribs{
	
	friend class CKShaderProgram;
	friend class CKMesh;
	friend class CKRendererable;
	friend class CKRenderer;
	
private:
	std::vector<CKShaderAttrib> attribs;
	Int size = 0;
	void* endoffset = 0;
	
	CKShaderAttribs();
	
	Int pushAttrib(const Char* name, GLuint id, CKType type, Int length);
	
public:
	
	Int has(const Char* name);
	Int has(GLuint id);
	
	Int getLength();
	Int getVertexSize();
	CKShaderAttrib *getAttrib(Int index);
	
};


#endif // cakengine_graphics_renderer_shaderattribs_h
