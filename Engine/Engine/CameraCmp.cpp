#pragma once
#include "pch.h"
#include "GameObject.h"
#include "CameraCmp.h"
namespace mmt_gd
{
	bool CameraCmp::init()
	{
		view.reset(sf::FloatRect(gameObject.getPosition(), size));
		return true;
	}
	void CameraCmp::update(float deltaTime)
	{
		view.setCenter(gameObject.getPosition());

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