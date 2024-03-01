#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


namespace Renderer {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray(VertexArray&&);
		VertexArray& operator=(VertexArray&&) noexcept;



		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
		void bind() const;
		void unbind() const;
		GLuint GetID() { return m_id; }
	private:
		GLuint m_id = 0;
		unsigned int m_elementsCount = 0;
	};
}