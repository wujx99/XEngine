#pragma once

#include "XEngine/Renderer/RendererAPI.h"

namespace XEg
{
	class OpenGLRendererAPI :public RendererAPI
	{
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}