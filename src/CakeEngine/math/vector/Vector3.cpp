#include <CakeEngine/math/vector/Vector3.hpp>
#include <CakeEngine/math/vector/Vector2.hpp>
#include <CakeEngine/math/matrix/Matrix4.hpp>


CKVec3::CKVec3(){
	x = 0;
	y = 0;
	z = 0;
}

CKVec3::CKVec3(Float x, Float y, Float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

CKVec3::CKVec3(CKVec2 *ovec){
	x = ovec->x;
	y = ovec->y;
	z = 0;
}

CKVec3::CKVec3(CKVec3 *ovec){
	x = ovec->x;
	y = ovec->y;
	z = ovec->z;
}


CKVec3 *CKVec3::set(Float x, Float y, Float z){
	this->x = x;
	this->y = y;
	this->z = z;
	
	return this;
}

CKVec3 *CKVec3::set(CKVec3 *ovec){
	x = ovec->x;
	y = ovec->y;
	z = ovec->z;
	
	return this;
}


CKVec3 CKVec3::clone(){
	return CKVec3(x, y, z);
}


Float CKVec3::distance(CKVec3 *ovec){
	Float dx = ovec->x-x;
	Float dy = ovec->y-y;
	Float dz = ovec->z-z;
	return sqrt(dx*dx+dy*dy+dz*dz);
}

Float CKVec3::distance(){
	return sqrt(x*x+y*y+z*z);
}


Float CKVec3::distance2(CKVec3 *ovec){
	Float dx = ovec->x-x;
	Float dy = ovec->y-y;
	Float dz = ovec->z-z;
	return dx*dx+dy*dy+dz*dz;
}

Float CKVec3::distance2(){
	return x*x+y*y+z*z;
}


Bool CKVec3::equal(Float x, Float y, Float z){
	return (this->x==x)&&(this->y==y)&&(this->z==z);
}

Bool CKVec3::equal(CKVec3 *ovec){
	return (x==ovec->x)&&(y==ovec->y)&&(z==ovec->z);
}


CKVec3 *CKVec3::add(Float x, Float y, Float z){
	this->x += x;
	this->y += y;
	this->z += z;
	
	return this;
}

CKVec3 *CKVec3::add(CKVec3 *ovec){
	x += ovec->x;
	y += ovec->y;
	z += ovec->z;
	
	return this;
}


CKVec3 *CKVec3::sub(Float x, Float y, Float z){
	this->x -= x;
	this->y -= y;
	this->z -= z;
	
	return this;
}

CKVec3 *CKVec3::sub(CKVec3 *ovec){
	x -= ovec->x;
	y -= ovec->y;
	z -= ovec->z;
	
	return this;
}


CKVec3 *CKVec3::mul(Float x, Float y, Float z){
	this->x *= x;
	this->y *= y;
	this->z *= z;
	
	return this;
}

CKVec3 *CKVec3::mul(CKVec3 *ovec){
	this->x *= x;
	this->y *= y;
	this->z *= z;
	
	return this;
}


CKVec3 *CKVec3::mulAdd(Float x, Float y, Float z, Float sc){
	this->x += x*sc;
	this->y += y*sc;
	this->z += z*sc;
	
	return this;
}

CKVec3 *CKVec3::mulAdd(CKVec3 *ovec, Float sc){
	x += ovec->x*sc;
	y += ovec->y*sc;
	z += ovec->z*sc;
	
	return this;
}


CKVec3 *CKVec3::scale(Float sc){
	x *= sc;
	y *= sc;
	z *= sc;
	
	return this;
}


CKVec3 *CKVec3::transformPoint(CKMat4 *omat){
	Float div = x*omat->values[omat->M30] + y*omat->values[omat->M31] + z*omat->values[omat->M32] + omat->values[omat->M33];
	
	Float nx = (x*omat->values[omat->M00] + y*omat->values[omat->M10] + z*omat->values[omat->M20] + omat->values[omat->M30])/div;
	Float ny = (x*omat->values[omat->M01] + y*omat->values[omat->M11] + z*omat->values[omat->M21] + omat->values[omat->M31])/div;
	Float nz = (x*omat->values[omat->M02] + y*omat->values[omat->M12] + z*omat->values[omat->M22] + omat->values[omat->M32])/div;
	x = nx;
	y = ny;
	z = nz;
	
	return this;
}

CKVec3 *CKVec3::transformDirection(CKMat4 *omat){
	Float nx = x*omat->values[omat->M00] + y*omat->values[omat->M10] + z*omat->values[omat->M20] + omat->values[omat->M30];
	Float ny = x*omat->values[omat->M01] + y*omat->values[omat->M11] + z*omat->values[omat->M21] + omat->values[omat->M31];
	Float nz = x*omat->values[omat->M02] + y*omat->values[omat->M12] + z*omat->values[omat->M22] + omat->values[omat->M32];
	x = nx;
	y = ny;
	z = nz;
	
	return this;
}

CKVec3 *CKVec3::transformNormal(CKMat4 *omat){
	CKMat4 imat = CKMat4(omat);
	imat.invert();
	
	Float nx = x*imat.values[imat.M00] + y*imat.values[imat.M10] + z*imat.values[imat.M20] + imat.values[imat.M30];
	Float ny = x*imat.values[imat.M01] + y*imat.values[imat.M11] + z*imat.values[imat.M21] + imat.values[imat.M31];
	Float nz = x*imat.values[imat.M02] + y*imat.values[imat.M12] + z*imat.values[imat.M22] + imat.values[imat.M32];
	x = nx;
	y = ny;
	z = nz;
	
	return this;
}


CKVec3 *CKVec3::lerp(Float x, Float y, Float z, Float alpha){
	this->x += (x-this->x)*alpha;
	this->y += (y-this->y)*alpha;
	this->z += (z-this->z)*alpha;
	
	return this;
}

CKVec3 *CKVec3::lerp(CKVec3 *ovec, Float alpha){
	x += (ovec->x-x)*alpha;
	y += (ovec->y-y)*alpha;
	z += (ovec->z-z)*alpha;
	
	return this;
}


Float CKVec3::dot(Float x, Float y, Float z){
	return this->x*x+this->y*y+this->z*z;
}

Float CKVec3::dot(CKVec3 *ovec){
	return x*ovec->x+y*ovec->y+z*ovec->z;
}


