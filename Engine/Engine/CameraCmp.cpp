#pragma once
#include "pch.h"
#include "GameObject.h"
#include "CameraCmp.h"
namespace mmt_gd
{
	view.reset(sf::FloatRect(target.getPosition(), size));
	return true;
}
void CameraCmp::update(float deltaTime)
{
	view.setCenter(target.getPosition());

	}

	void CameraCmp::draw()
	{
		m_renderWindow.setView(view);
	};

	void CameraCmp::rotate(float& degree)
	{
		view.rotate(degree);
	};

	void CameraCmp::zoom(float& zoom)
	{
		view.rotate(zoom);
	};

	void CameraCmp::setSize(sf::Vector2f& size)
	{
		view.setSize(size);
	};

	void CameraCmp::setViewPort(sf::FloatRect& viewPort)
	{
		view.setViewport(viewPort);
	};
}