#pragma once
#pragma once 
#include "IRenderComponent.h"
#include "SpriteRenderCmp.h"
#include<map>

namespace mmt_gd
{
	class Sprite;
	class Texture;
	class GameObject;
	class SpriteAnimationCmp : public SpriteRenderCmp
	{
	public:
		SpriteAnimationCmp(
			GameObject& gameObject,
			sf::RenderWindow& renderWindow,
			std::weak_ptr<sf::Texture> p_texture,
			int TILING_X,
			int TILING_Y,
			bool vertical,
			float animationSpeed);

		~SpriteAnimationCmp() {};
		bool init() override;
		void update(float deltaTime) override;

		/**
		 * \brief 
		 *Add a animation row to the sprite
		 */
		void addAnimation(std::string animation, int frames);
		/**
		 * \brief
		 *Add animations to the sprite
		 */
		void addAnimation(std::vector<std::pair<std::string, int>> animations);

		void setCurrentAnimation(std::string animtion)
		{
			if (m_animations[animtion])
			{
				m_currentAnimation = animtion;
			}
		};
		std::string getCurrentAnimation(std::string)
		{
			return m_currentAnimation;
		};

		int getCurrentAnimationIndex();
	protected:
		bool vertical;
		const int TILING_X;
		const int TILING_Y;
		float m_animationTime = 0;
		float m_animationSpeed;
		int m_animationFrame = 0;
		std::string m_currentAnimation;
		std::map<std::string, int> m_animations;
		std::vector<std::string> m_animationOrder;
	};
}