#pragma once
#include "pch.h"
#include "BoxCollisionCmp.h"
#include "GameObject.h"
#include "IComponent.h"
#include "RigidBodyCmp.h"
#include "PhysicsManager.h"

namespace mmt_gd
{
	bool BoxCollisionCmp::init()
	{
		if (gameObject.getComponent<RigidBodyCmp>())
		{
			rigidBody = gameObject.getComponent<RigidBodyCmp>();
		}
		
		return true;
	}
}