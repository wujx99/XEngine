#include "xepch.h"
#include "Buffer.h"

#include "XEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace XEg
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			XE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		
		}
		
		XE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indexs, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indexs, count);
		
		}
	
		XE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}