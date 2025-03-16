#include <map>
#include <string>
#include <vector>
#include "human_player.h"
#include "computer_player.h"

#pragma once

class game {
public:
    std::map<int, std::string> selection_map;
    rps::computer_player* comp;
    rps::human_player* me;
    int result;
    int wins;
    int losses;
    int ties;


    game()
    {
        initialize_game();
    }

    void initialize_game()
    {
        selection_map.insert(std::pair<int, std::string>(1, "Rock"));
        selection_map.insert(std::pair<int, std::string>(2, "Paper"));
        selection_map.insert(std::pair<int, std::string>(3, "Shears"));

        comp = new rps::computer_player();
        me = new rps::human_player();

        int wins = 0;
        int losses = 0;
        int ties = 0;
    }

    void make_selections()
    {
        me->make_selection();
        comp->make_selection();
    }

    void print_computer_selection()
    {
        std::cout << std::endl << "You Selected: " + selection_map.at(me->selection) << std::endl;
        std::cout << "Computer Selected: " + selection_map.at(comp->selection) << std::endl << std::endl;
    }

    void determine_winner()
    {
        result = (3 + (me->get_selection() - 1) - (comp->get_selection() - 1)) % 3;

        if (result == 1)
        {
            wins += 1;
        } 
        else if (result == 2)
        {
            losses += 1;
        }
        else 
        {
            ties += 1;
        }
    }
};

