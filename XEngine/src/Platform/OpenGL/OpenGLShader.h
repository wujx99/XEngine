#pragma once
#include "XEngine/Renderer/Shader.h"
#include <string>
#include <map>

namespace XEg
{
	// todo moved!
	typedef unsigned int GLenum;

	class OpenGLShader :public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& float3);
		void UploadUniformInt(const std::string& name, int value);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSource);
	private:
		uint32_t m_RendererID;
	};
}