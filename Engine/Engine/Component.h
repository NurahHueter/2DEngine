#pragma once
#include<string>

class Component
{
public:
	Component(std::string id) : id(id) {};
	virtual ~Component() = default;
	const std::string& getId() const { return id; }
	void setId(const std::string& newId) { id = newId; }

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected: 
	std::string id;
};