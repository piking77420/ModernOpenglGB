#pragma once
#include <vector>

#define ImplementIEcsSystem \
void Init(Scene* scene) override; \
void Awake(Scene* scene) override; \
void Start(Scene* scene) override; \
void FixedUpdate(Scene* scene) override; \
void Update(Scene* scene) override; \
void LateUpdate(Scene* scene) override; \
void Render(Scene* scene) override; \
void OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data) override;

class Scene;
class Register;
class Shader;

__interface IEcsSystem
{
public:

	
	virtual void Init(Scene* scene) {};

	virtual void Awake(Scene* scene) {};
	virtual void Start(Scene* scene){};

	
	virtual void FixedUpdate(Scene* scene){};
	virtual void Update(Scene* scene){};
	virtual void LateUpdate(Scene* scene){};

	virtual void Render(Scene* scene){};
	virtual void OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data) {};




};

/*
* 
void RendererSystem::Init(Scene* scene)
{

};

void RendererSystem::Awake(Scene* scene)
{

};
void RendererSystem::Start(Scene* scene)
{

};


void RendererSystem::FixedUpdate(Scene* scene) 
{

};
void RendererSystem::Update(Scene* scene) 
{

};
void RendererSystem::LateUpdate(Scene* scene) 
{

};

void RendererSystem::Render(Scene* scene) 
{

};
void RendererSystem::OnResizeData(std::vector<uint8_t>* data) 
{

};
* 
*/