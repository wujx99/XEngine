#pragma once
#include "XEngine.h"

class ExampleLayer :public XEg::Layer
{
public:
	ExampleLayer();
		
	~ExampleLayer();
		
	virtual void OnUpdate(XEg::TimeStep ts) override;
	virtual void OnEvent(XEg::Event& event) override;
	virtual void OnImGuiRender() override;

private:

	XEg::Ref<XEg::Shader> m_Shader;
	XEg::ShaderLibrary m_ShaderLibrary;
	XEg::Ref<XEg::VertexArray> m_VertexArray;

	XEg::Ref<XEg::Shader> m_FlatColorShader;
	XEg::Ref<XEg::VertexArray> m_SquareVA;

	XEg::Ref<XEg::Texture2D> m_Texture;
	XEg::Ref<XEg::Texture2D> m_LogoTexture;

	XEg::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};