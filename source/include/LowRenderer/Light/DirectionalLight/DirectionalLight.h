#pragma once
#include<Core/DataStructure/Component/Component.h>
#include<LowRenderer/Light/Light.h>
#include "Core/DataStructure/Entity/Entity.h"

class Light;
class Shader;

class DirectionalLight : public Light
{
public:


	//sMatrix4X4& SetLookAtMatrix();
	const Matrix4X4& GetLookAtMatrix() const ;

	Vector3 Direction;
	void ImguiWindowComponents() override;
	void SetUniform(Shader* shader) const override;
	void Update(Scene* scene) override;

	DirectionalLight( const Vector4& _ambiant, const Vector4& _diffuse , const Vector4& _specular, const Vector4& _Direction);

	DirectionalLight();
	~DirectionalLight();

private:


};

