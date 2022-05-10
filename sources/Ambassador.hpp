#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"
using namespace std;

namespace coup {
    class Ambassador: public Player {

        public:
            Ambassador(Game& g, string name): Player(g, name) {}
            //transfer one coin from p1 to p2.
            void transfer(Player& p1, Player& p2);
            void block(Player &player) override;
            string role() override;

    };
}