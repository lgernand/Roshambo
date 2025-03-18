#include <string>

#pragma once
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
	barber_ring()
	{
		rarity = 1;
	}
};