#include "UI/Log.hpp"
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>


void Log::UpdateLayer(Project& currentProject)
{
    
  /*
    if (!ImGui::Begin(WindowName.c_str(), &Isopen))
    {
      //  ImGui::End();
        return;
    }*/
 
    ImGui::Begin(WindowName.c_str(), &Isopen);
   

       if (ImGui::BeginPopup("Options"))
       {
           ImGui::Checkbox("Auto-scroll", &AutoScroll);
           ImGui::EndPopup();
       }


   ImGui::End();
    
}
