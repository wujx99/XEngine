#include "xepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace XEg
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case XEg::ShaderDataType::Float:    return GL_FLOAT;
		case XEg::ShaderDataType::Float2:   return GL_FLOAT;
		case XEg::ShaderDataType::Float3:   return GL_FLOAT;
		case XEg::ShaderDataType::Float4:   return GL_FLOAT;
		case XEg::ShaderDataType::Mat3:     return GL_FLOAT;
		case XEg::ShaderDataType::Mat4:     return GL_FLOAT;
		case XEg::ShaderDataType::Int:      return GL_INT;
		case XEg::ShaderDataType::Int2:     return GL_INT;
		case XEg::ShaderDataType::Int3:     return GL_INT;
		case XEg::ShaderDataType::Int4:     return GL_INT;
		case XEg::ShaderDataType::Bool:     return GL_BOOL;
		}

		XE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		XE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		m_VertexBuffers.push_back(vertexBuffer);

		auto layout = vertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
				);
			m_VertexBufferIndex++;
		}
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
	
}