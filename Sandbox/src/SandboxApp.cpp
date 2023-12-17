#include <XEngine.h>
#include <iostream>
#include "imgui/imgui.h"
class ExampleLayer :public XEg::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}
	virtual void OnUpdate() override
	{
		if (XEg::Input::IsKeyPressed(XE_KEY_TAB))
			XE_CLIENT_TRACE("Tab key is pressed!(poll)");
	}

	virtual void OnEvent(XEg::Event& event)
	{
		if (event.GetEventType() == XEg::EventType::KeyPressed)
		{
			XEg::KeyPressedEvent& e = (XEg::KeyPressedEvent&)event;
			if (e.GetKeyCode() == XE_KEY_TAB)
				XE_CLIENT_TRACE("Tab key is pressed!(event)");
			XE_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();
	}

};

class Sandbox : public XEg::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox () = default;
	

};

XEg::Application* XEg::CreateApplication()
{
	return new Sandbox();
}

