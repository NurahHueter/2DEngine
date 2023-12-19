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
            const fs::path& path,
            const RenderManager& renderManager,
            const GameObjectManager& gameObjectManager);
    };
} 