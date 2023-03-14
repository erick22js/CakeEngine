#include <CakeEngine/resources/objects/Object2D.hpp>


void CKObject2D::transform(){
	matrix.identity();
	matrix.rotate(rotation);
	matrix.scale(&scale);
	matrix.translate(&position);
}

CKObject2D::CKObject2D(){
	position = CKVec2(0, 0);
	scale = CKVec2(1, 1);
	rotation = 0;
}

CKMat3 *CKObject2D::getMat(){
	return &matrix;
}

