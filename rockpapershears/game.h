#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <vector>
#include "human_player.h"
#include "computer_player.h"

namespace rps
{
    class game {
    public:
        std::map<int, std::string> selection_map;
        rps::computer_player comp;
        rps::human_player me;
        int round_result;
        int wins;
        int losses;
        int ties;
        int victory_condition[5][5] = {
            // comp
//            r p  s
            /*player r*/{ 0,-1,1 },
            /*p*/{ 1,0,-1 },
            /*s*/{ -1,1,0 },
        };

        int ante_points;

        int rounds;

        int level;

        bool game_over;

        game();

        void initialize_game();

        void make_selections();

        void print_computer_selection();

        void determine_winner();

        void initialize_round();

        void play_round();
    };
}
#endif
