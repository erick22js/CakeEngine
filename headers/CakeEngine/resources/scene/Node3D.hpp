#ifndef cakengine_resources_scene_node3d_h
#define cakengine_resources_scene_node3d_h

#include <iostream>
#include <vector>

#include <CakeEngine/resources/objects/Object3D.hpp>
#include <CakeEngine/graphics/renderer/Renderer.hpp>


class CKNode3D:public CKObject3D{
	
	friend class CKScene3D;
	
private:
	CKNode3D* father = nullptr;
	std::vector<CKNode3D*> children = std::vector<CKNode3D*>(0);
	
	void render_(CKRenderer *renderer, CKMat4 *mat);
	
protected:
	virtual void render(CKRenderer *renderer, CKMat4 *mat) = 0;
	
public:
	CKNode3D();
	
	std::vector<CKNode3D*> getChildren();
	
	void addChild(CKNode3D *child);
	
	Bool hasChild(CKNode3D *child);
	
	Bool removeChild(CKNode3D *child);
	
};


#endif // cakengine_resources_scene_node3d_h
