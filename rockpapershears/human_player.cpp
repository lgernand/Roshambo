#include "human_player.h"
#include <string>

namespace rps
{
    human_player::human_player() 
    {
        this->base_points = 50;

        this->money = 0;
    }

    void human_player::make_selection(int selection) const
    {
        this->selection = selection;
    }

    void human_player::give_points()
    {
        int points = this->base_points;

        for (auto &ring : this->rings)
        {
            points += ring->apply_effect(this, points);
        }

        this->points += points;
    }

    void human_player::award_money()
    {
        int reward_money = 5;
        money += reward_money;
        std::cout << "You won $" + std::to_string(reward_money) + ". You have $" + std::to_string(money) << std::endl;
    }
};
