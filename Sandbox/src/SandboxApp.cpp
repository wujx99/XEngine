#include <XEngine.h>
#include <iostream>

class Sandbox : public XEg::Application
{
public:
	Sandbox () = default;
	~Sandbox () = default;
	/*virtual void Run() override 
	{

		while (true)
		{
			
		}
	}*/

};

XEg::Application* XEg::CreateApplication()
{
	return new Sandbox();
}

