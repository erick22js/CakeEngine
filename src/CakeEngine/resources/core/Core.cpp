#include <CakeEngine/resources/core/Core.hpp>



void CKCore::render(){
	renderer->copr.enableDepthTest();
	glClear(GL_DEPTH_BUFFER_BIT);
	if(enabled_3dmode&&scene3d){
		scene3d->render(renderer);
	}
	glClear(GL_DEPTH_BUFFER_BIT);
	if(enabled_2dmode&&scene2d){
		scene2d->render(renderer);
	}
}


void CKCore::e_execute(){
	e_init_();
	e_update_();
	e_end_();
}

void CKCore::e_init_(){
	window = new CKWindow("CK Game Engine", settings.window_width, settings.window_height, 0);
	renderer = new CKRenderer(window);
	inputh = new CKInputHanddler(window);
	
	e_init();
}

void CKCore::e_update_(){
	while(running){
		e_update();
		render();
		window->refresh();
		if(inputh->isQuitted()){
			running = false;
		}
	}
}

void CKCore::e_end_(){
	e_end();
	
	delete window;
	delete renderer;
	delete inputh;
}


CKCore::CKCore(CKCoreApplicationSettings *settings){
	this->settings = *settings;
}

CKCore::~CKCore(){
	
}


void CKCore::start(){
	running = true;
	e_execute();
}
