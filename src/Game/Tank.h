#pragma once
#include <memory>
#include <glm/vec2.hpp>



namespace RenderEngine {
	class Sprite;
	class AnimatedSprite;
};

class Tank final {
public:
	enum class EOrientation {
		Top,
		Bottom,
		Left,
		Right
	};

	Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position);
	void render() const;
	void setOrientatnion(const EOrientation eOrientation);
	void move(const bool move);
	void update(const uint64_t delta);

private:
	EOrientation m_eOrientation;
	std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;
	bool m_move;
	float m_velocity;
	glm::vec2 m_position;
	glm::vec2 m_moveOffset;
};