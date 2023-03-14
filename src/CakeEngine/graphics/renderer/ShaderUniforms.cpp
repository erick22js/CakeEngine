#include <string.h>

#include <CakeEngine/graphics/renderer/ShaderUniforms.hpp>


CKShaderUniforms::CKShaderUniforms(){
	uniforms = std::vector<CKShaderUniform>(0);
}

void CKShaderUniforms::pushUniform(const Char* name, GLuint id){
	CKShaderUniform uniform = {
		.name = name,
		.id = id,
	};
	uniforms.push_back(uniform);
}

Sint32 CKShaderUniforms::has(const Char* name){
	Sint32 index = 0;
	for(CKShaderUniform uniform:uniforms){
		if(strcmp(uniform.name, name)==0){
			return index;
		}
		index++;
	}
	return -1;
}

Sint32 CKShaderUniforms::has(GLuint id){
	Sint32 index = 0;
	for(CKShaderUniform uniform:uniforms){
		if(uniform.id==id){
			return index;
		}
		index++;
	}
	return -1;
}

CKShaderUniform* CKShaderUniforms::getUniform(Int index){
	return &uniforms[index];
}
