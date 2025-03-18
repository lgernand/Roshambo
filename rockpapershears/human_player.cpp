#include "human_player.h"
#include <string>

namespace rps
{
    human_player::human_player() 
    {
       // auto test_ring = new barber_ring();
    }

    void human_player::make_selection() const
    {
        std::cout << "Make a selection: ";
        std::cin >> this->selection;
    }

    void human_player::give_points()
    {
        int base_points = 50;
        points += base_points;
    }

    void human_player::award_money()
    {
        int reward_money = 5;
        money += reward_money;
        std::cout << "You won $" + std::to_string(reward_money) + ". You have $" + std::to_string(money) << std::endl;
    }
};
