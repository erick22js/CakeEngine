#ifndef cakengine_math_color_h
#define cakengine_math_color_h

#include "util.hpp"


class CKColor{
	
private:
	
	
public:
	Uint8 r, g, b, a;
	
	static const Uint32 WHITE = 0xFFFFFFFF;
	static const Uint32 BLACK = 0xFF000000;
	
	CKColor();
	CKColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	CKColor(Float r, Float g, Float b, Float a);
	CKColor(Uint32 value);
	CKColor(CKColor *color);
	
	Uint32 toValue();
	static Uint32 toValue(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	static Uint32 toValue(Float r, Float g, Float b, Float a);
	static Uint32 toValue(CKColor *color);
	
};


#endif // cakengine_math_color_h
