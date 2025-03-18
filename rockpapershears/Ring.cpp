#include "Ring.h"

class ring
{
public:
	std::string ring_name;
	int rarity;
	int price;

	virtual void apply_effect() {};
};

class barber_ring : ring
{
public:
	barber_ring()
	{
		ring_name = "Barber";
		rarity = 1;
		price = 5;
	}

	int apply_effect(rps::human_player player, int base_points)
	{
		if (player.selection == 3)
		{
			"Barber Bonus! base points * 2";
			return base_points * 2;
		}
	}
};