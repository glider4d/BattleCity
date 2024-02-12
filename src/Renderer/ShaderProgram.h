#pragma once
#include <glad/glad.h>
#include <string>

namespace Renderer {

	class ShaderProgram final {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		void use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&) = delete;

		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};
}