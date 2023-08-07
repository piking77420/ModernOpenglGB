#pragma once
#include<vector>
#include <ToolBoxMathHeaders.h>
#include "LowRenderer/Vertex/Vertex.h"
#include "Ressources/Texture/Texture.hpp"

class Shader;

class Mesh : public IResource
{
public:

	void Init() override;
	
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);


	GLuint VAO;
	GLuint  VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture> textures;
	void Draw(Shader& shader);

};

