#include "human_player.h"

namespace rps
{
    class human_player : public player {
    public:
        int points = 0;
        int money = 0;

        std::list<ring> rings;

        human_player() {
            auto test_ring = new barber_ring();
        }

        void make_selection() override
        {
            std::cout << "Make a selection: ";
            std::cin >> this->selection;
        }

        void give_points()
        {
            int base_points = 50;
            points += base_points;
        }

        void award_money()
        {
            int reward_money = 5;
            money += reward_money;

            std::cout << "You won $" + std::to_string(reward_money) + ". You have $" + std::to_string(money) << std::endl;
        }
    };

}