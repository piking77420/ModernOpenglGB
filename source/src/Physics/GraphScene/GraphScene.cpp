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

	// Getting All the data
	std::vector<Transform>* transformDataVector = reinterpret_cast<std::vector<Transform>*>(scene->GetComponentDataArray<Transform>());

	std::chrono::system_clock::time_point timeStart = std::chrono::system_clock::now();
	StarTree(transformDataVector);
	std::chrono::system_clock::time_point timeEnd = std::chrono::system_clock::now();

	m_timeForGraphUpdate = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();

};
void GraphScene::Update(Scene* scene)
{

};
void GraphScene::LateUpdate(Scene* scene)
{

};

void GraphScene::Render(Shader& shader,Scene* scene)
{

		if (ImGui::Begin("GraphSceneUpdate"))
		{
			ImGui::Text("Time for update  = %f  microseconds", m_timeForGraphUpdate);

			if (!App::IsMonoThread)
			{
				ImGui::Checkbox(" Is dynamic thread ", &GraphScene::IsDynamic);
			}
			ImGui::End();
		}

	


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


	if (App::IsMonoThread)
	{
		for (size_t i = 0; i < transformVector->size(); i++)
		{
			UpdateWorld(&transformVector->at(i));
		}
		return;
	}
	
	GraphScene::IsDynamic ? UpdateVector(transformVector) : UpdateArray(transformVector);

}



void GraphScene::UpdateArray(std::vector<Transform>* transformVector)
{
	for (size_t i = 0; i < m_threadPool.GetSize(); i++)
	{
		if (transformVector->size() <= m_threadPool.GetSize())
		{
			if (i > transformVector->size())
				break;

			m_threadPool[i] = std::thread(&GraphScene::ThreadUpdateTranform, transformVector, i, i);
			continue;
		}



		int offset = (transformVector->size() / m_threadPool.GetSize());
		int startIndex = i * offset;
		int endIndex = startIndex + offset;
		float fOffset = ((float)transformVector->size() / (float)m_threadPool.GetSize());

		if (fOffset > offset)
		{
			if (i == m_threadPool.GetSize() - 1)
			{
				int lastOffset = transformVector->size() - endIndex;
				endIndex += lastOffset;
			}

		}



		m_threadPool[i] = std::thread(&GraphScene::ThreadUpdateTranform, transformVector, startIndex, endIndex);
	}

	m_threadPool.JoinIfJoinable();
}

void GraphScene::UpdateVector(std::vector<Transform>* transformVector)
{
	m_threadPoolDynamic.Resize(THREADPOOLSIZE);

	for (size_t i = 0; i < THREADPOOLSIZE; i++)
	{
		if (transformVector->size() <= m_threadPoolDynamic.GetSize())
		{
			if (i > transformVector->size())
				break;

			m_threadPoolDynamic[i] = std::thread(&GraphScene::ThreadUpdateTranform, transformVector, i, i);
			continue;
		}



		int offset = (transformVector->size() / m_threadPoolDynamic.GetSize());
		int startIndex = i * offset;
		int endIndex = startIndex + offset;
		float fOffset = ((float)transformVector->size() / (float)m_threadPoolDynamic.GetSize());

		if (fOffset > offset)
		{
			if (i == m_threadPoolDynamic.GetSize() - 1)
			{
				int lastOffset = transformVector->size() - endIndex;

				m_threadPoolDynamic.Resize(m_threadPoolDynamic.GetSize() + 1);

				m_threadPoolDynamic[i + 1] = std::thread(&GraphScene::ThreadUpdateTranform, transformVector, endIndex, endIndex + lastOffset);
			}

		}



		m_threadPoolDynamic[i] = std::thread(&GraphScene::ThreadUpdateTranform, transformVector, startIndex, endIndex);
	}

	m_threadPoolDynamic.JoinIfJoinable();
	m_threadPoolDynamic.Clear();
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

