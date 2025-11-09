#include "roshambo.h"

namespace rps
{
    roshambo::roshambo()
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

    bool roshambo::OnUserCreate()
    {
        // Called once at the start, so create things here
        return true;
    }

    bool roshambo::OnUserUpdate(float fElapsedTime)
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
            }
        }
        else
        {
            shrinking_circle_radius -= .005;
        }

        return true;
    }
}