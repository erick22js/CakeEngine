#include <CakeEngine/input/InputHanddler.hpp>


void CKInputHanddler::handdleEvent(SDL_Event *event){
	switch(event->type){
		case SDL_KEYDOWN:{
			if(onKeyDown){
				onKeyDown(event->key.keysym.sym, event->key.keysym.mod);
			}
			keys[event->key.keysym.sym] = true;
			mod_keys = event->key.keysym.mod;
		}
		break;
		case SDL_KEYUP:{
			if(onKeyUp){
				onKeyUp(event->key.keysym.sym, event->key.keysym.mod);
			}
			keys[event->key.keysym.sym] = false;
			mod_keys = event->key.keysym.mod;
		}
		break;
		case SDL_QUIT:{
			if(onQuit){
				onQuit();
			}
			quitted = true;
		}
		break;
		default:{
			
		}
	}
}

CKInputHanddler::CKInputHanddler(CKWindow *window){
	this->window = window;
	window->i_handler = this;
}

Bool CKInputHanddler::isQuitted(){
	return quitted;
}

Bool CKInputHanddler::isKeyPressed(Uint32 code){
	return keys[code]==true;
}

Uint16 CKInputHanddler::getModKeys(){
	return mod_keys;
}
