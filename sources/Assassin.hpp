#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"
using namespace std;

namespace coup {
    class Assassin: public Player {

        public:
            Assassin(Game& g, string name): Player(g, name) {}
            //Assassin can coup with only 3 coins.
            void coup(Player &p) override;
            void block(Player &player) override;
            string role() override;

    };
}