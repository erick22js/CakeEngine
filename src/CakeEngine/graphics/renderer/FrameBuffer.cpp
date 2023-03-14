#include <CakeEngine/graphics/renderer/FrameBuffer.hpp>



CKFrameBuffer::CKFrameBuffer(){
	glGenFramebuffers(1, &framebuffer);
	glGenRenderbuffers(1, &renderbuffer);
}

CKFrameBuffer::~CKFrameBuffer(){
	glGenFramebuffers(1, &framebuffer);
	glGenRenderbuffers(1, &renderbuffer);
}


Bool CKFrameBuffer::setup(CKFramebufferMode mode, Int width, Int height){
	output.loadData(nullptr, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	
	output.format.gli_formatinternal = mode.format_internal;
	output.format.gli_format = mode.format;
	output.type.glconst = mode.texture_type;
	output.loadData_(nullptr);
	output.setFilter();
	
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, mode.attach_mode, GL_TEXTURE_2D, output.id, 0);
	
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return false;
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	return true;
}


CKTexture *CKFrameBuffer::getTexture(){
	return &output;
}


