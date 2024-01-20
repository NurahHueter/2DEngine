#pragma once
#include "IComponent.h"

#include<memory>
namespace mmt_gd
{
	class MapTile;
	class SteeringCmp : public IComponent
	{
	public:
		SteeringCmp(GameObject& gameObjectPlayer,  const sf::Vector2f& velocity)
			: IComponent(gameObjectPlayer),  m_velocity(velocity) {};
		bool init() override;
		void update(float deltaTime) override;
		void setTarget(sf::Vector2f target) { m_target = target; };
		bool reachedTarget() { return m_reachedTarget; };


	private:
		
		bool m_reachedTarget = false;
		sf::Vector2f m_target = { 0.f, 0.f };
		sf::Vector2f m_velocity;
		sf::Vector2f direction = { 0.f, 0.f };
	};
}