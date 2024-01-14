#pragma once
#include "IComponent.h"
#include<memory>
namespace mmt_gd
{
	enum AIState
	{
		Patrol,
		Attack,
		Flee
	};
	class AIControllerCmp : public IComponent
	{
	public:
		AIControllerCmp(GameObject& gameObject, std::vector<sf::Vector2f> patrolPoints)
			:IComponent(gameObject), m_patrolPoints(patrolPoints) {};
		bool init() override;
		void update(float deltaTime) override;

	private:
		std::vector<sf::Vector2f> m_patrolPoints;
		AIState currentState = Patrol;

	};
}