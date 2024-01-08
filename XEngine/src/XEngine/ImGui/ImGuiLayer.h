#pragma once

#include "XEngine/Core/Layer.h"

#include "XEngine/Event/ApplicationEvent.h"
#include "XEngine/Event/KeyEvent.h"
#include "XEngine/Event/MouseEvent.h"


namespace XEg
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
	};
}
