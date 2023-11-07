#pragma once
#include <map>

class GameState; // forward declaration to avoid circular header file dependency
class GameStateManager {
public:
	static
		GameStateManager&
		instance()
	{
		static GameStateManager s;
		return s;
	} // instance
	GameStateManager(const GameStateManager&) = delete;
	GameStateManager& operator = (const GameStateManager&) = delete;

	GameStateManager() : currentState(nullptr) 
	{
	};
	void update(float delta);
	void draw() {};
	void Init(){};
	void setState(std::string stateName);
private:
	~GameStateManager() {};
	std::map<std::string, std::unique_ptr<GameState>> states; // map of all available states
	std::unique_ptr<GameState> currentState; // holds the current state
};
