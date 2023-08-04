#include "Physics/GraphScene/GraphScene.h"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"





void GraphScene::Init(Scene* scene)
{

};

void GraphScene::Awake(Scene* scene)
{

};
void GraphScene::Start(Scene* scene)
{

};


void GraphScene::FixedUpdate(Scene* scene)
{

};
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

};
void GraphScene::LateUpdate(Scene* scene)
{

};

void GraphScene::Render(Scene* scene)
{

};



void GraphScene::OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data)
{
	if(ComponentTypeID == Transform::ComponentTypeID)
	{
		UpdateAllTransformPointers(data);
	}


};




void GraphScene::BeChildOf(Transform* Parent, Transform* Child)
{
	if (Parent == Child)
		return;

	Child->Parent = Parent;
	Child->ParentId = Parent->entity->ID;
	Parent->childs.push_back({ Child->entity->ID,Child });
}

void GraphScene::NoParent(Transform* transform)
{
	if (!transform->Parent)
		return;

	for (auto it = transform->Parent->childs.begin(); it != transform->Parent->childs.begin(); it++)
	{
		Transform* itera = it->second;
		if(itera == transform)
		{
			transform->childs.erase(it);
			UnbindParent(transform);
		}
	}

}

void GraphScene::UnChild(Transform* Parent, Transform* Child)
{
	if (Parent->childs.empty())
		return;


	for (auto it = Parent->childs.begin(); it != Parent->childs.begin(); it++)
	{
		Transform* itera = it->second;
		if (itera == Child)
		{
			Parent->childs.erase(it);
			UnbindParent(Child);
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

void GraphScene::UpdateAllTransformPointers(std::vector<uint8_t>* data)
{
	std::vector<Transform>* dataTransform = reinterpret_cast<std::vector<Transform>*>(data);


	for (size_t i = 0; i < dataTransform->size(); i++)
	{
		Transform* UpdatedTransform = &(*dataTransform)[i];
		if (!HasParent(UpdatedTransform)&& !HasChild(UpdatedTransform))
			continue;


		if(HasParent(UpdatedTransform))
		for (size_t k = 0; k < dataTransform->size(); k++)
		{
			const Transform* LookForParent = &(*dataTransform)[k];
			if(UpdatedTransform->ParentId == LookForParent->entity->ID)
			{
				UpdatedTransform->Parent = LookForParent;
				break;
			}

		}

		if (HasChild(UpdatedTransform))
		{
			for (size_t i = 0; i < UpdatedTransform->childs.size(); i++)
			{
				for (size_t k = 0; k < dataTransform->size(); k++)
				{
					Transform* LookChild = &(*dataTransform)[k];

					if (UpdatedTransform->childs[i].first == LookChild->entity->ID)
					{
						UpdatedTransform->childs[i].second = LookChild;
					}

				}
			}
			
		}


	}

}

bool GraphScene::HasParent(const Transform* transform)
{
	if (transform->Parent == nullptr && transform->ParentId == EntityNULL)
		return false;

	return true;
}

bool GraphScene::HasChild(const Transform* transform)
{
	if (transform->childs.empty())
		return false;


	return true;
}

void GraphScene::UnbindParent(Transform* transform)
{
	transform->ParentId = EntityNULL;
	transform->Parent = nullptr;
}

