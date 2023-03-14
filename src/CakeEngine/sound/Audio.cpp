#include <iostream>

#include <CakeEngine/sound/Audio.hpp>



Bool CKAudio::openDevice(){
	if(!open_device){
		device = SDL_OpenAudioDevice(NULL, 0, &buffer->spec, NULL, 0);
		open_device = true;
		SDL_QueueAudio(device, buffer->buffer, buffer->length);
		
		if(!device){
			std::cerr << "Error on loading SDL audio device" << std::endl;
		}
	}
	return true;
}

Bool CKAudio::reset(){
	if(open_device){
		close();
	}
	return openDevice();
}


Bool CKAudio::close(){
	if(open_device){
		SDL_CloseAudioDevice(device);
		open_device = false;
	}
	return true;
}


CKAudio::CKAudio(CKAudioBuffer *buffer){
	this->buffer = buffer;
	ext_buffer = true;
	
	reset();
}

CKAudio::CKAudio(Char* wavPath){
	buffer = new CKAudioBuffer();
	if(!SDL_LoadWAV(wavPath, &buffer->spec, &buffer->buffer, &buffer->length)){
		std::cerr << "Error, failed to load Wav file! Cause: " << SDL_GetError() << std::endl;
	}
	
	reset();
}

CKAudio::~CKAudio(){
	if(!ext_buffer){
		delete buffer;
	}
	
	SDL_CloseAudioDevice(device);
}


CKAudioBuffer *CKAudio::getBuffer(){
	return buffer;
}


Bool CKAudio::loadBuffer(CKAudioBuffer *buffer){
	if(this->buffer&&(!ext_buffer)){
		delete buffer;
	}
	
	this->buffer = buffer;
	ext_buffer = true;
	
	reset();
}


Bool CKAudio::loadWav(Char* wavPath){
	if(this->buffer&&(!ext_buffer)){
		delete buffer;
	}
	
	this->buffer = new CKAudioBuffer();
	if(!SDL_LoadWAV(wavPath, &buffer->spec, &buffer->buffer, &buffer->length)){
		std::cerr << "Error, failed to load Wav file! Cause: " << SDL_GetError() << std::endl;
	}
	ext_buffer = false;
	
	reset();
}
