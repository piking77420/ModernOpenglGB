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



struct ModelData
{
	std::vector<Vector3> vertexPos;
	std::vector<Vector3> vertexNormal;
	std::vector<Vector2> vertexUv;
	std::vector<uint32_t> indexVector;
	bool IsUi = false;
};




class Model : public IResource
{
public:


	static Model LoadCube();
	static Model LoadSphere();

	//void Load(std::string path) override;
	virtual void Draw() const;
	Model(const float& reduceFormat);
	Model(const std::string& ModelFileName, const float& reduceFormat);
	Model(const std::string& ModelFileName);
	void OnSelected() override;


	Model();
	~Model();


	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	std::vector<Vertex> vertexVector;
	std::vector<uint32_t> indexVector;
	std::string name;

	void Init() override;
	static float cube[];
private:
	void LoadVertex(const ModelData& data, bool& isFaced, bool& is3dTextute);
	ModelData ReadModelFileOBJ(std::ifstream& stream, bool* isFaced, bool* is3dTextute);
	static const std::string MODELPATH;
	bool ObjIsSquareformat;
	float m_reduceValue;


};
