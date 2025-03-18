#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

namespace rps
{
    class human_player : public player {
    public:
        int points = 0;
        int money = 0;

        //std::list<ring> rings;

        human_player();

        void make_selection() const;

        void give_points();

        void award_money();
    };

}

#endif