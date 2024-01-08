#pragma once

#include "XEngine/Core/Base.h"
#include "XEngine/Core/Application.h"

#ifdef XE_PLATFORM_WINDOWS

extern XEg::Application* XEg::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	XEg::Log::Init();
	
	XE_PROFILE_BEGIN_SESSION("Startup", "XEngineProfile-Startup.json");
	auto app = XEg::CreateApplication({argc, argv});
	XE_PROFILE_END_SESSION();

	XE_PROFILE_BEGIN_SESSION("Runtime", "XEngineProfile-Runtime.json");
	app->Run();
	XE_PROFILE_END_SESSION();

	XE_PROFILE_BEGIN_SESSION("Shutdown", "XEngineProfile-Shutdown.json");
	delete app;
	XE_PROFILE_END_SESSION();

}
#endif
