#include "Physics/GraphScene/GraphScene.h"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"






void GraphScene::Update(Scene* scene)
{
	// Getting All the data
	std::vector<uint8_t>* transformDataVector = scene->m_register.ComponentsData[Transform::ComponentTypeID].second;
	const uint32_t nbrOfTransform = transformDataVector->size();
	if (nbrOfTransform == 0)
		return;


	// Prepare Getting all the Transfrom
	std::vector<Transform*> ptr;
	for (size_t i = 0; i < transformDataVector->size() / sizeof(Transform); i++)
	{
		uint32_t index = i * sizeof(Transform);
		ptr.push_back(reinterpret_cast<Transform*>(&(*transformDataVector)[index]));
	}
	
	StarTree(ptr);

	
}




void GraphScene::UpdateTransform(Transform* transform,uint32_t treevalue)
{
	transform->Local = ToMatrix(transform);

	
	if(treevalue != 0 )
	{
		transform->World = transform->Parent->World * transform->Local;
		return;
	}

	transform->World = transform->Local;
}




void GraphScene::StarTree(std::vector<Transform*>& transformVector)
{
	uint32_t treeIndex = 0;
	std::vector<std::pair<Transform*, uint32_t>> treeNode;
	uint32_t getMaxIteration = 0;

	for (size_t i = 0; i < transformVector.size(); i++)
	{
		uint32_t CurrentTransformLinkValue = CountParentLink(transformVector[i]);

		if (CurrentTransformLinkValue > getMaxIteration)
			getMaxIteration = CurrentTransformLinkValue;

		treeNode.push_back({ transformVector[i],CurrentTransformLinkValue });
	}



	for (size_t i = 0; i < getMaxIteration; i++)
	{
		std::vector<std::thread*> Transformthread;

		for (size_t k = 0; k < treeNode.size(); k++)
		{
			// Push Mulihtrading here 
			std::thread* thread = new std::thread([this, treeNode, i, k]()
				{
					if (treeNode[k].second == i)
					{
						UpdateTransform(treeNode[k].first, treeNode[i].second);
					}
				});
			Transformthread.push_back(thread);
		
		}
		for(std::thread* thread : Transformthread)
		{
			thread->join();
		}

		Transformthread.clear();
	}
}

Matrix4X4 GraphScene::ToMatrix(const Transform* transform)
{
	return Matrix4X4::TRS(transform->pos,transform->rotation,transform->scaling);
}

// Get Recursif Value

void GraphScene::GetParentLink(const Transform* transform, uint32_t& currentValue)
{
	if (transform->Parent != nullptr)
	{
		currentValue++;
		GetParentLink(transform->Parent, currentValue);
	}

}

uint32_t GraphScene::CountParentLink(const Transform* transform)
{
	uint32_t LinkValue = 0;
	GetParentLink(transform, LinkValue);

	return LinkValue;

}

