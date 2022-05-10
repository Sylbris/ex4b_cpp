#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"
using namespace std;

namespace coup {
    class Captain: public Player {

        public:
            Captain(Game& g, string name): Player(g, name) {}
            void steal(Player& p);
            void block(Player &player) override;
            string role() override;
    };
}