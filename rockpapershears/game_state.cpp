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

	void rps_state::update_state()
	{
		//initiate rps
	}



	//STORE STATE METHODS////////////////////////////////////////////////////////////////
	store_state::store_state()
	{
		this->state = STORE;
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
	}

	state state_controller::get_state()
	{
		return this->curr_state->state;
	}

	game_state* state_controller::get_game_state()
	{
		return this->curr_state;
	}

	state_controller::~state_controller()
	{
		delete curr_state;
	}
};