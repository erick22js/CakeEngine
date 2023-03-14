#include <CakeEngine/resources/objects/Object3D.hpp>


void CKObject3D::transform(){
	matrix.identity();
	matrix.rotateX(rotation.x);
	matrix.rotateY(rotation.y);
	matrix.rotateZ(rotation.z);
	matrix.scale(&scale);
	matrix.translate(&position);
}

CKObject3D::CKObject3D(){
	position = CKVec3(0, 0, 0);
	scale = CKVec3(1, 1, 1);
	rotation = CKVec3(0, 0, 0);
}

CKMat4 *CKObject3D::getMat(){
	return &matrix;
}
