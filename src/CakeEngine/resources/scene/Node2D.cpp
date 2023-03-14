#include <CakeEngine/resources/scene/Node2D.hpp>



void CKNode2D::render_(CKRenderer *renderer, CKMat3 *mat){
	transform();
	CKMat3 tmat = CKMat3(mat);
	tmat.mul(&matrix);
	
	render(renderer, &tmat);
	
	Int quant = children.size();
	for(Int ci=0; ci<quant; ci++){
		children[ci]->render_(renderer, &tmat);
	}
}


CKNode2D::CKNode2D(){
	
}


void CKNode2D::addChild(CKNode2D *child){
	if(child->father==this){
		return;
	}
	child->father = this;
	children.push_back(child);
}

Bool CKNode2D::hasChild(CKNode2D *child){
	return child->father==this;
}

Bool CKNode2D::removeChild(CKNode2D *child){
	if(child->father==this){
		for(Int ci=0; ci<children.size(); ci++){
			if(children[ci]==child){
				children.erase(children.begin()+ci);
				break;
			}
		}
		child->father = nullptr;
		return true;
	}
	return false;
}
