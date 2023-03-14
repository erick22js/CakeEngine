#ifndef cakengine_math_shape2d_h
#define cakengine_math_shape2d_h

#include <CakeEngine/math/util.hpp>
#include <CakeEngine/math/vector/Vector2.hpp>


enum CKShapeType2D{
	CK_SHAPETYPE2D_NONE,
	CK_SHAPETYPE2D_RECTANGLE,
	CK_SHAPETYPE2D_CIRCLE,
};


class CKShape2D{
	
private:
	CKShapeType2D type = CK_SHAPETYPE2D_NONE;
	
public:
	CKVec2 position = CKVec2();
	
	CKShape2D(Float x = 0, Float y = 0);
	
	Bool testColision(CKShape2D *other);
	
};


class CKRectangle:public CKShape2D{
	
private:
	CKShapeType2D type = CK_SHAPETYPE2D_RECTANGLE;
	
public:
	CKVec2 size = CKVec2();
	
	CKRectangle(Float x = 0, Float y = 0, Float width = 1, Float height = 1);
	
	Bool testColision(CKShape2D *other);
	Bool testColision(CKRectangle *other);
	
};


class CKCircle:public CKShape2D{
	
private:
	CKShapeType2D type = CK_SHAPETYPE2D_CIRCLE;
	
public:
	Float radius = 1;
	
	CKCircle(Float x = 0, Float y = 0, Float radius = 1);
	
	Bool testColision(CKShape2D *other);
	Bool testColision(CKCircle *other);
	
};


#endif // cakengine_math_shape_h
