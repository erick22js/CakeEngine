#include <CakeEngine/graphics/renderer/Renderable.hpp>


void CKRenderable::bind(){
	program->use();
	mesh->bindBuffers();
}

void CKRenderable::unbind(){
	mesh->unbindBuffers();
}

CKRenderable::CKRenderable(CKMesh *mesh, CKShaderProgram *program){
	this->mesh = mesh;
	this->program = program;
}

GLint CKRenderable::getUniform(Char* name){
	return this->program->locateUniform(name);
}
