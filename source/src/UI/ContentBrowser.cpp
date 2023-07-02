#include "UI/ContentBrowser.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "App/App.h"
#include "UI/InspectorSelectable.h"

fs::path ContentBrowser::BasePath = fs::path("assets");

fs::path ContentBrowser::CurrentPath = fs::path("assets");




bool ContentBrowser::IsThisFormat(const fs::path& path, const std::string& format)
{
	std::string pathS = path.generic_string();
	int index = pathS.find_last_of('.');
	std::string test;

	for (size_t i = index; i < pathS.size(); i++)
	{
		test.push_back(pathS[i]);
	}

	if (test == format)
		return true;
	
	return false;
}

void ContentBrowser::Renderer(App& app)
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
				std::string ressourcename = app.m_Ressources->GetRessourcesName(path.generic_string());
				app.InspectorCurrentindow = app.m_Ressources->GetElement<InspectorSelectable>(ressourcename);
				std::cout << ressourcename << std::endl;
			}
			ImGui::Text(name.c_str());
		}
		ImGui::NextColumn();

	}

	ImGui::Columns(1);

}

void ContentBrowser::LookForInput(App& app)
{
	if(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		ImGui::ShowDemoWindow();

		
	}
}

std::string ContentBrowser::GetPreviousPath(const fs::path& currentPath)
{
	int lastof = CurrentPath.string().find_last_of('\\');
	std::string pathstring = CurrentPath.string();
	std::string newpathstring;
	for (size_t i = 0; i < lastof; i++)
	{
		newpathstring.push_back(pathstring[i]);
	}

	return newpathstring;
}




void ContentBrowser::Update(App& app)
{
	ImGui::Begin("ContentBrowser", NULL);
	Renderer(app);
	LookForInput(app);
	ImGui::End();
	StateApp();
	
}

void ContentBrowser::StateApp()
{
	ImGui::Begin(" PlayMode ", NULL);
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 24) * 0.5f);
	ImGui::ImageButton((ImTextureID)PlayIcon->ID, { 24,24 }, { 0,1 }, { 1,0 });
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		Launch = true;
	}

	ImGui::ImageButton((ImTextureID)PlayIcon->ID, { 24,24 }, { 0,1 }, { 1,0 });
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		Launch = true;
	}
	ImGui::End();
}

ContentBrowser::ContentBrowser()
{
	FolderIcon = new Texture("Ressources/Icon/FolderIcon.png");
	PlayIcon = new Texture("Ressources/Icon/Play.png");
	Pause = new Texture("Ressources/Icon/Pause.png");
	FolderIcon->Init();
	PlayIcon->Init();
	Pause->Init();
}

ContentBrowser::~ContentBrowser()
{
	delete FolderIcon;
	delete PlayIcon;
	delete Pause;

}
