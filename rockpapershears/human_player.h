#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"
#include "ring.h"
#include <list>
#include <vector>

namespace rps
{
    class human_player : public player {
    public:
        int points = 0;


        std::vector<ring*> rings;

        human_player();

        void make_selection() const override;

        void give_points();

        void award_money();
    };

};

#endif