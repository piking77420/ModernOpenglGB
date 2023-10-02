#pragma once
#include<Python.h>
#include <conio.h>
#include "Core/ECS/IECSSystem.h"
#include "Core/Python/PythonObject.h"
#include "Ressources/IResources/IResource.h"


class PythonScript : public IResource,public IEcsSystem
{
public:


	virtual void Init(Scene* scene) override;
	virtual void Awake(Scene* scene) override;
	virtual void Start(Scene* scene) override;
	virtual void OnDrawGizmo(Scene* scene) override;
	virtual void FixedUpdate(Scene* scene) override;
	virtual void Update(Scene* scene) override;
	virtual void LateUpdate(Scene* scene) override;
	virtual void Render(Shader& shader, Scene* scene) override;
	virtual void OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data) override;


	PythonScript() = delete;
	PythonScript(const fs::path& FilePath);

};

