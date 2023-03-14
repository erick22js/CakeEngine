#ifndef cakengine_math_vector2_h
#define cakengine_math_vector2_h

#include "../util.hpp"


class CKVec2{
	
private:
	
	
public:
	Float x = 0, y = 0;
	
	CKVec2();
	CKVec2(Float x, Float y);
	CKVec2(CKVec2 *ovec);
	
	CKVec2 *set(Float x, Float y);
	CKVec2 *set(CKVec2 *ovec);
	
	CKVec2 clone();
	
	Float distance(CKVec2 *ovec);
	Float distance();
	
	Float distance2(CKVec2 *ovec);
	Float distance2();
	
	Float angle(CKVec2 *ovec);
	Float angle();
	
	Bool equal(Float x, Float y);
	Bool equal(CKVec2 *ovec);
	
	CKVec2 *add(Float x, Float y);
	CKVec2 *add(CKVec2 *ovec);
	
	CKVec2 *sub(Float x, Float y);
	CKVec2 *sub(CKVec2 *ovec);
	
	CKVec2 *mul(Float x, Float y);
	CKVec2 *mul(CKVec2 *ovec);
	
	CKVec2 *mulAdd(Float x, Float y, Float sc);
	CKVec2 *mulAdd(CKVec2 *ovec, Float sc);
	
	CKVec2 *scale(Float sc);
	
	CKVec2 *transformPoint(class CKMat3 *omat);
	CKVec2 *transformDirection(class CKMat3 *omat);
	CKVec2 *transformNormal(class CKMat3 *omat);
	
	CKVec2 *lerp(Float x, Float y, Float alpha);
	CKVec2 *lerp(CKVec2 *ovec, Float alpha);
	
	Float dot(Float x, Float y);
	Float dot(CKVec2 *ovec);
	
};


#endif // cakengine_math_vector2_h
