#include <CakeEngine/math/general/PerlinNoise.hpp>



Uint8 CKPerlinNoise::ptable[512] = {
	151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
	140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
	247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
	 57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
	 74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
	 60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
	 65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
	200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
	 52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
	207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
	119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
	129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
	218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
	 81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
	184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
	222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180,
	/* TODO: Next 256 sequence repeat, must change it */
	151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
	140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
	247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
	 57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
	 74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
	 60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
	 65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
	200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
	 52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
	207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
	119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
	129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
	218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
	 81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
	184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
	222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180
};


Uint8 CKPerlinNoise::getv2(Uint8 x, Uint8 y){
	return ptable[ptable[x+hseed]+y];
}

CKVec2 CKPerlinNoise::getvec2(Uint8 v){
	switch(v&7){
		case 0:{
			return CKVec2(1, 1);
		}
		break;
		case 1:{
			return CKVec2(1, 0);
		}
		break;
		case 2:{
			return CKVec2(1, -1);
		}
		break;
		case 3:{
			return CKVec2(0, -1);
		}
		break;
		case 4:{
			return CKVec2(-1, -1);
		}
		break;
		case 5:{
			return CKVec2(-1, 0);
		}
		break;
		case 6:{
			return CKVec2(-1, 1);
		}
		break;
		case 7:{
			return CKVec2(0, 1);
		}
		break;
	}
	return CKVec2(0, 0);
}


void CKPerlinNoise::hashseed(){
	Int seed = this->seed;
	hseed = 0;
	for(Int i=0; i<sizeof(SizeT); i++){
		hseed += seed&0xff;
		seed >>= 8;
	}
}


CKPerlinNoise::CKPerlinNoise(SizeT seed){
	setseed(seed);
}


Float CKPerlinNoise::noise2d(Float x, Float y){
	// Floor axis values
	Float fx = CKMath::floor(x);
	Float fy = CKMath::floor(y);
	
	// Linear progression values
	Float ax = x-fx;
	Float ay = y-fy;
	
	// Smooth fade
	Float tx = CKMath::fade(ax);
	Float ty = CKMath::fade(ay);
	
	// Calculate the dots products
	CKVec2 vectl = getvec2(getv2((fx), (fy)));
	Float vtl = vectl.dot(x-(fx), y-(fy));
	CKVec2 vectr = getvec2(getv2((fx+1), (fy)));
	Float vtr = vectl.dot(x-(fx+1), y-(fy));
	CKVec2 vecbl = getvec2(getv2((fx), (fy+1)));
	Float vbl = vectl.dot(x-(fx), y-(fy+1));
	CKVec2 vecbr = getvec2(getv2((fx+1), (fy+1)));
	Float vbr = vectl.dot(x-(fx+1), y-(fy+1));
	
	Float vt = CKMath::lerp(vtl, vtr, tx);
	Float vb = CKMath::lerp(vbl, vbr, tx);
	return CKMath::lerp(vt, vb, ty);
}


void CKPerlinNoise::setseed(SizeT seed){
	this->seed = seed;
	hashseed();
}

