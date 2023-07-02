#include "LowRenderer/Gizmo/Gizmo.h"
#include "Ressources/Shader/Shader.h"
#include "Ressources/Scene/Scene.h"
#include "App/App.h"
#include "LowRenderer/Cam/Camera.h"
#include <vector>
#include "Collider/Collider.h"
#include "Core/DataStructure/Entity/Entity.h"

void Gizmo::Render(Shader* shaderProgramm, Scene* scene)
{


}

Gizmo::Gizmo(Collider* collider)
{
	transformEntity = &collider->EntityAttachTo;

}



Gizmo::~Gizmo()
{

}