#include "Ecs/PythonScript.h"

void PythonScript::Init(Scene* scene)
{
}

void PythonScript::Awake(Scene* scene)
{
}

void PythonScript::Start(Scene* scene)
{
}

void PythonScript::OnDrawGizmo(Scene* scene)
{
}

void PythonScript::FixedUpdate(Scene* scene)
{
}

void PythonScript::Update(Scene* scene)
{
}

void PythonScript::LateUpdate(Scene* scene)
{
}

void PythonScript::Render(Shader& shader, Scene* scene)
{
}

void PythonScript::OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data)
{
}

PythonScript::PythonScript(const fs::path& FilePath)
{
	return;

	Py_Initialize();
	PyObject* obj = Py_BuildValue("s", FilePath.c_str());
	FILE* file = _Py_fopen_obj(obj, "r+");
	if (file != NULL)
	{
		std::string c = FilePath.generic_string();
		PyRun_SimpleFile(file, c.c_str());
	}


}
