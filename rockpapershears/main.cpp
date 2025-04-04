#define OLC_PGE_APPLICATION
#include "olcUTIL_Geometry2D.h"
#include "olcPixelGameEngine.h"
#include "game_state.h"
#include "game.h"
#include "store.h"

class roshambo : public olc::PixelGameEngine
{
private:
    rps::state_controller state_controller;

    float target_circle_pos_x;
    float target_circle_pos_y;
    float target_circle_radius;

    float curr_score;

    olc::utils::geom2d::circle<float> target_circle;

    float shrinking_circle_radius;
public:
    roshambo()
    {
        // Name your application
        sAppName = "Roshambo";

        curr_score = 10;

        target_circle_radius = 10.0f;
        target_circle_pos_x = rand() % ScreenWidth();
        target_circle_pos_y = rand() % ScreenHeight();
        shrinking_circle_radius = 35.0f;

        target_circle = olc::utils::geom2d::circle({ target_circle_pos_x,target_circle_pos_y }, target_circle_radius);
    }

    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        state_controller.init();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (state_controller.get_state() == rps::ROSHAMBO)
        {

            Clear(olc::DARK_BLUE);

            FillCircle(target_circle_pos_x, target_circle_pos_y, target_circle_radius, olc::WHITE);
            DrawCircle(target_circle_pos_x, target_circle_pos_y, shrinking_circle_radius, olc::RED);

            DrawString({ 0 , 0 }, std::to_string(curr_score), olc::WHITE);

            if (GetMouse(0).bPressed)
            {
                olc::v_2d<float> mouse_pos = olc::v_2d<float>(float(GetMouseX()), float(GetMouseY()));

                if (olc::utils::geom2d::contains(target_circle, mouse_pos))
                {
                    float diff = abs(shrinking_circle_radius - target_circle_radius);

                    float points = 0;

                    if (diff < 2)
                    {
                        points = 10.0;
                        Clear(olc::GREEN);
                    }

                    if (diff > 2)
                    {
                        points = 0.0;
                    }

                    if (diff >= target_circle_radius)
                    {
                        points = -5.0;
                        Clear(olc::RED);
                    }

                    curr_score += points;

                    shrinking_circle_radius = 35.0f;
                    target_circle_pos_x = rand() % ScreenWidth();
                    target_circle_pos_x = rand() % ScreenHeight();

                    target_circle = olc::utils::geom2d::circle({ target_circle_pos_x,target_circle_pos_y }, target_circle_radius);

                    state_controller.get_game_state()->update_state();
                    if (state_controller.get_game_state()->end_of_state == true)
                    {
                        state_controller.transition_to_state(rps::RPS);
                    }
                }
            }
            else
            {
                shrinking_circle_radius -= .005;

            }
        }

        return true;
    }
};

int main()
{   
   /*rps::game game;
    rps::store store;
    
    for (auto i = game.selection_map.begin(); i != game.selection_map.end(); i++)
    {
        std::cout << std::to_string(i->first) + ". " + i->second << std::endl;
    }


    bool end = false;
    while (!end)
    {
        game.initialize_round();

        game.play_round();

        if (game.game_over == true)
        {
            std::cout << "GAME OVER!";
            end = true;

            game.initialize_game();
        }

        store.display_ring_inventory(&game.me);
    }*/

	roshambo demo;
	if (demo.Construct(256, 240, 3, 3))
		demo.Start();
	return 0;
}