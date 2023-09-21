#include <Ressources/Mesh/Mesh.h>
#include "Ressources/RessourcesManager/RessourcesManager.h"




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
	Vector3 result = Vector3::Zero();

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
	Vector2 result = Vector2::Zero();

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



MeshData Mesh::ReadMeshFileOBJ(std::ifstream& stream , bool* isFaced , bool* is3dTexture)
{
	MeshData newdata;
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

void Mesh::Draw() const
{
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertexVector.size());
	//glDrawElements(GL_TRIANGLES, indexVector.size(), GL_UNSIGNED_INT, &indexVector[0]);
	glBindVertexArray(0);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}




Mesh::Mesh(const fs::path& FilePath) 
{
	bool Is3dTextureCoordinate;

	bool IsFaced;
	std::ifstream stream(FilePath);

	if (!stream.is_open())
	{
		LOG("String doesn't match with any model",STATELOG::WARNING);
		Debug::Assert->Assertion(stream.is_open());
	}
	else
	{
		LOG("Model " +  FilePath.generic_string() + " has been corretly loaded", STATELOG::GOOD);
	}

	MeshData data = ReadMeshFileOBJ(stream, &IsFaced, &Is3dTextureCoordinate);


	LoadVertex(data, IsFaced, Is3dTextureCoordinate);
}



Mesh::~Mesh()
{
	if(glIsBuffer(VAO))
	{
		glDeleteBuffers(1, &VAO);
	}

	if (glIsBuffer(VBO))
	{
		glDeleteBuffers(1, &VBO);
	}
	vertexVector.clear();
	indexVector.clear();

}

void Mesh::Init()
{
	// Init VAO \ Init VBO //

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);



	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	unsigned long long bufferDataSize = sizeof(Vertex) * vertexVector.size();
	glBufferData(GL_ARRAY_BUFFER, bufferDataSize, &vertexVector[0], GL_STATIC_DRAW);

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




void Mesh::LoadVertex(const MeshData& data, bool& isFaced, bool& is3dTextute)
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






