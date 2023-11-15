#pragma once
#include <memory>
#include "GameObject.h"
class RenderCmp;
class MoveCmp;
class Rocket2 : public GameObject
{
public:
	void init() override;
	void draw(sf::RenderWindow& window) override;
	void update(float deltatime) override;

private:
	std::shared_ptr<RenderCmp> renderComponent;
	std::shared_ptr<MoveCmp> moveComponent;
};