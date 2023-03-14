#ifndef cakengine_stream_h
#define cakengine_stream_h

#include <stdio.h>
#include <iostream>
#include <vector>

#include "../api.hpp"


typedef enum{
	CK_STREAMTYPE_FILE,
	CK_STREAMTYPE_BUFFER,
}CKStreamType;

typedef enum{
	CK_STREAMMODE_TEXT,
	CK_STREAMMODE_BINARY,
}CKStreamMode;


class CKStreamInterface{
	
protected:
	CKStreamType type;
	CKStreamMode mode;
	
	FILE *file = nullptr;
	
	Uint8* buffer = nullptr;
	Uint32 buffer_seek = 0;
	Uint32 buffer_length = 0;
	
	CKStreamInterface(CKStreamType type, CKStreamMode mode);
	
	Bool loadFile(Char* filepath, Char* mode);
	
public:
	Bool open = false;
	
	Uint32 tell();
	
	Uint32 getLength();
	
	void seekBeg(Int offset);
	void seekCur(Int offset);
	void seekEnd(Int offset);
	
	Bool eof();
	
	void close();
	
	Bool isOpen();
	
};


class CKStreamReader:public CKStreamInterface{
	
protected:
	Int readc_();
	
public:
	CKStreamReader(Char* filepath, CKStreamMode mode);
	CKStreamReader(void* buffer, Uint32 buffer_length, CKStreamMode mode);
	
	Int readc();
	
	void read(void* outbuffer, Uint32 length);
	
};


class CKStreamWriter:public CKStreamInterface{
	
protected:
	std::vector<Uint8> wbuffer = std::vector<Uint8>(0);
	
	void writec_(Int chr);
	
public:
	CKStreamWriter(Char* filepath, CKStreamMode mode);
	CKStreamWriter(CKStreamMode mode);
	
	void writec(Int chr);
	
	void write(void* inbuffer, Uint32 length);
	
	Uint8* getBuffer();
	
};


#endif // cakengine_stream_h
