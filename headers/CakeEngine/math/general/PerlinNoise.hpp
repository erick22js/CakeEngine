#ifndef cakengine_math_general_perlinnoise_h
#define cakengine_math_general_perlinnoise_h

#include <CakeEngine/math/util.hpp>
#include <CakeEngine/math/vector/Vector2.hpp>
#include <CakeEngine/math/vector/Vector3.hpp>


class CKPerlinNoise{
	
private:
	static Uint8 ptable[512];
	
	Uint8 getv2(Uint8 x, Uint8 y);
	CKVec2 getvec2(Uint8 v);
	
	void hashseed();
	
public:
	SizeT seed = 0;
	Uint8 hseed = 0;
	
	CKPerlinNoise(SizeT seed = 0);
	
	Float noise2d(Float x, Float y);
	
	void setseed(SizeT seed);
	
};


#endif // cakengine_math_general_perlinnoise_h
