#pragma once


class Scene;


class ISerialzable
{
public:
	virtual void OnSerialize(Scene* scene) const {};
	virtual void OnDeSerialize(Scene* scene) const {};
};

