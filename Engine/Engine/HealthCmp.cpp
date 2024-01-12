#pragma
#include "pch.h"
#include "HealthCmp.h"
#include "GameObject.h"
#include "RigidBodyCmp.h"
#include "InputManager.h"

namespace mmt_gd
{
	bool HealthCmp::init()
	{ 
		m_background.setSize(sf::Vector2f(20.f, 5.f));
		m_background.setFillColor(sf::Color().Black);
		m_slider.setSize(sf::Vector2f(20.f, 2.f));
		m_slider.setFillColor(sf::Color().Red);
		return true;
	};
	void HealthCmp::update(float deltaTime)
	{
		//ToDo CollisonCheck --> Projectile
		auto const& rb = gameObject.getComponent<RigidBodyCmp>();
		if (std::shared_ptr<GameObject> tempP = rb->getCollision().lock())
		{
			if (tempP->getType() != ObjectType::Default)
			{
				m_currentHealth--;
				if (m_currentHealth <= 0)
				{
					gameObject.markForDelete();
				}
			}
		};
		//ToDo CollisonCheck --> Item
		//if (InputManager::instance().isMouseDown("space", 1))
		//{
		//	m_currentHealth++;
		//};

		float sliderWidth = (float)m_currentHealth / m_health * m_background.getSize().x;
		m_slider.setSize(sf::Vector2f(sliderWidth, m_slider.getSize().y)); 

		m_background.setPosition(gameObject.getPosition().x, gameObject.getPosition().y - 5.f);
		m_slider.setPosition(gameObject.getPosition().x, gameObject.getPosition().y - 5.f);
	};
	void HealthCmp::draw()
	{
		m_renderWindow.draw(m_background);
		m_renderWindow.draw(m_slider);
	};
}