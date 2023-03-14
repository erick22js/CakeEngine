#ifndef cakengine_resources_scene3d_h
#define cakengine_resources_scene3d_h

#include <CakeEngine/resources/scene/Node3D.hpp>
#include <CakeEngine/resources/objects/Pov3D.hpp>


class CKScene3D:public CKNode3D{
	
private:
	
	
protected:
	void render(CKRenderer *renderer, CKMat4 *mat);
	
public:
	CKPov3D *view = nullptr;
	
	CKScene3D();
	
	void render(CKRenderer *renderer);
	
};


#endif // cakengine_resources_scene3d_h
