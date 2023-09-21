#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Core/Python/PythonObject.h"

class PythonScript : public IEcsSystem
{
public:

	PythonObject pythonObject;

	virtual void Init(Scene* scene) override;
	virtual void Awake(Scene* scene) override;
	virtual void Start(Scene* scene) override;
	virtual void OnDrawGizmo(Scene* scene) override;
	virtual void FixedUpdate(Scene* scene) override;
	virtual void Update(Scene* scene) override;
	virtual void LateUpdate(Scene* scene) override;
	virtual void Render(Shader& shader, Scene* scene) override;
	virtual void OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data) override;
};

