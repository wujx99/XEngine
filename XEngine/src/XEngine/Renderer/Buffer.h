#pragma once
#include <cstdint>

namespace XEg
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool,
	};
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:
			return 4;
		case ShaderDataType::Float2:
			return 4 * 2;
		case ShaderDataType::Float3:
			return 4 * 3;
		case ShaderDataType::Float4:
			return 4 * 4;
		case ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case ShaderDataType::Int:
			return 4;
		case ShaderDataType::Int2:
			return 4 * 2;
		case ShaderDataType::Int3:
			return 4 * 3;
		case ShaderDataType::Int4:
			return 4 * 4;
		case ShaderDataType::Bool:
			return 1;
		}
		XE_CORE_ASSERT(false, "Unkonw Shader date type!");
		return 0;
	}
	struct BufferElement
	{
		std::string Name; //for debug
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:
				return 1;
			case ShaderDataType::Float2:
				return 2;
			case ShaderDataType::Float3:
				return 3;
			case ShaderDataType::Float4:
				return 4;
			case ShaderDataType::Mat3:
				return 3 * 3;
			case ShaderDataType::Mat4:
				return 4 * 4;
			case ShaderDataType::Int:
				return 1;
			case ShaderDataType::Int2:
				return 2;
			case ShaderDataType::Int3:
				return 3;
			case ShaderDataType::Int4:
				return 4;
			case ShaderDataType::Bool:
				return 1;
			}
			XE_CORE_ASSERT(false, "Unkonw Shader date type!");
			return 0;
		}
	};
	class BufferLayout
	{
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& bufferElements)
			:m_BufferElements(bufferElements)
		{
			CalcStrideAndOffset();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_BufferElements; }

		std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const{ return m_BufferElements.cbegin(); }
		std::vector<BufferElement>::const_iterator end() const{ return m_BufferElements.cend(); }
	private:
		void CalcStrideAndOffset()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& elem : m_BufferElements)
			{
				elem.Offset = offset;
				offset += elem.Size;
				m_Stride += elem.Size;
			}
		}
		std::vector<BufferElement> m_BufferElements;
		uint32_t m_Stride{ 0 };
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		// actual Constructor!!
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indexs, uint32_t count);
	};
}