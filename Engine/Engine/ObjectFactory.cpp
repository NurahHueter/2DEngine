#include "pch.h"

#include "ObjectFactory.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "MouseMoveCmp.h"
#include "MoveCmp.h"
#include "SpriteRenderCmp.h"
#include "Tileson.hpp"
#include "AssetManager.h"


namespace mmt_gd
{
void ObjectFactory::processTsonObject(tson::Object& object,
    const tson::Layer& layer,
    RenderManager& renderManager,
    GameObjectManager& gameObjectManager)
    {

        if (object.getType() == "Player" || "Enemy")
        {
           loadPlayer(object, layer.getName(), renderManager, gameObjectManager);
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
         std::string texturpath;
         float velocity;

         for (const auto* property : object.getProperties().get())
         {
             if (auto name = property->getName(); name == "Texture")
             {
                 if ((texturpath = std::any_cast<std::string>(property->getValue())).length() > 0)
                 {
                     std::cout << texturpath  << std::endl;
                     //texturpath = "../Engine/Assets/Hunter1-right.bmp";
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
                 std::cout << velocity << std::endl;
                 if (object.getType() == "Player")
                 {
                     gameObject->addComponent(std::make_shared<MoveCmp>(*gameObject, velocity));
                 }
                 else if (object.getType() == "Enemy")
                 {
                     gameObject->addComponent(std::make_shared<MouseMoveCmp>(*gameObject, velocity));
                 } 
             }
         }
         gameObject->init();
         gameObjectManager.addGameObject(gameObject);
    };
    
}

