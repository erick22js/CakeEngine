#include <string.h>

#include <CakeEngine/graphics/renderer/ShaderAttribs.hpp>



CKShaderAttribs::CKShaderAttribs(){
	attribs = std::vector<CKShaderAttrib>(0);
}

Int CKShaderAttribs::pushAttrib(const Char* name, GLuint id, CKType type, Int length){
	CKShaderAttrib attrib = {
		.name = name,
		.id = id,
		.type = type,
		.length = length,
		.offset = this->endoffset,
	};
	this->size += length*type.size;
	this->endoffset += length*type.size;
	attribs.push_back(attrib);
	return attribs.size()-1;
}

Int CKShaderAttribs::has(const Char* name){
	Int offset = 0;
	for(CKShaderAttrib attrib:attribs){
		if(strcmp(attrib.name, name)==0){
			return offset;
		}
		offset++;
	}
	return -1;
}

Int CKShaderAttribs::has(GLuint id){
	Int offset = 0;
	for(CKShaderAttrib attrib:attribs){
		if(attrib.id==id){
			return offset;
		}
		offset++;
	}
	return -1;
}

Int CKShaderAttribs::getLength(){
	return attribs.size();
}

Int CKShaderAttribs::getVertexSize(){
	return size;
}

CKShaderAttrib *CKShaderAttribs::getAttrib(Int index){
	return &attribs[index];
}
