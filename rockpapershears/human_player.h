#include "player.h"
#include <string>

#pragma once

namespace rps
{
    class human_player : public player {
    public:
        int points = 0;
        int money = 0;

        human_player() {

        }

        void make_selection() override
        {
            std::cout << "Make a selection: ";
            std::cin >> this->selection;
        }

        void give_points()
        {
            points += 50;
        }

        void award_money()
        {
            int reward_money = 5;
            money += reward_money;

            std::cout << "You won $" + std::to_string(reward_money) + ". You have $" + std::to_string(money) << std::endl;
        }
    };

}