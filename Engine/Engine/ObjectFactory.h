#pragma once
#include "GameObject.h"
#include "RenderManager.h"
#include "SpriteAnimationCmp.h"
#include "GameObjectManager.h"
#include "Tileson.hpp"

namespace tson
{
    class Object;
    class Layer;
}

namespace mmt_gd
{
    class ObjectFactory
    {
    public:
        static void processTsonObject(tson::Object& object, const tson::Layer& layer);
        static void loadSpaceship(tson::Object& object, const tson::Layer& layer);
        static void loadPowerUp(tson::Object& object, const tson::Layer& layer);
        static void loadStaticCollider(tson::Object& object, const tson::Layer& layer);
        static void loadWayPoint(tson::Object& object, const tson::Layer& layer);
        static void loadProjectile(tson::Object& object,
             const tson::Layer& layer,
            std::shared_ptr<GameObject> gameObject);


    };
} 