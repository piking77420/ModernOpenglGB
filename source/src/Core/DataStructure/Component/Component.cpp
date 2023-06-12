#include <Core/DataStructure/Component/Component.h>
#include <Core/DataStructure/Entity/Entity.h>


void Component::ImguiWindowComponents()
{
}

void Component::ImguiWindow()
{
	if(ImGui::TreeNode(m_ComponentName.c_str()))
	{
		ImGui::PushID("");
		ImGui::Checkbox("Enable", &IsEnabled);
		this->ImguiWindowComponents();
		ImGui::PopID();
		ImGui::TreePop();
		ImGui::Spacing();
	}
}

void Component::PreUpdate(Scene* scene)
{
}




void Component::Update(Scene* scene)
{
}

void Component::LateUpdate(Scene* scene)
{
}

Component::Component() 
{

}


