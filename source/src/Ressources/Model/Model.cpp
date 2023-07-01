#include <Ressources/Model/Model.h>
#include "LowRenderer/RendererComponent/MeshRenderer/MeshRenderer.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"

const std::string Model::MODELPATH = "include/Ressources/Model/";
#pragma region Cube
float Model::cube[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};
#pragma endregion


#pragma region LoadOBJ

int foundFirstIndex(const std::string& line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
			return i;
	}

	return 0;
}


Vector3 readLigneFromStringVec3(const std::string& line )
{
	Vector3 result = Vector3::Zero;

	std::string currentnbr;
	int coord = 0;
	int index = foundFirstIndex(line);

	while (coord < 3)
	{
		// jump vb or v specifing 



		for (; index < line.size(); index++)
		{
			if(line[index] != ' ')
			{
				currentnbr.push_back(line[index]);
			}
			else
			{
				// Jumspace
				index++;
				break;
			}
		}

		// convert string to float 

		switch (coord)
		{
		default:
			break;
		case 0:
			result.x = std::stof(currentnbr);
			coord++;
			break;

		case 1:
			result.y = std::stof(currentnbr);
			coord++;
			break;

		case 2:
			result.z = std::stof(currentnbr);
			coord++;
			break;
		}

		currentnbr.clear();
	}

	return result;
}



Vector2 readLigneFromStringVec2(const std::string& line)
{
	Vector2 result = Vector2::Zero;

	std::string currentnbr;
	int coord = 0;
	int index = foundFirstIndex(line);

	while (coord != 2)
	{
		// jump vb or v specifing 
		for (; index < line.size(); index++)
		{
			if (line[index] != ' ')
			{
				currentnbr.push_back(line[index]);
			}
			else
			{
				// Jumspace
				index++;
				break;
			}
		}

		// convert string to float 

		switch (coord)
		{
		default:
			break;
		case 0:
			result.x = std::stof(currentnbr);
			coord++;
			break;

		case 1:
			result.y = std::stof(currentnbr);
			coord++;		
			break;

		}

		currentnbr.clear();
	}

	return result;
}

void readLigneFromStringFaceSquareFormat(const std::string& line, std::vector<uint32_t>& data)
{
	bool hasreadLignData = false;
	int currentVecData = 0;
	int countSlash = 0;
	std::string currenbr;
	int index = foundFirstIndex(line);

	std::vector<uint32_t> databeforeConvertToTriangle;



	for (; index < line.size(); index++)
	{


		if (index == line.size() - 1)
		{
			currenbr.push_back(line[index]);
			data.push_back(std::atoi(currenbr.c_str()));
			currenbr.clear();

		}


		if (line[index] == ' ')
		{
			currentVecData++;
			int nbr = std::atoi(currenbr.c_str());
			if (nbr != 0)
			{
				data.push_back(std::atoi(currenbr.c_str()));
			}
			currenbr.clear();
			continue;
		}


		if (line[index] == '/')
		{
			currentVecData++;

			data.push_back(std::atoi(currenbr.c_str()));
			currenbr.clear();
		}

		if (line[index] != '/')
		{
			currenbr.push_back(line[index]);
		}





	}


}

void readLigneFromStringFace(const std::string& line, std::vector<uint32_t>& data)
{
	bool hasreadLignData = false;
	int currentVecData = 0 ;
	int countSlash = 0;


	std::string currenbr;
	int index = foundFirstIndex(line);
	

		for (; index < line.size(); index++)
		{
			

			if(index == line.size() - 1)
			{
				currenbr.push_back(line[index]);
				data.push_back(std::atoi(currenbr.c_str()));
				currenbr.clear();
				
			}


			if(line[index] == ' ')
			{
				currentVecData++;
				int nbr = std::atoi(currenbr.c_str());
				if(nbr != 0 )
				{
					data.push_back(std::atoi(currenbr.c_str()));
				}
				currenbr.clear();
				continue;
			}


			if (line[index] == '/')
			{
				currentVecData++;

				data.push_back(std::atoi(currenbr.c_str()));
				currenbr.clear();
			}

			if (line[index] != '/')
			{
				currenbr.push_back(line[index]);
			}




			
		}

		

	

}


bool CheckIfSquare(const std::string& line)
{
	int countSlash = 0;
	for (size_t i = 0; i < line.size(); i++)
	{
		if(line[i] == '/')
		{
			countSlash++;
			if (countSlash > 6)
				return true;
		}
	}

	return false;
}

bool CheckIfTextureIs3dCoord(std::string line)
{
	int startIndex = foundFirstIndex(line);

	int counterOfSpace = 0;
	for (size_t i = startIndex; i < line.size(); i++)
	{
		if(line[i] == ' ')
		{
			counterOfSpace++;
		}

		if (counterOfSpace == 2 && i < line.size())
		{
			return true;
		}
	}
	return false;
}



ModelData Model::ReadModelFileOBJ(std::ifstream& stream , bool* isFaced , bool* is3dTexture)
{
	ModelData newdata;
	std::string line;
	bool isFomatCheck = false;
	bool is3dcoordCheck = false;

	while (stream.good())
	{

		std::getline(stream, line);

		if (line[0] == '#' || line[0] == ' ')
			continue;

		if (line[0] == 'v')
		{
			if (line[1] == ' ')
			{
				Vector3 pos = readLigneFromStringVec3(line);
				pos = pos * this->m_reduceValue;
				//pos
				newdata.vertexPos.push_back(pos);
			}
			else if (line[1] == 'n')
			{
				// NORMAL

				newdata.vertexNormal.push_back(readLigneFromStringVec3(line));
			}
			else if (line[1] == 't')
			{
				//Debug::Log->LogTODO("make for w");	
				if(!is3dcoordCheck)
				{
					*is3dTexture = CheckIfTextureIs3dCoord(line);
					is3dcoordCheck = true;
				}


				
				newdata.vertexUv.push_back(readLigneFromStringVec2(line));
				
				// TEXTURE
			}



		}
		else if (line[0] == 'f')
		{
			if(!isFomatCheck)
			{
				*isFaced = CheckIfSquare(line);
				isFomatCheck = true;
				
			}


			readLigneFromStringFace(line, newdata.indexVector);
			
			
			
			
		}


	}


	return newdata;
}

#pragma endregion
/*
void Model::Load(std::string path)
{
	
	bool Is3dTextureCoordinate;

	bool IsFaced;

	name = RessourcesManager::GetRessourcesName(path);
	std::ifstream stream(path);

	if (!stream.is_open())
	{
		Debug::Log->LogWarning("String doesn't match with any model");
		Debug::Assert->Assertion(stream.is_open());
	}
	else
	{
		Debug::Log->LogGood("Model " + name + " has been corretly loaded");
	}

	ModelData data = ReadModelFileOBJ(stream, &IsFaced, &Is3dTextureCoordinate);


	LoadVertex(data, IsFaced, Is3dTextureCoordinate);

	
}
*/
void Model::Draw() const
{
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertexVector.size());
	//glDrawElements(GL_TRIANGLES, indexVector.size(), GL_UNSIGNED_INT, &indexVector[0]);
	glBindVertexArray(0);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

Model::Model(const float& reduceFormat) : m_reduceValue(reduceFormat)
{
	name = "";
}

Model::Model(const std::string& ModelFileName, const float& reduceFormat) : m_reduceValue(reduceFormat)
{
	bool Is3dTextureCoordinate;

	bool IsFaced;

	name = RessourcesManager::GetRessourcesName(ModelFileName);
	std::ifstream stream(ModelFileName);

	if (!stream.is_open())
	{
		Debug::Log->LogWarning("String doesn't match with any model");
		Debug::Assert->Assertion(stream.is_open());
	}
	else
	{
		Debug::Log->LogGood("Model " + name + " has been corretly loaded");
	}

	ModelData data = ReadModelFileOBJ(stream , &IsFaced , &Is3dTextureCoordinate);
	

	LoadVertex(data, IsFaced, Is3dTextureCoordinate);
}

Model::Model(const std::string& ModelFileName) : m_reduceValue(1)
{
	bool Is3dTextureCoordinate;

	bool IsFaced;
	name = RessourcesManager::GetRessourcesName(ModelFileName);
	std::ifstream stream(ModelFileName);

	if (!stream.is_open())
	{
		Debug::Log->LogWarning("String doesn't match with any model");
		Debug::Assert->Assertion(stream.is_open());
	}
	else
	{
		Debug::Log->LogGood("Model " + name + " has been corretly loaded");
	}

	ModelData data = ReadModelFileOBJ(stream, &IsFaced, &Is3dTextureCoordinate);


	LoadVertex(data, IsFaced, Is3dTextureCoordinate);
}

void Model::OnSelected()
{
	ImGui::PushID(name.c_str());
	ImGui::Text(name.c_str());
	ImGui::PopID();

}



Model::Model() 
{
	this->VAO = 0;
	this->VBO = 0;
	this->EBO = 0;

}

Model Model::LoadCube()
{
	Model Cube;
	Cube.name = "Cube";
		

	for (size_t i = 0; i < 36; i+=3)
	{
		Cube.vertexVector.push_back(Vertex(Vector3(cube[i], cube[i+1], cube[i+2]) ));
	}
	
	Cube.Init();


	return Cube;
}


Model Model::LoadSphere()
{
	Model Sphere;

	float latitude = 0;
	float longitude = 0;

	int slice = 32;

	for (int i = 0; i < slice; i++)
	{
		float theta1 = (float)i * 2.0f * M_PI / slice;
		float theta2 = (float)(i + 1) * 2.0f * M_PI / slice;

		for (size_t k = 0; k <= slice; k++)
		{
			float phi = (float)k * M_PI / slice;

			float x1 =  sin(theta1) * sin(phi);
			float y1 =  cos(phi);
			float z1 =  cos(theta1) * sin(phi);

			float x2 =  sin(theta2) * sin(phi);
			float y2 =  cos(phi);
			float z2 =  cos(theta2) * sin(phi);
			Vector3 current = Vector3(x1,y1,z1);
			Vector3 current2 = Vector3(x2, y2, z2);
			Sphere.vertexVector.push_back(current);

		}
	}

	
	Sphere.Init();

	return Sphere;
}


	






Model::~Model()
{

	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

}

void Model::Init()
{
	// Init VAO \ Init VBO //

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	//glGenBuffers(1, &EBO);



	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	unsigned long long bufferDataSize = sizeof(Vertex) * vertexVector.size();
	glBufferData(GL_ARRAY_BUFFER, bufferDataSize, &vertexVector[0], GL_STATIC_DRAW);



	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//unsigned long  bufferEboDataSize = sizeof(uint32_t) * indexVector.size();
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferEboDataSize, &indexVector[0], GL_STATIC_DRAW);

	//pos
	glEnableVertexAttribArray(0); //layout 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// normal
	glEnableVertexAttribArray(1);//layout 1;
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	// Uv
	glEnableVertexAttribArray(2);//layout 2;
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));


	// Color
	glEnableVertexAttribArray(3);//layout 3;
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
}




void Model::LoadVertex(const ModelData& data, bool& isFaced, bool& is3dTextute)
{
	// https://fr.wikipedia.org/wiki/Objet_3D_(format_de_fichier)
	// f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
	// v1 : vertex one 
	// vt1 : texturecoord for v1
	// vn1 : normal for v1
	
	/*
	if(data.IsUi)
	{
		for (size_t i = 0; i < data.indexVector.size(); i += 2)
		{
			int posIndex = (data.indexVector[i]) - 1;
			int posTexture = (data.indexVector[i + 1]) - 1;



			Vertex newVertex = Vertex(data.vertexPos[posIndex] , Vector3::Zero, data.vertexUv[posTexture]);

			vertexVector.push_back(newVertex);


			indexVector.push_back(posIndex);
		}
	}

	*/

	if(!isFaced)
	{
		for (size_t i = 0; i < data.indexVector.size(); i += 3)
		{
			int posIndex = (data.indexVector[i]) - 1;
			int posNormal = (data.indexVector[i + 2]) - 1;
			int posTexture = (data.indexVector[i + 1]) - 1;


			
			Vertex newVertex = Vertex(data.vertexPos[posIndex], data.vertexNormal[posNormal], data.vertexUv[posTexture]);

			vertexVector.push_back(newVertex);


			indexVector.push_back(posIndex);
		}
	}
	else
	{
		// Wip read faces // 

		Vertex Face[4];
		int counter = 0;
		for (size_t i = 0; i < data.indexVector.size(); i += 3)
		{
			int posIndex = (data.indexVector[i]) - 1;
			int posNormal = (data.indexVector[i + 2]) - 1;
			int posTexture = (data.indexVector[i + 1]) - 1;

			//Vertex newVertex = Vertex(data.vertexPos[posIndex], data.vertexNormal[posNormal], data.vertexUv[posTexture]);
			

			Face[counter] = Vertex(data.vertexPos[posIndex], data.vertexNormal[posNormal], data.vertexUv[posTexture]);

			if (counter < 4)
			{
				counter++;
			}
			else
			{
				Vertex pushBackVertex[6];

				pushBackVertex[0] = Face[0];
				pushBackVertex[1] = Face[1];
				pushBackVertex[2] = Face[2];
				pushBackVertex[3] = Face[2];
				pushBackVertex[4] = Face[3];
				pushBackVertex[5] = Face[0];

				indexVector.push_back(posIndex - 4);
				indexVector.push_back(posIndex - 3);
				indexVector.push_back(posIndex - 2);
				indexVector.push_back(posIndex - 2);



				for (size_t k = 0; k < 6; k++)
				{
					vertexVector.push_back(pushBackVertex[k]);

				}
				counter = 0;
			}
			//vertexVector.push_back(newVertex);
			
		}
	}

}






