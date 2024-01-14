#pragma once
#include "pch.h"
#include "PowerUpsCmp.h"
#include "GameObject.h"
#include "ObjectTypes.h"
#include "HealthCmp.h"
#include "RigidBodyCmp.h"

namespace mmt_gd
{
	void PowerUpCmp::collect(GameObject* go)
	{
		if(m_type == Health)
		{
			go->getComponent<HealthCmp>()->getHealth();
		}
		else if (m_type == Speed)
		{
			go->getComponent<RigidBodyCmp>()->setVelocityP(go->getComponent<RigidBodyCmp>()->getVelocity() += sf::Vector2f(0.5f, 0.5f));
		}

		respawn();
	}
	void PowerUpCmp::respawn()
	{
		float randomX = m_respawnBounds.left + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * m_respawnBounds.width;
		float randomY = m_respawnBounds.top + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * m_respawnBounds.height;
		this->gameObject.setPosition(sf::Vector2f(randomX, randomY));
	}
}