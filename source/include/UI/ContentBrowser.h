#pragma once
#include<filesystem>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "ImguiLayer.h"
namespace fs = std::filesystem;

class Texture;
class App;
class Project;

class ContentBrowser : public ImguiLayer
{
public:

	static fs::path BasePath;
	static fs::path CurrentPath;
	static fs::path PreviousPath;

	void UpdateLayer(Project& currentProject, std::vector<InputEvent*>& inputsEvents) override;


	ContentBrowser();
	~ContentBrowser();
protected:
	void ListenToInput(Project& currentProject,std::vector<InputEvent*>& inputEvent);


private:
	bool IsThisFormat(const fs::path& path, const std::string& format);
	void Renderer(Project& currentProject);
	std::string GetPreviousPath(const fs::path& currentPath);
	Texture* FolderIcon;
	Texture* PlayIcon;
	Texture* Pause;


};

