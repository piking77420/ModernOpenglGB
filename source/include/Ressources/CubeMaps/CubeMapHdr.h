#pragma once
#include "CubeMaps.h"

class Shader;

class CubeMapHdr : public CubeMaps
{
public:


	CubeMapHdr(const std::string& PathToHdri);
	~CubeMapHdr();
	void InitCubeMap(const Shader* shader);
	void DrawCube();

	void BindEnvCubeMap() const;
	void UnEnvBindCubeMap() const;

	void BindIBL() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
	}
	void UnBindIBL() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	}


	void InitCubemaptoRender();
	void InitIbl();

	virtual void InitResource() override;


private:


	static inline unsigned int cubeVAO = 0;
	static inline unsigned int cubeVBO = 0;
	bool HasInt = false;

	GLuint captureFBO;
	GLuint captureRBO;
	GLuint irradianceMap;
	GLuint envCubemap;

};
