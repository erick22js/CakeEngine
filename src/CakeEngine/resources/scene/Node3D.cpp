#include <CakeEngine/resources/scene/Node3D.hpp>



void CKNode3D::render_(CKRenderer *renderer, CKMat4 *mat){
	transform();
	CKMat4 tmat = CKMat4(mat);
	tmat.mul(&matrix);
	
	render(renderer, &tmat);
	
	Int quant = children.size();
	for(Int ci=0; ci<quant; ci++){
		children[ci]->render_(renderer, &tmat);
	}
}


CKNode3D::CKNode3D(){
	
}


std::vector<CKNode3D*> CKNode3D::getChildren(){
	std::vector<CKNode3D*> rchildren = std::vector<CKNode3D*>(0);
	for(CKNode3D *child:children){
		rchildren.push_back(child);
	}
	return rchildren;
}


void CKNode3D::addChild(CKNode3D *child){
	if(child->father==this){
		return;
	}
	child->father = this;
	children.push_back(child);
}

Bool CKNode3D::hasChild(CKNode3D *child){
	return child->father==this;
}

Bool CKNode3D::removeChild(CKNode3D *child){
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
