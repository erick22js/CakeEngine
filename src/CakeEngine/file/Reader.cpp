#include <string.h>

#include <CakeEngine/file/Reader.hpp>



CKReader::CKReader(Char* filepath): CKStreamReader(filepath, CK_STREAMMODE_TEXT){}
CKReader::CKReader(): CKStreamReader(nullptr, 0, CK_STREAMMODE_TEXT){}


CKReader *CKReader::createFromFile(Char* filepath){
	CKReader *reader = new CKReader(filepath);
	return reader;
}

CKReader *CKReader::createFromSrc(Char* src){
	CKReader *reader = new CKReader();
	reader->buffer = (Uint8*)src;
	reader->buffer_length = strlen(src);
	return reader;
}


Int CKReader::readc(){
	Int chr = 0;
	if(rbuffer_e){
		chr = rbuffer;
		rbuffer_e = false;
	}
	else{
		chr = CKStreamReader::readc();
		rbuffer = chr;
	}
	return chr;
}


void CKReader::unreadc(){
	rbuffer_e = true;
}


