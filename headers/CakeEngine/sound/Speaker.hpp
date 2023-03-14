#ifndef cakengine_audio_speaker_h
#define cakengine_audio_speaker_h

#include <CakeEngine/graphics/window/Window.hpp>
#include <CakeEngine/sound/Audio.hpp>


class CKSpeaker{
	
private:
	CKWindow *window = nullptr;
	
public:
	CKSpeaker(CKWindow *window);
	
	~CKSpeaker();
	
	Bool play(CKAudio *audio);
	Bool reset(CKAudio *audio);
	Bool stop(CKAudio *audio);
	
	void pause(CKAudio *audio);
	void resume(CKAudio *audio);
	
};


#endif // cakengine_audio_speaker_h
