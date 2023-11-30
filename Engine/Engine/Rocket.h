#pragma once
#include <memory>
#include "GameObject.h"
#include "Projectile.h"
class RenderCmp;
class MoveCmp;
class Rocket : public GameObject, public std::enable_shared_from_this<Rocket>
{
public:
	void init() override;
	void draw(sf::RenderWindow& window) override;
	void update(float deltatime) override;

private:
	/*std::vector<std::shared_ptr<Projectile>> objectPool[100];*/
	std::shared_ptr<RenderCmp> renderComponent;
	std::shared_ptr<MoveCmp> moveComponent;
};