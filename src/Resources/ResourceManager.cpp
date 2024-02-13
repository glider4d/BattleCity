#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executablePath) : m_path(executablePath) {
	m_path = m_path.substr(0, executablePath.find_last_of("/\\"));

}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const{
	std::ifstream f;

 
	f.open(m_path + "\\" + relativeFilePath, std::ios::in | std::ios::binary);
	if (!f.is_open()) {
		std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

 
 

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexString = getFileString(vertexPath);

 	if (vertexString.empty()) {
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}


	std::string fragmentString = getFileString(fragmentPath);

 
	if (fragmentString.empty()) {
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}

	//std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	auto pairResult = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString));
	if (!pairResult.second) {
		std::cerr << "Emplace to map error!" << std::endl;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = pairResult.first->second;

	if (newShader->isCompiled()) {
		return newShader;
	}
	std::cerr << "Can't load shader program:\n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName) {
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end()) {
		return it->second;
	}
	std::cerr << "Can't find the shader program: " << shaderName << std::endl;
	return nullptr;
}
