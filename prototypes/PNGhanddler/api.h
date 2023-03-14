#ifndef cakengine_api_h
#define cakengine_api_h

#include <cstdint>

typedef bool Bool;

typedef char Char;

typedef unsigned int Uint;
typedef int Int;

typedef intptr_t IntPtr;

typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;
typedef uint64_t Uint64;

typedef int8_t Sint8;
typedef int16_t Sint16;
typedef int32_t Sint32;
typedef int64_t Sint64;

typedef float Float32;
typedef double Float64;

typedef float Float;
typedef double Double;

#define Atomic(T) atomic T

#endif // API_H_INCLUDED
