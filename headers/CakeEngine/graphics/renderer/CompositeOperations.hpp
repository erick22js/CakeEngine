#ifndef cakengine_graphics_renderer_compositeoperations_h
#define cakengine_graphics_renderer_compositeoperations_h

#include "../opengl/opengl.hpp"


class CKCompositeOperations{
	
	friend class CKRenderer;
	
private:
	CKCompositeOperations(){};
	
public:
	void enableDepthTest();
	void enableStencilTest();
	void enableFaceCulling(CKFaceCullingMode mode = CK_FACECULLINGMODE_BACK);
	void enableOpacity();
	
	void disableDepthTest();
	void disableStencilTest();
	void disableFaceCulling();
	void disableOpacity();
	
	void setFrontFace(CKFrontFace front);
	
};


#endif // cakengine_graphics_renderer_compositeoperations_h
