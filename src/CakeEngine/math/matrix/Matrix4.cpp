#include <CakeEngine/math/matrix/Matrix4.hpp>
#include <CakeEngine/math/vector/Vector3.hpp>


CKMat4::CKMat4(){
	values[M00] = 0;
	values[M10] = 0;
	values[M20] = 0;
	values[M30] = 0;
	values[M01] = 0;
	values[M11] = 0;
	values[M21] = 0;
	values[M31] = 0;
	values[M02] = 0;
	values[M12] = 0;
	values[M22] = 0;
	values[M32] = 0;
	values[M03] = 0;
	values[M13] = 0;
	values[M23] = 0;
	values[M33] = 0;
}

CKMat4::CKMat4(CKMat4 *omat){
	set(omat);
}

CKMat4::CKMat4(Float vals[]){
	set(vals);
}


CKMat4 *CKMat4::identity(){
	values[M00] = 1;
	values[M10] = 0;
	values[M20] = 0;
	values[M30] = 0;
	values[M01] = 0;
	values[M11] = 1;
	values[M21] = 0;
	values[M31] = 0;
	values[M02] = 0;
	values[M12] = 0;
	values[M22] = 1;
	values[M32] = 0;
	values[M03] = 0;
	values[M13] = 0;
	values[M23] = 0;
	values[M33] = 1;
	
	return this;
}


CKMat4 *CKMat4::set(CKMat4 *omat){
	values[M00] = omat->values[M00];
	values[M10] = omat->values[M10];
	values[M20] = omat->values[M20];
	values[M30] = omat->values[M30];
	values[M01] = omat->values[M01];
	values[M11] = omat->values[M11];
	values[M21] = omat->values[M21];
	values[M31] = omat->values[M31];
	values[M02] = omat->values[M02];
	values[M12] = omat->values[M12];
	values[M22] = omat->values[M22];
	values[M32] = omat->values[M32];
	values[M03] = omat->values[M03];
	values[M13] = omat->values[M13];
	values[M23] = omat->values[M23];
	values[M33] = omat->values[M33];
	
	return this;
}

CKMat4 *CKMat4::set(Float vals[]){
	values[M00] = vals[0];
	values[M10] = vals[1];
	values[M20] = vals[2];
	values[M30] = vals[3];
	values[M01] = vals[4];
	values[M11] = vals[5];
	values[M21] = vals[6];
	values[M31] = vals[7];
	values[M02] = vals[8];
	values[M12] = vals[9];
	values[M22] = vals[10];
	values[M32] = vals[11];
	values[M03] = vals[12];
	values[M13] = vals[13];
	values[M23] = vals[14];
	values[M33] = vals[15];
}


CKMat4 *CKMat4::copyTo(CKMat4 *omat){
	omat->set(this);
	return this;
}


Float CKMat4::determinant(){
	return
		values[M30]*values[M21]*values[M12]*values[M03] - values[M20]*values[M31]*values[M12]*values[M03] -
		values[M30]*values[M11]*values[M22]*values[M03] + values[M10]*values[M31]*values[M22]*values[M03] +
		values[M20]*values[M11]*values[M32]*values[M03] - values[M10]*values[M21]*values[M32]*values[M03] -
		values[M30]*values[M21]*values[M02]*values[M13] + values[M20]*values[M31]*values[M02]*values[M13] +
		values[M30]*values[M01]*values[M22]*values[M13] - values[M00]*values[M31]*values[M22]*values[M13] - 
		values[M20]*values[M01]*values[M32]*values[M13] + values[M00]*values[M21]*values[M32]*values[M13] + 
		values[M30]*values[M11]*values[M02]*values[M23] - values[M10]*values[M31]*values[M02]*values[M23] - 
		values[M30]*values[M01]*values[M12]*values[M23] + values[M00]*values[M31]*values[M12]*values[M23] + 
		values[M10]*values[M01]*values[M32]*values[M23] - values[M00]*values[M11]*values[M32]*values[M23] - 
		values[M20]*values[M11]*values[M02]*values[M33] + values[M10]*values[M21]*values[M02]*values[M33] + 
		values[M20]*values[M01]*values[M12]*values[M33] - values[M00]*values[M21]*values[M12]*values[M33] - 
		values[M10]*values[M01]*values[M22]*values[M33] + values[M00]*values[M11]*values[M22]*values[M33];
}


CKMat4 *CKMat4::setToTranslation(Float x, Float y, Float z){
	identity();
	values[M03] = x;
	values[M13] = y;
	values[M23] = z;
	return this;
}

CKMat4 *CKMat4::setToTranslation(class CKVec3 *ovec){
	identity();
	values[M03] = ovec->x;
	values[M13] = ovec->y;
	values[M23] = ovec->z;
	return this;
}


CKMat4 *CKMat4::setToScale(Float x, Float y, Float z){
	identity();
	values[M00] = x;
	values[M11] = y;
	values[M22] = z;
	return this;
}

CKMat4 *CKMat4::setToScale(class CKVec3 *ovec){
	identity();
	values[M00] = ovec->x;
	values[M11] = ovec->y;
	values[M22] = ovec->z;
	return this;
}


CKMat4 *CKMat4::setToRotationX(Float rad){
	identity();
	
	Float cosf = cos(rad);
	Float sinf = sin(rad);
	Float* val = values;
	
	val[M11] = cosf;
	val[M21] = sinf;
	val[M12] = -sinf;
	val[M22] = cosf;
	
	return this;
}

CKMat4 *CKMat4::setToRotationY(Float rad){
	identity();
	
	Float cosf = cos(rad);
	Float sinf = sin(rad);
	Float* val = values;
	
	val[M00] = cosf;
	val[M20] = -sinf;
	val[M02] = sinf;
	val[M22] = cosf;
	
	return this;
}

CKMat4 *CKMat4::setToRotationZ(Float rad){
	identity();
	
	Float cosf = cos(rad);
	Float sinf = sin(rad);
	Float* val = values;
	
	val[M00] = cosf;
	val[M10] = sinf;
	val[M11] = -sinf;
	val[M11] = cosf;
	
	return this;
}


CKMat4 *CKMat4::setToRotation(Float ax, Float ay, Float az, Float rad){
	Float n = sqrt(ax*ax + ay*ay + az*az);
	
	Float x = ax;
	Float y = ay;
	Float z = az;
	
	Float xx = x * x;
	Float yy = y * y;
	Float zz = z * z;
	
	Float cosv = cos(rad);
	Float sinv = sin(rad);
	Float oc = 1 - cosv;
	
	values[M00] = xx + (1-xx)*cosv;
	values[M10] = x*y*oc + z*sinv;
	values[M20] = x*z*oc - y*sinv;
	values[M30] = 0;
	values[M01] = x*y* oc - z*sinv;
	values[M11] = yy + (1-yy)*cosv;
	values[M21] = y*z*oc + x*sinv;
	values[M31] = 0;
	values[M02] = x*z*oc + y*sinv;
	values[M12] = y*z*oc - x*sinv;
	values[M22] = zz + (1-zz)*cosv;
	values[M32] = 0;
	values[M03] = 0;
	values[M13] = 0;
	values[M23] = 0;
	values[M33] = 1;
	
	return this;
}

CKMat4 *CKMat4::setToRotation(class CKVec3 *axis, Float rad){
	Float n = sqrt(axis->x*axis->x + axis->y*axis->y + axis->z*axis->z);
	
	Float x = axis->x/n;
	Float y = axis->y/n;
	Float z = axis->z/n;
	
	Float xx = x * x;
	Float yy = y * y;
	Float zz = z * z;
	
	Float cosv = cos(rad);
	Float sinv = sin(rad);
	Float oc = 1 - cosv;
	
	values[M00] = xx + (1-xx)*cosv;
	values[M10] = x*y*oc + z*sinv;
	values[M20] = x*z*oc - y*sinv;
	values[M30] = 0;
	values[M01] = x*y* oc - z*sinv;
	values[M11] = yy + (1-yy)*cosv;
	values[M21] = y*z*oc + x*sinv;
	values[M31] = 0;
	values[M02] = x*z*oc + y*sinv;
	values[M12] = y*z*oc - x*sinv;
	values[M22] = zz + (1-zz)*cosv;
	values[M32] = 0;
	values[M03] = 0;
	values[M13] = 0;
	values[M23] = 0;
	values[M33] = 1;
	
	return this;
}


CKMat4 *CKMat4::setToProjection(Float near, Float far, Float fov, Float aspectRatio){
	Float l_fd = tan(CKMath::PI*0.5f - 0.5f*fov);
	Float range_inv = 1.0f/(near-far);
	
	values[M00] = l_fd/aspectRatio;
	values[M10] = 0;
	values[M20] = 0;
	values[M30] = 0;
	values[M01] = 0;
	values[M11] = l_fd;
	values[M21] = 0;
	values[M31] = 0;
	values[M02] = 0;
	values[M12] = 0;
	values[M22] = (near+far)*range_inv;
	values[M32] = -1.0f;
	values[M03] = 0;
	values[M13] = 0;
	values[M23] = near*far*range_inv*2;
	values[M33] = 0;
	/*
	Float l_fd = 1.0f/tan(fov/2.0f);
	Float l_a1 = (far+near)/(near-far);
	Float l_a2 = (2*far*near)/(near-far);
	
	values[M00] = l_fd/aspectRatio;
	values[M10] = 0;
	values[M20] = 0;
	values[M30] = 0;
	values[M01] = 0;
	values[M11] = l_fd;
	values[M21] = 0;
	values[M31] = 0;
	values[M02] = 0;
	values[M12] = 0;
	values[M22] = l_a1;
	values[M32] = -1;
	values[M03] = 0;
	values[M13] = 0;
	values[M23] = l_a2;
	values[M33] = 0;
	*/
	return this;
}

CKMat4 *CKMat4::setToProjection(Float left, Float right, Float top, Float bottom, Float far, Float near){
	Float x = 2.0f*near/(right-left);
	Float y = 2.0f*near/(top-bottom);
	Float a = (right+left)/(right-left);
	Float b = (top+bottom)/(top-bottom);
	Float l_a1 = (far+near)/(near-far);
	Float l_a2 = (2*far*near)/(near-far);
	
	values[M00] = x;
	values[M10] = 0;
	values[M20] = 0;
	values[M30] = 0;
	values[M01] = 0;
	values[M11] = y;
	values[M21] = 0;
	values[M31] = 0;
	values[M02] = a;
	values[M12] = b;
	values[M22] = l_a1;
	values[M32] = -1;
	values[M03] = 0;
	values[M13] = 0;
	values[M23] = l_a2;
	values[M33] = 0;
	
	return this;
}


CKMat4 *CKMat4::translate(Float x, Float y, Float z){
	Float m03 = values[M00]*x + values[M01]*y + values[M02]*z + values[M03];
	Float m13 = values[M10]*x + values[M11]*y + values[M12]*z + values[M13];
	Float m23 = values[M20]*x + values[M21]*y + values[M22]*z + values[M23];
	Float m33 = values[M30]*x + values[M31]*y + values[M32]*z + values[M33];
	values[M03] = m03;
	values[M13] = m13;
	values[M23] = m23;
	values[M33] = m33;
	
	return this;
}

CKMat4 *CKMat4::translate(class CKVec3 *ovec){
	Float m03 = values[M00]*ovec->x + values[M01]*ovec->y + values[M02]*ovec->z + values[M03];
	Float m13 = values[M10]*ovec->x + values[M11]*ovec->y + values[M12]*ovec->z + values[M13];
	Float m23 = values[M20]*ovec->x + values[M21]*ovec->y + values[M22]*ovec->z + values[M23];
	Float m33 = values[M30]*ovec->x + values[M31]*ovec->y + values[M32]*ovec->z + values[M33];
	values[M03] = m03;
	values[M13] = m13;
	values[M23] = m23;
	values[M33] = m33;
	
	return this;
}


CKMat4 *CKMat4::scale(Float x, Float y, Float z){
	values[M00] *= x;
	values[M10] *= x;
	values[M20] *= x;
	values[M30] *= x;
	values[M01] *= y;
	values[M11] *= y;
	values[M21] *= y;
	values[M31] *= y;
	values[M02] *= z;
	values[M12] *= z;
	values[M22] *= z;
	values[M32] *= z;
	
	return this;
}

CKMat4 *CKMat4::scale(class CKVec3 *ovec){
	values[M00] *= ovec->x;
	values[M10] *= ovec->x;
	values[M20] *= ovec->x;
	values[M30] *= ovec->x;
	values[M01] *= ovec->y;
	values[M11] *= ovec->y;
	values[M21] *= ovec->y;
	values[M31] *= ovec->y;
	values[M02] *= ovec->z;
	values[M12] *= ovec->z;
	values[M22] *= ovec->z;
	values[M32] *= ovec->z;
	
	return this;
}

CKMat4 *CKMat4::scale(Float sc){
	values[M00] *= sc;
	values[M10] *= sc;
	values[M20] *= sc;
	values[M30] *= sc;
	values[M01] *= sc;
	values[M11] *= sc;
	values[M21] *= sc;
	values[M31] *= sc;
	values[M02] *= sc;
	values[M12] *= sc;
	values[M22] *= sc;
	values[M32] *= sc;
	
	return this;
}


CKMat4 *CKMat4::rotateX(Float rad){
	Float cosf = cos(rad);
	Float sinf = sin(rad);
	Float* val = values;
	
	Float m01 = cosf*val[M01] + sinf*val[M02];
	Float m11 = cosf*val[M11] + sinf*val[M12];
	Float m21 = cosf*val[M21] + sinf*val[M22];
	Float m31 = cosf*val[M31] + sinf*val[M32];
	Float m02 = cosf*val[M02] - sinf*val[M01];
	Float m12 = cosf*val[M12] - sinf*val[M11];
	Float m22 = cosf*val[M22] - sinf*val[M21];
	Float m32 = cosf*val[M32] - sinf*val[M31];
	
	val[M01] = m01;
	val[M11] = m11;
	val[M21] = m21;
	val[M31] = m31;
	val[M02] = m02;
	val[M12] = m12;
	val[M22] = m22;
	val[M32] = m32;
	
	return this;
}

CKMat4 *CKMat4::rotateY(Float rad){
	Float cosf = cos(rad);
	Float sinf = sin(rad);
	Float* val = values;
	
	Float m00 = cosf*val[M00] - sinf*val[M02];
	Float m10 = cosf*val[M10] - sinf*val[M12];
	Float m20 = cosf*val[M20] - sinf*val[M22];
	Float m30 = cosf*val[M30] - sinf*val[M32];
	Float m02 = cosf*val[M02] + sinf*val[M00];
	Float m12 = cosf*val[M12] + sinf*val[M10];
	Float m22 = cosf*val[M22] + sinf*val[M20];
	Float m32 = cosf*val[M32] + sinf*val[M30];
	
	val[M00] = m00;
	val[M10] = m10;
	val[M20] = m20;
	val[M30] = m30;
	val[M02] = m02;
	val[M12] = m12;
	val[M22] = m22;
	val[M32] = m32;
	
	return this;
}

CKMat4 *CKMat4::rotateZ(Float rad){
	Float cosf = cos(rad);
	Float sinf = sin(rad);
	Float* val = values;
	
	Float m00 = cosf*val[M00] + sinf*val[M01];
	Float m10 = cosf*val[M10] + sinf*val[M11];
	Float m20 = cosf*val[M20] + sinf*val[M21];
	Float m30 = cosf*val[M30] + sinf*val[M31];
	Float m01 = cosf*val[M01] - sinf*val[M00];
	Float m11 = cosf*val[M11] - sinf*val[M10];
	Float m21 = cosf*val[M21] - sinf*val[M20];
	Float m31 = cosf*val[M31] - sinf*val[M30];
	
	val[M00] = m00;
	val[M10] = m10;
	val[M20] = m20;
	val[M30] = m30;
	val[M01] = m01;
	val[M11] = m11;
	val[M21] = m21;
	val[M31] = m31;
	
	return this;
}


CKMat4 *CKMat4::mul(CKMat4 *omat){
	Float m00 = values[M00]*omat->values[M00] + values[M01]*omat->values[M10] + values[M02]*omat->values[M20] + values[M03]*omat->values[M30];
	Float m01 = values[M00]*omat->values[M01] + values[M01]*omat->values[M11] + values[M02]*omat->values[M21] + values[M03]*omat->values[M31];
	Float m02 = values[M00]*omat->values[M02] + values[M01]*omat->values[M12] + values[M02]*omat->values[M22] + values[M03]*omat->values[M32];
	Float m03 = values[M00]*omat->values[M03] + values[M01]*omat->values[M13] + values[M02]*omat->values[M23] + values[M03]*omat->values[M33];
	Float m10 = values[M10]*omat->values[M00] + values[M11]*omat->values[M10] + values[M12]*omat->values[M20] + values[M13]*omat->values[M30];
	Float m11 = values[M10]*omat->values[M01] + values[M11]*omat->values[M11] + values[M12]*omat->values[M21] + values[M13]*omat->values[M31];
	Float m12 = values[M10]*omat->values[M02] + values[M11]*omat->values[M12] + values[M12]*omat->values[M22] + values[M13]*omat->values[M32];
	Float m13 = values[M10]*omat->values[M03] + values[M11]*omat->values[M13] + values[M12]*omat->values[M23] + values[M13]*omat->values[M33];
	Float m20 = values[M20]*omat->values[M00] + values[M21]*omat->values[M10] + values[M22]*omat->values[M20] + values[M23]*omat->values[M30];
	Float m21 = values[M20]*omat->values[M01] + values[M21]*omat->values[M11] + values[M22]*omat->values[M21] + values[M23]*omat->values[M31];
	Float m22 = values[M20]*omat->values[M02] + values[M21]*omat->values[M12] + values[M22]*omat->values[M22] + values[M23]*omat->values[M32];
	Float m23 = values[M20]*omat->values[M03] + values[M21]*omat->values[M13] + values[M22]*omat->values[M23] + values[M23]*omat->values[M33];
	Float m30 = values[M30]*omat->values[M00] + values[M31]*omat->values[M10] + values[M32]*omat->values[M20] + values[M33]*omat->values[M30];
	Float m31 = values[M30]*omat->values[M01] + values[M31]*omat->values[M11] + values[M32]*omat->values[M21] + values[M33]*omat->values[M31];
	Float m32 = values[M30]*omat->values[M02] + values[M31]*omat->values[M12] + values[M32]*omat->values[M22] + values[M33]*omat->values[M32];
	Float m33 = values[M30]*omat->values[M03] + values[M31]*omat->values[M13] + values[M32]*omat->values[M23] + values[M33]*omat->values[M33];
	
	values[M00] = m00;
	values[M10] = m10;
	values[M20] = m20;
	values[M30] = m30;
	values[M01] = m01;
	values[M11] = m11;
	values[M21] = m21;
	values[M31] = m31;
	values[M02] = m02;
	values[M12] = m12;
	values[M22] = m22;
	values[M32] = m32;
	values[M03] = m03;
	values[M13] = m13;
	values[M23] = m23;
	values[M33] = m33;
	
	return this;
}


CKMat4 *CKMat4::transpose(){
	Float m01 = values[M01];
	Float m02 = values[M02];
	Float m03 = values[M03];
	Float m12 = values[M12];
	Float m13 = values[M13];
	Float m23 = values[M23];
	
	values[M01] = values[M10];
	values[M02] = values[M20];
	values[M03] = values[M30];
	values[M10] = m01;
	values[M12] = values[M21];
	values[M13] = values[M31];
	values[M20] = m02;
	values[M21] = m12;
	values[M23] = values[M32];
	values[M30] = m03;
	values[M31] = m13;
	values[M32] = m23;
	
	return this;
}


CKMat4 *CKMat4::invert(){
	float l_det = determinant();
	
	if(l_det==0.0f){
		return this;
	}
	
	Float m00 = values[M12] * values[M23] * values[M31] - values[M13] * values[M22] * values[M31] + values[M13] * values[M21] * values[M32] -
		values[M11] * values[M23] * values[M32] - values[M12] * values[M21] * values[M33] + values[M11] * values[M22] * values[M33];
	Float m01 = values[M03] * values[M22] * values[M31] - values[M02] * values[M23] * values[M31] - values[M03] * values[M21] * values[M32] +
		values[M01] * values[M23] * values[M32] + values[M02] * values[M21] * values[M33] - values[M01] * values[M22] * values[M33];
	Float m02 = values[M02] * values[M13] * values[M31] - values[M03] * values[M12] * values[M31] + values[M03] * values[M11] * values[M32] -
		values[M01] * values[M13] * values[M32] - values[M02] * values[M11] * values[M33] + values[M01] * values[M12] * values[M33];
	Float m03 = values[M03] * values[M12] * values[M21] - values[M02] * values[M13] * values[M21] - values[M03] * values[M11] * values[M22] +
		values[M01] * values[M13] * values[M22] + values[M02] * values[M11] * values[M23] - values[M01] * values[M12] * values[M23];
	Float m10 = values[M13] * values[M22] * values[M30] - values[M12] * values[M23] * values[M30] - values[M13] * values[M20] * values[M32] +
		values[M10] * values[M23] * values[M32] + values[M12] * values[M20] * values[M33] - values[M10] * values[M22] * values[M33];
	Float m11 = values[M02] * values[M23] * values[M30] - values[M03] * values[M22] * values[M30] + values[M03] * values[M20] * values[M32] -
		values[M00] * values[M23] * values[M32] - values[M02] * values[M20] * values[M33] + values[M00] * values[M22] * values[M33];
	Float m12 = values[M03] * values[M12] * values[M30] - values[M02] * values[M13] * values[M30] - values[M03] * values[M10] * values[M32] +
		values[M00] * values[M13] * values[M32] + values[M02] * values[M10] * values[M33] - values[M00] * values[M12] * values[M33];
	Float m13 = values[M02] * values[M13] * values[M20] - values[M03] * values[M12] * values[M20] + values[M03] * values[M10] * values[M22] -
		values[M00] * values[M13] * values[M22] - values[M02] * values[M10] * values[M23] + values[M00] * values[M12] * values[M23];
	Float m20 = values[M11] * values[M23] * values[M30] - values[M13] * values[M21] * values[M30] + values[M13] * values[M20] * values[M31] -
		values[M10] * values[M23] * values[M31] - values[M11] * values[M20] * values[M33] + values[M10] * values[M21] * values[M33];
	Float m21 = values[M03] * values[M21] * values[M30] - values[M01] * values[M23] * values[M30] - values[M03] * values[M20] * values[M31] +
		values[M00] * values[M23] * values[M31] + values[M01] * values[M20] * values[M33] - values[M00] * values[M21] * values[M33];
	Float m22 = values[M01] * values[M13] * values[M30] - values[M03] * values[M11] * values[M30] + values[M03] * values[M10] * values[M31] -
		values[M00] * values[M13] * values[M31] - values[M01] * values[M10] * values[M33] + values[M00] * values[M11] * values[M33];
	Float m23 = values[M03] * values[M11] * values[M20] - values[M01] * values[M13] * values[M20] - values[M03] * values[M10] * values[M21] +
		values[M00] * values[M13] * values[M21] + values[M01] * values[M10] * values[M23] - values[M00] * values[M11] * values[M23];
	Float m30 = values[M12] * values[M21] * values[M30] - values[M11] * values[M22] * values[M30] - values[M12] * values[M20] * values[M31] +
		values[M10] * values[M22] * values[M31] + values[M11] * values[M20] * values[M32] - values[M10] * values[M21] * values[M32];
	Float m31 = values[M01] * values[M22] * values[M30] - values[M02] * values[M21] * values[M30] + values[M02] * values[M20] * values[M31] -
		values[M00] * values[M22] * values[M31] - values[M01] * values[M20] * values[M32] + values[M00] * values[M21] * values[M32];
	Float m32 = values[M02] * values[M11] * values[M30] - values[M01] * values[M12] * values[M30] - values[M02] * values[M10] * values[M31] +
		values[M00] * values[M12] * values[M31] + values[M01] * values[M10] * values[M32] - values[M00] * values[M11] * values[M32];
	Float m33 = values[M01] * values[M12] * values[M20] - values[M02] * values[M11] * values[M20] + values[M02] * values[M10] * values[M21] -
		values[M00] * values[M12] * values[M21] - values[M01] * values[M10] * values[M22] + values[M00] * values[M11] * values[M22];
	
	Float inv_det = 1.0f / l_det;
	
	values[M00] = m00 * inv_det;
	values[M10] = m10 * inv_det;
	values[M20] = m20 * inv_det;
	values[M30] = m30 * inv_det;
	values[M01] = m01 * inv_det;
	values[M11] = m11 * inv_det;
	values[M21] = m21 * inv_det;
	values[M31] = m31 * inv_det;
	values[M02] = m02 * inv_det;
	values[M12] = m12 * inv_det;
	values[M22] = m22 * inv_det;
	values[M32] = m32 * inv_det;
	values[M03] = m03 * inv_det;
	values[M13] = m13 * inv_det;
	values[M23] = m23 * inv_det;
	values[M33] = m33 * inv_det;
	
	return this;
}


void CKMat4::decompose(class CKVec3 *ovec_position, class CKVec3 *ovec_scale, class CKVec3 *ovec_rotation){
	ovec_position->x = values[M03];
	ovec_position->y = values[M13];
	ovec_position->z = values[M23];

	Float m11 = values[M11];
	Float m21 = values[M21];
	Float m31 = values[M31];
	Float m12 = values[M12];
	Float m22 = values[M22];
	Float m32 = values[M32];
	Float m13 = values[M13];
	Float m23 = values[M23];
	Float m33 = values[M33];

	ovec_scale->x = sqrt(m11*m11 + m21*m21 + m31*m31);
	ovec_scale->y = sqrt(m12*m12 + m22*m22 + m32*m32);
	ovec_scale->z = sqrt(m13*m13 + m23*m23 + m33*m33);

	Float is1 = 1.0f/ovec_scale->x;
	Float is2 = 1.0f/ovec_scale->y;
	Float is3 = 1.0f/ovec_scale->z;

	Float sm11 = m11*is1;
	Float sm21 = m21*is2;
	Float sm31 = m31*is3;
	Float sm12 = m12*is1;
	Float sm22 = m22*is2;
	Float sm32 = m32*is3;
	Float sm13 = m13*is1;
	Float sm23 = m23*is2;
	Float sm33 = m33*is3;

	Float trace = sm11+sm22+sm33;
	Float S = 0;
	
	Float out_r[4];
	if(trace>0){
		S = sqrt(trace+1.0)*2;
		out_r[3] = 0.25 * S;
		out_r[0] = (sm32-sm23)/S;
		out_r[1] = (sm13-sm31)/S;
		out_r[2] = (sm21-sm12)/S;
	}
	else if(sm11>sm22 && sm11>sm33){
		S = sqrt(1.0+sm11-sm22-sm33)*2;
		out_r[3] = (sm32-sm23)/S;
		out_r[0] = 0.25*S;
		out_r[1] = (sm21+sm12)/S;
		out_r[2] = (sm13+sm31)/S;
	}
	else if(sm22>sm33){
		S = sqrt(1.0+sm22-sm11-sm33)*2;
		out_r[3] = (sm13-sm31)/S;
		out_r[0] = (sm21+sm12)/S;
		out_r[1] = 0.25*S;
		out_r[2] = (sm32+sm23)/S;
	}
	else{
		S = sqrt(1.0+sm33-sm11-sm22)*2;
		out_r[3] = (sm21-sm12)/S;
		out_r[0] = (sm13+sm31)/S;
		out_r[1] = (sm32+sm23)/S;
		out_r[2] = 0.25*S;
	}
	
	Float w_1sqrt = sqrt(1.0f-out_r[3]*out_r[3]);
	
	ovec_rotation->x = out_r[0]/w_1sqrt;
	ovec_rotation->y = out_r[1]/w_1sqrt;
	ovec_rotation->z = out_r[2]/w_1sqrt;
	/*
	ovec_position->x = values[M03];
	ovec_position->y = values[M13];
	ovec_position->z = values[M23];

	Float m11 = values[0];
	Float m12 = values[1];
	Float m13 = values[2];
	Float m21 = values[4];
	Float m22 = values[5];
	Float m23 = values[6];
	Float m31 = values[8];
	Float m32 = values[9];
	Float m33 = values[10];

	ovec_scale->x = sqrt(m11 * m11 + m12 * m12 + m13 * m13);
	ovec_scale->y = sqrt(m21 * m21 + m22 * m22 + m23 * m23);
	ovec_scale->z = sqrt(m31 * m31 + m32 * m32 + m33 * m33);

	Float is1 = 1.0f / ovec_scale->x;
	Float is2 = 1.0f / ovec_scale->y;
	Float is3 = 1.0f / ovec_scale->z;

	Float sm11 = m11 * is1;
	Float sm12 = m12 * is2;
	Float sm13 = m13 * is3;
	Float sm21 = m21 * is1;
	Float sm22 = m22 * is2;
	Float sm23 = m23 * is3;
	Float sm31 = m31 * is1;
	Float sm32 = m32 * is2;
	Float sm33 = m33 * is3;

	Float trace = sm11 + sm22 + sm33;
	Float S = 0;
	
	Float out_r[4];
	if(trace > 0){
		S = sqrt(trace + 1.0) * 2;
		out_r[3] = 0.25 * S;
		out_r[0] = (sm23 - sm32) / S;
		out_r[1] = (sm31 - sm13) / S;
		out_r[2] = (sm12 - sm21) / S;
	}
	else if(sm11 > sm22 && sm11 > sm33){
		S = sqrt(1.0 + sm11 - sm22 - sm33) * 2;
		out_r[3] = (sm23 - sm32) / S;
		out_r[0] = 0.25 * S;
		out_r[1] = (sm12 + sm21) / S;
		out_r[2] = (sm31 + sm13) / S;
	}
	else if(sm22 > sm33){
		S = sqrt(1.0 + sm22 - sm11 - sm33) * 2;
		out_r[3] = (sm31 - sm13) / S;
		out_r[0] = (sm12 + sm21) / S;
		out_r[1] = 0.25 * S;
		out_r[2] = (sm23 + sm32) / S;
	}
	else{
		S = sqrt(1.0 + sm33 - sm11 - sm22) * 2;
		out_r[3] = (sm12 - sm21) / S;
		out_r[0] = (sm31 + sm13) / S;
		out_r[1] = (sm23 + sm32) / S;
		out_r[2] = 0.25 * S;
	}
	
	Float w_1sqrt = sqrt(1.0f-out_r[3]*out_r[3]);
	
	ovec_rotation->x = out_r[0]/w_1sqrt;
	ovec_rotation->y = out_r[1]/w_1sqrt;
	ovec_rotation->z = out_r[2]/w_1sqrt;
	*/
}


