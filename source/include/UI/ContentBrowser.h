#pragma once
#include<filesystem>
namespace fs = std::filesystem;

class ContentBrowser
{
public:

	static fs::path BasePath;
	static fs::path CurrentPath;
	static fs::path PreviousPath;
	void Update();

	ContentBrowser(){};
	~ContentBrowser(){};

private:

};

