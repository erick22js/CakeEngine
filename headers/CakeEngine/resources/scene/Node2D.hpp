#ifndef cakengine_resources_scene_node2d_h
#define cakengine_resources_scene_node2d_h

#include <iostream>
#include <vector>

#include <CakeEngine/resources/objects/Object2D.hpp>
#include <CakeEngine/graphics/renderer/Renderer.hpp>


class CKNode2D:public CKObject2D{
	
	friend class CKScene2D;
	
private:
	CKNode2D* father = nullptr;
	std::vector<CKNode2D*> children = std::vector<CKNode2D*>(0);
	
	void render_(CKRenderer *renderer, CKMat3 *mat);
	
protected:
	virtual void render(CKRenderer *renderer, CKMat3 *mat) = 0;
	
public:
	CKNode2D();
	
	void addChild(CKNode2D *child);
	
	Bool hasChild(CKNode2D *child);
	
	Bool removeChild(CKNode2D *child);
	
};


#endif // cakengine_resources_scene_node2d_h
