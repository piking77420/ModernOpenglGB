#include "Physics/GraphScene/GraphScene.h"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"






void GraphScene::Update(Scene* scene)
{
	// Getting All the data
	std::vector<uint8_t>* transformDataVector = scene->GetComponentDataArray<Transform>();
	
	const uint32_t nbrOfTransform = transformDataVector->size();
	if (nbrOfTransform == 0)
		return;


	// Prepare Getting all the Transfrom
	std::vector<Transform*> transformVector;
	for (size_t i = 0; i < transformDataVector->size() / sizeof(Transform); i++)
	{
		uint32_t index = i * sizeof(Transform);
		transformVector.push_back(reinterpret_cast<Transform*>(&(*transformDataVector)[index]));
	}


	
	StarTree(transformVector);

	
}

void GraphScene::BeChildOf(Transform* Parent, Transform* Child)
{
	Child->Parent = Parent;
	Parent->childs.push_back(Child);
}

void GraphScene::NoParent(Transform* transform)
{
	if (!transform->Parent)
		return;

	for (auto it = transform->Parent->childs.begin(); it != transform->Parent->childs.begin(); it++)
	{
		Transform* itera = *it;
		if(itera == transform)
		{
			transform->childs.erase(it);
			transform->Parent = nullptr;
		}
	}

}

void GraphScene::UnChild(Transform* Parent, Transform* Child)
{
	if (Parent->childs.empty())
		return;


	for (auto it = Parent->childs.begin(); it != Parent->childs.begin(); it++)
	{
		Transform* itera = *it;
		if (itera == Child)
		{
			Parent->childs.erase(it);
			Child->Parent = nullptr;
		}
	}



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
	// Update Local Matrix


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

	// Push Mulihtrading here
	 /*std::thread* thread = new std::thread([this, treeNode, i, k]()
		{
		});
	Transformthread.push_back(thread);*/


	size_t k = 0;
	do
	{


		//std::vector<std::thread*> Transformthread;

		for (size_t i = 0; i < treeNode.size(); i++)
		{
			
			
				if (treeNode[i].second == k)
				{
					UpdateTransform(treeNode[i].first, treeNode[i].second);
				}

			
			
		}

		/*
		for (std::thread* thread : Transformthread)
		{
			thread->join();
		}

		Transformthread.clear();

		*/
		k++;
	} while (k < getMaxIteration + 1);
	



	/*
	for (size_t i = 0; i < treeNode.size(); i++)
	{
		std::cout << treeNode[i].first->World << std::endl;
	}*/
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

