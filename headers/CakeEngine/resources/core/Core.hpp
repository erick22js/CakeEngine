#ifndef cakengine_resources_core_h
#define cakengine_resources_core_h

#include <CakeEngine/api.hpp>
#include <CakeEngine/resources/core/CoreApplicationSettings.hpp>
#include <CakeEngine/graphics/window/Window.hpp>
#include <CakeEngine/graphics/renderer/Renderer.hpp>
#include <CakeEngine/input/InputHanddler.hpp>

#include <CakeEngine/resources/scene/Scene2D.hpp>
#include <CakeEngine/resources/scene/Scene3D.hpp>


class CKCore{
	
private:
	void e_execute();
	void e_init_();
	void e_update_();
	void e_end_();
	
	CKCoreApplicationSettings settings;
	
	Bool running = false;
	
	void render();
	
protected:
	CKWindow *window = nullptr;
	CKRenderer *renderer = nullptr;
	CKInputHanddler *inputh = nullptr;
	
	CKScene2D *scene2d = nullptr;
	CKScene3D *scene3d = nullptr;
	
	Bool enabled_2dmode = true;
	Bool enabled_3dmode = true;
	
	virtual void e_init() = 0;
	virtual void e_update() = 0;
	virtual void e_end() = 0;
	
public:
	CKCore(CKCoreApplicationSettings *settings);
	~CKCore();
	
	void start();
};


#endif // cakengine_resources_core_h
