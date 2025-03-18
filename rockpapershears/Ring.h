#ifndef RING_H
#define RING_H

#include "game.h"
#include "human_player.h"

class ring
{
public:
	std::string ring_name;
	int rarity;
	int price;

	virtual void apply_effect() { };
};

class barber_ring : ring
{
public:
	barber_ring();

	int apply_effect(rps::human_player player, int base_points);
};

#endif