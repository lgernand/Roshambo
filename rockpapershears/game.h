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
    int round_result;
    int wins;
    int losses;
    int ties;
    int victory_condition[5][5] = {
                    // comp
        //            r p  s
        /*player r*/{ 0,-1,1 },
               /*p*/{ 1,0,-1 },
               /*s*/{ -1,1,0 },
    };

    int ante_points;

    int rounds;

    int level;

    bool game_over;

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

        level = 0;

        game_over = false;

        ante_points = 25;
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
        round_result = this->victory_condition[me->selection-1][comp->selection-1];

        if (round_result == 1)
        {
            wins += 1;
            rounds += 1;
            me->give_points();
        } 
        else if (round_result == -1)
        {
            losses += 1;
            rounds += 1;
        }
        else 
        {
            ties += 1;
        }
    }

    void initialize_round()
    {
        if (level > 0)
        {
            ante_points *= 1.5;
        }

        me->points = 0;
        wins = 0;
        losses = 0;
        ties = 0;
    }

    void play_round()
    {
        std::cout << "Level " + std::to_string(this->level) + ". Points to gain " + std::to_string(ante_points) << std::endl;

        rounds = 0;

        while (rounds < 3)
        {
            this->make_selections();
            this->print_computer_selection();
            this->determine_winner();

            std::cout << std::endl << "Wins: " + std::to_string(this->wins) << " Losses: " + std::to_string(this->losses) << " Ties: " + std::to_string(this->ties) << std::endl;
            std::cout << "You have " + std::to_string(me->points) + " points! Out of " + std::to_string(this->ante_points) + "!" << std::endl;
        }

        if (me->points >= ante_points)
        {
            level += 1;
            std::cout << std::endl << "Round Survived!" << std::endl;
            me->award_money();
            std::cout << std::endl << "Next Level!" << std::endl;
        } 
        else 
        { 
            game_over = true;
        }
    }
};

