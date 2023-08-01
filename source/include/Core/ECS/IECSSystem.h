#pragma once



class Scene;
class Register;

class IEcsSystem
{
public:


	virtual void Init(Scene* scene) {};

	virtual void Awake(Scene* scene) {};
	virtual void Start(Scene* scene){};

	
	virtual void FixedUpdate(Scene* scene){};
	virtual void Update(Scene* scene){};
	virtual void LateUpdate(Scene* scene){};

	virtual void Render(Scene* scene){};

	virtual ~IEcsSystem(){};

private:

};

