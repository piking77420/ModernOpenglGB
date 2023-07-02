#pragma once
#include<filesystem>
namespace fs = std::filesystem;

class Texture;
class App;

class ContentBrowser
{
public:

	static fs::path BasePath;
	static fs::path CurrentPath;
	static fs::path PreviousPath;
	void Update(App& app);
	void StateApp();
	bool Launch;



	ContentBrowser();
	~ContentBrowser();

	
private:
	bool IsThisFormat(const fs::path& path, const std::string& format);
	void Renderer(App& app);
	void LookForInput(App& app);
	std::string GetPreviousPath(const fs::path& currentPath);
	Texture* FolderIcon;
	Texture* PlayIcon;
	Texture* Pause;


};

