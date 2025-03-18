#ifndef RING_H
#define RING_H

#include "game.h"

namespace rps
{
	class ring
	{
	public:
		std::string ring_name;
		int rarity;
		int price;

		virtual int apply_effect(human_player* player, int base_points) const = 0;
	};

	class barber_ring : public ring
	{
	public:
		barber_ring();

		int apply_effect(human_player* player, int base_points);
	};
}
#endif