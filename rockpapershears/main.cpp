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

    olc::v_2d<float> rps_button_size = { 50.0f, 15.0f };

    std::string selection = "";
    std::string computer_selection = "";

    float target_circle_pos_x;
    float target_circle_pos_y;
    float target_circle_radius;

    float curr_score;
    float multiplier;
    float total_score;

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
        selection_button_pos_map.insert(std::pair<int, olc::v_2d<float>>(2, { 75.0f, ScreenHeight() / 1.5f }));
        selection_button_pos_map.insert(std::pair<int, olc::v_2d<float>>(3, { 135.0f, ScreenHeight() / 1.5f }));

        

        curr_score = 10;
        multiplier = 1;
        total_score = 0;

        target_circle_radius = 10.0f;
        target_circle_pos_x = rand() % ScreenWidth();
        target_circle_pos_y = rand() % ScreenHeight();
        shrinking_circle_radius = 35.0f;

        target_circle = olc::utils::geom2d::circle({ target_circle_pos_x,target_circle_pos_y }, target_circle_radius);
    }

    void DisplayHUD(rps::game* game)
    {

        DrawString({ 0 , 0 }, std::to_string(game->curr_score) + " x " + std::to_string(game->multiplier), olc::WHITE);
        DrawString({ 0 , 10 }, std::to_string(game->total_score) + " / " + std::to_string(game->ante_points), olc::WHITE);
        DrawString({ 0 , 100 }, selection, olc::WHITE);
        DrawString({ 170, 50 }, computer_selection, olc::WHITE);
        DrawString({ 0, ScreenHeight() - 15 }, std::to_string(state_controller.get_game()->me.wins) + " / 3", olc::WHITE);
        DrawString({ ScreenWidth() - 45, 0}, std::to_string(state_controller.get_game()->me.losses) + " / 3", olc::WHITE);

        DrawString({ ScreenWidth() - 80, ScreenHeight() - 15}, "Level: " + std::to_string(state_controller.get_game()->level), olc::WHITE);
    }

    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        srand(time(NULL));

        state_controller.init();
        state_controller.get_game_state()->game->initialize_round();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {

        if (state_controller.get_state() == rps::ROSHAMBO)
        {

            Clear(olc::DARK_BLUE);

            std::string ro_sham_or_bo;

            if (state_controller.get_game_state()->repititions == 0)
            {
                ro_sham_or_bo = "RO!";
            }

            if (state_controller.get_game_state()->repititions == 1)
            {
                ro_sham_or_bo = "SHAM!";
            }

            if (state_controller.get_game_state()->repititions == 2)
            {
                ro_sham_or_bo = "BO!";
            }

            DrawString({ ScreenWidth() / 2, ScreenHeight() / 2 }, ro_sham_or_bo, olc::DARK_RED);

            FillCircle(target_circle_pos_x, target_circle_pos_y, target_circle_radius, olc::WHITE);
            DrawCircle(target_circle_pos_x, target_circle_pos_y, shrinking_circle_radius, olc::RED);

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

                    state_controller.get_game()->curr_score += points;

                    shrinking_circle_radius = 35.0f;
                    target_circle_pos_x = rand() % ScreenWidth();
                    target_circle_pos_y = rand() % ScreenHeight();

                    target_circle = olc::utils::geom2d::circle({ target_circle_pos_x,target_circle_pos_y }, target_circle_radius);

                    state_controller.get_game_state()->update_state();
                    if (state_controller.get_game_state()->end_of_state == true)
                    {
                        if (state_controller.get_game_state()->game->rounds == 3)
                        {
                            state_controller.transition_to_state(rps::STORE);
                        }
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
                DrawString(button.second+5, selection_map.at(button.first), olc::WHITE);
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
                            if (state_controller.get_game()->rounds >= 3)
                            {
                                state_controller.transition_to_state(rps::EVALUATE_STAGE);
                            }
                            else {
                                state_controller.transition_to_state(rps::ROSHAMBO);
                            }
                        }
                    }
                }
            }
        }

        if (state_controller.get_state() == rps::EVALUATE_STAGE)
        {
            if (state_controller.get_game()->total_score > state_controller.get_game()->ante_points)
            {
                DrawString({ ScreenWidth() / 2, ScreenHeight() / 2 }, "YOU WIN", olc::WHITE);

                if (GetKey(olc::ENTER).bPressed)
                {
                    state_controller.get_game()->initialize_round();
                    state_controller.transition_to_state(rps::ROSHAMBO);
                }
            }
            else {
                Clear(olc::DARK_RED);
                DrawString({ ScreenWidth() / 2, ScreenHeight() / 2 }, "YOU LOSE", olc::WHITE);
                if (GetKey(olc::ENTER).bPressed)
                {
                    state_controller.get_game()->initialize_game();
                    state_controller.transition_to_state(rps::ROSHAMBO);
                }
            }

            DrawString({ ScreenWidth() / 6, (ScreenHeight() / 2) + 10 }, "HIT ENTER TO CONTINUE", olc::WHITE);
        }

        DisplayHUD(state_controller.get_game());


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