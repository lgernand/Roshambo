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

	int barber_ring::apply_effect(int criteria, int base_points) const
	{
		if (criteria == 3)
		{
			std::cout << "Barber Bonus! base points * 2!" << std::endl;
			return base_points * 2;
		}
		return base_points;
	}

	/*best_two_of_three_ring::best_two_of_three_ring()
	{
		ring_name = "Best Two out of Three";
		rarity = 1;
		price = 5;
	}

	int  best_two_of_three_ring::apply_effect(int criteria, int base_points) const
	{
		if 
	}*/
}