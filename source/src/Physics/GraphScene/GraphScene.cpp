#include "Physics/GraphScene/GraphScene.h"
#include "ECS/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/Gizmo/Gizmo.hpp"
#include "App/App.h"
#include<algorithm>



void GraphScene::Init(Scene* scene)
{

};

void GraphScene::Awake(Scene* scene)
{

};
void GraphScene::Start(Scene* scene)
{

};

void GraphScene::OnDrawGizmo(Scene* scene)
{
	

}
void GraphScene::FixedUpdate(Scene* scene)
{
	StarTree(scene->GetComponentDataArray<Transform>());
};
void GraphScene::Update(Scene* scene)
{

};
void GraphScene::LateUpdate(Scene* scene)
{

};

void GraphScene::Render(Shader& shader,Scene* scene)
{

};



void GraphScene::OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data)
{
	if(ComponentTypeID == Transform::componentTypeID)
	{
		UpdateAllTransformPointers(data);
	}


};




void GraphScene::BeChildOf(Transform* Parent, Transform* Child)
{
	if (Parent == Child)
		return;

	Child->parent = Parent;
	Child->parentID = Parent->entityID;
	Parent->childs.push_back({ Child->entityID,Child });
}

void GraphScene::NoParent(Transform* transform)
{
	if (!transform->parent)
		return;

	for (auto it = transform->parent->childs.begin(); it != transform->parent->childs.begin(); it++)
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
	transform->local = ToMatrix(transform);

	
	if(treevalue != 0 )
	{
		transform->world = transform->parent->world * transform->local;
		return;
	}

	transform->world = transform->local;
}


void ThreadingCountParent(Transform* transform,uint32_t index,uint32_t* max, std::vector<std::pair<Transform*, uint32_t>>& _treeNod)
{
	uint32_t CurrentTransformLinkValue = GraphScene::CountParentLink(transform);



	if (CurrentTransformLinkValue > *max)
	{

		*max = CurrentTransformLinkValue;
	}

	_treeNod.at(index) = { transform,CurrentTransformLinkValue };
}

void GraphScene::StarTree(std::vector<Transform>* transformVector)
{
	if (transformVector->empty())
		return;

	UpdateLocalMatrix(transformVector);

	for (size_t i = 0; i < transformVector->size(); i++)
	{
			UpdateWorld(&transformVector->at(i));
	}
	
}



void GraphScene::UpdateLocalMatrix(std::vector<Transform>* transformVector)
{
	for (size_t i = 0; i < transformVector->size(); i++)
	{
		transformVector->at(i).local = ToMatrix(&transformVector->at(i));
	}
}

void GraphScene::UpdateWorld(Transform* transform)
{
	if(!GraphScene::HasParent(transform))
	{
		transform->world = transform->local;
		return;
	}

	transform->world = ReturnParentsMatrix(transform->parent) * transform->local;

}

void GraphScene::ThreadUpdateTranform(std::vector<Transform>* transformVector,uint32_t startIndex, uint32_t endIndex)
{
	for (uint32_t j = startIndex; j < endIndex; j++)
	{
		UpdateWorld(&transformVector->at(j));
	}
}

Matrix4X4 GraphScene::ReturnParentsMatrix(const Transform* parent)
{
	if(!GraphScene::HasParent(parent))
	{
		return parent->local;
	}
	
	return parent->local * ReturnParentsMatrix(parent);
	

}



Matrix4X4 GraphScene::ToMatrix(Transform* transform)
{
	transform->m_rotation = Quaternion::EulerAngle(transform->rotationValue * Math::Deg2Rad);
	return Matrix4X4::TRS(transform->pos, transform->m_rotation, transform->scaling);
}

// Get Recursif Value
void GraphScene::GetParentLink(const Transform* transform, uint32_t& currentValue)
{
	if (transform->parent != nullptr)
	{
		currentValue++;
		GetParentLink(transform->parent, currentValue);
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
		if (!HasParent(UpdatedTransform) && !HasChild(UpdatedTransform))
			continue;


		if(HasParent(UpdatedTransform))
		for (size_t k = 0; k < dataTransform->size(); k++)
		{
			const Transform* LookForParent = &(*dataTransform)[k];
			if(UpdatedTransform->parentID == LookForParent->entityID)
			{
				UpdatedTransform->parent = LookForParent;
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

					if (UpdatedTransform->childs[i].first == LookChild->entityID)
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
	if (transform->parent == nullptr && transform->parentID == EntityNULL)
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
	transform->parentID = EntityNULL;
	transform->parent = nullptr;
}

