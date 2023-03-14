#include <string.h>

#include <CakeEngine/file/Writer.hpp>



CKWriter::CKWriter(Char* filepath): CKStreamWriter(filepath, CK_STREAMMODE_TEXT){}
CKWriter::CKWriter(): CKStreamWriter(CK_STREAMMODE_TEXT){}


CKWriter *CKWriter::createToFile(Char* filepath){
	CKWriter *writer = new CKWriter(filepath);
	return writer;
}

CKWriter *CKWriter::createToSrc(){
	CKWriter *writer = new CKWriter();
	return writer;
}


Char* CKWriter::getBuffer(){
	return (Char*)CKStreamWriter::getBuffer();
}


void CKWriter::write(Char* cstr){
	CKStreamWriter::write(cstr, strlen(cstr));
}

void CKWriter::writec(Int c){
	CKStreamWriter::writec(c);
}

void CKWriter::writec(Int c, Int times){
	while(times>0){
		CKStreamWriter::writec(c);
		times--;
	}
}

