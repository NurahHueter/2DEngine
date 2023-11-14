#pragma once
#include<string>

class Component
{
public:
	virtual ~Component() = default;

	//Getter identidy-oriented
	const std::string& getId() const { return id; }

	//Setter
	void setId(const std::string& newId) { id = newId; }

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

private: 
	std::string id;
};