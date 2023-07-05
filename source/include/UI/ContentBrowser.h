#pragma once
#include<filesystem>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
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



	ContentBrowser();
	~ContentBrowser();

	static ImGuiWindow* renderer;

private:
	bool IsThisFormat(const fs::path& path, const std::string& format);
	void Renderer(App& app);
	void LookForInput(App& app);
	std::string GetPreviousPath(const fs::path& currentPath);
	Texture* FolderIcon;
	Texture* PlayIcon;
	Texture* Pause;


};

