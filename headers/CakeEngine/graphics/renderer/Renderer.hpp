#ifndef cakengine_graphics_renderer_h
#define cakengine_graphics_renderer_h

#include "../window/Window.hpp"
#include "Renderable.hpp"
#include "Texture.hpp"
#include "CompositeOperations.hpp"
#include <CakeEngine/graphics/renderer/FrameBuffer.hpp>



class CKRenderer{
	
private:
	CKWindow *window = nullptr;
	CKFrameBuffer *current_framebuffer = nullptr;
	
public:
	CKCompositeOperations copr = CKCompositeOperations();
	
	CKRenderer(CKWindow *window);
	~CKRenderer();
	
	void bindFramebuffer(CKFrameBuffer *framebuffer);
	void unbindFramebuffer();
	
	void render(CKRenderable *renderable);
	
};


#endif // cakengine_graphics_renderer_h
