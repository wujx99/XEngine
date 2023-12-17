#include <XEngine.h>
#include <iostream>

class ExampleLayer :public XEg::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}
	virtual void OnUpdate() override
	{
		//XE_CORE_INFO("Example Update!");
	}

	virtual void OnEvent(XEg::Event& event)
	{
		XE_CLIENT_TRACE("{0}",event);
	}

};

class Sandbox : public XEg::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverLay(new XEg::ImGuiLayer());
	}
	~Sandbox () = default;
	

};

XEg::Application* XEg::CreateApplication()
{
	return new Sandbox();
}

