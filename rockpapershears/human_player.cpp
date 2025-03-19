#include "human_player.h"
#include <string>

namespace rps
{
    human_player::human_player() 
    {
        barber_ring* test_ring = new barber_ring();
        best_two_of_three_ring* test_ring2 = new best_two_of_three_ring();
        pay_day_ring* test_ring3 = new pay_day_ring();

        this->rings.push_back(test_ring2);
        this->rings.push_back(test_ring);
        this->rings.push_back(test_ring3);
        this->base_points = 50;

        this->money = 0;
    }

    void human_player::make_selection() const
    {
        std::cout << "Make a selection: ";
        std::cin >> this->selection;
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
