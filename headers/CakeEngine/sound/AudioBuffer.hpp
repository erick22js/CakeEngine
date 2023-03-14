#ifndef cakengine_audio_audiobuffer_h
#define cakengine_audio_audiobuffer_h

#include <SDL2/SDL.h>

#include <CakeEngine/api.hpp>


class CKAudioBuffer{
	
	friend class CKAudio;
	friend class CKSpeaker;
	
private:
	SDL_AudioSpec spec;
	Uint32 length;
	Uint8* buffer;
	
	CKAudioBuffer();
	
public:
	~CKAudioBuffer();
	
};


#endif // cakengine_audio_audiobuffer_h
