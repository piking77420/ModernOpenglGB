#pragma once
#include <vector>
#include "Mathf.h";
#include "LowRenderer/RendererComponent/RendererComponent.h"
#include "Ressources/Model/Model.h"
#include "Ressources/Texture/Texture.hpp"

class UIRenderer : public RendererComponent
{	
public:

	Texture texure;
	Model m_Model;
	void Draw(Scene* scene, Shader* shader) override;
	
	
	UIRenderer(Entity& entity);
	~UIRenderer();

private:
};

