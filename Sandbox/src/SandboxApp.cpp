#include <XEngine.h>
#include <iostream>

class Sandbox : public XEg::Application
{
public:
	Sandbox () = default;
	virtual ~Sandbox () = default;
	/*virtual void Run() override 
	{

		while (true)
		{
			
		}
	}*/
private:

};

XEg::Application* XEg::CreateApplication()
{
	return new Sandbox();
}

