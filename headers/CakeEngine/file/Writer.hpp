#ifndef cakengine_file_writer_h
#define cakengine_file_writer_h

#include "Stream.hpp"


class CKWriter:public CKStreamWriter{
	
private:
	CKWriter(Char* filepath);
	CKWriter();
	
public:
	static CKWriter *createToFile(Char* filepath);
	static CKWriter *createToSrc();
	
	Char* getBuffer();
	
	void write(Char* cstr);
	void writec(Int c);
	void writec(Int c, Int times);
	
};


#endif // cakengine_file_writer_h
