#include <CakeEngine/graphics/renderer/materials/ModelMaterial.hpp>



const Char* CKModelMaterial::src_vertex = "\
attribute vec3 a_position;\
attribute vec3 a_normal;\
attribute vec3 a_color;\
attribute vec2 a_tex0uv;\
uniform mat4 u_mat;\
varying vec3 v_color;\
varying vec2 v_tex0uv;\
void main(){\
	v_tex0uv = a_tex0uv;\
	gl_Position = u_mat*vec4(a_position, 1.0);\
	vec4 t_normal = normalize(u_mat*vec4(a_normal, 1.0));\
	v_color = a_color*a_normal;\
}";

const Char* CKModelMaterial::src_fragment = "\
varying vec3 v_color;\
varying vec2 v_tex0uv;\
uniform sampler2D u_tex0;\
void main(){\
	vec4 tex0Color = texture2D(u_tex0, v_tex0uv);\
	gl_FragColor = vec4(v_color, 1.0)*tex0Color;\
}";


CKModelMaterial::CKModelMaterial(): CKShaderProgram(src_vertex, src_fragment){
	a_position = locateAttrib("a_position", CK_TYPE_FLOAT, 3);
	a_normal = locateAttrib("a_normal", CK_TYPE_FLOAT, 3);
	a_color = locateAttrib("a_color", CK_TYPE_FLOAT, 3);
	a_tex0uv = locateAttrib("a_tex0uv", CK_TYPE_FLOAT, 3);
	
	u_mat = locateUniform("u_mat");
	u_tex0 = locateUniform("u_tex0");
}
