#pragma once
#include<Python.h>
#include <conio.h>

class PythonObject
{
public:

	PythonObject()
	{
		Py_Initialize();
	}
	PythonObject(PyObject* _p) : m_p(_p)
	{
		Py_Initialize();
	}

	void SetObject(PyObject* _p)
	{
		m_p = _p;
	}

	const PyObject* GetObject() const
	{
		return m_p;
	}

	PyObject* GetObject()
	{
		return m_p;
	}

	PyObject* operator->()
	{
		return m_p;
	}

	const PyObject* operator->() const 
	{
		return m_p;
	}

	bool IsNull()
	{
		return m_p ? true : false;
	}

	~PythonObject()
	{
		Py_Finalize();
	}
private:
	PyObject* m_p = nullptr;
};

