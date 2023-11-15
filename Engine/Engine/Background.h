#pragma once
#include <memory>
#include "GameObject.h"
class RenderCmp;
class Background : public GameObject
{
public:
	~Background() {};
	void init() override;
	void draw(sf::RenderWindow& window) override;
	void update(float deltatime) override {};
	void swap(float check);
private:
	int switchCount = 0;
	std::shared_ptr<RenderCmp> renderComponent;
	std::shared_ptr<RenderCmp> renderComponent2; 
};