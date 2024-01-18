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
		AIControllerCmp(GameObject& gameObject)
			:IComponent(gameObject){};
		bool init() override { return true; };
		void update(float deltaTime) override;
		void addPatrolPoint(sf::Vector2f point);

	private:
		void patrol();
		void attack();
		void flee();
		float m_attackRange = 100;
		float m_fleeRange = 400;
		int m_currentWayPoint = 0;
		std::vector<sf::Vector2f> m_patrolPoints = {};
		AIState currentState = Patrol;

	};
}