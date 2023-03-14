#ifndef cakengine_resources_core_object2d_h
#define cakengine_resources_core_object2d_h

#include "../../math/vector/Vector2.hpp"
#include "../../math/matrix/Matrix3.hpp"


class CKObject2D{
	
protected:
	CKMat3 matrix;
	
	void transform();
	
public:
	/* Main object properties */
	CKVec2 position;
	CKVec2 scale;
	Float rotation;
	
	CKObject2D();
	
	CKMat3 *getMat();
	
};


#endif // cakengine_resources_scene_object2d_h
