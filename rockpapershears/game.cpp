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

        this->comp = rps::computer_player();
        this->me = rps::human_player();

        level = 0;

        game_over = false;

        curr_score = 20;
        multiplier = 1;
        total_score = 0;

        ante_points = 300;
    }

    void game::make_selections(int player_selection)
    {
        me.make_selection(player_selection);
        comp.make_selection(player_selection);
    }

    void game::print_computer_selection()
    {
        std::cout << std::endl << "You Selected: " + selection_map.at(me.selection) << std::endl;
        std::cout << "Computer Selected: " + selection_map.at(comp.selection) << std::endl << std::endl;
    }

    std::string game::get_computer_selection()
    {
        return selection_map.at(comp.selection);
    }

    void game::determine_winner()
    {
        round_result = this->victory_condition[me.selection - 1][comp.selection - 1];

        if (round_result == 1)
        {
            me.wins += 1;
            rounds += 1;
            this->multiplier += 1;
        }
        else if (round_result == -1)
        {
            me.losses += 1;
            rounds += 1;
        }
        else
        {
            me.ties += 1;
        }
    }

    void game::initialize_round()
    {
        if (level > 0)
        {
            ante_points *= 2;
        }

        me.points = 0;
        me.wins = 0;
        me.losses = 0;
        me.ties = 0;
    }

    void game::play_round()
    {
        std::cout << "Level " + std::to_string(this->level) + ". Points to gain " + std::to_string(ante_points) << std::endl;

        rounds = 0;

        while (rounds < 3)
        {
            this->make_selections(1);
            this->print_computer_selection();
            this->determine_winner();

            std::cout << std::endl << "Wins: " + std::to_string(me.wins) << " Losses: " + std::to_string(me.losses) << " Ties: " + std::to_string(me.ties) << std::endl;
            std::cout << "You have " + std::to_string(me.points) + " points! Out of " + std::to_string(this->ante_points) + "!" << std::endl;
        }

        if (me.points >= ante_points)
        {
            level += 1;
            std::cout << std::endl << "Round Survived!" << std::endl;
            me.award_money();
            std::cout << std::endl << "Next Level!" << std::endl;
        }
        else
        {
            game_over = true;
        }
    }

    void game::determine_stage_score()
    {
        this->total_score = this->curr_score * this->multiplier;
    }
};