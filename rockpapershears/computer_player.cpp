#include "computer_player.h"

namespace rps
{
    class computer_player : public player {
    public:
        computer_player() {

        }

        void make_selection() override
        {
            this->selection = (rand() * 1.0 / RAND_MAX * 3) + 1;
        }
    };
}