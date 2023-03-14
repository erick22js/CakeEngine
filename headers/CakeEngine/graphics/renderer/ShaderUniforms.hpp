#ifndef cakengine_graphics_renderer_shaderuniforms_h
#define cakengine_graphics_renderer_shaderuniforms_h

#include <iostream>
#include <vector>

#include "../../api.hpp"
#include "../opengl/opengl.hpp"


struct CKShaderUniform{
	const Char* name;
	GLuint id;
};


class CKShaderUniforms{
	
	friend class CKShaderProgram;
	friend class CKRenderable;
	friend class CKRenderer;
	
private:
	std::vector<CKShaderUniform> uniforms;
	
	CKShaderUniforms();
	
	void pushUniform(const Char* name, GLuint id);
	
public:
	Sint32 has(const Char* name);
	Sint32 has(GLuint id);
	
	CKShaderUniform* getUniform(Int index);
	
};


#endif // cakengine_graphics_renderer_shaderuniforms_h
