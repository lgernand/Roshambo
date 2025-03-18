#include "game.h"

namespace rps
{

    game::game()
    {
        initialize_game();
    }

    void game::initialize_game()
    {
        selection_map.insert(std::pair<int, std::string>(1, "Rock"));
        selection_map.insert(std::pair<int, std::string>(2, "Paper"));
        selection_map.insert(std::pair<int, std::string>(3, "Shears"));

        comp = new computer_player();
        me = new human_player();

        level = 0;

        game_over = false;

        ante_points = 25;
    }

    void game::make_selections()
    {
        me->make_selection();
        comp->make_selection();
    }

    void game::print_computer_selection()
    {
        std::cout << std::endl << "You Selected: " + selection_map.at(me->selection) << std::endl;
        std::cout << "Computer Selected: " + selection_map.at(comp->selection) << std::endl << std::endl;
    }

    void game::determine_winner()
    {
        round_result = this->victory_condition[me->selection - 1][comp->selection - 1];

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

    void game::initialize_round()
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

    void game::play_round()
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