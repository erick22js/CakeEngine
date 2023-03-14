#include <CakeEngine/graphics/renderer/Texture.hpp>


void CKTexture::loadData_(void* buffer, Int width, Int height){
	glBindTexture(GL_TEXTURE_2D, id);
	this->width = width;
	this->height = height;
	glTexImage2D(GL_TEXTURE_2D, 0, format.gli_formatinternal, width, height, 0, format.gli_format, type.glconst, buffer);
}

void CKTexture::loadData_(void* buffer){
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, format.gli_formatinternal, width, height, 0, format.gli_format, type.glconst, buffer);
}

void CKTexture::setFilter(){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void CKTexture::deleteTexture(){
	glDeleteTextures(1, &id);
}

CKTexture::CKTexture(){
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	setFilter();
}

CKTexture::CKTexture(void* buffer, Int width, Int height){
	glGenTextures(1, &id);
	loadData_(buffer, width, height);
	setFilter();
}

CKTexture::CKTexture(Int width, Int height){
	glGenTextures(1, &id);
	this->width = width;
	this->height = height;
	setFilter();
}

CKTexture::CKTexture(CKImage *image){
	Int wid, hei;
	
	glGenTextures(1, &id);
	image->getSize(&wid, &hei);
	
	void *pixels = (void*)new Uint8[wid*hei*4];
	image->getPixels(pixels);
	loadData_(pixels, wid, hei);
	
	delete pixels;
	setFilter();
}

CKTexture::~CKTexture(){
	deleteTexture();
}

void CKTexture::loadData(void* buffer, Int width, Int height){
	loadData_(buffer, width, height);
}

void CKTexture::useTexture(Int index){
	glActiveTexture(GL_TEXTURE0+index);
	glBindTexture(GL_TEXTURE_2D, id);
}
