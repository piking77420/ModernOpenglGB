#pragma once
#include<ComponentsBehaviours.h>
#include <vector>
#include "LowRenderer/RendererComponent/GizmoRenderer/GizmoRenderer.h"

enum ColliderType
{
	SPHERE,
	PLANE

};

class CollisionType;

class Collider : public Component
{
public:
	void DrawGizmo(Shader* shaderProgramm);
	void PreUpdate(Scene* scene) override;
	virtual void Update(Scene* scene);
	void ImguiWindowComponents() override;
	void HasBeenCollided();
	void LateUpdate(Scene* scene) override;


	bool isCollided;		
	ColliderType ID;
	GizmoRenderer* Gizmorenderer;
	std::vector<CollisionType*> CollisionShape;
	std::vector<Entity*> entitesHasBeenCollid;



	Collider() { isCollided = false;
	Gizmorenderer = nullptr;
	};
	virtual	~Collider()
	{
		
	};
};

