#pragma once
#include <memory>
#include "GameObject.h"
class RenderComponent;
class Background : GameObject
{
public:
	~Background() {};
	void init() override;
	void draw(sf::RenderWindow& window) override;
private:
	std::shared_ptr<RenderComponent> renderComponent;
};