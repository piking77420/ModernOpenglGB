#pragma once
#include<filesystem>
namespace fs = std::filesystem;

class Scene;


class Serializer
{
public:


	void Serialize(const fs::path& _path,const Scene* scene);
	void Desrialize(const fs::path& _path, const Scene* scene);

	Serializer();
	~Serializer();
};

