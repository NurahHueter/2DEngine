#pragma once
#include <map>

struct InputManager
{
    static
        InputManager&
        instance()
    {
        static InputManager s;
        return s;
    } // instance

    InputManager(const InputManager&) = delete;
    InputManager& operator = (const InputManager&) = delete;

    //void Init(sf::Window& window);
    void update();


    bool isKeyDown(int keyCode);
    bool isKeyUp(int keyCode);
    bool isKeyPressed(int keyCode);


    bool isKeyDown(const std::string& action, int playerIdx);
    bool isKeyUp(const std::string& action, int playerIdx);
    bool isKeyPressed(const std::string& action, int playerIdx);

    // Tastenaktionen binden und lösen
    void bind(const std::string& name, int keyCode, int playerIdx);
    void unbind(const std::string& name, int playerIdx);

    void handleEvents(sf::Event& event);


private:

    std::map<int, bool> m_isKeyDown{};
    std::map<int, bool> m_isKeyPressed{};
    std::map<int, bool> m_isKeyUp{};
	
 //   void OnKeyPressed(const Event::KeyEvent& e) ;
	//void OnKeyReleased(const Event::KeyEvent& e);

    class BindingForPlayer {
    public:
        int keyCode;
        int playerIdx;
    };


    std::map<std::string, BindingForPlayer> m_bindings{};                //(action), (keyCode,playerIdx)
	
    InputManager() {}
    ~InputManager() {}

};
