#include <XEngine.h>
#include <XEngine/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public XEg::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}
	~Sandbox () = default;
	

};

XEg::Application* XEg::CreateApplication()
{
	return new Sandbox();
}

