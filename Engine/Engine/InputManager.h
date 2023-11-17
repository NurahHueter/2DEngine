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
    // bool isKeyReleased(int keyCode);     ist das selbe rwie isKEyUp

    // Aktionen abfragen
    bool isKeyDown(const std::string& action);
    bool isKeyUp(const std::string& action);
    bool isKeyPressed(const std::string& action);
    // bool isKeyReleased(const std::string& action, int playerIdx);

    // Tastenaktionen binden und lösen
    void bind(const std::string& name, int keyCode);
    void unbind(const std::string& name);

    void handleEvents(sf::Event& event);


private:

    std::map<int, bool> m_isKeyDown{};
    std::map<int, bool> m_isKeyPressed{};
    std::map<int, bool> m_isKeyUp{};
	
 //   void OnKeyPressed(const Event::KeyEvent& e) ;
	//void OnKeyReleased(const Event::KeyEvent& e);

    std::map<std::string, int> m_bindings{};                //action, keyCode
	

    InputManager() {}
    ~InputManager() {}

};
