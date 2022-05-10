#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"
using namespace std;

namespace coup {
    class Contessa: public Player {

        public:
            Contessa(Game& g, string name): Player(g, name) {}
            void block(Player &player) override;
            string role() override;
    };
}