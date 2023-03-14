#ifndef cakengine_util_string_h
#define cakengine_util_string_h

#include <string.h>
#include <string>

#include <CakeEngine/api.hpp>


class CKString{
	
private:
	
	
public:
	static Char* wrap(Char* cstr);
	static void unwrap(Char* cstr);
	static Char* record(Char* cstr);
	
	static Int length(Char* cstr);
	
	static Int compare(Char* cstr1, Char* cstr2);
	static Bool isEqual(Char* cstr1, Char* cstr2);
	
	static SizeT hash(Char* cstr);
	
	/* Conversions */
	
	static Int toInt(Char* cstr);
	static Float toFloat(Char* cstr);
	
};


#endif // cakengine_util_string_h
