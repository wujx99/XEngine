#pragma once
#include "XEngine/Renderer/Shader.h"
#include <string>
namespace XEg
{
	class OpenGLShader :public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& float3);
		void UploadUniformInt(const std::string& name, int value);
	private:
		uint32_t m_RendererID;
	};
}