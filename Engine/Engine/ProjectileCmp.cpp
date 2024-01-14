#pragma once
#include "pch.h"
#include "ProjectileCmp.h"
#include "GameObject.h"
#include "InputManager.h"
#include "VectorAlgebra2D.h"
#include "SpriteAnimationCmp.h"

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

				//ToDo -> CollisionCheck
				if (std::get<1>(p) <= 0)
				{
					std::get<0>(p)->setActive(false);
					std::get<1>(p) = m_timeToLife;
				}
			}
			else
			{
				if (InputManager::instance().isKeyPressed("shoot", gameObject.getPlayerIdx()) && lastSpawnTimer == 0)
				{
					lastSpawnTimer += deltaTime;
					const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();

					std::get<0>(p)->setActive(true);
					std::get<0>(p)->setPosition(gameObject.getPosition().x + 100, gameObject.getPosition().y - 100);

					sf::Vector2f direction = InputManager::instance().getMousPosition() - std::get<0>(p)->getPosition();
					std::get<2>(p) = MathUtil::unitVector(direction);

				}
			}
		}
	};
}