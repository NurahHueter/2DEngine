#include "pch.h"

#include "ObjectFactory.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "ProjectileCmp.h"
#include "MouseMoveCmp.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"
#include "CameraCmp.h"
#include "SpriteRenderCmp.h"
#include "HealthCmp.h"
#include "Tileson.hpp"
#include "AssetManager.h"
#include "RigidBodyCmp.h"
#include "ProjectileCmp.h"
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

         gameObject->addComponent(std::make_shared<MoveCmp>(*gameObject, sf::Vector2f(velocity, velocity)));

         const auto& animationCmp = std::make_shared<SpriteAnimationCmp>(*gameObject, renderManager.getWindow(), texture, 8, 8, false, 4);
         animationCmp->addAnimation( {
            {"MoveUp", 8},
            {"MoveLeftUp", 8},
            {"MoveRight", 8},
            {"MoveRightDown", 8},
            {"MoveDown", 8},
            {"MoveLeftDown", 8},
            {"MoveLeft", 8},
            {"MoveRightUp", 8}, 
         });
         animationCmp->setCurrentAnimation("MoveRight");
         animationCmp->init();
         renderManager.addCompToLayer(layer, animationCmp);
         gameObject->addComponent(animationCmp);

         gameObject->addComponent(std::make_shared<RigidBodyCmp>(*gameObject, mass, sf::Vector2f(velocity, velocity)));

         const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(animationCmp->getTextureRect()));
         gameObject->addComponent(boxCollider);

         PhysicsManager::instance().addBoxCollisionCmp(boxCollider);

         const auto cameraCmp = std::make_shared<CameraCmp>(*gameObject, renderManager.getWindow(), sf::Vector2f(renderManager.getWindow().getSize().x / 2.0f, renderManager.getWindow().getSize().y / 2.0f));
         cameraCmp->setTarget(gameObject);
         gameObject->addComponent(cameraCmp);
         renderManager.addCompToLayer(layer, cameraCmp);

         const auto healtCmp = std::make_shared<HealthCmp>(*gameObject, renderManager.getWindow(), 5);
         renderManager.addCompToLayer(layer, healtCmp);
         gameObject->addComponent(healtCmp);

         loadProjectile(object,
             layer,
             renderManager,
             gameObjectManager,
             gameObject);

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

        const auto& animationCmp = std::make_shared<SpriteAnimationCmp>(*gameObject, renderManager.getWindow(), texture, 6, 8, false, 4);
        renderManager.addCompToLayer(layer, animationCmp);
        animationCmp->addAnimation({
           {"MoveUp", 6},
           {"MoveLeftUp", 6},
           {"MoveRight", 6},
           {"MoveRightDown", 6},
           {"MoveDown", 6},
           {"MoveLeftDown", 6},
           {"MoveLeft", 6},
           {"MoveRightUp", 6},
            });
        animationCmp->setCurrentAnimation("MoveRight");
        animationCmp->init();
        renderManager.addCompToLayer(layer, animationCmp);
        gameObject->addComponent(animationCmp);

         gameObject->addComponent(std::make_shared<MouseMoveCmp>(*gameObject, sf::Vector2f((object.getPosition().x), static_cast<float>(object.getPosition().y)), velocity));
        
         const auto healtCmp = std::make_shared<HealthCmp>(*gameObject, renderManager.getWindow(), 3);
         renderManager.addCompToLayer(layer, healtCmp);
         gameObject->addComponent(healtCmp);

        gameObject->addComponent(std::make_shared<RigidBodyCmp>(*gameObject, mass, sf::Vector2f(velocity, velocity)));
        const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(sf::FloatRect(animationCmp->getTextureRect())));
        gameObject->addComponent(boxCollider);
        PhysicsManager::instance().addBoxCollisionCmp(boxCollider);
        gameObject->init();
        gameObjectManager.addGameObject(gameObject);

    }

    void ObjectFactory::loadProjectile(tson::Object& object,
        const std::string layer,
        RenderManager& renderManager,
        GameObjectManager& gameObjectManager,
        std::shared_ptr<GameObject> gameObject)
    {

        std::shared_ptr<sf::Texture> texture;
        std::string texturePath = "";
        float velocity = 0;
        float timeToLive = 0;
        float intervall = 0;
        int sizeObjectPool = 20;

        for (const auto* property : object.getProperties().get())
        {
            auto name = property->getName();
            if (name == "Projectile")
            {
                if ((texturePath = property->getValue<std::string>()).length() > 0)
                {
                    AssetManager::instance().LoadTexture("projectile", texturePath);
                    texture = AssetManager::instance().m_Textures["projectile"];
                }
            }
            else if (name == "timeToLive")
            {
                timeToLive = property->getValue<float>();
            }
            else if (name == "velocityP")
            {
                velocity = property->getValue<float>();
            }
            else if (name == "shootIntervall")
            {
                intervall = property->getValue<float>();
            }
        }

        std::vector<GameObject::Ptr> projectiles;
        for (int i = 0; i < sizeObjectPool; i++)
        {
            auto projectile = std::make_shared<GameObject>(object.getName() + "projectile" + std::to_string(i));

            const auto& renderCmp = std::make_shared<SpriteRenderCmp>(*projectile, renderManager.getWindow(), texture);
            renderManager.addCompToLayer(layer, renderCmp);

            projectile->addComponent(renderCmp);
            const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*projectile, sf::FloatRect(renderCmp->getTextureRect()));
            projectile->addComponent(boxCollider);
            projectile->addComponent(boxCollider);
            PhysicsManager::instance().addBoxCollisionCmp(boxCollider);
            projectile->init();

            projectiles.push_back(projectile);
            gameObjectManager.addGameObject(projectile);
        }
        
        gameObject->addComponent(std::make_shared<ProjectileCmp>(*gameObject, projectiles, timeToLive, velocity, intervall));
    }
}

