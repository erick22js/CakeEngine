#include <iostream>

#include <CakeEngine/graphics/renderer/ShaderProgram.hpp>



GLint CKShaderProgram::createShader(const Char** srcs, Int srcs_length, GLenum type){
	char info_log[1024];
	
	GLint id = glCreateShader(type);
	glShaderSource(id, srcs_length, srcs, NULL);
	glCompileShader(id);
	
	GLint info_status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &info_status);
	
	if(!info_status){
		glGetShaderInfoLog(id, 1023, NULL, info_log);
		std::cout << "Error in " << (type==GL_VERTEX_SHADER?"Vertex":type==GL_FRAGMENT_SHADER?"Fragment":"Unknown") << " Shader :\n\"%s\"\n" << info_log << std::endl;
		/* TODO: Error thrown */
		return -1;
	}
	
	return id;
}

void CKShaderProgram::createProgram(GLint id_vert, GLint id_frag){
	char info_log[1024];
	
	program = glCreateProgram();
	glAttachShader(program, id_vert);
	glAttachShader(program, id_frag);
	glLinkProgram(program);
	
	GLint info_status;
	glGetProgramiv(program, GL_LINK_STATUS, &info_status);
	
	if(!info_status){
		glGetProgramInfoLog(program, 1023, NULL, info_log);
		std::cout << "Error in Program:\n\"%s\"\n" << info_log << std::endl;
		/* TODO: Error thrown */
	}
	
	glUseProgram(program);
	glDeleteShader(id_vert);
	glDeleteShader(id_frag);
}

void CKShaderProgram::createFromSource(const Char* src_vertex, const Char* src_fragment){
	GLint id_vert = createShader(&src_vertex, 1, GL_VERTEX_SHADER);
	GLint id_frag = createShader(&src_fragment, 1, GL_FRAGMENT_SHADER);
	
	createProgram(id_vert, id_frag);
}

void CKShaderProgram::deleteProgram(){
	glDeleteProgram(program);
}

CKShaderProgram::CKShaderProgram(const Char* src_vertex, const Char* src_fragment){
	CKShaderProgram::createFromSource(src_vertex, src_fragment);
}

CKShaderProgram::~CKShaderProgram(){
	deleteProgram();
}

Int CKShaderProgram::locateAttrib(const Char *name, CKType type, Int length){
	Int offset;
	if((offset = attribs.has(name))!=(-1)){
		return offset;
	}
	GLint id = glGetAttribLocation(program, name);
	if(id==(-1)){
		return -1;
	}
	return attribs.pushAttrib(name, id, type, length);
}

CKShaderAttribs *CKShaderProgram::getAttribs(){
	return &attribs;
}

Int CKShaderProgram::locateUniform(const Char *name){
	GLint id = glGetUniformLocation(program, name);
	return id;
}

void CKShaderProgram::use(){
	glUseProgram(program);
}
