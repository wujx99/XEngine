#pragma once

#ifdef XE_PLATFORM_WINDOWS

extern XEg::Application* XEg::CreateApplication();

int main(int argc, char** argv)
{
	printf("XEngine Platform");
	auto app = XEg::CreateApplication();
	app->Run();
	delete app;
}
#endif
