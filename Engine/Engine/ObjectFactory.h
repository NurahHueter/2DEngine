#pragma once
#include "GameObject.h"
#include "RenderManager.h"
#include "GameObjectManager.h"
#include "Tileson.hpp"

namespace tson
{
    class Object;
}

namespace mmt_gd
{
    class ObjectFactory
    {
    public:
        static void processTsonObject(tson::Object& object,
            const tson::Layer& layer,
            RenderManager& renderManager,
           GameObjectManager& gameObjectManager);
        static void loadPlayer(tson::Object& object,
            const std::string layer,
            RenderManager& renderManager,
            GameObjectManager& gameObjectManager);
    };
} 