#ifndef ROSHAMBO_H
#define ROSHAMBO_H

#define OLC_PGE_APPLICATION
#include "olcUTIL_Geometry2D.h"
#include "olcPixelGameEngine.h"

namespace rps
{
    class roshambo : public olc::PixelGameEngine
    {
    private:
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

        bool OnUserCreate() override;

        bool OnUserUpdate(float fElapsedTime) override;
    };
}
#endif