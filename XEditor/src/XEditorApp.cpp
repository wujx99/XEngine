#include <XEngine.h>
#include <XEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace XEg
{
	class XEditor : public Application
	{
	public:
		XEditor(ApplicationCommandLineArgs args)
			:Application("XEngine Editor", args)
		{
			PushLayer(new EditorLayer());
		}
		~XEditor() = default;


	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new XEditor(args);
	}
}


