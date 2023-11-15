#pragma once
#include <memory>
#include "GameObject.h"
class RenderCmp;
class Background : GameObject
{
public:
	~Background() {};
	void init() override;
	void draw(sf::RenderWindow& window) override;
	void update(float deltatime) override {};
private:
	std::shared_ptr<RenderCmp> renderComponent;
};