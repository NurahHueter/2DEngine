#pragma once
class GameStateManager;
class GameState
{
public:
	virtual void init() = 0;
	virtual void exit() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

private:
	GameStateManager* manager;
};

class MenuState : public GameState
{
public:
	virtual void init() override {};
	virtual void exit() override {};
	virtual void update(float deltaTime) override {};
	virtual void render() override {};
};

class MainState : public GameState
{
public:
	virtual void init() override {};
	virtual void exit() override{};
	virtual void update(float deltaTime) override {};
	virtual void render() override {};
private:
	sf::Sprite sprite;
};