#pragma once
#include<filesystem>
namespace fs = std::filesystem;

class Texture;

class ContentBrowser
{
public:

	static fs::path BasePath;
	static fs::path CurrentPath;
	static fs::path PreviousPath;
	void Update();




	ContentBrowser();
	~ContentBrowser();


private:
	std::string GetPreviousPath(const fs::path& currentPath);
	Texture* FolderIcon;
};

