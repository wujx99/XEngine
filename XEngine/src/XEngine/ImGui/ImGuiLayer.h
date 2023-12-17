#pragma once

#include "XEngine/Layer.h"

#include "XEngine/Event/ApplicationEvent.h"
#include "XEngine/Event/KeyEvent.h"
#include "XEngine/Event/MouseEvent.h"


namespace XEg
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}