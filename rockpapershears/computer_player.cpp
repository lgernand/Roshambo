#include "computer_player.h"

namespace rps
{
    computer_player::computer_player() 
    {

    }

    void computer_player::make_selection() const
    {
        this->selection = (rand() * 1.0 / RAND_MAX * 3) + 1;
    }
}