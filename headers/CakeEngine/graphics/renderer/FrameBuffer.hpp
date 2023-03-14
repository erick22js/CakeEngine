#ifndef cakengine_graphics_renderer_framebuffer_h
#define cakengine_graphics_renderer_framebuffer_h

#include <CakeEngine/api.hpp>
#include <CakeEngine/graphics/opengl/opengl.hpp>
#include <CakeEngine/graphics/renderer/Texture.hpp>


class CKFrameBuffer{
	
	friend class CKRenderer;
	
private:
	GLuint framebuffer = 0;
	GLuint renderbuffer = 0;
	CKTexture output = CKTexture(1, 1);
	
public:
	CKFrameBuffer();
	~CKFrameBuffer();
	
	Bool setup(CKFramebufferMode mode, Int width, Int height);
	
	CKTexture *getTexture();
	
};


#endif // cakengine_graphics_renderer_framebuffer_h
