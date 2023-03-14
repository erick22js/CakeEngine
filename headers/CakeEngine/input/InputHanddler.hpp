#ifndef cakengine_input_inputhanddler_h
#define cakengine_input_inputhanddler_h

#include <iostream>
#include <map>

#include "../graphics/window/Window.hpp"


#define CKI_MOD_LCTRL KMOD_LCTRL
#define CKI_MOD_RCTRL KMOD_RCTRL
#define CKI_MOD_LSHIFT KMOD_LSHIFT
#define CKI_MOD_RSHIFT KMOD_RSHIFT
#define CKI_MOD_LALT KMOD_LALT
#define CKI_MOD_RALT KMOD_RALT
#define CKI_MOD_CAPS KMOD_CAPS


class CKInputHanddler{
	
	friend class CKWindow;
	
private:
	CKWindow *window;
	
	std::map<Uint32, Bool> keys;
	Uint16 mod_keys = 0;
	
	Bool quitted = false;
	
	void handdleEvent(SDL_Event *event);
	
public:
	/* Callback Functions */
	void (*onKeyDown)(Uint32 code, Uint16 mod) = nullptr;
	void (*onKeyUp)(Uint32 code, Uint16 mod) = nullptr;
	
	void (*onQuit)() = nullptr;
	
	CKInputHanddler(CKWindow *window);
	
	/* KeyInput Functions */
	Bool isQuitted();
	Bool isKeyPressed(Uint32 code);
	Uint16 getModKeys();
	
};


#endif // cakengine_input_inputhanddler_h
