#pragma once
#include "pch.h"
#include "ProjectileCmp.h"
#include "GameObject.h"
#include "InputManager.h"

namespace mmt_gd
{
	ProjectileCmp::ProjectileCmp(GameObject& gameObject, std::vector<GameObject&> projectiles, float timeToLife, float velocity, float shootIntervall)
		:IComponent(gameObject), m_velocity(velocity), m_timeToLife(timeToLife), m_shootIntervall(shootIntervall)
	{
		for (auto& p : projectiles)
		{
			p.setActive(false);
			m_projectiles.emplace_back(p, timeToLife, (0.f, 0.f));
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
			if (std::get<0>(p).isActive())
			{
				std::get<0>(p).setPosition(
					std::get<0>(p).getPosition()
					+ std::get<2>(p)
					* m_velocity
					* deltaTime);

				std::get<1>(p) -= deltaTime;

				//ToDo -> CollisionCheck
				if (std::get<1>(p) <= 0)
				{
					std::get<0>(p).setActive(false);
					std::get<1>(p) = m_timeToLife;

				}
			}
			else
			{
				if (InputManager::instance().isMouseDown("shoot", 2) && lastSpawnTimer != 0)
				{
					lastSpawnTimer += deltaTime;
					sf::Vector2f direction = InputManager::instance().getMousPosition();
					std::get<0>(p).setActive(true);
					std::get<0>(p).setPosition(gameObject.getPosition());
					std::get<2>(p) = direction;
				}
			}

		}
	};
}