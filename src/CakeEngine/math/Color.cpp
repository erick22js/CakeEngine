#include <CakeEngine/math/Color.hpp>



CKColor::CKColor(){
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

CKColor::CKColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

CKColor::CKColor(Float r, Float g, Float b, Float a){
	this->r = r*0xFF;
	this->g = g*0xFF;
	this->b = b*0xFF;
	this->a = a*0xFF;
}

CKColor::CKColor(Uint32 value){
	/* RGBA format */
	r = (value>>0)&0xFF;
	g = (value>>8)&0xFF;
	b = (value>>16)&0xFF;
	a = (value>>24)&0xFF;
}

CKColor::CKColor(CKColor *color){
	r = color->r;
	g = color->g;
	b = color->b;
	a = color->a;
}

Uint32 CKColor::toValue(){
	return (r<<0)|(g<<8)|(b<<16)|(a<<24);
}

Uint32 CKColor::toValue(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	return (r<<0)|(g<<8)|(b<<16)|(a<<24);
}

Uint32 CKColor::toValue(Float r, Float g, Float b, Float a){
	return (((Uint8)(r*0xFF))<<0)|(((Uint8)(g*0xFF))<<8)|(((Uint8)(b*0xFF))<<16)|(((Uint8)(a*0xFF))<<24);
}

Uint32 CKColor::toValue(CKColor *color){
	return color->toValue();
}


