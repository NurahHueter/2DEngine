//#pragma once
#include"pch.h"
//#include"Projectile.h"
//#include"RenderCmp.h"
//#include"MoveCmp.h"
//#include"InputManager.h"
//
//void Projectile::init()
//{
//	renderComponent = std::make_shared<RenderCmp>(std::weak_ptr<GameObject>(shared_from_this()), "../Assets/projectile.png", "projectile");
//	renderComponent->init();
//	moveComponent = std::make_shared<MoveCmp>(std::weak_ptr<GameObject>(shared_from_this()), sf::Vector2f(0, 0), 400.f);
//	moveComponent->init();
//};
//void Projectile::draw(sf::RenderWindow& window)
//{
//	renderComponent->draw(window);
//};
//void Projectile::update(float deltatime)
//{
//	moveComponent->update(deltatime);
//	renderComponent->update(deltatime);
//};