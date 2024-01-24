#pragma once
#include "IComponent.h"
#include<memory>
namespace mmt_gd
{
	class ProjectileIdentityCmp : public IComponent
	{
	public:
		ProjectileIdentityCmp(GameObject& gameObject, std::string id)
			:IComponent(gameObject), m_id(id) {};
		bool init() override { return true; };
		void update(float deltaTime) override {};
		
		std::string getSpaceShipId() const { return m_id; };
	protected:
		std::string m_id;
	};
}