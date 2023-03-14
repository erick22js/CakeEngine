#ifndef cakengine_resources_core_object3d_h
#define cakengine_resources_core_object3d_h

#include "../../math/vector/Vector3.hpp"
#include "../../math/matrix/Matrix4.hpp"


class CKObject3D{
	
protected:
	CKMat4 matrix;
	
	void transform();
	
public:
	/* Main object properties */
	CKVec3 position;
	CKVec3 scale;
	CKVec3 rotation;
	
	CKObject3D();
	
	CKMat4 *getMat();
	
};


#endif // cakengine_resources_core_object3d_h
