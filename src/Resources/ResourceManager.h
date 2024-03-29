#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RenderEngine {
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
}

class ResourceManager final {
public:
	static void setExecutablePath(const std::string& executablePath);
	static void unloadAllResources();
	~ResourceManager() = delete;
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(const ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;

	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);

	static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);

	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);

	static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);

	static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(std::string textureName,
		std::string texturePath,
		std::vector<std::string> subTextures,
		const unsigned int subTextureWidth,
		const unsigned int subTextureHight);
private:
	static std::string  getFileString(const std::string& relativeFilePath);
	//typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	using ShaderProgramsMap = std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>>;
	static ShaderProgramsMap m_shaderPrograms;


	//typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;

	using TexturesMap = std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>>;

	using SpritesMap = std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>>;
	using AnimatedSpritesMap = std::map<const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>>;

	static TexturesMap m_textures;

	static SpritesMap m_sprites;

	static AnimatedSpritesMap m_animatedSprites;

	static std::string m_path;
};