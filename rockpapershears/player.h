#include <iostream>

#pragma once

namespace rps
{
    class player {
    public:
        int selection;

        virtual void make_selection()
        {

        }

        int get_selection()
        {
            return this->selection;
        }
    };
}