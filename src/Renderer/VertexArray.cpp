#include "VertexArray.h"

namespace RenderEngine {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_id);
	}
	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_id);
	}

	VertexArray& VertexArray::operator=(VertexArray&& vertexArray) noexcept {
		m_id = vertexArray.m_id;
		vertexArray.m_id = 0;
		return *this;
	}
	

 


	void VertexArray::bind() const {
		glBindVertexArray(m_id);
	}
	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}

	VertexArray::VertexArray(VertexArray&& vertexArray) {
		m_id = vertexArray.m_id;
		vertexArray.m_id = 0;

	}

	void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) {
		bind();
		vertexBuffer.bind();
		GLbyte* offset = nullptr;
		const auto& layoutElements = layout.getLayoutElements();
		for (unsigned int i = 0; i < layoutElements.size(); ++i) {
			const auto& currentLayoutElement = layoutElements[i];
			GLuint currentAttribIndex = m_elementsCount + i;
			glEnableVertexAttribArray(currentAttribIndex);
			glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.nomrialized, layout.getStride(), offset);
			offset += currentLayoutElement.size;
		}

		m_elementsCount += layoutElements.size();
	}

}