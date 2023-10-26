#pragma once
#include "All_Includes.h"

    int main()
    {
        std::cout << "Running!\n";

        Game *game = new Game();
        game->Run();
      
        std::cout << "Finished!\n";
        return 0;
    }

