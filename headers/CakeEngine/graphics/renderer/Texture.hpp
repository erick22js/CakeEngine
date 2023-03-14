#ifndef cakengine_graphics_renderer_texture_h
#define cakengine_graphics_renderer_texture_h

#include "../opengl/opengl.hpp"
#include "../../util/Image.hpp"


class CKTexture{
	
	friend class CKRenderer;
	friend class CKFrameBuffer;
	
private:
	GLuint id;
	void* pixels = nullptr;
	Int width, height;
	CKPixelFormat format = CK_PIXELFORMAT_RGBA8888;
	CKType type = CK_TYPE_UNSIGNEDBYTE;
	
	void loadData_(void* buffer, Int width, Int height);
	void loadData_(void* buffer);
	
	void setFilter();
	
	void deleteTexture();
	
public:
	CKTexture();
	CKTexture(void* buffer, Int width, Int height);
	CKTexture(Int width, Int height);
	CKTexture(CKImage *image);
	~CKTexture();
	
	void loadData(void* buffer, Int width, Int height);
	
	void useTexture(Int index);
	
};


#endif // cakengine_graphics_renderer_texture_h
