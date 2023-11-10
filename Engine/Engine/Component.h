#pragma once
#include "pch.h"

class Component
{
public:
	virtual ~Component() = default;
	Component(std::string&& initialValue)
		: value(initialValue) {
	}

	virtual void init() {}
	virtual void update(float deltaTime) {}
	virtual void draw() {}
private:
	std::string value = "uninitialized";
};