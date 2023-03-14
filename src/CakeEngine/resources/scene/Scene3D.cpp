#include <CakeEngine/resources/scene/Scene3D.hpp>


CKScene3D::CKScene3D(){
	
}

void CKScene3D::render(CKRenderer *renderer){
	CKMat4 tmat;
	if(view){
		view->transform();
		tmat.set(view->getMat());
	}
	else{
		tmat.identity();
	}
	render_(renderer, &tmat);
}


void CKScene3D::render(CKRenderer *renderer, CKMat4 *mat){
	
}

