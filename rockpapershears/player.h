#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

namespace rps
{
    class player {
    public:
        int selection;

        virtual void make_selection();

        int get_selection();
    };
}

#endif