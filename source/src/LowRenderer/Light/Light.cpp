#include "LowRenderer/Light/Light.hpp"
#include<random>
#include<glad/glad.h>
#include <GLFW/glfw3.h>

float GetRandomValue()
{
	static std::default_random_engine generator;
	static std::uniform_real_distribution<float> distrib(-0.5f, 0.5f);

	return distrib(generator);
}

static void GenerateOffSetTexture(int windowSize, int FilterSize, std::vector<float>* data)
{
	int BuffersSize = windowSize * windowSize * FilterSize * FilterSize * 2;
	data->resize(BuffersSize);

	int index = 0;

	for (size_t TexY = 0; TexY < windowSize; TexY++)
	{
		for (size_t TexX = 0; TexX < windowSize; TexX++)
		{
			for (size_t v = FilterSize - 1; v >= 0; v--)
			{
				for (size_t u = 0; u < FilterSize; u++)
				{
					float randomX = GetRandomValue();
					float randomY = GetRandomValue();

					float x = ((float)u + 0.5f + randomX) / (float)FilterSize;
					float y = ((float)u + 0.5f + randomY) / (float)FilterSize;

					data->at(index) = std::sqrtf(y) * cosf(2 * M_PI * x);
					data->at(index + 1) = std::sqrtf(y) * sinf(2 * M_PI * x);

					index += 2;

				}
			}
		}
	}
}
OffSetTexture::OffSetTexture(int windowSize, int FilterSize)
{
	std::vector<float> data;
	GenerateOffSetTexture(windowSize, FilterSize, &data);
	CreateTextureOffSet(windowSize, FilterSize, data);
}

void OffSetTexture::BindTexture(uint32_t bindingLoc)
{
	glActiveTexture(bindingLoc);
	glBindTexture(GL_TEXTURE_3D, textureObj);
}





void OffSetTexture::CreateTextureOffSet(int windowSize, int FilterSize, const std::vector<float>& data)
{

	int NumFilterSamples = FilterSize * FilterSize;

	glGenTextures(1, &textureObj);

	glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_3D, textureObj);

	// Use glTexImage3D instead of glTexStorage3D
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32F, NumFilterSamples / 2, windowSize, windowSize, 0, GL_RGBA, GL_FLOAT, &data[0]);

	glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, NumFilterSamples / 2, windowSize, windowSize, GL_RGBA, GL_FLOAT, &data[0]);


	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



	glBindTexture(GL_TEXTURE_3D, 0);



}

