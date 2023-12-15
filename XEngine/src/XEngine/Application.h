#pragma once

namespace XEg {
	class Application
	{
	public:
		virtual ~Application() {};

		virtual void Run();
	private:

	};

	// to be define by CLIENT!
	Application* CreateApplication();
}


