#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

namespace rps
{
    class player {
    public:
        mutable int selection;

        int base_points;

        int wins;
        int losses;
        int ties;

        int money;

        virtual void make_selection(int selection) const = 0;

        int get_selection();
    };
}

#endif