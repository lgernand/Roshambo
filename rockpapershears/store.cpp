#include "store.h"

namespace rps
{
	store::store()
	{
        barber_ring* test_ring = new barber_ring();
        best_two_of_three_ring* test_ring2 = new best_two_of_three_ring();
        pay_day_ring* test_ring3 = new pay_day_ring();

        this->ring_inventory.push_back(test_ring2);
        this->ring_inventory.push_back(test_ring);
        this->ring_inventory.push_back(test_ring3);
	}

    void store::display_ring_inventory(human_player* player)
    {
        std::cout << std::endl << "Store: type 0 to continue to the next level" << std::endl;
        for (auto ring : this->ring_inventory)
        {
            std::cout << ring->ring_name + " $" + std::to_string(ring->price) << std::endl;
        }
        std::cout << std::endl;

        bool exit_store = false;

        while (!exit_store)
        {
            int store_selection;

            std::cin >> store_selection;

            if (store_selection == 0)
            {
                exit_store = true;
            }
            else 
            {
                if (player->money >= ring_inventory[store_selection - 1]->price)
                {
                    player->rings.push_back(ring_inventory[store_selection - 1]);
                    player->money -= ring_inventory[store_selection - 1]->price;
                    std::cout << ring_inventory[store_selection - 1]->ring_name + " Purchased!" << std::endl;
                }
                else {
                    std::cout << "Insufficient funds!" << std::endl;
                }
            }
        }
    }
}