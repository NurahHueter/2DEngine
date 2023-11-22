#pragma once
#include <memory>
#include "GameObject.h"
class RenderCmp;
class MoveCmp;
class Projectile;
class Rocket : public GameObject
{
public:
	void init() override;
	void draw(sf::RenderWindow& window) override;
	void update(float deltatime) override;
private:
	/*std::vector<Projectile> projectiles;*/
	std::shared_ptr<RenderCmp> renderComponent;
	std::shared_ptr<MoveCmp> moveComponent;
};