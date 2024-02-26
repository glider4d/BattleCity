#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace Renderer {
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
}

class ResourceManager final {
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;


	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(const ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

	std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

	std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);

	std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(std::string textureName,
		std::string texturePath,
		std::vector<std::string> subTextures,
		const unsigned int subTextureWidth,
		const unsigned int subTextureHight);
private:
	std::string  getFileString(const std::string& relativeFilePath) const;
	//typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	using ShaderProgramsMap = std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>>;
	ShaderProgramsMap m_shaderPrograms;


	//typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;

	using TexturesMap = std::map<const std::string, std::shared_ptr<Renderer::Texture2D>>;

	using SpritesMap = std::map<const std::string, std::shared_ptr<Renderer::Sprite>>;
	using AnimatedSpritesMap = std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>>;

	TexturesMap m_textures;

	SpritesMap m_sprites;

	AnimatedSpritesMap m_animatedSprites;

	std::string m_path;
};