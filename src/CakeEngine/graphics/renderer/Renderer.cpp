#include <CakeEngine/graphics/renderer/Renderer.hpp>
#include <stdio.h>



CKRenderer::CKRenderer(CKWindow *window){
	this->window = window;
}

CKRenderer::~CKRenderer(){
	
}

void CKRenderer::bindFramebuffer(CKFrameBuffer *framebuffer){
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->framebuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, framebuffer->renderbuffer);
	current_framebuffer = framebuffer;
}

void CKRenderer::unbindFramebuffer(){
	current_framebuffer = nullptr;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


void CKRenderer::render(CKRenderable *renderable){
	CKMesh *mesh = renderable->mesh;
	CKShaderAttribs *attribs = renderable->program->getAttribs();
	
	/* Binds all the renderable properties */
	renderable->bind();
	
	/* Setup each attrib */
	Int attribs_n = attribs->getLength();
	for(int ai=0; ai<attribs_n; ai++){
		CKShaderAttrib *attrib = attribs->getAttrib(ai);
		glVertexAttribPointer(
			attrib->id,
			attrib->length,
			GL_FLOAT,
			GL_FALSE,
			attribs->size,
			attrib->offset);
		glEnableVertexAttribArray(attrib->id);
	}
	
	/* Draws the mesh on screen */
	if(mesh->uses_indices){
		glDrawElements(mesh->renderMode, mesh->indices, GL_UNSIGNED_SHORT, (void*)(mesh->indices_offset*sizeof(Uint16)));
	}
	else{
		glDrawArrays(mesh->renderMode, mesh->vertices_offset, mesh->vertices);
	}
	
	/* Disables each attrib */
	for(int ai=0; ai<attribs_n; ai++){
		CKShaderAttrib *attrib = attribs->getAttrib(ai);
		glDisableVertexAttribArray(attrib->id);
	}
	
	/* Unbinds the Mesh Geometry buffer */
	renderable->unbind();
}
