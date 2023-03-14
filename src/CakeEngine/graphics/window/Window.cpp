#include <CakeEngine/graphics/window/Window.hpp>
#include <CakeEngine/input/InputHanddler.hpp>

#include <iostream>

bool CKWindow::video_init = false;

void CKWindow::init(){
	if(!CKWindow::video_init){
		if(SDL_Init(SDL_INIT_EVERYTHING)){
			std::cerr << "Error in Window Initializing;\nSDL_Error => " << SDL_GetError() << std::endl;
		}
	}
	
	window = SDL_CreateWindow(title, x, y, width, height, flags|SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	gl = SDL_GL_CreateContext(window);
	
	if(!CKWindow::video_init){
		CKWindow::video_init = true;
		glewInit();
	}
	/* TODO: Error handling for each function */
}

void CKWindow::terminate(){
	SDL_GL_DeleteContext(gl);
	SDL_DestroyWindow(window);
}

CKWindow::CKWindow(){
	this->title = "";
	this->x = this->y = SDL_WINDOWPOS_CENTERED;
	this->width = 800;
	this->height = 480;
	this->flags = 0;
	init();
}

CKWindow::CKWindow(Bool init_win){
	this->title = "";
	this->x = this->y = SDL_WINDOWPOS_CENTERED;
	this->width = 800;
	this->height = 480;
	this->flags = 0;
	if(init_win){
		init();
	}
}

CKWindow::CKWindow(Char* title, Int flags){
	this->title = title;
	this->x = this->y = SDL_WINDOWPOS_CENTERED;
	this->width = 800;
	this->height = 480;
	this->flags = flags;
	init();
}

CKWindow::CKWindow(Char* title, Int width, Int height, Int flags){
	this->title = title;
	this->x = this->y = SDL_WINDOWPOS_CENTERED;
	this->width = width;
	this->height = height;
	this->flags = flags;
	init();
}

CKWindow::CKWindow(Int width, Int height, Int flags){
	this->title = title;
	this->x = this->y = SDL_WINDOWPOS_CENTERED;
	this->width = width;
	this->height = height;
	this->flags = flags;
	init();
}

CKWindow::CKWindow(Char* title, Int x, Int y, Int width, Int height, Int flags){
	this->title = title;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->flags = flags;
	init();
}

CKWindow::CKWindow(Int x, Int y, Int width, Int height, Int flags){
	this->title = title;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->flags = flags;
	init();
}

CKWindow::~CKWindow(){
	terminate();
	SDL_Quit();
}

void CKWindow::getSize(Int *width, Int *height){
	*width = this->width;
	*height = this->height;
}

void CKWindow::setSize(Int width, Int height){
	this->width = width;
	this->height = height;
	SDL_SetWindowSize(window, width, height);
}


void CKWindow::refresh(){
	while(SDL_PollEvent(&event)){
		if(event.type==SDL_WINDOWEVENT){
			SDL_GetWindowSize(window, &this->width, &this->height);
		}
		if(i_handler){
			i_handler->handdleEvent(&event);
		}
		else if(event.type==SDL_QUIT){
			exit(0);
		}
	}
	SDL_GL_SwapWindow(window);
	glViewport(0, 0, this->width, this->height);
}

void CKWindow::setViewport(Int x, Int y, Int w, Int h){
	glViewport(x, y, w, h);
}

void CKWindow::resetViewport(){
	glViewport(0, 0, this->width, this->height);
}
