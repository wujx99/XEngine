#include <XEngine.h>
#include <iostream>

class Sandbox : public XEg::Application
{
public:
	Sandbox () = default;
	virtual ~Sandbox () = default;
	virtual void Run() override 
	{
		while (true)
		{
			std::cout << "this is the first app i create!" << std::endl;
		}
	}
private:

};

XEg::Application* XEg::CreateApplication()
{
	return new Sandbox();
}

