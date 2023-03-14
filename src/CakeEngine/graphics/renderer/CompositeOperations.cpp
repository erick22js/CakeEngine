#include <CakeEngine/graphics/renderer/CompositeOperations.hpp>


void CKCompositeOperations::enableDepthTest(){
	glEnable(GL_DEPTH_TEST);
}

void CKCompositeOperations::enableStencilTest(){
	glEnable(GL_STENCIL_TEST);
}

void CKCompositeOperations::enableFaceCulling(CKFaceCullingMode mode){
	glEnable(GL_CULL_FACE);
	glCullFace(mode);
}

void CKCompositeOperations::enableOpacity(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void CKCompositeOperations::disableDepthTest(){
	glDisable(GL_DEPTH_TEST);
}

void CKCompositeOperations::disableStencilTest(){
	glDisable(GL_STENCIL_TEST);
}

void CKCompositeOperations::disableFaceCulling(){
	glDisable(GL_CULL_FACE);
}

void CKCompositeOperations::disableOpacity(){
	glDisable(GL_BLEND);
}


void CKCompositeOperations::setFrontFace(CKFrontFace front){
	glFrontFace(front);
}

