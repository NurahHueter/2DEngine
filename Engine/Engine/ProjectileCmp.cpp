#pragma once
#include "pch.h"
#include "ProjectileCmp.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteAnimationCmp.h"
#include "VectorAlgebra2D.h"
#include "AnimationTypes.h"
#include "SpriteRenderCmp.h"

namespace mmt_gd
{
	ProjectileCmp::ProjectileCmp(GameObject& gameObject, std::vector<std::shared_ptr<GameObject>> projectiles, float timeToLife, float velocity, float shootIntervall)
		:IComponent(gameObject), m_velocity(velocity), m_timeToLife(timeToLife), m_shootIntervall(shootIntervall)
	{
		for (auto p : projectiles)
		{
			p->setActive(false);
			m_projectiles.emplace_back(p, timeToLife, sf::Vector2f(0.f, 0.f));
		}
	};

	void ProjectileCmp::update(float deltaTime)
	{
		if (lastSpawnTimer > 0)
		{
			lastSpawnTimer += deltaTime;
		}
		if (lastSpawnTimer > m_shootIntervall)
		{
			lastSpawnTimer = 0;
		}

		for (auto& p : m_projectiles)
		{
			if (std::get<0>(p)->isActive())
			{
				std::get<0>(p)->setPosition(
					std::get<0>(p)->getPosition()
					+ std::get<2>(p)
					* m_velocity
					* deltaTime);
				std::get<1>(p) -= deltaTime;

				if (std::get<1>(p) <= 0)
				{
					std::get<0>(p)->setActive(false);
					std::get<1>(p) = m_timeToLife;
				}
			}
		} 

		if (InputManager::instance().isKeyDown("shoot", gameObject.getPlayerIdx()))
		{
			shoot(InputManager::instance().getMousPosition());
		}
	}
	void ProjectileCmp::shoot(sf::Vector2f direction)
	{
		if (lastSpawnTimer == 0)
		{
			lastSpawnTimer += 0.1;
			for (auto& p : m_projectiles)
			{
				if (!std::get<0>(p)->isActive())
				{
					std::get<0>(p)->setActive(true);
					std::get<0>(p)->setPosition(getAlignment(gameObject, *std::get<0>(p)));

					direction = direction - std::get<0>(p)->getPosition();
					std::get<2>(p) = MathUtil::unitVector(direction);
					break;
				};
			}
		}
	}
	sf::Vector2f ProjectileCmp::getAlignment(GameObject& go, GameObject& projectile)
	{
		const auto animation = go.getComponent<SpriteAnimationCmp>();
		const auto projectileSprite = projectile.getComponent<SpriteRenderCmp>();
		float width = static_cast<float>(animation->getTextureRect().width) +1;
		float height = static_cast<float>(animation->getTextureRect().height) +1;
		float widthP = static_cast<float>(projectileSprite->getTextureRect().width) + 1;
		float heightP = static_cast<float>(projectileSprite->getTextureRect().height) + 1;
		
		sf::Vector2f position(gameObject.getPosition().x, gameObject.getPosition().y);

		switch (animation->getCurrentAnimation())
		{
		case AnimationType::MoveUp:
			position.x += width / 2;
			position.y -= heightP;
			break;
		case AnimationType::MoveRight:
			position.x += width;
			position.y += height / 2;
			break;
		case AnimationType::MoveDown:
			position.x += width / 2;
			position.y += height;
			break;
		case AnimationType::MoveLeft:
			position.y += height / 2;
			position.x -= widthP;
			break;
		default:
			break;
		}
		return position;
	}
}