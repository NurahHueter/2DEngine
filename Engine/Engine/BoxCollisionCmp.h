#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>


namespace mmt_gd
{
	class RigidBodyCmp;

	class BoxCollisionCmp
	{
	public:
		BoxCollisionCmp(const sf::Vector2f& initialSize = sf::Vector2f(1.0f, 1.0f),
			const sf::Vector2f& initialPosition = sf::Vector2f(0.0f, 0.0f),
			std::shared_ptr<RigidBodyCmp> initialRigidBody)
			: size(initialSize), position(initialPosition), ownRigidBody(initialRigidBody) {};




	private:
		sf::Vector2f size;
		sf::Vector2f position;
		std::shared_ptr<RigidBodyCmp> ownRigidBody;


	};



}