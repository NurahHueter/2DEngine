#pragma once
#include "pch.h"
#include "Game.h"
    int main()
    {
        std::cout << "Läuft ;)" << std::endl;
        std::unique_ptr<Game> game = std::make_unique<Game>();
        game->Run();


        std::cout<<"Endlich Fertig <.<"<<std::endl;


        return 0;
    }

