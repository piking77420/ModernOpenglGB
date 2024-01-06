#include "UI/ContentBrowser.h"
#include<Core/Debug/Imgui/imgui.h>

#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "App/App.h"
#include "UI/InspectorSelectable.h"
#include "ECS/Scene.h"
#include "Core/DataStructure/Project.hpp" 
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "External/ImguiGizmo/ImGuizmo.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "UI/Hierarchy.hpp"

fs::path ContentBrowser::BasePath;

fs::path ContentBrowser::CurrentPath;



bool ContentBrowser::IsThisFormat(const fs::path& path, const std::string& format)
{
	std::string pathS = path.generic_string();
	size_t index = pathS.find_last_of('.');
	std::string test;

	for (size_t i = index; i < pathS.size(); i++)
	{
		test.push_back(pathS[i]);
	}

	if (test == format)
		return true;
	
	return false;
}

void ContentBrowser::Renderer(Project& currentProject)
{


	//ImGui::SliderFloat("dsq", &columnSpacing, 1, 500);
	float columnSpacing = 100;
	float padding = 16.f;
	float thumbailSize = 64;
	float cellsize = thumbailSize + padding;

	float panelwidht = ImGui::GetContentRegionAvail().x;
	int colomnCount = (int)(panelwidht / cellsize);
	if (colomnCount < 1)
		colomnCount = 1;


	if (CurrentPath == BasePath)
	{

	}
	else if (ImGui::ArrowButton("Reverse", ImGuiDir_Left) && CurrentPath.string() != BasePath.string())
	{
		CurrentPath = fs::path(GetPreviousPath(CurrentPath));
	}



	ImGui::Columns(colomnCount, 0, false);

	for (auto& entry : fs::directory_iterator(CurrentPath))
	{
		const auto& path = entry.path();
		auto relative = path.relative_path();
		std::string name = relative.filename().string();

		if (IsThisFormat(entry, ".metaData"))
			continue;

		if (entry.is_directory())
		{

			ImGui::ImageButton((ImTextureID)FolderIcon->ID, { thumbailSize,thumbailSize }, { 0,1 }, { 1,0 });

			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				CurrentPath = path;
			}
			ImGui::Text(name.c_str());
		}
		else
		{
			if (ImGui::Button(name.c_str(), { thumbailSize,thumbailSize }))
			{
				std::string ressourcename = path.filename().generic_string();
				//app.InspectorCurrentindow = app.m_Ressources->GetElement<InspectorSelectable>(ressourcename);
			}
			ImGui::Text(name.c_str());
		}
		ImGui::NextColumn();

	}

	ImGui::Columns(1);

}



std::string ContentBrowser::GetPreviousPath(const fs::path& currentPath)
{
	size_t lastof = CurrentPath.string().find_last_of('\\');
	std::string pathstring = CurrentPath.string();
	std::string newpathstring;
	for (size_t i = 0; i < lastof; i++)
	{
		newpathstring.push_back(pathstring[i]);
	}

	return newpathstring;
}



void ContentBrowser::UpdateLayer(Project& currentProject)
{
	ImGui::Begin("ContentBrowser", NULL);
	Renderer(currentProject);
	ImGui::End();
	
}

ContentBrowser::ContentBrowser()
{
	FolderIcon = new Texture("Ressources/Icon/FolderIcon.png");
	PlayIcon = new Texture("Ressources/Icon/Play.png");
	Pause = new Texture("Ressources/Icon/Pause.png");
	FolderIcon->InitResource();
	PlayIcon->InitResource();
	Pause->InitResource();
}

ContentBrowser::~ContentBrowser()
{
	delete FolderIcon;
	delete PlayIcon;
	delete Pause;

}

void ContentBrowser::ListenToInput(Project& currentProject,std::vector<InputEvent*>& inputEvent)
{
}
