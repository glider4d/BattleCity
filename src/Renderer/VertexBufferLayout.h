#pragma once
#include <vector>
#include <glad/glad.h>

namespace RenderEngine {
	struct VertexBufferLayoutElement {
		GLint count;
		GLenum type;
		GLboolean nomrialized;
		unsigned int size;
	};


	class VertexBufferLayout {
	public:
		VertexBufferLayout();

		void reserveElements(const size_t count);
		unsigned int getStride() const { return m_stride; }
		const std::vector<VertexBufferLayoutElement>& getLayoutElements() const { return m_layoutElements; }
		void addElementLayoutFloat(const unsigned int count, const bool nomralized);

 	private:
		std::vector<VertexBufferLayoutElement> m_layoutElements;
		unsigned int m_stride; //it's step
	};
}