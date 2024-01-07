#include "RumicsCube.h"
#include "Physics/GraphScene/GraphScene.h"
#include "Physics/Transform/Transform.hpp"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include"Physics/Collider/BoxCollider.hpp"

RumicsCube::RumicsCube()
{
}

RumicsCube::~RumicsCube()
{
}
void RumicsCube::Init(Scene* scene)
{
	

	Rumicube = scene->CreateEntity();
	Rumicube->entityName = "Rumicube";
	RumicksCubeEntityId = Rumicube->ID;



    int numCubesPerRow = 2; // Number of cubes in each row
    int cubeSize = 2; // Size of each cube
    float spacing = 2.0f; // Spacing between cubes

    for (int i = 0; i < numCubesPerRow; i++) {
        for (int j = 0; j < numCubesPerRow; j++) {
            for (int x = 0; x < cubeSize; x++) {
                for (int y = 0; y < cubeSize; y++) {
                    for (int z = 0; z < cubeSize; z++) {
                        Entity* entity = scene->CreateEntity();
                        scene->AddComponent<MeshRenderer>(entity);
                        //scene->AddComponent<BoxCollider>(entity);
                        float offsetX = static_cast<float>(x - cubeSize / 2) + i * spacing * cubeSize;
                        float offsetY = static_cast<float>(y - cubeSize / 2) + j * spacing * cubeSize;
                        float offsetZ = static_cast<float>(z - cubeSize / 2);
                        scene->GetComponent<Transform>(entity)->pos = Vector3(offsetX, offsetY, offsetZ) * spacing;

                        GraphScene::BeChildOf(scene->GetComponent<Transform>(Rumicube), scene->GetComponent<Transform>(entity));

                        MeshRenderer* meshRenderer = scene->GetComponent<MeshRenderer>(entity);
                        meshRenderer->mesh = *ResourcesManager::GetElement<Mesh>("cube.obj");
                        meshRenderer->material.phongMaterial.albedo = *ResourcesManager::GetElement<Texture>("DiamondBlock.jpg");
                    }
                }
            }
        }
    }
	

};


void RumicsCube::Update(Scene* scene)
{

	scene->GetComponent<Transform>(Rumicube)->rotationValue += Vector3(1, -1, 1);


};

