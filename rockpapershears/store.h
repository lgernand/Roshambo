#ifndef STORE_H
#define STORE_H

#include <list>
#include "ring.h"
#include <vector>
#include "human_player.h"

namespace rps
{
	class store
	{
	public:
		std::vector<ring*> ring_inventory;

		store();
		void display_ring_inventory(human_player* player);
	};
}
#endif