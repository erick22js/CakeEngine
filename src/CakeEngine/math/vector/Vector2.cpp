#include <CakeEngine/math/vector/Vector2.hpp>
#include <CakeEngine/math/matrix/Matrix3.hpp>


CKVec2::CKVec2(){
	x = 0;
	y = 0;
}

CKVec2::CKVec2(Float x, Float y){
	this->x = x;
	this->y = y;
}

CKVec2::CKVec2(CKVec2 *ovec){
	x = ovec->x;
	y = ovec->y;
}


CKVec2 *CKVec2::set(Float x, Float y){
	this->x = x;
	this->y = y;
	
	return this;
}

CKVec2 *CKVec2::set(CKVec2 *ovec){
	x = ovec->x;
	y = ovec->y;
	
	return this;
}


CKVec2 CKVec2::clone(){
	return CKVec2(x, y);
}


Float CKVec2::distance(CKVec2 *ovec){
	Float xd = ovec->x-this->x;
	Float yd = ovec->y-this->y;
	return sqrt(xd*xd+yd*yd);
}

Float CKVec2::distance(){
	return sqrt(x*x+y*y);
}


Float CKVec2::distance2(CKVec2 *ovec){
	Float xd = ovec->x-this->x;
	Float yd = ovec->y-this->y;
	return xd*xd+yd*yd;
}

Float CKVec2::distance2(){
	return x*x+y*y;
}


Float CKVec2::angle(CKVec2 *ovec){
	Float xd = ovec->x-this->x;
	Float yd = ovec->y-this->y;
	return atan2(yd*yd, xd*xd);
}

Float CKVec2::angle(){
	return atan2(y, x);
}


Bool CKVec2::equal(Float x, Float y){
	return (this->x==x)&&(this->y==y);
}

Bool CKVec2::equal(CKVec2 *ovec){
	return (x==ovec->x)&&(y==ovec->y);
}


CKVec2 *CKVec2::add(Float x, Float y){
	this->x += x;
	this->y += y;
	
	return this;
}

CKVec2 *CKVec2::add(CKVec2 *ovec){
	x += ovec->x;
	y += ovec->y;
	
	return this;
}


CKVec2 *CKVec2::sub(Float x, Float y){
	this->x -= x;
	this->y -= y;
	
	return this;
}

CKVec2 *CKVec2::sub(CKVec2 *ovec){
	x -= ovec->x;
	y -= ovec->y;
	
	return this;
}


CKVec2 *CKVec2::mul(Float x, Float y){
	this->x *= x;
	this->y *= y;
	
	return this;
}

CKVec2 *CKVec2::mul(CKVec2 *ovec){
	x *= ovec->x;
	y *= ovec->y;
	
	return this;
}


CKVec2 *CKVec2::mulAdd(Float x, Float y, Float sc){
	this->x += x*sc;
	this->y += y*sc;
	
	return this;
}

CKVec2 *CKVec2::mulAdd(CKVec2 *ovec, Float sc){
	x += ovec->x*sc;
	y += ovec->y*sc;
	
	return this;
}


CKVec2 *CKVec2::scale(Float sc){
	x *= sc;
	y *= sc;
	
	return this;
}


CKVec2 *CKVec2::transformPoint(CKMat3 *omat){
	Float div = x*omat->values[omat->M20] + y*omat->values[omat->M21] + omat->values[omat->M22];
	
	Float nx = (x*omat->values[omat->M00] + y*omat->values[omat->M10] + omat->values[omat->M20])/div;
	Float ny = (x*omat->values[omat->M01] + y*omat->values[omat->M11] + omat->values[omat->M21])/div;
	x = nx;
	y = ny;
	
	return this;
}

CKVec2 *CKVec2::transformDirection(CKMat3 *omat){
	Float nx = x*omat->values[omat->M00] + y*omat->values[omat->M10] + omat->values[omat->M20];
	Float ny = x*omat->values[omat->M01] + y*omat->values[omat->M11] + omat->values[omat->M21];
	x = nx;
	y = ny;
	
	return this;
}

CKVec2 *CKVec2::transformNormal(CKMat3 *omat){
	CKMat3 imat = CKMat3(omat);
	imat.invert();
	
	Float nx = x*imat.values[imat.M00] + y*imat.values[imat.M10] + imat.values[imat.M20];
	Float ny = x*imat.values[imat.M01] + y*imat.values[imat.M11] + imat.values[imat.M21];
	x = nx;
	y = ny;
	
	return this;
}


CKVec2 *CKVec2::lerp(Float x, Float y, Float alpha){
	Float inv_alpha = 1-alpha;
	this->x = (this->x*inv_alpha)+(x*inv_alpha);
	this->y = (this->y*inv_alpha)+(y*inv_alpha);
	
	return this;
}

CKVec2 *CKVec2::lerp(CKVec2 *ovec, Float alpha){
	Float inv_alpha = 1-alpha;
	x = (x*inv_alpha)+(ovec->x*inv_alpha);
	y = (y*inv_alpha)+(ovec->y*inv_alpha);
	
	return this;
}


Float CKVec2::dot(Float x, Float y){
	return this->x*x+this->y*y;
}

Float CKVec2::dot(CKVec2 *ovec){
	return x*ovec->x+y*ovec->y;
}

