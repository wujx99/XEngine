#include "xepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace XEg
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: 
			XE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		
		}
		
		XE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indexs, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			XE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indexs, count);
		
		}
	
		XE_CORE_ASSERT(false, "Unknown RendererAPI!");
	}
}