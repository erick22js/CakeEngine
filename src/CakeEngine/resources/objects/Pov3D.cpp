#include <CakeEngine/resources/objects/Pov3D.hpp>


CKPov3D::CKPov3D(Float near, Float far, Float fov, Float aspectRatio){
	this->near = near;
	this->far = far;
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	resetPerspective();
}

CKMat4 *CKPov3D::getMat(){
	return &matrix;
}

void CKPov3D::resetPerspective(){
	pmatrix.identity();
	pmatrix.setToProjection(near, far, fov, aspectRatio);
}

void CKPov3D::transform(){
	matrix.set(&pmatrix);
	matrix.rotateX(rotation.x);
	matrix.rotateY(rotation.y);
	matrix.rotateZ(rotation.z);
	matrix.translate(&position);
}
