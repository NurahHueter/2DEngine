#include "pch.h"

#include "ObjectFactory.h"
#include "RenderManager.h"
#include "MouseMoveCmp.h"
#include "MoveCmp.h"
#include "SpriteRenderCmp.h"
#include "Tileson.hpp"

namespace mmt_gd
{
void ObjectFactory::processTsonObject(tson::Object& object,
    const tson::Layer& layer,
    const fs::path& path,
    const RenderManager& renderManager,
    const GameObjectManager& gameObjectManager)
    {
        if (object.getType() == "Player")
        {
            auto sprite = loadSprite(object, layer.getName(), path, spriteManager);
        }
        if (object.getType() == "Collider")
        {
            //auto collider = loadCollider(object, layer.getName());
        }
        if (object.getType() == "Trigger")
        {
            //auto trigger = loadTrigger(object, layer.getName());
        }

        return {};
    }
}

