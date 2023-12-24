#include "ExampleLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
ExampleLayer::ExampleLayer()
	:Layer("Example"), m_CameraController(1280.f / 720.f)
{
	// to draw triangle
	m_VertexArray = XEg::VertexArray::Create();

	float vertices[3 * 7] =
	{
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 0.1f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 0.1f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
	};
	XEg::Ref<XEg::VertexBuffer> vertexBuffer;
	vertexBuffer = XEg::VertexBuffer::Create(vertices, sizeof(vertices));


	XEg::BufferLayout layout = {
		{XEg::ShaderDataType::Float3,"a_Position", },
		{XEg::ShaderDataType::Float4,"a_Color"}
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);


	unsigned int indexs[3] = {
		0,1,2,
	};
	XEg::Ref<XEg::IndexBuffer> indexBuffer;
	indexBuffer = XEg::IndexBuffer::Create(indexs, sizeof(indexs) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);


	m_SquareVA = XEg::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};

	XEg::Ref<XEg::VertexBuffer> squareVB;
	squareVB = XEg::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ XEg::ShaderDataType::Float3, "a_Position" },
		{ XEg::ShaderDataType::Float2, "a_TexCoord"}
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	XEg::Ref<XEg::IndexBuffer> squareIB;
	squareIB = XEg::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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

	m_Shader = XEg::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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

	m_FlatColorShader = XEg::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);



	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = XEg::Texture2D::Create("assets/textures/Checkerboard.png");
	m_LogoTexture = XEg::Texture2D::Create("assets/textures/Chernologo.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);

}
ExampleLayer::~ExampleLayer()
{
}
void ExampleLayer::OnUpdate(XEg::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);


	glm::vec4 color(.1, .1, .1, 1);
	XEg::RenderCommand::SetClearColor(color);
	XEg::RenderCommand::Clear();


	XEg::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			XEg::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}
	auto textureShader = m_ShaderLibrary.Get("Texture");
	m_Texture->Bind();
	XEg::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

	m_LogoTexture->Bind();
	XEg::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

}

void ExampleLayer::OnEvent(XEg::Event& event)
{
	m_CameraController.OnEvent(event);
}

void ExampleLayer::OnImGuiRender() 
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}