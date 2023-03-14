#include "pnghanddler.h"


void log_bin(Char *name_file, void* data, Uint32 size){
	FILE *file = fopen(name_file, "wb");
	fwrite(data, 1, size, file);
	fclose(file);
}

void ckzlib::ifstream::advanceBits(Uint32 bits){
	Uint32 bytes = bits>>3;
	bits &= 0b111;
	
	offset_byte += bytes+(bits>>3);
	offset_bit += bits&0b111;
	
	offset_byte += offset_bit>>3;
	offset_bit &= 0b111;
}

void ckzlib::ifstream::advanceBytes(Uint32 bytes){
	offset_byte += bytes;
}


void ckzlib::ifstream::seekSet(Uint32 bytes, Uint32 bits){
	offset_byte = bytes;
	offset_bit = bits;
}

void ckzlib::ifstream::seekCur(Sint32 bytes, Sint32 bits){
	offset_byte += bytes;
	
	if(bits<0){
		offset_byte -= (-bits)>>3;
		offset_bit -= (-bits)&0b111;
		
		offset_byte -= (offset_bit>>3)!=0;
		offset_bit &= 0b111;
	}
	else{
		offset_byte += bits>>3;
		offset_bit += bits&0b111;
		
		offset_byte += offset_bit>>3;
		offset_bit &= 0b111;
	}
}

void ckzlib::ifstream::seekEnd(Sint32 bytes, Sint32 bits){
	offset_byte = length;
	offset_bit = 0;
	
	offset_byte += bytes;
	
	if(bits<0){
		offset_byte -= (-bits)>>3;
		offset_bit -= (-bits)&0b111;
		
		offset_byte -= (offset_bit>>3)!=0;
		offset_bit &= 0b111;
	}
	else{
		offset_byte += bits>>3;
		offset_bit += bits&0b111;
		
		offset_byte += offset_bit>>3;
		offset_bit &= 0b111;
	}
}


Bool ckzlib::ifstream::ended(){
	return offset_byte>= length;
}


Uint32 ckzlib::ifstream::read32(){
	Uint32 data = 0;
	static const Uint32 UINT8SIZE = 8;
	static const Uint32 UINT32SIZE = 32;
	Uint32 remaining = UINT32SIZE;
	
	if(offset_byte>=length){
		return 0;
	}
	
	if(offset_bit){
		data |= (((Uint8*)buffer)[offset_byte]>>offset_bit);
		remaining -= UINT8SIZE-offset_bit;
	}
	
	for(Int bi=offset_byte+(offset_bit!=0); (remaining>0)&&(bi<length); bi++){
		data |= (((Uint8*)buffer)[bi])<<(UINT32SIZE-remaining);
		if(remaining>=UINT8SIZE){
			remaining -= UINT8SIZE;
		}
		else{
			remaining = 0;
		}
	}
	
	return data;
}

Uint32 ckzlib::ifstream::fetchBits(Uint32 bits){
	Uint32 data = read32();
	advanceBits(bits);
	return data&((Uint32)(((Uint32)1<<bits)-1));
}


Uint32 ckzlib::inf_init_hdyn(ifstream *stream){
	Int num_litlen_lens;
	Int num_dist_lens;
	Int num_code_lens;
	Uint8 codelen_lengths[19];
	Uint8 code_lengths[320];
	
	num_litlen_lens = stream->fetchBits(5)+257;
	if(num_litlen_lens>288){
		/* TODO: Error => Excceded the maximum value */
		return 1;
	}
	printf("Num litlen lens = %d\n", num_litlen_lens);
	
	num_dist_lens = stream->fetchBits(5)+1;
	if(num_dist_lens>32){
		/* TODO: Error => Excceded the maximum value */
		return 1;
	}
	printf("Num dist lens = %d\n", num_dist_lens);
	
	num_code_lens = stream->fetchBits(4)+4;
	if(num_code_lens>19){
		/* TODO: Error => Excceded the maximum value */
		return 1;
	}
	printf("Num code lens = %d\n", num_code_lens);
	
	
	
	return 0;
}


Uint32 ckzlib::inflate(Uint8* stream_u8, Uint32 length, std::vector<Uint8> *out){
	ifstream stream = {
		.buffer = stream_u8+2,
		.length = length-6,
	};
	
	Bool ended = false;
	
	while((!stream.ended())&&(!ended)){
		Uint8 entry = stream.fetchBits(3);
		ended = entry&1;
		Uint8 type = entry>>1;
		
		switch(type){
			case 0:{ /* No Compression */
				printf("# INFLATE :: No Compression\n");
			}
			break;
			case 1:{ /* Compressed with fixed Huffman codes */
				printf("# INFLATE :: Fixed Huffman\n");
			}
			break;
			case 2:{ /* Compressed with "dynamic" Huffman codes */
				printf("# INFLATE :: Dynamic Huffman\n");
				inf_init_hdyn(&stream);
			}
			break;
			default:{
				printf("# INFLATE :: Invalid Block Type");
				return 1; /* TODO: Error => Invalid block compression type */
			}
		}
		if(ended){
			printf(" (The last one)\n");
		}
		else{
			printf("\n");
		}
	}
	
	return 0;
}

Uint32 ckzlib::decompress(Uint8* stream_u8, Uint32 length, std::vector<Uint8>* out){
	/* Log test data */
	log_bin("data-compressed.bin", stream_u8, length);
	
	/* Check Compression Method */
	printf("Compression Method/Flags: 0x%.2x\n\n", stream_u8[0]);
	if((stream_u8[0]&0xf)==0x08){
		Uint32 err = inflate(stream_u8, length, out);
		/* Log test data */
		log_bin("data-decompressed.bin", (void*)out->data(), out->size());
		return err;
	}
	
	return 1; /* TODO: Error => Invalid Compression Method */
}


Uint8 ckpng::DecodeInstance::getFile(){
	Uint8 data = ((Uint8)fgetc(file));
	if(feof(file)){
		return 0x00;
	}
	return data;
}

Uint8 ckpng::DecodeInstance::getBuffer(){
	if(buffer_seek>=buffer_size){
		return 0x00;
	}
	Uint8 data = ((Uint8*)buffer)[buffer_seek];
	buffer_seek++;
	return data;
}


Uint8 ckpng::DecodeInstance::get8(){
	Uint8 data = 0;
	if(mode==FILESTREAM){
		data = getFile();
	}
	else{
		data = getBuffer();
	}
	//printf("# Emmited data 0x%.2x\n", (data>>0)&0xFF);
	return data;
}

Uint16 ckpng::DecodeInstance::get16(){
	Uint16 data = 0;
	if(mode==FILESTREAM){
		data |= getFile()<<8;
		data |= getFile();
	}
	else{
		data = getBuffer();
		data = getBuffer();
	}
	//printf("# Emmited data 0x%.2x 0x%.2x\n", (data>>8)&0xFF, (data>>0)&0xFF);
	return data;
}

Uint32 ckpng::DecodeInstance::get32(){
	Uint32 data = 0;
	if(mode==FILESTREAM){
		data |= getFile()<<24;
		data |= getFile()<<16;
		data |= getFile()<<8;
		data |= getFile();
	}
	else{
		data = getBuffer();
		data = getBuffer();
		data = getBuffer();
		data = getBuffer();
	}
	//printf("# Emmited data 0x%.2x 0x%.2x 0x%.2x 0x%.2x\n", (data>>24)&0xFF, (data>>16)&0xFF, (data>>8)&0xFF, (data>>0)&0xFF);
	return data;
}

Bool ckpng::DecodeInstance::eof(){
	if(mode==FILESTREAM){
		return feof(file);
	}
	else{
		return buffer_seek>=buffer_size;
	}
}


void ckpng::DecodeInstance::seek(Uint32 position){
	if(mode==FILESTREAM){
		return_seek = ftell(file);
		fseek(file, position, SEEK_SET);
	}
	else{
		return_seek = buffer_seek;
		buffer_seek = position;
	}
}

void ckpng::DecodeInstance::seekret(){
	if(mode==FILESTREAM){
		fseek(file, return_seek, SEEK_SET);
	}
	else{
		buffer_seek = return_seek;
	}
}


Uint32 ckpng::DecodeInstance::tell(){
	if(mode==FILESTREAM){
		return ftell(file);
	}
	else{
		return buffer_seek;
	}
}


ckpng::DecodeInstance::DecodeInstance(Char* filepath){
	mode = FILESTREAM;
	file = fopen(filepath, "rb");
}

ckpng::DecodeInstance::DecodeInstance(void* buffer, Uint32 size){
	mode = DATASTREAM;
	this->buffer = buffer;
	buffer_size = size;
}

ckpng::DecodeInstance::~DecodeInstance(){
	if(mode==FILESTREAM){
		fclose(file);
	}
	else{
		/* Nothing More for now :-) */
	}
}


Bool ckpng::dec_checkFileEntry(DecodeInstance *instance){
	if(instance->get32()!=0x89504E47){
		return false;
	}
	if(instance->get32()!=0x0D0A1A0A){
		return false;
	}
	return true;
}


Uint32 ckpng::dec_getChunk(DecodeInstance *instance){
	Chunk chunk;
	chunk.length = instance->get32();
	chunk.type = instance->get32();
	if(chunk.type=='IEND'){
		instance->ended = true;
	}
	chunk.data_offset = instance->tell();
	for(Uint32 i=chunk.length; i>0; i--){
		instance->get8();
	}
	chunk.crc = instance->get32();
	
	instance->chunks.push_back(chunk);
	
	printf("\n=============CHUNK==============\n");
	printf("# Type: %c%c%c%c\n", ((chunk.type>>24)&0xFF), ((chunk.type>>16)&0xFF), ((chunk.type>>8)&0xFF), ((chunk.type>>0)&0xFF));
	printf("# Length: %d\n", chunk.length);
	printf("# Data Offset: 0x%x\n", chunk.data_offset);
	printf("# CRC: 0x%x\n", chunk.crc);
	
	Uint32 code = dec_dealChunk(instance, &chunk, chunk.type);
	return code;
}


Uint32 ckpng::dec_dealChunk(DecodeInstance *instance, Chunk *chunk, Uint32 type){
	Uint32 stype = type&0b11011111110111111101111111011111;
	printf("Type Signature is = '%c%c%c%c'\n", ((stype>>24)&0xFF), ((stype>>16)&0xFF), ((stype>>8)&0xFF), ((stype>>0)&0xFF));
	switch(stype){
		case 'IHDR':{
			instance->seek(chunk->data_offset);
			
			instance->image_header.width = instance->get32();
			instance->image_header.height = instance->get32();
			instance->image_header.bit_depth = instance->get8();
			instance->image_header.color_type = (ColorType)instance->get8();
			instance->image_header.compression_method = instance->get8();
			instance->image_header.filter_method = instance->get8();
			instance->image_header.interlace_method = instance->get8();
			
			printf("\n@ IMAGE HEADER\n");
			printf("\t* width: %d\n", instance->image_header.width);
			printf("\t* heigh: %d\n", instance->image_header.height);
			printf("\t* bit depth: %d\n", instance->image_header.bit_depth);
			printf("\t* color type: %d\n", instance->image_header.color_type);
			printf("\t* compression method: %d\n", instance->image_header.compression_method);
			printf("\t* filter method: %d\n", instance->image_header.filter_method);
			printf("\t* interlace method: %d\n", instance->image_header.interlace_method);
			
			instance->pixels.resize(instance->image_header.width*instance->image_header.height);
			
			instance->seekret();
		}
		case 'GAMA':{
			/* For now ignore */
		}
		break;
		case 'CHRM':{
			/* For now ignore */
		}
		break;
		case 'SRGB':{
			/* For now ignore */
		}
		break;
		case 'PLTE':{
			Uint32 length = chunk->length;
			
			if((length%3)!=0){
				return 2; /* TODO: Error => palette chunk may be multiple of 3 */
			}
			
			instance->seek(chunk->data_offset);
			
			while(length){
				instance->palette.entries[instance->palette.entries_count] = {
					.r = instance->get8(),
					.g = instance->get8(),
					.b = instance->get8(),
				};
				instance->palette.entries_count++;
				length -= 3;
			}
			
			instance->seekret();
		}
		break;
		case 'PHYS':{
			instance->seek(chunk->data_offset);
			
			instance->physical_sizes.pixels_per_unit_x = instance->get32();
			instance->physical_sizes.pixels_per_unit_y = instance->get32();
			instance->physical_sizes.unit_type = instance->get8();
			
			printf("\n@ IMAGE PHYSICAL SIZING\n");
			printf("\t* pixels per unit X: %d\n", instance->physical_sizes.pixels_per_unit_x);
			printf("\t* pixels per unit Y: %d\n", instance->physical_sizes.pixels_per_unit_y);
			printf("\t* unit type: %d\n", instance->physical_sizes.unit_type);
			
			instance->seekret();
		}
		break;
		case 'IDAT':{
			instance->seek(chunk->data_offset);
			
			Uint8* data = new Uint8[chunk->length];
			std::vector<Uint8> dec_data = std::vector<Uint8>(0);
			for(Int i=0; i<(chunk->length); i++){
				data[i] = instance->get8();
			}
			
			Uint32 err = ckzlib::decompress(data, chunk->length, &dec_data);
			if(err){
				return err;
			}
			
			instance->seekret();
		}
		break;
	}
	
	return 0;
}


Uint32 ckpng::decode(DecodeInstance *instance){
	if(!dec_checkFileEntry(instance)){
		return 1; //* TODO: Error => Invalid Header 
	}
	
	while(!instance->ended){
		Uint32 code = dec_getChunk(instance);
		if(code){
			return code;
		}
	}
	
	return 0;
}


void ckpng::decode(Char* filepath){
	DecodeInstance instance = DecodeInstance(filepath);
	Uint32 code = decode(&instance);
	printf("\n\nStatus returned with code error: 0x%x\n", code);
}

void ckpng::decode(void* buffer, Uint32 buffer_size){
	DecodeInstance instance = DecodeInstance(buffer, buffer_size);
	Uint32 code = decode(&instance);
	printf("\n\nStatus returned with code error: 0x%x\n", code);
}
