#include "xepch.h"
#include "LayerStack.h"
namespace XEg
{
	LayerStack::LayerStack()
		:m_LayerIndex(0)
	{
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_Layers.emplace(m_Layers.begin()+m_LayerIndex, layer);
		m_LayerIndex++;
	}
	void LayerStack::PushOverLayer(Layer* overlay)
	{
		overlay->OnAttach();
		m_Layers.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto  itr = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (itr != m_Layers.begin() + m_LayerIndex)
		{
			layer->OnDetach();
			m_Layers.erase(itr);
			m_LayerIndex--;
		}
			
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto  itr = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (itr != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(itr);

		}
	}
}