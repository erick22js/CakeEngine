#include <CakeEngine/math/matrix/Matrix3.hpp>
#include <CakeEngine/math/vector/Vector2.hpp>
#include <CakeEngine/math/vector/Vector3.hpp>


CKMat3::CKMat3(){
	values[M00] = 0;
	values[M10] = 0;
	values[M20] = 0;
	values[M01] = 0;
	values[M11] = 0;
	values[M21] = 0;
	values[M02] = 0;
	values[M12] = 0;
	values[M22] = 0;
}

CKMat3::CKMat3(CKMat3 *omat){
	set(omat);
}

CKMat3::CKMat3(Float vals[]){
	set(vals);
}


CKMat3 *CKMat3::identity(){
	values[M00] = 1;
	values[M10] = 0;
	values[M20] = 0;
	values[M01] = 0;
	values[M11] = 1;
	values[M21] = 0;
	values[M02] = 0;
	values[M12] = 0;
	values[M22] = 1;
	
	return this;
}


CKMat3 *CKMat3::affine(){
	values[M20] = 0;
	values[M21] = 0;
	values[M22] = 1;
	
	return this;
}


CKMat3 *CKMat3::set(CKMat3 *omat){
	values[M00] = omat->values[M00];
	values[M10] = omat->values[M10];
	values[M20] = omat->values[M20];
	values[M01] = omat->values[M01];
	values[M11] = omat->values[M11];
	values[M12] = omat->values[M12];
	values[M02] = omat->values[M02];
	values[M12] = omat->values[M12];
	values[M22] = omat->values[M22];
	
	return this;
}

CKMat3 *CKMat3::set(Float vals[]){
	values[M00] = vals[0];
	values[M10] = vals[1];
	values[M20] = vals[2];
	values[M01] = vals[3];
	values[M11] = vals[4];
	values[M21] = vals[5];
	values[M02] = vals[6];
	values[M12] = vals[7];
	values[M22] = vals[8];
	
	return this;
}


CKMat3 *CKMat3::copyTo(CKMat3 *omat){
	omat->set(this);
	return omat;
}


Float CKMat3::determinant(){
	return
		values[M00]*values[M11]*values[M22] + values[M01]*values[M12]*values[M20] + values[M02]*values[M10]*values[M21] -
		values[M00]*values[M12]*values[M21] - values[M01]*values[M10]*values[M22] - values[M02]*values[M11]*values[M20];
}


CKMat3 *CKMat3::setToTranslation(Float x, Float y){
	Float* val = values;
	
	val[M00] = 1;
	val[M10] = 0;
	val[M20] = 0;
	val[M01] = 0;
	val[M11] = 1;
	val[M21] = 0;
	val[M02] = x;
	val[M12] = y;
	val[M22] = 1;

	return this;
}

CKMat3 *CKMat3::setToTranslation(class CKVec2 *ovec){
	Float* val = values;
	
	val[M00] = 1;
	val[M10] = 0;
	val[M20] = 0;
	val[M01] = 0;
	val[M11] = 1;
	val[M21] = 0;
	val[M02] = ovec->x;
	val[M12] = ovec->y;
	val[M22] = 1;

	return this;
}


CKMat3 *CKMat3::setToScale(Float x, Float y){
	Float* val = values;
	
	val[M00] = x;
	val[M10] = 0;
	val[M20] = 0;
	val[M01] = 0;
	val[M11] = y;
	val[M21] = 0;
	val[M02] = 0;
	val[M12] = 0;
	val[M22] = 1;
	
	return this;
}

CKMat3 *CKMat3::setToScale(class CKVec2 *ovec){
	Float* val = values;
	
	val[M00] = ovec->x;
	val[M10] = 0;
	val[M20] = 0;
	val[M01] = 0;
	val[M11] = ovec->y;
	val[M21] = 0;
	val[M02] = 0;
	val[M12] = 0;
	val[M22] = 1;
	
	return this;
}


CKMat3 *CKMat3::setToRotation(Float rad){
	Float cosf = cos(rad);
	Float sinf = sin(rad);
	Float* val = values;

	val[M00] = cosf;
	val[M10] = sinf;
	val[M20] = 0;

	val[M01] = -sinf;
	val[M11] = cosf;
	val[M21] = 0;

	val[M02] = 0;
	val[M12] = 0;
	val[M22] = 1;

	return this;
}

CKMat3 *CKMat3::setToRotation(class CKVec3 *axis, Float rad){
	Float* val = values;
	
	Float cosv = cos(rad);
	Float sinv = sin(rad);
	Float oc = 1.0f - cosv;
	
	val[M00] = oc*axis->x*axis->x + cosv;
	val[M01] = oc*axis->x*axis->y - axis->z*sinv;
	val[M02] = oc*axis->z*axis->x + axis->y*sinv;
	val[M10] = oc*axis->x*axis->y + axis->z*sinv;
	val[M11] = oc*axis->y*axis->y + cosv;
	val[M12] = oc*axis->y*axis->z - axis->x*sinv;
	val[M20] = oc*axis->z*axis->x - axis->y*sinv;
	val[M21] = oc*axis->y*axis->z + axis->x*sinv;
	val[M22] = oc*axis->z*axis->z + cosv;
	
	return this;
}


CKMat3 *CKMat3::translate(Float x, Float y){
	CKMat3 tmp = CKMat3();
	
	tmp.values[M00] = 1;
	tmp.values[M10] = 0;
	tmp.values[M01] = 0;
	tmp.values[M11] = 1;
	tmp.values[M02] = x;
	tmp.values[M12] = y;
	
	mul(&tmp);
	
	return this;
}

CKMat3 *CKMat3::translate(class CKVec2 *ovec){
	CKMat3 tmp = CKMat3();
	
	tmp.values[M00] = 1;
	tmp.values[M10] = 0;
	tmp.values[M01] = 0;
	tmp.values[M11] = 1;
	tmp.values[M02] = ovec->x;
	tmp.values[M12] = ovec->y;
	
	mul(&tmp);
	
	return this;
}


CKMat3 *CKMat3::scale(Float x, Float y){
	CKMat3 tmp = CKMat3();
	
	tmp.values[M00] = x;
	tmp.values[M10] = 0;
	tmp.values[M01] = 0;
	tmp.values[M11] = y;
	tmp.values[M02] = 0;
	tmp.values[M12] = 0;
	
	mul(&tmp);
	
	return this;
}

CKMat3 *CKMat3::scale(class CKVec2 *ovec){
	CKMat3 tmp = CKMat3();
	
	tmp.values[M00] = ovec->x;
	tmp.values[M10] = 0;
	tmp.values[M01] = 0;
	tmp.values[M11] = ovec->y;
	tmp.values[M02] = 0;
	tmp.values[M12] = 0;
	
	mul(&tmp);
	
	return this;
}

CKMat3 *CKMat3::scale(Float sc){
	values[M00] *= sc;
	values[M11] *= sc;
	return this;
}


CKMat3 *CKMat3::rotate(Float rad){
	CKMat3 tmp = CKMat3();
	
	Float cosf = cos(rad);
	Float sinf = sin(rad);
	
	tmp.values[M00] = cosf;
	tmp.values[M10] = sinf;
	tmp.values[M01] = -sinf;
	tmp.values[M11] = cosf;
	tmp.values[M02] = 0;
	tmp.values[M12] = 0;
	
	mul(&tmp);
	
	return this;
}


CKMat3 *CKMat3::mul(CKMat3 *omat){
	Float* val = values;

	Float v00 = val[M00]*omat->values[M00] + val[M01]*omat->values[M10] + val[M02]*omat->values[M20];
	Float v01 = val[M00]*omat->values[M01] + val[M01]*omat->values[M11] + val[M02]*omat->values[M21];
	Float v02 = val[M00]*omat->values[M02] + val[M01]*omat->values[M12] + val[M02]*omat->values[M22];

	Float v10 = val[M10]*omat->values[M00] + val[M11]*omat->values[M10] + val[M12]*omat->values[M20];
	Float v11 = val[M10]*omat->values[M01] + val[M11]*omat->values[M11] + val[M12]*omat->values[M21];
	Float v12 = val[M10]*omat->values[M02] + val[M11]*omat->values[M12] + val[M12]*omat->values[M22];

	Float v20 = val[M20]*omat->values[M00] + val[M21]*omat->values[M10] + val[M22]*omat->values[M20];
	Float v21 = val[M20]*omat->values[M01] + val[M21]*omat->values[M11] + val[M22]*omat->values[M21];
	Float v22 = val[M20]*omat->values[M02] + val[M21]*omat->values[M12] + val[M22]*omat->values[M22];

	val[M00] = v00;
	val[M10] = v10;
	val[M20] = v20;
	val[M01] = v01;
	val[M11] = v11;
	val[M21] = v21;
	val[M02] = v02;
	val[M12] = v12;
	val[M22] = v22;

	return this;
}


CKMat3 *CKMat3::transpose(){
	Float* val = values;
	Float v01 = val[M10];
	Float v02 = val[M20];
	Float v10 = val[M01];
	Float v12 = val[M21];
	Float v20 = val[M02];
	Float v21 = val[M12];
	val[M01] = v01;
	val[M02] = v02;
	val[M10] = v10;
	val[M12] = v12;
	val[M20] = v20;
	val[M21] = v21;
	
	return this;
}


CKMat3 *CKMat3::invert(){
	Float det = determinant();
	if(det==0){
		return this;
	}

	Float inv_det = 1.0f/det;
	Float* val = values;

	Float v00 = val[M11]*val[M22] - val[M21]*val[M12];
	Float v10 = val[M20]*val[M12] - val[M10]*val[M22];
	Float v20 = val[M10]*val[M21] - val[M20]*val[M11];
	Float v01 = val[M21]*val[M02] - val[M01]*val[M22];
	Float v11 = val[M00]*val[M22] - val[M20]*val[M02];
	Float v21 = val[M20]*val[M01] - val[M00]*val[M21];
	Float v02 = val[M01]*val[M12] - val[M11]*val[M02];
	Float v12 = val[M10]*val[M02] - val[M00]*val[M12];
	Float v22 = val[M00]*val[M11] - val[M10]*val[M01];

	val[M00] = inv_det*v00;
	val[M10] = inv_det*v10;
	val[M20] = inv_det*v20;
	val[M01] = inv_det*v01;
	val[M11] = inv_det*v11;
	val[M21] = inv_det*v21;
	val[M02] = inv_det*v02;
	val[M12] = inv_det*v12;
	val[M22] = inv_det*v22;

	return this;
}

