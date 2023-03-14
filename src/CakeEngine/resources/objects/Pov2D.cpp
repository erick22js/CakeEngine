#include <CakeEngine/resources/objects/Pov2D.hpp>


CKPov2D::CKPov2D(Float width, Float height){
	this->width = width;
	this->height = height;
	resetPerspective();
}

CKMat3 *CKPov2D::getMat(){
	return &matrix;
}

void CKPov2D::resetPerspective(){
	pmatrix.identity();
	pmatrix.scale(1.0f/width, 1.0f/height);
}

void CKPov2D::transform(){
	matrix.set(&pmatrix);
	matrix.rotate(rotation);
	matrix.translate(&position);
}
