#include "xepch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
namespace XEg
{
	static GLenum ShaderTypeFormString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		XE_CORE_ASSERT(false, "unkonw shader type");
		return 0;
	}
	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::string source = ReadFile(path);
		auto shaderSource = PreProcess(source);
		Compile(shaderSource);

		// Extract name from filepath
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		m_Name = path.substr(lastSlash, count);
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		:m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSource;
		shaderSource[GL_VERTEX_SHADER] = vertexSrc;
		shaderSource[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSource);

		
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);

	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);

	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);

	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& float3)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, float3.x, float3.y, float3.z);
	}
	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in|std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			XE_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSource;
		const char* token = "#type";
		size_t tokenLength = strlen(token);
		size_t pos = source.find(token, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find("\n", pos);
			XE_CORE_ASSERT(eol != std::string::npos, "Syntax error!");

			size_t begin = pos + tokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			XE_CORE_ASSERT(ShaderTypeFormString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\n", eol);
			pos = source.find(token, nextLinePos);
			shaderSource[ShaderTypeFormString(type)] = 
				source.substr(nextLinePos, pos - (nextLinePos == std::string::npos? source.size()-1:nextLinePos));

		}

		return shaderSource;
	}
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSource)
	{
		GLuint program = glCreateProgram();

		XE_CORE_ASSERT(shaderSource.size() <= 2, "We only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;

		int glShaderIDIndex = 0;
		for (auto& kv : shaderSource)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				XE_CORE_ERROR("{0}", infoLog.data());
				XE_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);
		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			XE_CORE_ERROR("{0}", infoLog.data());
			XE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);
	}
}

