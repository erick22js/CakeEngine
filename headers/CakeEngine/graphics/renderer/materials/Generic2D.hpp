#ifndef cakengine_graphics_renderer_materials_generic2d_h
#define cakengine_graphics_renderer_materials_generic2d_h

#include "../ShaderProgram.hpp"


class CKGeneric2DMaterial:public CKShaderProgram{
	
private:
	static const Char* src_vertex;
	static const Char* src_fragment;
	
public:
	Int a_position;
	Int a_color;
	Int a_texuv;
	
	Int u_matworld;
	Int u_depth;
	Int u_tex0;
	
	CKGeneric2DMaterial();
	
};


#endif // cakengine_graphics_renderer_materials_generic2d_h
