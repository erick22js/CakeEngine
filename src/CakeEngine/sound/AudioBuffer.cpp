#include <iostream>

#include <CakeEngine/sound/AudioBuffer.hpp>



CKAudioBuffer::CKAudioBuffer(){
	
}

CKAudioBuffer::~CKAudioBuffer(){
	SDL_FreeWAV(buffer);
}
