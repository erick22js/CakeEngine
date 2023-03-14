#include <CakeEngine/execution/Thread.hpp>



CKThread::CKThread(Int (*func)(void* arg)){
	this->func = func;
}

CKThread::~CKThread(){
	th.detach();
}


void CKThread::init(void* arg){
	if(running){
		return;
	}
	th = std::thread(func, arg);
	running = true;
}

void CKThread::join(){
	if(running){
		th.join();
	}
	running = false;
}
