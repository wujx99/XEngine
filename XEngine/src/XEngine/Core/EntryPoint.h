#pragma once

#include "Core.h"

#ifdef XE_PLATFORM_WINDOWS

extern XEg::Application* XEg::CreateApplication();

int main(int argc, char** argv)
{
	XEg::Log::Init();
	XE_CORE_WARN("Init logging");
	int a = 5;
	XE_CLIENT_INFO("the value a = {}", a);

	printf("XEngine Platform\n");
	auto app = XEg::CreateApplication();
	app->Run();
	delete app;
}
#endif
