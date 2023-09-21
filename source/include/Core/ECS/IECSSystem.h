#pragma once
#include <vector>
#define ImplementIEcsSystem \
void Init(Scene* scene) override; \
void Awake(Scene* scene) override; \
void Start(Scene* scene) override; \
void OnDrawGizmo(Scene* scene) override;\
void FixedUpdate(Scene* scene) override; \
void Update(Scene* scene) override; \
void LateUpdate(Scene* scene) override; \
void Render(Shader& shader,Scene* scene) override; \
void OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data) override;

class Scene;
class Register;
class Shader;



class IEcsSystem
{
public:

	
	virtual void Init(Scene* scene)  = 0;

	virtual void Awake(Scene* scene)  = 0;
	virtual void Start(Scene* scene) = 0;

	virtual void OnDrawGizmo(Scene* scene) = 0;
	
	virtual void FixedUpdate(Scene* scene) = 0;
	virtual void Update(Scene* scene) = 0;
	virtual void LateUpdate(Scene* scene) = 0;

	virtual void Render(Shader& shader,Scene* scene) = 0;
	virtual void OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data)  = 0;

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
void RendererSystem::OnDrawGizmo(Scene* scene)
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

void RendererSystem::Render(Shader& shader, Scene* scene) 
{

};
void RendererSystem::OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data) 
{

};
* 
*/