#include "UI/ContentBrowser.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "Ressources/RessourcesManager/RessourcesManager.h"


fs::path ContentBrowser::BasePath = fs::path("assets");

fs::path ContentBrowser::CurrentPath = fs::path("assets");




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

void ContentBrowser::Update()
{


	ImGui::Begin("ContentBrowser",NULL);
	
		//ImGui::SliderFloat("dsq", &columnSpacing, 1, 500);
		float columnSpacing = 100;
		float padding = 16.f;
		float thumbailSize = 64;
		float cellsize = thumbailSize + padding;

		float panelwidht = ImGui::GetContentRegionAvail().x;
		int colomnCount = (int)(panelwidht / cellsize);
		if (colomnCount < 1)
			colomnCount = 1;


		if(CurrentPath == BasePath)
		{

		}
		else if (ImGui::ArrowButton("Reverse", ImGuiDir_Left) && CurrentPath.string() != BasePath.string())
		{
			CurrentPath = fs::path(GetPreviousPath(CurrentPath));	
		}
		

		
		ImGui::Columns(colomnCount,0, false);
		
		for (auto& entry : fs::directory_iterator(CurrentPath))
		{
			const auto& path = entry.path();
			auto relative = path.relative_path();
			std::string name = relative.filename().string();
			

			if (entry.is_directory())
			{
				
				ImGui::ImageButton((ImTextureID)FolderIcon->ID, { thumbailSize,thumbailSize }, { 0,1 }, { 1,0 });

				if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					std::cout << "dsqd";
					CurrentPath = path;
				}
				ImGui::Text(name.c_str());
			}
			else
			{
				if (ImGui::Button(name.c_str(), { thumbailSize,thumbailSize }))
				{
				}
				ImGui::Text(name.c_str());
			}
			ImGui::NextColumn();

		}

		ImGui::Columns(1);

		ImGui::End();
	
}

ContentBrowser::ContentBrowser()
{
	FolderIcon = new Texture("Ressources/Icon/FolderIcon.png");
	FolderIcon->Init();
}

ContentBrowser::~ContentBrowser()
{
	delete FolderIcon;
}
