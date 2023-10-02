#pragma once
#include<iostream>
#include <vector>
#include<Ressources/Texture/Texture.hpp>
#include <Core/Debug/Debug.h>
#include <fstream>
#include <Ressources/IResources/IResource.h>
#include <LowRenderer/Vertex/Vertex.h>
#include<string>
#include<glad/glad.h>
#include<Ressources/Shader/Shader.h>
#include<Mathf.h>



struct MeshData
{
	std::vector<Vector3> vertexPos;
	std::vector<Vector3> vertexNormal;
	std::vector<Vector2> vertexUv;
	std::vector<uint32_t> indexVector;
};




class Mesh : public IResource
{
public:



	void Draw() const;
	Mesh(const fs::path& FilePath);


	Mesh(const std::vector<Vertex>& vertex, const std::vector<uint32_t>& indexVector, const std::vector<Texture>& Texture) {};
	 virtual ~Mesh();
	Mesh() {};

	GLuint VAO;
	GLuint VBO;
	std::vector<Vertex> vertexVector;
	std::vector<uint32_t> indexVector;
	


	virtual void InitResource() override;
private:


	void LoadVertex(const MeshData& data, bool& isFaced, bool& is3dTextute);
	MeshData ReadMeshFileOBJ(std::ifstream& stream, bool* isFaced, bool* is3dTextute);


};

