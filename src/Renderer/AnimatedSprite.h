#pragma once
#include "Sprite.h"
#include <map>
#include <vector>

namespace RenderEngine {
	class AnimatedSprite final : public Sprite {
	public:
		AnimatedSprite(const std::shared_ptr<Texture2D> pTexture,
			const std::string initialSubTexture,
			const std::shared_ptr<ShaderProgram> pShaderProgram,
			const glm::vec2& position = glm::vec2(0.f),
			const glm::vec2& size = glm::vec2(1.f),
			const float rotation = 0.f);

 		void insertState(std::string state, std::vector<std::pair<std::string,uint64_t>> subTexturesDuration);
		void render() const override;

		void setState(const std::string& newState);
		void update(const uint64_t delta);

		virtual ~AnimatedSprite() {}
	private:
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationDurations;
		size_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0;
		mutable bool m_dirty = false;
	};
}