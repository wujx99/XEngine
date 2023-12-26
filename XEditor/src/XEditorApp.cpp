#include <XEngine.h>
#include <XEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace XEg
{
	class XEditor : public Application
	{
	public:
		XEditor()
			:Application("XEngine Editor")
		{
			PushLayer(new EditorLayer());
		}
		~XEditor() = default;


	};

	Application* CreateApplication()
	{
		return new XEditor();
	}
}


