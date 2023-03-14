#ifndef cakengine_graphics_renderer_renderable_h
#define cakengine_graphics_renderer_renderable_h

#include "Mesh.hpp"
#include "ShaderProgram.hpp"

class CKRenderable{
	
	friend class CKRenderer;
	
protected:
	CKMesh *mesh;
	CKShaderProgram *program;
	
	virtual void bind();
	virtual void unbind();
	
public:
	CKRenderable(CKMesh *mesh, CKShaderProgram *program);
	
	GLint getUniform(Char* name);
	
};


#endif // cakengine_graphics_renderer_renderable_h
