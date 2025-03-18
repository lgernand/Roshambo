#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

namespace rps
{
    class player {
    public:
        mutable int selection;

        virtual void make_selection() const = 0;

        int get_selection();
    };
}

#endif