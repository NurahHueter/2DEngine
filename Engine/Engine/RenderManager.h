#pragma once
#include <unordered_map>
namespace mmt_gd
{
    class IRenderComponent;

    class RenderManager
    {
    public:
    
        explicit RenderManager(sf::RenderWindow& window) : m_window(window){}

        void setLayerOrder(std::string layer, int order);
        void addLayer(std::string layer, int order);
        void addCompToLayer(const std::string layer, std::shared_ptr<IRenderComponent> comp);

        void shutdown();
        void draw();

    private:
        sf::RenderWindow& m_window;
        std::map<std::string, std::vector<std::shared_ptr<IRenderComponent>>> m_CmpInLayer;
        std::vector<std::pair<std::string, int>> m_layers;
    };
}