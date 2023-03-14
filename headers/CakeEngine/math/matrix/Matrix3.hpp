#ifndef cakengine_math_matrix3_h
#define cakengine_math_matrix3_h

#include "../util.hpp"


class CKMat3{
	
private:
	
	
public:
	Float values[9];
	
	static const Int M00 = 0;
	static const Int M10 = 1;
	static const Int M20 = 2;
	static const Int M01 = 3;
	static const Int M11 = 4;
	static const Int M21 = 5;
	static const Int M02 = 6;
	static const Int M12 = 7;
	static const Int M22 = 8;
	
	CKMat3();
	CKMat3(CKMat3 *omat);
	CKMat3(Float vals[]);
	
	CKMat3 *identity();
	
	CKMat3 *affine();
	
	CKMat3 *set(CKMat3 *omat);
	CKMat3 *set(Float vals[]);
	
	CKMat3 *copyTo(CKMat3 *omat);
	
	Float determinant();
	
	CKMat3 *setToTranslation(Float x, Float y);
	CKMat3 *setToTranslation(class CKVec2 *ovec);
	
	CKMat3 *setToScale(Float x, Float y);
	CKMat3 *setToScale(class CKVec2 *ovec);
	
	CKMat3 *setToRotation(Float rad);
	CKMat3 *setToRotation(class CKVec3 *axis, Float rad);
	
	CKMat3 *translate(Float x, Float y);
	CKMat3 *translate(class CKVec2 *ovec);
	
	CKMat3 *scale(Float x, Float y);
	CKMat3 *scale(class CKVec2 *ovec);
	CKMat3 *scale(Float sc);
	
	CKMat3 *rotate(Float rad);
	
	CKMat3 *mul(CKMat3 *omat);
	
	CKMat3 *transpose();
	
	CKMat3 *invert();
	
};


#endif // cakengine_math_matrix3_h
