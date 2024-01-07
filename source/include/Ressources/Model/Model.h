#pragma once
/*
#include <string>
#include <vector>
#include "Ressources/IResources/IResource.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Texture;
class Mesh;

class Model : public IResource
{
public:
	std::vector<Texture*> textures_loaded;
	std::vector<Mesh*> meshes;
	std::string directory;


	Model(const fs::path& FilePath);
	
	~Model();
private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

*/