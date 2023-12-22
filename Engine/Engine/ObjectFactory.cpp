#include "pch.h"

#include "ObjectFactory.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "MouseMoveCmp.h"
#include "MoveCmp.h"
#include "SpriteRenderCmp.h"
#include "Tileson.hpp"
#include "AssetManager.h"
#include "RigidBodyCmp.h"
#include "BoxCollisionCmp.h"
#include "PhysicsManager.h"


namespace mmt_gd
{
void ObjectFactory::processTsonObject(tson::Object& object,
    const tson::Layer& layer,
    RenderManager& renderManager,
    GameObjectManager& gameObjectManager)
    {
        if (object.getType() == "Player" || object.getType() == "Enemy")
        {
           loadPlayer(object, layer.getName(), renderManager, gameObjectManager);
        }
        if (object.getType() == "Collider")
        {
            auto gameObject = std::make_shared<GameObject>(object.getName());
            gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));
            const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y), static_cast<float>(object.getSize().x), static_cast<float>(object.getSize().y)));
            gameObject->addComponent(boxCollider);
            PhysicsManager::instance().addBoxCollisionCmp(boxCollider);
            gameObject->init();
            gameObjectManager.addGameObject(gameObject);

        }
        if (object.getType() == "Trigger")
        {
            
        }
    }
void ObjectFactory::loadPlayer(tson::Object& object,
    const std::string layer,
    RenderManager& renderManager,
    GameObjectManager& gameObjectManager)
    {
         auto gameObject =  std::make_shared<GameObject>(object.getName());
         gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

         std::string id;
         std::string texturpath;
         float velocity;
         float mass;

         for (const auto* property : object.getProperties().get())
         {
             if (auto name = property->getName(); name == "Texture")
             {
                 if ((texturpath = std::any_cast<std::string>(property->getValue())).length() > 0)
                 {
                     AssetManager::instance().LoadTexture(object.getName(), texturpath);
                     std::shared_ptr<sf::Texture> texture = AssetManager::instance().m_Textures[object.getName()];
                     const auto& renderCmp = std::make_shared<SpriteRenderCmp>(*gameObject,renderManager.getWindow(),texture);
                     renderManager.addCompToLayer(layer, renderCmp);
                     gameObject->addComponent(renderCmp);
                 }
             }
             else if (name == "id")
             {
                 if ((id = std::any_cast<std::string>(property->getValue())).length() > 0)
                 {
                     gameObject->setId(id);
                 }
             }
             else if (name == "velocity")
             {
                 velocity = std::any_cast<float>(property->getValue());
             }
             else if (name == "mass")
             {
                 mass = std::any_cast<float>(property->getValue());
             }
         }

         if (object.getType() == "Player")
         {
             gameObject->addComponent(std::make_shared<MoveCmp>(*gameObject, velocity));
         }
         else if (object.getType() == "Enemy")
         {
             gameObject->addComponent(std::make_shared<MouseMoveCmp>(*gameObject, sf::Vector2f((object.getPosition().x), static_cast<float>(object.getPosition().y)), velocity));
         }

         gameObject->addComponent(std::make_shared<RigidBodyCmp>(*gameObject, mass, sf::Vector2f(velocity, velocity)));
         const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y), static_cast<float>(object.getSize().x), static_cast<float>(object.getSize().y)));
         gameObject->addComponent(boxCollider);
         PhysicsManager::instance().addBoxCollisionCmp(boxCollider);
         gameObject->init();
         gameObjectManager.addGameObject(gameObject);
    };
    
}

