#include <CakeEngine/graphics/renderer/materials/Generic3D.hpp>


const Char* CKGeneric3DMaterial::src_vertex = "\
attribute vec3 a_position;\
attribute vec3 a_color;\
attribute vec2 a_texuv;\
uniform mat4 u_matworld;\
varying vec3 v_color;\
varying float v_depth;\
varying vec2 v_texuv;\
void main(){\
	v_color = a_color;\
	v_texuv = a_texuv;\
	gl_Position = u_matworld*vec4(a_position, 1.0);\
	v_depth = 1.0-gl_Position.z;\
}";

const Char* CKGeneric3DMaterial::src_fragment = "\
precision mediump float;\
varying vec3 v_color;\
varying vec2 v_texuv;\
varying float v_depth;\
uniform sampler2D u_tex0;\
void main(){\
	vec4 texColor = texture2D(u_tex0, v_texuv);\
	gl_FragColor = vec4(v_color, 1.0)*texColor;\
}";


CKGeneric3DMaterial::CKGeneric3DMaterial(): CKShaderProgram(src_vertex, src_fragment){
	a_position = locateAttrib("a_position", CK_TYPE_FLOAT, 3);
	a_color = locateAttrib("a_color", CK_TYPE_FLOAT, 3);
	a_texuv = locateAttrib("a_texuv", CK_TYPE_FLOAT, 2);
	
	u_matworld = locateUniform("u_matworld");
	u_tex0 = locateUniform("u_tex0");
}

