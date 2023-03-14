#ifndef cakengine_util_image_h
#define cakengine_util_image_h

#include "Pixels.hpp"


class CKImage{
	
private:
	SDL_Surface *surface;
	
public:
	CKImage(Char *filepath);
	CKImage(void* buffer, Uint32 length);
	~CKImage();
	
	void getSize(Int *w, Int *h);
	
	void getPixels(void* dest);
	
};


#endif // cakengine_util_image_h
