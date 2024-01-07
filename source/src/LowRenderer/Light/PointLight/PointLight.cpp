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
    /*
    CubeMaps& cubemap = this->depthMap;
    depthMap.width = 2048;
    depthMap.height = 2048;

    // create depth cubemap texture
    glGenFramebuffers(1, &depthMapFBO);
              
    glGenTextures(1, &depthMap.ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap.ID);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, depthMap.width, depthMap.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap.ID, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }  
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    */
    
}

PointLight::~PointLight()
{
}
