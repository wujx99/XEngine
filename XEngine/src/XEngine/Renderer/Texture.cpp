#include "xepch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "Renderer.h"
namespace XEg
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);

		}
		XE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}