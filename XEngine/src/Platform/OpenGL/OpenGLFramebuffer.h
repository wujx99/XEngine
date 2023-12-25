#pragma once
#include "XEngine/Renderer/Framebuffer.h"
namespace XEg
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();
		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_RendererID; };
		virtual const FramebufferSpecification& GetSpecificaiton() const override { return m_Specification; };
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FramebufferSpecification m_Specification;
	};
}
