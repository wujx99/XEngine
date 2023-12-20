#include <XEngine.h>


#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer :public XEg::Layer
{
public:
	ExampleLayer()
		:Layer("Example"),m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),m_CameraPosition(0.f)
	{
		// to draw triangle
		m_VertexArray.reset(XEg::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 0.1f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 0.1f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};
		std::shared_ptr<XEg::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(XEg::VertexBuffer::Create(vertices, sizeof(vertices)));


		XEg::BufferLayout layout = {
			{XEg::ShaderDataType::Float3,"a_Position", },
			{XEg::ShaderDataType::Float4,"a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		unsigned int indexs[3] = {
			0,1,2,
		};
		std::shared_ptr<XEg::IndexBuffer> indexBuffer;
		indexBuffer.reset(XEg::IndexBuffer::Create(indexs, sizeof(indexs) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA.reset(XEg::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<XEg::VertexBuffer> squareVB;
		squareVB.reset(XEg::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ XEg::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<XEg::IndexBuffer> squareIB;
		squareIB.reset(XEg::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Shader
		std::string vertexSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			layout(location=0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position*0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(XEg::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(XEg::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}
	virtual void OnUpdate(XEg::TimeStep ts) override
	{
		if (XEg::Input::IsKeyPressed(XE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (XEg::Input::IsKeyPressed(XE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (XEg::Input::IsKeyPressed(XE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (XEg::Input::IsKeyPressed(XE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (XEg::Input::IsKeyPressed(XE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (XEg::Input::IsKeyPressed(XE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		glm::vec4 color(.1, .1, .1, 1);
		XEg::RenderCommand::SetClearColor(color);
		XEg::RenderCommand::Clear();

		m_Camera.SetPostion(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		XEg::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		std::dynamic_pointer_cast<XEg::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				XEg::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
	}

	virtual void OnEvent(XEg::Event& event)
	{
		
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:
	
	std::shared_ptr<XEg::Shader> m_Shader;
	std::shared_ptr<XEg::VertexArray> m_VertexArray;

	std::shared_ptr<XEg::Shader> m_FlatColorShader;
	std::shared_ptr<XEg::VertexArray> m_SquareVA;

	XEg::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public XEg::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox () = default;
	

};

XEg::Application* XEg::CreateApplication()
{
	return new Sandbox();
}

