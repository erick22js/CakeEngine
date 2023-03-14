#ifndef cakengine_math_matrix4_h
#define cakengine_math_matrix4_h

#include "../util.hpp"


class CKMat4{
	
private:
	
	
public:
	Float values[16];
	
	static const Int M00 = 0;
	static const Int M10 = 1;
	static const Int M20 = 2;
	static const Int M30 = 3;
	static const Int M01 = 4;
	static const Int M11 = 5;
	static const Int M21 = 6;
	static const Int M31 = 7;
	static const Int M02 = 8;
	static const Int M12 = 9;
	static const Int M22 = 10;
	static const Int M32 = 11;
	static const Int M03 = 12;
	static const Int M13 = 13;
	static const Int M23 = 14;
	static const Int M33 = 15;
	
	CKMat4();
	CKMat4(CKMat4 *omat);
	CKMat4(Float vals[]);
	
	CKMat4 *identity();
	
	CKMat4 *set(CKMat4 *omat);
	CKMat4 *set(Float vals[]);
	
	CKMat4 *copyTo(CKMat4 *omat);
	
	Float determinant();
	
	CKMat4 *setToTranslation(Float x, Float y, Float z);
	CKMat4 *setToTranslation(class CKVec3 *ovec);
	
	CKMat4 *setToScale(Float x, Float y, Float z);
	CKMat4 *setToScale(class CKVec3 *ovec);
	
	CKMat4 *setToRotationX(Float rad);
	CKMat4 *setToRotationY(Float rad);
	CKMat4 *setToRotationZ(Float rad);
	
	CKMat4 *setToRotation(Float ax, Float ay, Float az, Float rad);
	CKMat4 *setToRotation(class CKVec3 *axis, Float rad);
	
	CKMat4 *setToProjection(Float near, Float far, Float fov, Float aspectRatio);
	CKMat4 *setToProjection(Float left, Float right, Float top, Float bottom, Float far, Float near);
	
	CKMat4 *translate(Float x, Float y, Float z);
	CKMat4 *translate(class CKVec3 *ovec);
	
	CKMat4 *scale(Float x, Float y, Float z);
	CKMat4 *scale(class CKVec3 *ovec);
	CKMat4 *scale(Float sc);
	
	CKMat4 *rotateX(Float rad);
	CKMat4 *rotateY(Float rad);
	CKMat4 *rotateZ(Float rad);
	
	CKMat4 *mul(CKMat4 *omat);
	
	CKMat4 *transpose();
	
	CKMat4 *invert();
	
	void decompose(class CKVec3 *ovec_position, class CKVec3 *ovec_scale, class CKVec3 *ovec_rotation);
	
};


#endif // cakengine_math_matrix4_h
