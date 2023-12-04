#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Component.h"

void GameObject::init()
{
    for (const auto& component : components)
    {
        component.second->init();
    }
};
void GameObject::update(float deltaTime)
{
    for (const auto& component : components)
    {
        component.second->update(deltaTime);
    }
};
void GameObject::draw(sf::RenderWindow& window)
{
    for (const auto& component : components)
    {
        component.second->draw(window);
    }
};
void GameObject::addComponent(std::string key,std::shared_ptr<Component> component)
{
    components.insert(std::make_pair(key, component));
};
std::shared_ptr<Component> GameObject::getComponent(std::string id)
{
    return components[id];
}
void GameObject::deleteComponent(std::shared_ptr<Component> component)
{
    auto it = components.find(component->getId());

    if (it != components.end())
    {
        components.erase(it);
    }
};

