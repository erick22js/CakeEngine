#ifndef cakengine_resources_core_pov2d_h
#define cakengine_resources_core_pov2d_h

#include "../../math/vector/Vector2.hpp"
#include "../../math/matrix/Matrix3.hpp"


class CKPov2D{
	
private:
	CKMat3 pmatrix;
	CKMat3 matrix;
	
public:
	/* Main object properties */
	CKVec2 position;
	Float rotation;
	
	/* Camera Main properties */
	Float width, height;
	
	CKPov2D(Float width, Float height);
	
	CKMat3 *getMat();
	
	void resetPerspective();
	void transform();
	
};

#endif // cakengine_resources_core_camer2d_h
