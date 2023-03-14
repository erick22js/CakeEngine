#ifndef cakengine_graphics_renderer_shaderprogram_h
#define cakengine_graphics_renderer_shaderprogram_h

#include "ShaderAttribs.hpp"



class CKShaderProgram{
	
	friend class CKRenderer;
	
private:
	GLint program;
	
	CKShaderAttribs attribs;
	
	GLint createShader(const Char** srcs, Int srcs_count, GLenum type);
	void createProgram(GLint id_vert, GLint id_frag);
	void createFromSource(const Char* src_vertex, const Char* src_fragment);
	
	void deleteProgram();
	
public:
	CKShaderProgram(const Char* src_vertex, const Char* src_fragment);
	~CKShaderProgram();
	
	Int locateAttrib(const Char *name, CKType type, Int length);
	CKShaderAttribs *getAttribs();
	
	Int locateUniform(const Char *name);
	
	void use();
	
};


#endif // cakengine_graphics_renderer_shaderprogram_h
