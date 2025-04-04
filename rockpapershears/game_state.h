#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game.h"

namespace rps
{
	enum state
	{
		ROSHAMBO,
		RPS,
		EVALUATE_RPS,
		STORE
	};

	class game_state
	{
	public:
		game* game;
		state state;
		bool end_of_state;

		game_state()
		{
			this->game = new rps::game();
		}

		virtual void init_state() = 0;
		virtual void update_state() = 0;
	};

	class roshambo_state : public game_state
	{
	public:
		int repititions;

		roshambo_state();
		void init_state() override;
		void update_state() override;
	};

	class rps_state : public game_state
	{
	public:
		rps_state();
		void init_state() override;
		void update_state() override;
	};

	class evaluate_rps_state : public game_state
	{
	public:
		evaluate_rps_state();
		void init_state() override;
		void update_state() override;
	};

	class store_state : public game_state
	{
	public:
		store_state();
		void init_state() override;
		void update_state();
	};

	class state_controller
	{
	private:
		game_state* curr_state = nullptr;


	public:
		void init();

		void transition_to_state(state state);

		state get_state();

		game_state* get_game_state();

		~state_controller();

	};
}

#endif