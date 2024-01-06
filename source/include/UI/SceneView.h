#pragma once
#include"ImguiLayer.h" 
#include "FrameBuffer/FrameBuffer.h"
#include "Cam/Camera.h"
#include "FrameBuffer/MultiSamples/MultiSamples.h"

enum SceneViewEnum
{
	EDITOR,
	GAME
};




class SceneView : public ImguiLayer
{
public:

	void BindSceneView();
	virtual void UpdateLayer(Project& currentProject) override;
	virtual void RendererLayer(Project& currentProject)override;

	void ResizeBuffer(int widht, int heignt);

	void Gizmo(Project& currentProject);

	SceneView();
	~SceneView();
	SceneViewEnum sceneViewEnum = EDITOR;

	MultiSamples m_SceneBuffer;
	//FrameBuffer m_SceneBuffer;

	Camera m_cam;
private:


};

