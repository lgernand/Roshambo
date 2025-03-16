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
        game.make_selections();

        game.print_computer_selection();
        
        game.determine_winner();

        if (game.result == 1)
        {
            std::cout << "You Win!";
        }
        else if (game.result == 2) 
        {
            std::cout << "You Lose!";
        }
        else
        {
            std::cout << "Tie!";
        }

        std::cout << std::endl << "Wins: " + std::to_string(game.wins) << " Losses: " + std::to_string(game.losses) << " Ties: " + std::to_string(game.ties) << std::endl;

        std::cout << std::endl << "exit?";
        std::cin >> end;
    }
}