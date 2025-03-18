#include "player.h"

#pragma once

namespace rps
{
    class human_player : public player {
    public:
        int points = 0;
        int money;

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
    };

}