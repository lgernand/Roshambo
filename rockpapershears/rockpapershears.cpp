#include "game.h"

int main()
{   
    game game;
    
    for (auto i = game.selection_map.begin(); i != game.selection_map.end(); i++)
    {
        std::cout << std::to_string(i->first) + ". " + i->second << std::endl;
    }


    bool end = false;
    while (!end)
    {
        game.initialize_round();

        game.play_round();

        if (game.game_over == true)
        {
            std::cout << "GAME OVER!";
            end = true;

            game.initialize_game();
        }
    }
}