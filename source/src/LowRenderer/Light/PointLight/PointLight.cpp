#include "LowRenderer/Light/PointLight/PointLight.hpp"



void PointLight::ImguiWindowComponent()
{

    ImGui::Spacing();
    ImGui::ColorPicker4("ambiantColor", lightData.color.SetPtr());
    ImGui::DragFloat("Intensity", &lightData.intensity);
    ImGui::DragFloat("minimumRange", &lightData.minimumRange);
    ImGui::DragFloat("maxRange", &lightData.maxRange);
    ImGui::DragFloat("Size", &lightData.size);
    ImGui::Spacing();
}

PointLight::PointLight()
{
   
    
}

PointLight::~PointLight()
{
}
