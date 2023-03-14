#ifndef cakengine_resources_scene2d_h
#define cakengine_resources_scene2d_h

#include <CakeEngine/resources/scene/Node2D.hpp>
#include <CakeEngine/resources/objects/Pov2D.hpp>


class CKScene2D:public CKNode2D{
	
private:
	CKPov2D *view = nullptr;
	
protected:
	void render(CKRenderer *renderer, CKMat3 *mat);
	
public:
	CKScene2D();
	
	void render(CKRenderer *renderer);
	
	
};


#endif // cakengine_resources_scene2d_h
