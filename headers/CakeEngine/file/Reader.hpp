#ifndef cakengine_file_reader_h
#define cakengine_file_reader_h

#include "Stream.hpp"


class CKReader:public CKStreamReader{
	
private:
	Int rbuffer = 0;
	Bool rbuffer_e = false;
	
	CKReader(Char* filepath);
	CKReader();
	
public:
	static CKReader *createFromFile(Char* filepath);
	static CKReader *createFromSrc(Char* src);
	
	Int readc();
	
	void unreadc();
	
};


#endif // cakengine_file_reader_h
