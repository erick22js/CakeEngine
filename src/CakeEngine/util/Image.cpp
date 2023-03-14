#include <SDL2/SDL_image.h>

#include <CakeEngine/util/Image.hpp>


CKImage::CKImage(Char *filepath){
	surface = IMG_Load(filepath);
}

CKImage::CKImage(void* buffer, Uint32 length){
	surface = IMG_Load_RW((SDL_RWops*)buffer, length);
}

CKImage::~CKImage(){
	SDL_FreeSurface(surface);
}


void CKImage::getSize(Int *w, Int *h){
	*w = surface->w;
	*h = surface->h;
}


void CKImage::getPixels(void* dest){
	Int bytes = surface->w*surface->h*4;
	Int di = 0, si = 0;
	if((surface->pitch*surface->h)!=bytes){
		for(; di<bytes;){
			((Uint8*)dest)[di++] = ((Uint8*)surface->pixels)[si++];
			((Uint8*)dest)[di++] = ((Uint8*)surface->pixels)[si++];
			((Uint8*)dest)[di++] = ((Uint8*)surface->pixels)[si++];
			((Uint8*)dest)[di++] = 0xFF;
		}
	}
	else{
		for(; di<bytes;){
			((Uint8*)dest)[di++] = ((Uint8*)surface->pixels)[si++];
		}
	}
}

