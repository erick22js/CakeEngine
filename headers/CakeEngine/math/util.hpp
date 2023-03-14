#ifndef cakengine_math_util_h
#define cakengine_math_util_h

#include <SDL2/SDL.h>
#include <math.h>

#include <CakeEngine/api.hpp>


//#define PI (3.1415f)


class CKMath{
	
public:
	static constexpr Float PI = 3.14159265359f;
	
	static constexpr Float E = 2.71828182846f;
	
	static Float rad2Deg(Float rad);
	static Float deg2Rad(Float deg);
	
	static Float normalizeAngle(Float rad);
	
	static Float sin(Float rad);
	static Float cos(Float rad);
	static Float tan(Float rad);
	static Float asin(Float sin);
	static Float acos(Float cos);
	static Float atan(Float tan);
	static Float atan2(Float y, Float x);
	
	static Float floor(Float val);
	static Float ceil(Float val);
	static Float round(Float val);
	
	static Float sqrt(Float val);
	static Float cbrt(Float val);
	static Float pow(Float base, Float exp);
	
	static Float log(Float val);
	static Float log10(Float val);
	
	static Float lerp(Float v1, Float v2, Float a);
	static Float fade(Float a);
	
	static void srandom(Float seed);
	static Float random();
	
};


#endif // cakengine_math_util_h
