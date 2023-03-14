#ifndef cakengine_math_vector3_h
#define cakengine_math_vector3_h

#include "../util.hpp"


class CKVec3{
	
private:
	
	
public:
	Float x = 0, y = 0, z = 0;
	
	CKVec3();
	CKVec3(Float x, Float y, Float z);
	CKVec3(class CKVec2 *ovec);
	CKVec3(CKVec3 *ovec);
	
	CKVec3 *set(Float x, Float y, Float z);
	CKVec3 *set(CKVec3 *ovec);
	
	CKVec3 clone();
	
	Float distance(CKVec3 *ovec);
	Float distance();
	
	Float distance2(CKVec3 *ovec);
	Float distance2();
	
	Bool equal(Float x, Float y, Float z);
	Bool equal(CKVec3 *ovec);
	
	CKVec3 *add(Float x, Float y, Float z);
	CKVec3 *add(CKVec3 *ovec);
	
	CKVec3 *sub(Float x, Float y, Float z);
	CKVec3 *sub(CKVec3 *ovec);
	
	CKVec3 *mul(Float x, Float y, Float z);
	CKVec3 *mul(CKVec3 *ovec);
	
	CKVec3 *mulAdd(Float x, Float y, Float z, Float sc);
	CKVec3 *mulAdd(CKVec3 *ovec, Float sc);
	
	CKVec3 *scale(Float sc);
	
	CKVec3 *transformPoint(class CKMat4 *omat);
	CKVec3 *transformDirection(class CKMat4 *omat);
	CKVec3 *transformNormal(class CKMat4 *omat);
	
	CKVec3 *lerp(Float x, Float y, Float z, Float alpha);
	CKVec3 *lerp(CKVec3 *ovec, Float alpha);
	
	Float dot(Float x, Float y, Float z);
	Float dot(CKVec3 *ovec);
	
};


#endif // cakengine_math_vector3_h
