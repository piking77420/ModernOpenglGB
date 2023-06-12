#include "LowRenderer/Ui/UIRenderer.h"
#include "App/App.h"
#include "LowRenderer/Cam/Camera.h"
#include "Ressources/Scene/Scene.h"
float BaseImage[] =
{
-1.000000 ,1.000000 ,0.000000,
 1.000000, 1.000000, 0.000000,
-1.000000, -1.000000, 0.000000,
 1.000000, 1.000000, 0.000000,
 -1.000000 ,-1.000000, 0.000000,
 1.000000 ,-1.000000, 0.000000,
};



UIRenderer::~UIRenderer()
{
}



UIRenderer::UIRenderer(Entity& entity) : RendererComponent(entity)
{
	for (size_t i = 0; i < 18; i += 3)
	{
		m_Model.vertexVector.push_back(Vector3(BaseImage[i], BaseImage[i + 1], BaseImage[i + 2]));
	}

	m_Model.InitBuffers();

}
void UIRenderer::Draw(Scene* scene, Shader* shader)
{
	Matrix4X4 orthoMatrix = Matrix4X4().OrthoGraphicMatrix(-9.6, 9.6, -5.4, 5.4, 0, 1000);

	Matrix4X4 model = EntityAttachTo.transform.GetMatrix();
	
	shader->Use();
	texure.BindTexture();	
	shader->SetMaxtrix("model", model.GetPtr());
	shader->SetMaxtrix("Ortho", orthoMatrix.GetPtr());

	// Draw The Object
	//m_Model.Draw();
	texure.UnBindTexture();

}