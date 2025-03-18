#include "ring.h"

namespace rps
{
	barber_ring::barber_ring()
	{
		ring_name = "Barber";
		rarity = 1;
		price = 5;
	}

	int barber_ring::apply_effect(rps::human_player* player, int base_points)
	{
		if (player->selection == 3)
		{
			"Barber Bonus! base points * 2";
			return base_points * 2;
		}
		return base_points;
	}
}