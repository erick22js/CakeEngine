#include <CakeEngine/util/String.hpp>
#include <CakeEngine/util/Dictionary.hpp>


CKDictionary<Char*> recorded_str = CKDictionary<Char*>();


Char* CKString::wrap(Char* cstr){
	Char* nstr = new Char[length(cstr)+1];
	
	Int i=0;
	while(*cstr){
		nstr[i] = *cstr;
		i++;
		cstr++;
	}
	nstr[i] = 0;
	
	return nstr;
}

void CKString::unwrap(Char* cstr){
	delete cstr;
}

Char* CKString::record(Char* cstr){
	if(recorded_str.has(cstr)){
		return recorded_str.get(cstr);
	}
	else{
		Char* nstr = wrap(cstr);
		recorded_str.set(nstr, nstr);
		return nstr;
	}
}


Int CKString::length(Char* cstr){
	Int length = 0;
	while(*cstr){
		length++;
		cstr++;
	}
	return length;
}


Int CKString::compare(Char* cstr1, Char* cstr2){
	return strcmp(cstr1, cstr2);
}

Bool CKString::isEqual(Char* cstr1, Char* cstr2){
	return strcmp(cstr1, cstr2)==0;
}


/*
	Function: Custom Hashing Strings
	Obs: can be customized to any needs, I think this version is pretty fast
*/

SizeT CKString::hash(Char* cstr){
	SizeT code = 0x0;
	while(*cstr){
		code = (*cstr)+(code<<6)+(code<<16)-code*33;
		cstr++;
	}
	return code;
}


/**
	CONVERSION FUNCTIONS
*/

#include <stdio.h>

Int CKString::toInt(Char* cstr){
	Int value = 0;
	sscanf(cstr, "%d", &value);
	return value;
}

Float CKString::toFloat(Char* cstr){
	Float value = 0;
	sscanf(cstr, "%f", &value);
	return value;
}

