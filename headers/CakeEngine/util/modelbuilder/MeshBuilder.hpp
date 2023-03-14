#ifndef cakengine_util_meshbuilder_h
#define cakengine_util_meshbuilder_h

#include <iostream>
#include <vector>

#include "../../graphics/renderer/Mesh.hpp"


class CKMeshBuilder{
	
private:
	CKShaderAttribs *attribs;
	
	std::vector<Uint8> vertices = std::vector<Uint8>(0);
	std::vector<Uint16> indices = std::vector<Uint16>(0);
	
	Uint16 vindex = 0;
	Uint16 tindex = 0;
	
	Bool uses_index = false;
	
	void* getVertex();
	
public:
	CKMeshBuilder(CKShaderAttribs *attribs);
	~CKMeshBuilder();
	
	Uint16 addVertex();
	Uint16 addIndices(Uint16 v1, Uint16 v2, Uint16 v3);
	
	
	template<typename T> void setAttrib1v(Int attribid, T val){
		void* vertex = getVertex();
		CKShaderAttrib* attrib = attribs->getAttrib(attribid);
		
		vertex += (IntPtr)attrib->offset;
		*((T*)vertex) = val;
	}

	template<typename T> void setAttrib2v(Int attribid, T val1, T val2){
		void* vertex = getVertex();
		CKShaderAttrib* attrib = attribs->getAttrib(attribid);
		
		vertex += (IntPtr)attrib->offset;
		*((T*)vertex) = val1;
		vertex += (IntPtr)attrib->type.size;
		*((T*)vertex) = val2;
	}

	template<typename T> void setAttrib3v(Int attribid, T val1, T val2, T val3){
		void* vertex = getVertex();
		CKShaderAttrib* attrib = attribs->getAttrib(attribid);
		
		vertex += (IntPtr)attrib->offset;
		*((T*)vertex) = val1;
		vertex += (IntPtr)attrib->type.size;
		*((T*)vertex) = val2;
		vertex += (IntPtr)attrib->type.size;
		*((T*)vertex) = val3;
	}

	template<typename T> void setAttrib4v(Int attribid, T val1, T val2, T val3, T val4){
		void* vertex = getVertex();
		CKShaderAttrib* attrib = attribs->getAttrib(attribid);
		
		vertex += (IntPtr)attrib->offset;
		*((T*)vertex) = val1;
		vertex += (IntPtr)attrib->type.size;
		*((T*)vertex) = val2;
		vertex += (IntPtr)attrib->type.size;
		*((T*)vertex) = val3;
		vertex += (IntPtr)attrib->type.size;
		*((T*)vertex) = val4;
	}

	template<typename T> void setAttribnv(Int attribid, T* vals, Int length){
		void* vertex = getVertex();
		CKShaderAttrib* attrib = attribs->getAttrib(attribid);
		
		vertex += (IntPtr)attrib->offset;
		while(length){
			*((T*)vertex) = *vals;
			vertex += (IntPtr)attrib->type.size;
			length--; vals++;
		}
	}

	template<typename T> void setAttribv(Int attribid, T* vals){
		void* vertex = getVertex();
		CKShaderAttrib* attrib = attribs->getAttrib(attribid);
		
		vertex += (IntPtr)attrib->offset;
		Int length = attrib->length;
		while(length){
			*((T*)vertex) = *vals;
			vertex += (IntPtr)attrib->type.size;
			length--; vals++;
		}
	}
	
	void* getVertices();
	void* getIndices();
	
	CKMesh* createMesh();
	
};


#endif // cakengine_util_modelbuilder_h
