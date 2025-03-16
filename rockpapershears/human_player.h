#include "player.h"

#pragma once

namespace rps
{
    class human_player : public player {
    public:
        human_player() {

        }

        void make_selection() override
        {
            std::cout << "Make a selection: ";
            std::cin >> this->selection;
        }
    };

}