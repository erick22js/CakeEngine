#include <iostream>

#include <CakeEngine/sound/Speaker.hpp>



CKSpeaker::CKSpeaker(CKWindow *window){
	this->window = window;
}

CKSpeaker::~CKSpeaker(){
}


Bool CKSpeaker::play(CKAudio *audio){
	audio->openDevice();
	SDL_PauseAudioDevice(audio->device, 0);
}

Bool CKSpeaker::reset(CKAudio *audio){
	if(!audio->reset()){
		return false;
	}
	SDL_PauseAudioDevice(audio->device, 0);
}

Bool CKSpeaker::stop(CKAudio *audio){
	return audio->close();
}

void CKSpeaker::pause(CKAudio *audio){
	SDL_PauseAudioDevice(audio->device, 1);
}

void CKSpeaker::resume(CKAudio *audio){
	SDL_PauseAudioDevice(audio->device, 0);
}
