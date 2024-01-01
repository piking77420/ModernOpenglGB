#pragma once
#include "Texture.hpp"


class NormalMap : public Texture
{
public:

	void InitResource() override;


	NormalMap(const fs::path& FilePath);
	NormalMap();

	~NormalMap();

private: 

};

