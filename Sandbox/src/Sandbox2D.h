#pragma once

#include "XEngine.h"

class Sandbox2D : public XEg::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(XEg::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(XEg::Event& event) override;

private:
	XEg::OrthographicCameraController m_CameraController;

	// temp
	XEg::Ref<XEg::VertexArray> m_SquareVA;
	XEg::Ref<XEg::Shader> m_FlatColorShader;
	XEg::Ref<XEg::Framebuffer> m_Framebuffer;
	XEg::Ref<XEg::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { .2f, .3f, .8f, 1.f };

	
};