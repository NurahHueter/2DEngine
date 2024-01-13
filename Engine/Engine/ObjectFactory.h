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
        static void loadSpaceship(tson::Object& object, const std::string layer);
        static void loadProjectile(tson::Object& object,
             const std::string layer,
            std::shared_ptr<GameObject> gameObject);

    };
} 