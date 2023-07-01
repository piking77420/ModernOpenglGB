#pragma once
#include<Core/DataStructure/Component/Component.h>
#include<Mathf.h>
#include<vector>

class AppData;

class Transform : public Component
{
public:


	Matrix4X4& SetMatrix();
	const Matrix4X4& GetMatrix() const;
	const Matrix4X4& GetLocal() const;
	const Vector3 GetWordlPos() const;
	const Vector3 GetWordlPos();
	

	void SetParent(Transform& parents);
	void AddChildren(Transform* Childs);
	void ImguiWindowComponents() override;
	void Update(Scene* scene) override;


	const Transform* Parents;
	Matrix4X4 m_GlobalMatrix;
	std::vector<Transform*> Childrens;

	Vector3& SetPos();
	Vector3& SetRotation();
	Vector3& SetScale();


	const Vector3 GetPos() const ;
	const Vector3 GetRotation() const ;
	const Vector3 GetScale() const ;

	Transform(Entity& currentObject, const Vector3& _pos, const Vector3& _rotation, const Vector3& _scaling);
	Transform(Entity& currentObject);
	~Transform();

private:
	void UpdateMatrix();
	int IdTransform;
	static int TransformGlobalID;
	Matrix4X4 m_LocalMatrix;
	Vector3 pos;
	Vector3 rotate;
	Vector3 scale;
	bool TransformChange;

};

