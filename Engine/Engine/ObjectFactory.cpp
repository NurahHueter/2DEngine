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
#include "ObjectTypes.h"
#include "Tileson.hpp"
#include "AssetManager.h"
#include "RigidBodyCmp.h"
#include "ProjectileCmp.h"
#include "BoxCollisionCmp.h"
#include "PhysicsManager.h"


namespace mmt_gd
{
void ObjectFactory::processTsonObject(tson::Object& object, const tson::Layer& layer)
    {
        if (object.getType() == "Player")
        {
           loadPlayer(object, layer.getName());
        }
        if (object.getType() == "Enemy")
        {
            loadEnemy(object, layer.getName());
        }
        if (object.getType() == "Collider")
        {
        }
        if (object.getType() == "Trigger")
        {         
        }
    }
void ObjectFactory::loadPlayer(tson::Object& object,
    const std::string layer)
    {
         auto gameObject =  std::make_shared<GameObject>(object.getName());
         gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));
         gameObject->setType(ObjectType::Player);
         gameObject->setPlayerIdx(1);        //Player 1
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

         const auto& animationCmp = std::make_shared<SpriteAnimationCmp>(*gameObject, RenderManager::instance().getWindow(),
             texture,
             8,
             8,
             false,
             4);
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
         RenderManager::instance().addCompToLayer(layer, animationCmp);
         gameObject->addComponent(animationCmp);

         gameObject->addComponent(std::make_shared<RigidBodyCmp>(*gameObject,
             mass, 
             sf::Vector2f(velocity, velocity)));

         const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject, sf::FloatRect(animationCmp->getTextureRect()));
         gameObject->addComponent(boxCollider);

         PhysicsManager::instance().addBoxCollisionCmp(boxCollider);

         const auto cameraCmp = std::make_shared<CameraCmp>(*gameObject,
             RenderManager::instance().getWindow(),
             sf::Vector2f(RenderManager::instance().getWindow().getSize().x / 2.0f,
             RenderManager::instance().getWindow().getSize().y / 2.0f));

         cameraCmp->setTarget(gameObject);
         gameObject->addComponent(cameraCmp);
         RenderManager::instance().addCompToLayer(layer, cameraCmp);

         const auto healtCmp = std::make_shared<HealthCmp>(*gameObject,
             RenderManager::instance().getWindow(),
             5);
         RenderManager::instance().addCompToLayer(layer, healtCmp);
         gameObject->addComponent(healtCmp);

         loadProjectile(object, layer, gameObject);

         gameObject->init();
         GameObjectManager::instance().addGameObject(gameObject);
    };
    
    void ObjectFactory::loadEnemy(tson::Object& object, const std::string layer)
    {
        auto gameObject = std::make_shared<GameObject>(object.getName());
        gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));
        gameObject->setType(ObjectType::Enemy);
        gameObject->setPlayerIdx(2);        //Player 2
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

        const auto& animationCmp = std::make_shared<SpriteAnimationCmp>(*gameObject, RenderManager::instance().getWindow(),
            texture,
            6,
            8,
            false,
            4);
        RenderManager::instance().addCompToLayer(layer, animationCmp);
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
        RenderManager::instance().addCompToLayer(layer, animationCmp);
        gameObject->addComponent(animationCmp);

         //gameObject->addComponent(std::make_shared<MouseMoveCmp>(*gameObject, sf::Vector2f((object.getPosition().x), static_cast<float>(object.getPosition().y)), velocity));
        gameObject->addComponent(std::make_shared<MoveCmp>(*gameObject, sf::Vector2f(velocity, velocity)));
         const auto healtCmp = std::make_shared<HealthCmp>(*gameObject,
             RenderManager::instance().getWindow(),
             3);

         RenderManager::instance().addCompToLayer(layer, healtCmp);
         gameObject->addComponent(healtCmp);

        gameObject->addComponent(std::make_shared<RigidBodyCmp>(*gameObject,
            mass,
            sf::Vector2f(velocity, velocity)));

        const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*gameObject,
            sf::FloatRect(sf::FloatRect(animationCmp->getTextureRect())));
        gameObject->addComponent(boxCollider);
        PhysicsManager::instance().addBoxCollisionCmp(boxCollider);
        loadProjectile(object, layer, gameObject);
        gameObject->init();
        GameObjectManager::instance().addGameObject(gameObject);

    }

    void ObjectFactory::loadProjectile(tson::Object& object,
        const std::string layer,
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
            projectile->setType(ObjectType::Projectle);
            const auto& renderCmp = std::make_shared<SpriteRenderCmp>(*projectile,
                RenderManager::instance().getWindow(),
                texture);
            
            RenderManager::instance().addCompToLayer(layer, renderCmp);
            projectile->addComponent(renderCmp);

            renderCmp->init();
            const auto& boxCollider = std::make_shared<BoxCollisionCmp>(*projectile,
                sf::FloatRect(sf::FloatRect(renderCmp->getTextureRect())));
            std::cout << renderCmp->getTextureRect().left << renderCmp->getTextureRect().top << std::endl;
            projectile->addComponent(boxCollider);
            PhysicsManager::instance().addBoxCollisionCmp(boxCollider);
            
            projectile->init();
            projectiles.push_back(projectile);
            GameObjectManager::instance().addGameObject(projectile);
        }
        
        gameObject->addComponent(std::make_shared<ProjectileCmp>(*gameObject, projectiles, timeToLive, velocity, intervall));
    }
}

