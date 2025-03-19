#include "ring.h"
#include <iostream>

namespace rps
{
	barber_ring::barber_ring()
	{
		ring_name = "Barber";
		rarity = 1;
		price = 5;
	}

	int barber_ring::apply_effect(player* player, int points) const
	{
		if (player->selection == 3)
		{
			std::cout << "Barber Bonus! base points * 2!" << std::endl;
			return points;
		}
		return 0;
	}

	best_two_of_three_ring::best_two_of_three_ring()
	{
		ring_name = "Best Two out of Three";
		rarity = 1;
		price = 5;
	}

	int  best_two_of_three_ring::apply_effect(player* player, int points) const
	{
		if (player->wins == 2)
		{
			std::cout << "Best Two out of Three Bonus! base points + 15!" << std::endl;
			return 15;
		}
		return 0;
	}

	pay_day_ring::pay_day_ring()
	{
		ring_name = "Payday";
		rarity = 1;
		price = 5;
	}

	int pay_day_ring::apply_effect(player* player, int points) const
	{
		if (player->wins == 3)
		{
			std::cout << "Payday Bonus! Extra $2!";
			player->money += 2;
		}
		return 0;
	}
}