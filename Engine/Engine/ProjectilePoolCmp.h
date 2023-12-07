//#pragma once
//#include "Component.h"
//#include<memory>
//
//class GameObject;
//class RenderCmp;
//class ProjectilePoolCmp : public Component
//{
//public:
//	ProjectilePoolCmp(std::string id, std::weak_ptr<GameObject> gameObject, float timeToLife, int number)
//		:Component(id), gameObject(gameObject),timeToLife(timeToLife), number(number){};
//	void init() override;
//	void update(float deltaTime) override;
//
//private:
//	std::weak_ptr<GameObject> gameObject;
//	std::map<std::shared_ptr<GameObject>, float> projectiles;
//	float timeToLife; 
//	int number;
//};