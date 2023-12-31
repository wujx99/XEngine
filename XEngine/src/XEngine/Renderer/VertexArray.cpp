#include "xepch.h"
#include "VertexArray.h"

#include "XEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace XEg
{
	Ref<VertexArray>VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();

		}

		XE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}