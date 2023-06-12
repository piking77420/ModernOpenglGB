#include <LowRenderer/RendererComponent/MeshRenderer/MeshRenderer.h>
#include<Ressources/Texture/Texture.hpp>
#include<Core/DataStructure/Entity/Entity.h>
#include<Ressources/Model/Model.h>
#include "LowRenderer/Vertex/Vertex.h"
#include "LowRenderer/Cam/Camera.h"
#include "Ressources/Scene/Scene.h"
#include <Ressources/RessourcesManager/RessourcesManager.h>







void MeshRenderer::ImguiWindowComponents()
{


	ImGui::InputText("Current Model", &modelName[0], sizeof(modelName));
	OnTyping = ImGui::IsItemEdited();
	ImGui::Text(("Model name : " + m_Model->name).c_str());
	ImGui::Checkbox("StencilTest", &StencilTest) ;
	ImGui::SliderInt("Diffuse ", &material.diffuse,0,30);
	ImGui::SliderInt("Specular ", &material.specular, 0, 30);
	ImGui::DragFloat("shininess ", &material.shininess);

}


MeshRenderer::MeshRenderer(const Model& modelToCopy, const Texture& _textures, Entity& entityAttach) : RendererComponent(entityAttach), texture(_textures)
{
	m_Model = &modelToCopy;
	m_ComponentName = "MeshRenderer";
	vertexVector = modelToCopy.vertexVector;
	indexVector = modelToCopy.indexVector;
	material = Material(texture.slot, 0,32.f);
	for (size_t i = 0; i < m_Model->name.size(); i++)
	{
		modelName[i] = m_Model->name[i];
	}

}


MeshRenderer::MeshRenderer() : RendererComponent(*EntityAttachTo)
{
	m_Model = ressourcesManager->GetElement<Model>("Sphere.obj");
	for (size_t i = 0; i < m_Model->name.size(); i++)
	{
		modelName[i] = m_Model->name[i];
	}
	m_ComponentName = "MeshRenderer";
	material = Material(texture.slot, 0, 32.f);
	
}








void MeshRenderer::Draw(Scene* scene , Shader* shader)
{
	if (IsEnabled)
	{
		ChangeModel();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (StencilTest)
		{
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
			MeshRendererDraw(scene, shader);
		}
		else
		{
			glStencilMask(0x00);
			MeshRendererDraw(scene, shader);
		}

	}
}




MeshRenderer::~MeshRenderer()
{
	
}

void MeshRenderer::OnTapingModel()
{



	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
	{
		OnChangModel = true;
		std::cout << OnTyping << std::endl;

	}
}

void MeshRenderer::ChangeModel()
{
	OnTapingModel();
	if (OnChangModel)
	{
		std::string string = modelName;
		m_Model =  RendererComponent::ressourcesManager->GetElement<Model>(string);
		OnChangModel = false;
	}
}

void MeshRenderer::MeshRendererDraw(Scene* scene, Shader* shader)
{
	// get Shader and bind
	shader->Use();
	texture.BindTexture();
	// Set info to shader
	shader->SetMaterial("material", material);
		
	Matrix4X4 model = EntityAttachTo->transform.GetMatrix();
	Matrix4X4 MVP = scene->cam->GetProjectionMatrix() * scene->cam->GetLookMatrix() * model;
	shader->SetMaxtrix("model", model.GetPtr());

	shader->SetMaxtrix("MVP", MVP.GetPtr());
	shader->SetMaxtrix("rotation",Matrix4X4().RotationMatrix4X4(EntityAttachTo->transform.rotate).GetPtr());
	// Draw The Object
	m_Model->Draw();
	texture.UnBindTexture();
}

void MeshRenderer::MeshRendererDrawStencil(Scene* scene, Shader* shader)
{
	// do it on another cycle in scene update 
	if (!StencilTest)
		return;



	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);

	Matrix4X4 model = EntityAttachTo->transform.GetMatrix();


	// Get Stencil Shader and bind everything
	shader->Use();
	texture.BindTexture();
	Matrix4X4 mode2 = model * Matrix4X4().ScalingMatrix4X4(Vector3(1.05, 1.05, 1.05));
	shader->SetMaxtrix("model", mode2.GetPtr());
	// Draw The Object
	m_Model->Draw();
	texture.UnBindTexture();
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
}
