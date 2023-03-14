#ifndef cakegine_resources_g3d_modelinstance_h
#define cakegine_resources_g3d_modelinstance_h

#include <CakeEngine/util/modelbuilder/MeshBuilder.hpp>
#include <CakeEngine/graphics/renderer/materials/ModelMaterial.hpp>
#include <CakeEngine/graphics/renderer/Renderable.hpp>
#include <CakeEngine/resources/scene/Node3D.hpp>
#include <CakeEngine/graphics/renderer/Texture.hpp>



class CKModelInstance:public CKRenderable, public CKNode3D{
	
	friend class CKModelBuilder;
	
private:
	static CKModelMaterial *de_material;
	static CKTexture *de_texture;
	
	CKModelInstance(CKMesh *mesh, CKShaderProgram *material);
	
protected:
	void render(CKRenderer *renderer, CKMat4 *mat);
	
public:
	CKTexture *tex0 = nullptr;
	
	~CKModelInstance();
	
};


class CKModelBuilder{
	
	friend class CKModelInstance;
	
private:
	Int de_material_ref;
	
	CKMeshBuilder *mesh_builder = nullptr;
	
	CKMesh *de_mesh = nullptr;
	Int de_mesh_ref = 0;
	
public:
	CKModelBuilder();
	~CKModelBuilder();
	
	CKMeshBuilder *getMeshBuilder();
	CKModelMaterial *getMaterial();
	
	CKModelInstance *build();
	
};


#endif // cakegine_resources_g3d_modelinstance_h
