#ifndef cakengine_graphics_window_h
#define cakengine_graphics_window_h

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "../../api.hpp"


class CKWindow{
	
	friend class CKRenderer;
	friend class CKSpeaker;
	friend class CKInputHanddler;
	
private:
	SDL_Window *window;
	SDL_Event event;
	SDL_GLContext gl;
	
	Char* title;
	Int x, y, width, height;
	Uint32 flags;
	
	static Bool video_init;
	
	class CKInputHanddler *i_handler = nullptr;
	
	void init();
	void terminate();
	
public:
	CKWindow();
	CKWindow(Bool init);
	CKWindow(Char* title, Int flags);
	CKWindow(Char* title, Int width, Int height, Int flags);
	CKWindow(Int width, Int height, Int flags);
	CKWindow(Char* title, Int x, Int y, Int width, Int height, Int flags);
	CKWindow(Int x, Int y, Int width, Int height, Int flags);
	
	~CKWindow();
	
	void getSize(Int *x, Int *y);
	void setSize(Int x, Int y);
	
	void setViewport(Int x, Int y, Int w, Int h);
	void resetViewport();
	
	void refresh();
	
};




#endif // cakengine_graphics_window_h
