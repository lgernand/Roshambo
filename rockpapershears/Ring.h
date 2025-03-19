#ifndef RING_H
#define RING_H

#include <string>>
#include "player.h"

namespace rps
{
	class ring
	{
	public:
		std::string ring_name;
		int rarity;
		int price;

		virtual int apply_effect(player* player, int points) const = 0;
	};

	class barber_ring : public ring
	{
	public:
		barber_ring();

		int apply_effect(player* player, int points) const override;
	};

	class best_two_of_three_ring : public ring
	{
	public:
		best_two_of_three_ring();

		int apply_effect(player* player, int points) const override;
	};

	class pay_day_ring : public ring
	{
	public:
		pay_day_ring();

		int apply_effect(player* player, int points) const override;
	};
}
#endif