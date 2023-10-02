#include "Core/ECS/Component.h"
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>



std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t, std::string> >* Component::m_componentTypeInfos = new  std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t, std::string> >();