#include <CakeEngine/resources/scene/Scene2D.hpp>


CKScene2D::CKScene2D(){
	
}

void CKScene2D::render(CKRenderer *renderer){
	CKMat3 tmat;
	if(view){
		view->transform();
		tmat.set(view->getMat());
	}
	else{
		tmat.identity();
	}
	render_(renderer, &tmat);
}


void CKScene2D::render(CKRenderer *renderer, CKMat3 *mat){
	
}
