#include "pch.h"

#include "ObjectFactory.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "MouseMoveCmp.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"
#include "CameraCmp.h"
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
        if (object.getType() == "Player")
        {
           loadPlayer(object, layer.getName(), renderManager, gameObjectManager);
        }
        if (object.getType() == "Enemy")
        {
            loadEnemy(object, layer.getName(), renderManager, gameObjectManager);
        }
        if (object.getType() == "Collider")
        {
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
         std::shared_ptr<sf::Texture> texture;
         std::string texturePath;
         float velocity;
         float mass;

         for (const auto* property : object.getProperties().get())
         {
             auto name = property->getName();
             if (name == "Texture")
             {
                 if ((texturePath = property->getValue<std::string>()).length() > 0)
                 {
                     AssetManager::instance().LoadTexture(object.getName(), texturePath);
                     texture = AssetManager::instance().m_Textures[object.getName()];
                 }
             }
             else if (name == "id")
             {
                 if ((id = property->getValue<std::string>()).length() > 0)
                 {
                     gameObject->setId(id);
                 }
             }
             else if (name == "velocity")
             {
                 velocity = property->getValue<float>();
             }
             else if (name == "mass")
             {
                 mass = property->getValue<float>();
             }
         }

         gameObject->addComponent(std::make_shared<MoveCmp>(*gameObject, velocity));

         const auto& animationCmp = std::make_shared<SpriteAnimationCmp>(*gameObject, renderManager.getWindow(), texture, 8, 8, false, 4);
         renderManager.addCompToLayer(layer, animationCmp);
         animationCmp->m_animations = {
            {"MoveUp", 8},
            {"MoveRightUp", 8},
            {"MoveRight", 8},
            {"MoveRightDown", 8},
            {"MoveDown", 8},
            {"MoveLeftDown", 8},
            {"MoveLeft", 8},
            {"MoveLeftUp", 8}
         };
         animationCmp->setCurrentAnimation("MoveRight");
         gameObject->addComponent(animationCmp);

         gameObject->addComponent(std::make_shared<RigidBodyCmp>(*gameObject, mass, sf::Vector2f(velocity, velocity)));

         const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y), static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y)));
         gameObject->addComponent(boxCollider);

         PhysicsManager::instance().addBoxCollisionCmp(boxCollider);

         const auto cameraCmp = std::make_shared<CameraCmp>(*gameObject, renderManager.getWindow(), sf::Vector2f(renderManager.getWindow().getSize().x / 2.0f, renderManager.getWindow().getSize().y / 2.0f));
         cameraCmp->setTarget(gameObject);
         gameObject->addComponent(cameraCmp);
         renderManager.addCompToLayer(layer, cameraCmp);

         gameObject->init();
         gameObjectManager.addGameObject(gameObject);
    };
    
    void ObjectFactory::loadEnemy(tson::Object& object,
        const std::string layer,
        RenderManager& renderManager,
        GameObjectManager& gameObjectManager)
    {
        auto gameObject = std::make_shared<GameObject>(object.getName());
        gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

        std::string id;
        std::string texturpath;
        std::shared_ptr<sf::Texture> texture;
        float velocity;
        float mass;

        for (const auto* property : object.getProperties().get())
        {
            if (auto name = property->getName(); name == "Texture")
            {
                if ((texturpath = std::any_cast<std::string>(property->getValue())).length() > 0)
                {
                    AssetManager::instance().LoadTexture(object.getName(), texturpath);
                    texture = AssetManager::instance().m_Textures[object.getName()];
                    const auto& renderCmp = std::make_shared<SpriteRenderCmp>(*gameObject, renderManager.getWindow(), texture);
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

 
         gameObject->addComponent(std::make_shared<MouseMoveCmp>(*gameObject, sf::Vector2f((object.getPosition().x), static_cast<float>(object.getPosition().y)), velocity));
  
        gameObject->addComponent(std::make_shared<RigidBodyCmp>(*gameObject, mass, sf::Vector2f(velocity, velocity)));
        const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y), static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y)));
        gameObject->addComponent(boxCollider);
        PhysicsManager::instance().addBoxCollisionCmp(boxCollider);
        gameObject->init();
        gameObjectManager.addGameObject(gameObject);

    }
}

