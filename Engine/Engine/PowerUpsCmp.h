#pragma once
#include "IComponent.h"
#include<memory>
namespace mmt_gd
{
	enum PowerUpType
	{
		Health,
		Speed
	};
	class PowerUpCmp : public IComponent
	{
	public:
		PowerUpCmp(GameObject& gameObject, sf::FloatRect respawnBounds, PowerUpType type)
			:IComponent(gameObject), m_respawnBounds(respawnBounds), m_type(type){};
		bool init() override { return true; };
		void update(float deltaTime) override {};
		void collect(GameObject* go);

		void respawn();

	protected:
		sf::FloatRect m_respawnBounds;
		PowerUpType m_type;
	};
}