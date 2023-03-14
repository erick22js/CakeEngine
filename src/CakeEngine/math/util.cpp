#include <CakeEngine/math/util.hpp>



Float CKMath::rad2Deg(Float rad){
	return (rad/PI)*180;
}

Float CKMath::deg2Rad(Float deg){
	return (deg/180)*PI;
}


Float CKMath::normalizeAngle(Float rad){
	while(rad<(-PI)){
		rad += PI*2;
	}
	while(rad>(-PI)){
		rad -= PI*2;
	}
	return rad;
}


Float CKMath::sin(Float rad){
	return SDL_sinf(rad);
}

Float CKMath::cos(Float rad){
	return SDL_cosf(rad);
}

Float CKMath::tan(Float rad){
	return SDL_tanf(rad);
}

Float CKMath::asin(Float sin){
	return SDL_asinf(sin);
}

Float CKMath::acos(Float cos){
	return SDL_acosf(cos);
}

Float CKMath::atan(Float tan){
	return SDL_atanf(tan);
}

Float CKMath::atan2(Float y, Float x){
	return SDL_atan2f(y, x);
}


Float CKMath::floor(Float val){
	return SDL_floorf(val);
}

Float CKMath::ceil(Float val){
	return SDL_ceilf(val);
}

Float CKMath::round(Float val){
	return SDL_roundf(val);
}


Float CKMath::sqrt(Float val){
	return SDL_sqrtf(val);
}

Float CKMath::cbrt(Float val){
	return SDL_powf(val, 0.3333333f);
}

Float CKMath::pow(Float base, Float exp){
	return SDL_powf(base, exp);
}


Float CKMath::log(Float val){
	return SDL_logf(val);
}

Float CKMath::log10(Float val){
	return SDL_log10f(val);
}


Float CKMath::lerp(Float v1, Float v2, Float a){
	return v1 + (v2-v1)*a;
}

Float CKMath::fade(Float a){
	return ((6*a-15)*a+10)*a*a*a;
}


void srandom(Float seed){
	srand(seed);
}

Float random(){
	return rand();
}

