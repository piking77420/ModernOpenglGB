#include "RumicsCube.h"
#include "Physics/GraphScene/GraphScene.h"
#include "Physics/Transform/Transform.hpp"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"
RumicsCube::RumicsCube()
{
}

RumicsCube::~RumicsCube()
{
}
void RumicsCube::Init(Scene* scene)
{
	/*
	int cubeSize = 3;
	float spacing = 2.f;  // Adjust the spacing between cubes


	Entity* Rumicube = scene->CreateEntity();
	Rumicube->Entityname = "Rumicube";
	RumicksCubeEntityId = Rumicube->ID;





	for (int x = 0; x < cubeSize; x++)
	{
		for (int y = 0; y < cubeSize; y++)
		{
			for (int z = 0; z < cubeSize; z++)
			{
				Entity* entity = scene->CreateEntity();
				scene->AddComponent<MeshRenderer>(entity);

				float offsetX = static_cast<float>(x - cubeSize / 2);
				float offsetY = static_cast<float>(y - cubeSize / 2);
				float offsetZ = static_cast<float>(z - cubeSize / 2);

				scene->GetComponent<Transform>(entity)->pos = Vector3(offsetX, offsetY, offsetZ) * spacing;


				GraphScene::BeChildOf(scene->GetComponent<Transform>(Rumicube), scene->GetComponent<Transform>(entity));



				MeshRenderer* meshRenderer = scene->GetComponent<MeshRenderer>(entity);
				meshRenderer->mesh = *scene->currentproject->ressourcesManager.GetElement<Mesh>("cube.obj");
				meshRenderer->material.diffuse = *scene->currentproject->ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
				meshRenderer->material.specular = *scene->currentproject->ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
			}
		}
	}*/
};

void RumicsCube::Awake(Scene* scene)
{

};
void RumicsCube::Start(Scene* scene)
{

};
void RumicsCube::OnDrawGizmo(Scene* scene)
{

};

void RumicsCube::FixedUpdate(Scene* scene)
{

};
void RumicsCube::Update(Scene* scene)
{




};
void RumicsCube::LateUpdate(Scene* scene)
{

};

void RumicsCube::Render(Shader& shader, Scene* scene)
{

};



void RumicsCube::OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data)
{

};