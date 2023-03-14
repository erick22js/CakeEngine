#include <CakeEngine/graphics/renderer/materials/Generic2D.hpp>


const Char* CKGeneric2DMaterial::src_vertex = "\
attribute vec2 a_position;\
attribute vec3 a_color;\
attribute vec2 a_texuv;\
uniform mat3 u_matworld;\
uniform float u_depth;\
varying vec3 v_color;\
varying vec2 v_texuv;\
void main(){\
	v_color = a_color;\
	v_texuv = a_texuv;\
	gl_Position = vec4(u_matworld*vec3(a_position, u_depth), 1.0);\
}";

const Char* CKGeneric2DMaterial::src_fragment = "\
precision mediump float;\
varying vec3 v_color;\
varying vec2 v_texuv;\
uniform sampler2D u_tex0;\
void main(){\
	vec4 texColor = texture2D(u_tex0, v_texuv);\
	gl_FragColor = vec4(v_color, 1.0)*texColor;\
}";


CKGeneric2DMaterial::CKGeneric2DMaterial(): CKShaderProgram(src_vertex, src_fragment){
	a_position = locateAttrib("a_position", CK_TYPE_FLOAT, 2);
	a_color = locateAttrib("a_color", CK_TYPE_FLOAT, 3);
	a_texuv = locateAttrib("a_texuv", CK_TYPE_FLOAT, 2);
	
	u_matworld = locateUniform("u_matworld");
	u_depth = locateUniform("u_depth");
	u_tex0 = locateUniform("u_tex0");
}

