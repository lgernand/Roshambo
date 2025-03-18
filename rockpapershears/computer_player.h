#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "player.h"

namespace rps
{
    class computer_player : public player {
    public:
        computer_player();

        void make_selection() const;
    };
}

#endif