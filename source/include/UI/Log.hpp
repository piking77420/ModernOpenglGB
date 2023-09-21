#pragma once
#include "ImguiLayer.h"


class Log : public ImguiLayer
{
public:


	std::string WindowName;
	 void UpdateLayer(Project& currentProject, std::vector<InputEvent*>& inputsEvents) override;

	 Log() {
		 WindowName = "Log";
	 }
	 ~Log() override{};

protected:
	void ListenToInput(Project& currentProject,std::vector<InputEvent*>& inputEvent) override;

private:
	static char buffer[36];
	static inline bool Isopen = true;
	static inline bool AutoScroll = true;

};

