#ifndef cakengine_sound_audio_h
#define cakengine_sound_audio_h

#include <CakeEngine/sound/AudioBuffer.hpp>


class CKAudio{
	
	friend class CKSpeaker;
	
private:
	SDL_AudioDeviceID device;
	Bool open_device = false;
	
	CKAudioBuffer *buffer = nullptr;
	Bool ext_buffer = false;
	
	Bool openDevice();
	
	Bool reset();
	
	Bool close();
	
public:
	CKAudio(Char* wavPath);
	CKAudio(CKAudioBuffer *buffer);
	
	~CKAudio();
	
	CKAudioBuffer *getBuffer();
	
	Bool loadBuffer(CKAudioBuffer *buffer);
	
	Bool loadWav(Char* wavPath);
	
};


#endif // cakengine_sound_audio_h
