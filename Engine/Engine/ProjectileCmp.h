#pragma once
#include "IComponent.h"
#include<memory>

class GameObject;
class RenderCmp;
namespace mmt_gd
{
	class ProjectileCmp : public IComponent
	{
	public:
		ProjectileCmp(GameObject& gameObject, std::vector<std::shared_ptr<GameObject>> projectiles, float timeToLife, float velocity, float shootIntervall);
		bool init() override { return true; };
		void update(float deltaTime) override;
		void shoot(sf::Vector2f direction);
	private:
		/**
		 * \brief gets the Alignment of the spaceShip
		 * so that the projectile is spawned at the correct side
		 */
		sf::Vector2f getAlignment(GameObject& go);

		std::vector<std::tuple<std::shared_ptr<GameObject>, float, sf::Vector2f>> m_projectiles;
		float m_shootIntervall;
		float lastSpawnTimer = 0;
		float m_velocity;
		float m_timeToLife;
	};
}