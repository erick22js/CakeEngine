#ifndef cakengine_graphics_renderer_materials_modelmaterial_h
#define cakengine_graphics_renderer_materials_modelmaterial_h

#include <CakeEngine/graphics/renderer/ShaderProgram.hpp>


class CKModelMaterial:public CKShaderProgram{
	
private:
	static const Char* src_vertex;
	static const Char* src_fragment;
	
public:
	Int a_position;
	Int a_normal;
	Int a_color;
	Int a_tex0uv;
	
	Int u_mat;
	Int u_tex0;
	
	CKModelMaterial();
	
};


#endif // cakengine_graphics_renderer_materials_modelmaterial_h
