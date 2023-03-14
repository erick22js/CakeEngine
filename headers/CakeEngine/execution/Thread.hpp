#ifndef cakengine_execution_thread_h
#define cakengine_execution_thread_h

#include <iostream>
#include <thread>
#include <SDL2/SDL_thread.h>

#include "../api.hpp"



class CKThread{
	
private:
	std::thread th;
	
	Int (*func)(void* arg) = nullptr;
	void* args = nullptr;
	
	Bool running = false;
	
public:
	CKThread(Int (*func)(void* arg));
	~CKThread();
	
	void init(void* arg);
	
	void join();
	
};


#endif // cakengine_execution_thread_h
