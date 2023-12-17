#pragma once
#define _CRTDBG_MAP_ALLOC
#include "pch.h"
#include "Game.h"

    int main()
    {
#if _DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
        {
            std::cout << "Läuft ;)" << std::endl;
            std::unique_ptr<mmt_gd::Game> game = std::make_unique<mmt_gd::Game>();
            game->Run();


            std::cout << "Endlich Fertig <.<" << std::endl;
        }
        _CrtDumpMemoryLeaks();

        return 0;
    }
