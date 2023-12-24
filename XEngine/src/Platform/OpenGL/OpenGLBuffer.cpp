#include "xepch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace XEg
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		XE_PROFILE_FUNCTION();

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		

	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		XE_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		XE_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

	}
	void OpenGLVertexBuffer::UnBind() const
	{
		XE_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indexes, uint32_t count)
		:m_Count(count)
	{
		XE_PROFILE_FUNCTION();

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, count*sizeof(uint32_t), indexes, GL_STATIC_DRAW);

	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		XE_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		XE_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	}
	void OpenGLIndexBuffer::UnBind() const
	{
		XE_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
}