#ifndef PNGHANDDLER_H_INCLUDED
#define PNGHANDDLER_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <vector>

#include "api.h"


void log_bin(Char *name_file, void* data, Uint32 size);

class ckzlib{
	
private:
	typedef struct ifstream{
		void* buffer = nullptr;
		Uint32 length = 0;
		Uint32 offset_byte = 0;
		Uint8 offset_bit = 0;
		
		void advanceBits(Uint32 bits);
		void advanceBytes(Uint32 bytes);
		
		void seekSet(Uint32 bytes, Uint32 bits);
		void seekCur(Sint32 bytes, Sint32 bits);
		void seekEnd(Sint32 bytes, Sint32 bits);
		
		Bool ended();
		
		Uint32 read32();
		Uint32 fetchBits(Uint32 bits);
	}ifstream;
	
	typedef struct huffmantable{
		struct{
			Uint16 sym:9;
			Uint16 ebits:7;
		}table[512];
		
		void init();
	}huffmantable;
	
	static constexpr const int codelen_lengths_order[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
	
	static Uint32 inf_init_hdyn(ifstream *stream);
	
	static Uint32 inf_block(ifstream *stream, std::vector<Uint8> *out);
	
	static Uint32 inflate(Uint8* stream_u8, Uint32 length, std::vector<Uint8> *out);
	
public:
	static Uint32 decompress(Uint8* stream_u8, Uint32 length, std::vector<Uint8>* out);
	
};

class ckpng{
	
private:
	typedef enum InstanceMode{
		DATASTREAM,
		FILESTREAM
	}InstanceMode;
	
	typedef enum ColorType{
		CT_GRAY = 0,
		CT_RGB = 2,
		CT_PALINDEX = 3,
		CT_GRAYALPHA = 4,
		CT_RGBALPHA = 6,
	}ColorType;
	
	struct Chunk{
		Uint32 length;
		Uint32 type;
		Uint32 data_offset;
		Uint32 crc;
	};
	
	struct Pixel{
		union{
			struct{
				Uint16 r, g, b, a;
			}color;
			Uint32 index;
		}data;
	};
	
	class DecodeInstance{
		
	public:
		InstanceMode mode = DATASTREAM;
		void* buffer = nullptr;
		Uint32 buffer_size = 0;
		Uint32 buffer_seek = 0;
		
		FILE *file = nullptr;
		
		Uint32 return_seek = 0;
		
		std::vector<Chunk> chunks = std::vector<Chunk>(0);
		Bool ended = false;
		
		struct{
			Uint32 width = 0, height = 0;
			Uint8 bit_depth = 0;
			ColorType color_type:8;
			Uint8 compression_method = 0;
			Uint8 filter_method = 0;
			Uint8 interlace_method = 0;
		}image_header;
		
		struct{
			struct{
				Uint8 r, g, b;
			}entries[256];
			Uint32 entries_count = 0;
		}palette;
		
		struct{
			Uint32 pixels_per_unit_x = 0;
			Uint32 pixels_per_unit_y = 0;
			Uint8 unit_type = 0;
		}physical_sizes;
		
		std::vector<Pixel> pixels = std::vector<Pixel>(0);
		
		Uint8 getFile();
		Uint8 getBuffer();
		
		Uint8 get8();
		Uint16 get16();
		Uint32 get32();
		
		Bool eof();
		
		void seek(Uint32 position);
		void seekret();
		Uint32 tell();
		
		DecodeInstance(Char* filepath);
		DecodeInstance(void* buffer, Uint32 size);
		~DecodeInstance();
		
	};
	
	static Bool dec_checkFileEntry(DecodeInstance *instance);
	
	static Uint32 dec_getChunk(DecodeInstance *instance);
	
	static Uint32 dec_dealChunk(DecodeInstance *instance, Chunk *chunk, Uint32 type);
	
	static Uint32 decode(DecodeInstance *instance);
	
public:
	static void decode(Char* filepath);
	static void decode(void* buffer, Uint32 size);
	
};


#endif // PNGHANDDLER_H_INCLUDED
