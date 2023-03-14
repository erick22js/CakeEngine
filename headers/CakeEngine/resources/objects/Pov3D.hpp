#ifndef cakengine_resources_core_pov3d_h
#define cakengine_resources_core_pov3d_h

#include "../../math/vector/Vector3.hpp"
#include "../../math/matrix/Matrix4.hpp"


class CKPov3D{
	
private:
	CKMat4 pmatrix;
	CKMat4 matrix;
	
public:
	/* Main object properties */
	CKVec3 position;
	CKVec3 rotation;
	
	/* Camera Main properties */
	Float near, far, fov, aspectRatio;
	
	CKPov3D(Float near, Float far, Float fov, Float aspectRatio);
	
	CKMat4 *getMat();
	
	void resetPerspective();
	void transform();
	
};

#endif // cakengine_resources_core_camera3d_h
