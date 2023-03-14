#include <CakeEngine/file/Stream.hpp>



/**
	STREAM INTERFACE
*/

CKStreamInterface::CKStreamInterface(CKStreamType type, CKStreamMode mode){
	this->type = type;
}

Bool CKStreamInterface::loadFile(Char* filepath, Char* mode){
	file = fopen(filepath, mode);
	if(file==nullptr){
		return false;
	}
	return true;
}


Uint32 CKStreamInterface::tell(){
	if(type==CK_STREAMTYPE_FILE){
		return ftell(file);
	}
	else{
		return buffer_seek;
	}
}


Uint32 CKStreamInterface::getLength(){
	if(type==CK_STREAMTYPE_FILE){
		Uint32 pos = ftell(file);
		fseek(file, 0, SEEK_END);
		Uint32 len = ftell(file);
		fseek(file, pos, SEEK_SET);
		return len;
	}
	else{
		return buffer_length;
	}
}


void CKStreamInterface::seekBeg(Int offset){
	if(type==CK_STREAMTYPE_FILE){
		fseek(file, offset, SEEK_SET);
	}
	else{
		buffer_seek = offset;
	}
}

void CKStreamInterface::seekCur(Int offset){
	if(type==CK_STREAMTYPE_FILE){
		fseek(file, offset, SEEK_CUR);
	}
	else{
		buffer_seek += offset;
	}
}

void CKStreamInterface::seekEnd(Int offset){
	if(type==CK_STREAMTYPE_FILE){
		fseek(file, offset, SEEK_END);
	}
	else{
		buffer_seek = buffer_length+offset;
	}
}


Bool CKStreamInterface::eof(){
	if(type==CK_STREAMTYPE_FILE){
		return feof(file)!=0;
	}
	else{
		return buffer_seek>=buffer_length;
	}
}


void CKStreamInterface::close(){
	if(open){
		if(type==CK_STREAMTYPE_FILE){
			fclose(file);
		}
		else{
			buffer = nullptr;
			buffer_length = 0;
			buffer_seek = 0;
		}
		open = false;
	}
}

Bool CKStreamInterface::isOpen(){
	return open;
}


/**
	STREAM READER
*/

Int CKStreamReader::readc_(){
	if(open){
		if(type==CK_STREAMTYPE_FILE){
			return fgetc(file);
		}
		else{
			if(buffer_seek>=buffer_length){
				return EOF;
			}
			return buffer[buffer_seek++];
		}
	}
	return 0;
}

CKStreamReader::CKStreamReader(Char* filepath, CKStreamMode mode): CKStreamInterface(CK_STREAMTYPE_FILE, mode){
	if(!loadFile(filepath, (Char*)"rb")){
		return;
	}
	open = true;
}

CKStreamReader::CKStreamReader(void* buffer, Uint32 buffer_length, CKStreamMode mode): CKStreamInterface(CK_STREAMTYPE_BUFFER, mode){
	this->buffer = (Uint8*)buffer;
	this->buffer_length = buffer_length;
	open = true;
}

Int CKStreamReader::readc(){
	return readc_();
}

void CKStreamReader::read(void* outbuffer, Uint32 length){
	if(type==CK_STREAMTYPE_FILE){
		fread(outbuffer, 1, length, file);
	}
	else{
		while(length){
			if(buffer_seek>=buffer_length){
				return;
			}
			*(Uint8*)outbuffer = buffer[buffer_seek++];
			outbuffer++;
			length--;
		}
	}
}


/**
	STREAM WRITER
*/

void CKStreamWriter::writec_(Int chr){
	if(open){
		if(type==CK_STREAMTYPE_FILE){
			fputc((Uint8)chr, file);
		}
		else{
			if(buffer_seek==buffer_length){
				wbuffer.push_back(0);
				buffer_length++;
			}
			else if(buffer_seek>buffer_length){
				wbuffer.resize(buffer_seek+1);
				buffer_length = buffer_seek+1;
			}
			wbuffer[buffer_seek++] = (Uint8)chr;
		}
	}
}

CKStreamWriter::CKStreamWriter(Char* filepath, CKStreamMode mode): CKStreamInterface(CK_STREAMTYPE_FILE, mode){
	if(!loadFile(filepath, (Char*)"wb")){
		return;
	}
	open = true;
}

CKStreamWriter::CKStreamWriter(CKStreamMode mode): CKStreamInterface(CK_STREAMTYPE_BUFFER, mode){
	open = true;
}

void CKStreamWriter::writec(Int chr){
	return writec_(chr);
}

void CKStreamWriter::write(void* inbuffer, Uint32 length){
	if(type==CK_STREAMTYPE_FILE){
		fwrite(inbuffer, 1, length, file);
	}
	else{
		while(length){
			if(buffer_seek==buffer_length){
				wbuffer.push_back(0);
				buffer_length++;
			}
			else if(buffer_seek>buffer_length){
				wbuffer.resize(buffer_seek+1);
				buffer_length = buffer_seek+1;
			}
			wbuffer[buffer_seek++] = *(Uint8*)inbuffer;
			inbuffer++;
			length--;
		}
	}
}

Uint8* CKStreamWriter::getBuffer(){
	return wbuffer.data();
}

