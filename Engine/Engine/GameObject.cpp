#include"pch.h";
#include "GameObject.h";
#include "Component.h"

void GameObject::init()
{
    for (const auto& component : components)
    {
        component->init();
    }
};
void GameObject::update(float deltaTime)
{
    for (const auto& component : components)
    {
        component->update(deltaTime);
    }

};
void GameObject::draw(sf::RenderWindow& window)
{
    for (const auto& component : components)
    {
        component->draw(window);
    }
};
void GameObject::addComponent(std::unique_ptr<Component> component)
{
    components.push_back(component);
};