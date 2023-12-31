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
		ProjectileCmp(GameObject& gameObject, std::vector<GameObject&> projectiles, float timeToLife, float velocity, float shootIntervall);
		bool init() override {};
		void update(float deltaTime) override;

	private:
		std::vector<std::tuple<GameObject&, float, sf::Vector2f>> m_projectiles;
		float m_shootIntervall;
		float lastSpawnTimer;
		float m_velocity;
		float m_timeToLife;
	};
}