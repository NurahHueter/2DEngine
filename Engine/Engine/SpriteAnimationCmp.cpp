#pragma once
#include"pch.h"
#include"SpriteAnimationCmp.h"
#include"SpriteRenderCmp.h"
#include "GameObject.h"
namespace mmt_gd
{
	SpriteAnimationCmp::SpriteAnimationCmp(
		GameObject& gameObject,
		sf::RenderWindow& renderWindow,
		std::weak_ptr<sf::Texture> p_texture,
		const int TILING_X,
		const int TILING_Y,
		bool vertical,
		float animationSpeed)
		: SpriteRenderCmp(gameObject, renderWindow, p_texture),
		TILING_X(TILING_X), TILING_Y(TILING_Y), vertical(vertical), m_animationSpeed(animationSpeed){};

	bool SpriteAnimationCmp::init()
	{
		if (sprite)
		{
			if(std::shared_ptr<sf::Texture> tempP = p_texture.lock()) 
			{
				sprite->setTextureRect(sf::IntRect(0, 0, tempP->getSize().x / TILING_X, tempP->getSize().y / TILING_Y));
			}
			else
			{
				return false;
			}
			return true;
		}
		return false;
	}

	void SpriteAnimationCmp::update(float deltaTime)
	{
		m_animationTime += deltaTime * m_animationSpeed;
		m_animationFrame = (int)m_animationTime % m_animations[m_currentAnimation];
		int spriteOffsetX;
		int spriteOffsetY;
		if (vertical)
		{
			spriteOffsetX = m_animations[m_currentAnimation] * sprite->getTextureRect().width;
			spriteOffsetY = m_animationFrame * sprite->getTextureRect().height;
		}
		else
		{
			spriteOffsetX = m_animationFrame * sprite->getTextureRect().width;
			spriteOffsetY = m_animations[m_currentAnimation] * sprite->getTextureRect().height;
		}
		sprite->setTextureRect(sf::IntRect(
			spriteOffsetX,
			spriteOffsetY,
			sprite->getTextureRect().width,
			sprite->getTextureRect().height));
	}

	void SpriteAnimationCmp::addAnimation(std::string animation, int frames)
	{
			m_animations[animation] = frames;
	}
}