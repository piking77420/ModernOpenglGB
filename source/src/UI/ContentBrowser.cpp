#include "UI/ContentBrowser.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "Ressources/RessourcesManager/RessourcesManager.h"

fs::path ContentBrowser::BasePath = fs::path("assets");

fs::path ContentBrowser::CurrentPath = fs::path("assets");




void ContentBrowser::Update()
{
	if(ImGui::Begin("ContentBrowser"))
	{
		if(CurrentPath == BasePath)
		{

		}
		else if (ImGui::ArrowButton("Reverse", ImGuiDir_Left))
		{
			

			int lastof = CurrentPath.string().find_last_of('\\');
			std::string pathstring = CurrentPath.string();
			std::string newpathstring;
			for (size_t i = 0; i < lastof; i++)
			{
					newpathstring.push_back(pathstring[i]);
			}
			fs::path newpath = fs::path(newpathstring);

			CurrentPath = newpath;
		}
		
		int i = 0;
		for (const auto& entry : fs::directory_iterator(CurrentPath))
		{
			const auto& path = entry.path();
			auto relative = path.relative_path();
			std::string name = relative.filename().string();
			
			if (entry.is_directory())
			{
				
				if(ImGui::Button(name.c_str()))
				{
					CurrentPath = path;
				}
			}
			else
			{
				ImGui::Text(name.c_str());
			}
			ImGui::NextColumn();

		}

		ImGui::Columns(1);

		ImGui::End();
	}
}
