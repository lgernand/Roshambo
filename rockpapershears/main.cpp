#define OLC_PGE_APPLICATION
#include "olcUTIL_Geometry2D.h"
#include "olcPixelGameEngine.h"
#include "game_state.h"

class roshambo : public olc::PixelGameEngine
{
private:
    rps::state_controller state_controller;

    std::map<int, std::string> selection_map;
    std::map<int, olc::v_2d<float>> selection_button_pos_map;

    olc::v_2d<float> rps_button_size = { 30.0f, 15.0f };

    std::string selection = "";
    std::string computer_selection = "";

    float target_circle_pos_x;
    float target_circle_pos_y;
    float target_circle_radius;

    float curr_score;
    float multiplier;

    olc::utils::geom2d::circle<float> target_circle;

    float shrinking_circle_radius;
public:
    roshambo()
    {
        // Name your application
        sAppName = "Roshambo";

        selection_map.insert(std::pair<int, std::string>(1, { "Rock" }));
        selection_map.insert(std::pair<int, std::string>(2, { "Paper" }));
        selection_map.insert(std::pair<int, std::string>(3, { "Shears" }));

        selection_button_pos_map.insert(std::pair<int, olc::v_2d<float>>(1, { 15.0f, ScreenHeight() / 1.5f }));
        selection_button_pos_map.insert(std::pair<int, olc::v_2d<float>>(2, { 55.0f, ScreenHeight() / 1.5f }));
        selection_button_pos_map.insert(std::pair<int, olc::v_2d<float>>(3, { 95.0f, ScreenHeight() / 1.5f }));

        

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
        srand(time(NULL));

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
                    target_circle_pos_y = rand() % ScreenHeight();

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

        if (state_controller.get_state() == rps::RPS)
        {
            Clear(olc::DARK_GREEN);

            for (auto button : selection_button_pos_map)
            {
                DrawRect(button.second, rps_button_size, olc::WHITE);
            }

            if (GetMouse(0).bPressed)
            {
                olc::v_2d<float> mouse_pos = olc::v_2d<float>(float(GetMouseX()), float(GetMouseY()));
                for (auto button : selection_button_pos_map)
                {
                    auto rect = olc::utils::geom2d::rect<float>({ button.second, rps_button_size });
                    if (olc::utils::geom2d::contains(rect, mouse_pos))
                    {
                        selection = selection_map[button.first];
                        state_controller.get_game_state()->game->make_selections(button.first);
                        computer_selection = state_controller.get_game_state()->game->get_computer_selection();
                        state_controller.transition_to_state(rps::EVALUATE_RPS);
                        
                        if (state_controller.get_game_state()->end_of_state == true)
                        {
                            state_controller.transition_to_state(rps::RPS);
                        }
                    }
                }
            }
        }



        DrawString({ 0 , 0 }, std::to_string(curr_score), olc::WHITE);
        DrawString({ 0 , 100 }, selection, olc::WHITE);
        DrawString({ 150, 0 }, computer_selection, olc::WHITE);
        DrawString({ 0, ScreenHeight() - 15 }, std::to_string(state_controller.get_game_state()->game->me.wins) + "/ 3", olc::WHITE);

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