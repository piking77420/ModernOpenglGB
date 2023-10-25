#pragma once
#include<Core/CoreEngine.h>

enum InputEventType 
{
	KEYPRESS = BIT(0)
	,MOUSERIGHTCLICK = BIT(1)
	,MOUSELEFTCLICK = BIT(2)
};



class InputEvent
{
public:

	InputEventType eventType = {};
	virtual std::string ToString() = 0;

};


class MouseRightClick : public InputEvent
{
public:

	uint32_t eventType = KEYPRESS | MOUSERIGHTCLICK;
	std::string ToString() override
	{
		return "MouseRightClick";
	}

};



class MouseLeftClick : public InputEvent
{
public:

	uint32_t eventType = KEYPRESS | MOUSELEFTCLICK;
	std::string ToString() override
	{
		return "MouseLeftClick";
	}

};


class IsKeyPress : public InputEvent
{
public:

	uint32_t eventType = KEYPRESS ;
	std::string ToString() override
	{
		return std::to_string(keyCode);
	}

	IsKeyPress() = delete;
	IsKeyPress(uint32_t _keyCode) { _keyCode = keyCode; };

	const uint32_t GetKeyCode() { return keyCode; }

private:
	uint32_t keyCode = -1;

};