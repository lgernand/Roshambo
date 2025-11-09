#include "game_state.h"

namespace rps
{
	//GAME STATE BASE CLASS METHODS //////////////////////////////////////////////////////////


	//ROSHAMBO STATE METHODS /////////////////////////////////////////////////////////////////

	roshambo_state::roshambo_state()
	{
		this->state = ROSHAMBO;
		this->repititions = 0;
		this->end_of_state = false;
	}

	void roshambo_state::init_state()
	{

	}

	void roshambo_state::update_state()
	{
		//initiate roshambo
		repititions += 1;

		if (repititions > 2)
		{
			end_of_state = true;
		}
	}



	//RPS STATE METHODS////////////////////////////////////////////////////////////////////
	rps_state::rps_state()
	{
		this->state = RPS;
	}

	void rps_state::init_state()
	{

	}

	void rps_state::update_state()
	{

	}


	//EVALUATE RPS METHODS/////////////////////////////////////////////////////////////////
	evaluate_rps_state::evaluate_rps_state()
	{
		this->state = EVALUATE_RPS;
	}

	void evaluate_rps_state::init_state()
	{
		game->determine_winner();
		end_of_state = true;
	}

	void evaluate_rps_state::update_state()
	{
		//
	}

	//EVALUATE RPS METHODS/////////////////////////////////////////////////////////////////
	evaluate_stage_state::evaluate_stage_state()
	{
		this->state = EVALUATE_STAGE;
	}

	void evaluate_stage_state::init_state()
	{
		game->determine_stage_score();
		end_of_state = true;
	}

	void evaluate_stage_state::update_state()
	{
		//
	}

	//STORE STATE METHODS////////////////////////////////////////////////////////////////
	store_state::store_state()
	{
		this->state = STORE;
	}

	void store_state::init_state()
	{

	}

	void store_state::update_state()
	{
		//initiate store
	}


	//STATE CONTROLLER METHODS//////////////////////////////////////////////////////////////
	void state_controller::init()
	{
		curr_state = new roshambo_state();
	}

	void state_controller::transition_to_state(state state)
	{
		rps::game* temp_game = curr_state->game;
		
		delete curr_state;

		if (state == ROSHAMBO)
		{
			curr_state = new roshambo_state();
		}

		if (state == RPS)
		{
			curr_state = new rps_state();
		}

		if (state == STORE)
		{
			curr_state = new store_state();
		}
		if (state == EVALUATE_RPS)
		{
			curr_state = new evaluate_rps_state();
		}
		if (state == EVALUATE_STAGE)
		{
			curr_state = new evaluate_stage_state();
		}

		curr_state->game = temp_game;
		curr_state->init_state();
	}

	state state_controller::get_state()
	{
		return this->curr_state->state;
	}

	game_state* state_controller::get_game_state()
	{
		return this->curr_state;
	}

	game* state_controller::get_game()
	{
		return this->get_game_state()->game;
	}

	state_controller::~state_controller()
	{
		delete curr_state;
	}
};