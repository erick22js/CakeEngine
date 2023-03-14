#ifndef cakengine_util_formats_daehanddler_h
#define cakengine_util_formats_daehanddler_h

#include <CakeEngine/util/formats/XmlHanddler.hpp>
#include <CakeEngine/resources/g3d/ModelInstance.hpp>
#include <CakeEngine/resources/scene/Scene3D.hpp>


class CKDae{
	
	friend class CKDaeImporter;
	
public:
	enum NmToken{
		NONE = 0,
		BINORMAL,
		COLOR,
		CONTINUITY,
		IMAGE,
		INPUT,
		IN_TANGENT,
		INTERPOLATION,
		INV_BIND_MATRIX,
		JOINT,
		LINEAR_STEPS,
		MORPH_TARGET,
		MORPH_WEIGHT,
		NORMAL,
		OUTPUT,
		OUT_TANGENT,
		POSITION,
		TANGENT,
		TEXBINORMAL,
		TEXCOORD,
		TEXTANGENT,
		UV,
		VERTEX,
		WEIGHT
	};
	
	enum Type{
		NILL = 0,
		INT,
		FLOAT,
		BOOL,
	};
	
private:
	struct Identifiable{
		Char* id = nullptr;
		Char* name = nullptr;
	};
	
	struct Array:public Identifiable{
		void* data = nullptr;
		Int count = 0;
		Type type = NILL;
	};
	
	struct SourceLookable{
		virtual Int getCount() = 0;
		virtual Bool getBool(Int index) = 0;
		virtual Float getFloat(Int index) = 0;
		virtual Int getInt(Int index) = 0;
	};
	
	struct Source:public Identifiable, public SourceLookable{
		Array array;
		
		Int getCount(){
			return array.count;
		};
		Bool getBool(Int index){
			if(index>=array.count){
				std::cout << "Trying to access out of bounds!" << std::endl;
				return 0;
			}
			return ((Bool*)array.data)[index];
		};
		Float getFloat(Int index){
			if(index>=array.count){
				std::cout << "Trying to access out of bounds!" << std::endl;
				return 0;
			}
			return ((Float*)array.data)[index];
		};
		Int getInt(Int index){
			if(index>=array.count){
				std::cout << "Trying to access out of bounds!" << std::endl;
				return 0;
			}
			return ((Int*)array.data)[index];
		};
	};
	
	struct Input:public SourceLookable{
		NmToken semantic = NONE;
		SourceLookable* src = nullptr;
		
		Int getCount(){
			if(src==nullptr){
				std::cout << "Trying to a not defined source!" << std::endl;
				return 0;
			}
			return src->getCount();
		};
		Bool getBool(Int index){
			if(src==nullptr){
				std::cout << "Trying to a not defined source!" << std::endl;
				return 0;
			}
			return src->getBool(index);
		};
		Float getFloat(Int index){
			if(src==nullptr){
				std::cout << "Trying to a not defined source!" << std::endl;
				return 0;
			}
			return src->getFloat(index);
		};
		Int getInt(Int index){
			if(src==nullptr){
				std::cout << "Trying to a not defined source!" << std::endl;
				return 0;
			}
			return src->getInt(index);
		};
	};
	
	struct InputUnshared:public Input{};
	
	struct InputShared:public Input{
		Uint offset = 0;
		Uint set = 0;
	};
	
	struct VerticesAttribs:public Identifiable, public SourceLookable{
		std::vector<InputUnshared*> inputs = std::vector<InputUnshared*>(0);
		
		Int getCount(){
			if(inputs.size()==0){
				std::cout << "Trying to a not defined input!" << std::endl;
				return 0;
			}
			return inputs[0]->getCount();
		};
		Bool getBool(Int index){
			if(inputs.size()==0){
				std::cout << "Trying to a not defined input!" << std::endl;
				return 0;
			}
			return inputs[0]->getBool(index);
		};
		Float getFloat(Int index){
			if(inputs.size()==0){
				std::cout << "Trying to a not defined input!" << std::endl;
				return 0;
			}
			return inputs[0]->getFloat(index);
		};
		Int getInt(Int index){
			if(inputs.size()==0){
				std::cout << "Trying to a not defined input!" << std::endl;
				return 0;
			}
			return inputs[0]->getInt(index);
		};
	};
	
	struct Triangles{
		Int count = 0;
		Uint16* indices = nullptr;
		Int indices_count = 0;
		std::vector<struct InputShared*> inputs = std::vector<struct InputShared*>(0);
	};
	
	struct Mesh{
		VerticesAttribs attribs;
		
		std::vector<Triangles*> triangles = std::vector<Triangles*>(0);
		
		CKModelBuilder *builder = nullptr;
		
		std::vector<Source*> c_src = std::vector<Source*>(0);
		std::vector<InputShared*> c_inputs = std::vector<InputShared*>(0);
	};
	
	struct Geometry:public Identifiable{
		Mesh *mesh = nullptr;
		CKModelBuilder *builder = nullptr;
	};
	
	std::vector<Geometry> lib_geometries = std::vector<Geometry>(0);
	
public:
	
	
};

class CKDaeImporter{
	
private:
	static Char* translate_reference(Char* reference);
	
	static CKDae::Source *locate_sourceById(std::vector<CKDae::Source*> *identifiables, Char* referenceId);
	
	
	static Int decode_arrayFloat(Float* array, Char* str, Int length);
	static Int decode_arrayUint16(Uint16* array, Char* str, Int length);
	
	
	static Int load_source(CKDae::Mesh *mesh, CKDae::Source *source, CKXmlNode *xmlsrc);
	
	static Int load_triangles(CKDae::Triangles* triangles, CKDae::Mesh *mesh, CKXmlNode *xmltriangles);
	
	static Int load_mesh(CKDae* dae, CKDae::Mesh *mesh, CKXmlNode *xmlmesh);
	
	static Int build_mesh(CKDae* dae, CKDae::Mesh *mesh, CKXmlNode *xmlmesh);
	
	static Int load_geometry(CKDae* dae, CKDae::Geometry *geometry, CKXmlNode *xmlgeo);
	static Int load_geometry_(CKDae* dae, CKDae::Geometry *geometry, CKXmlNode *xmlgeo);
	
	static Int load_libraries(CKDae* dae, CKXmlNode *xmldae);
	
public:
	static CKScene3D *import(CKReader *reader);
	static CKScene3D *import_(CKReader *reader);
	
};


#endif // cakengine_util_formats_daehanddler_h
