#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"
using namespace std;

namespace coup {
    class Duke: public Player {

        public:
            Duke(Game& g, string name): Player(g, name) {}
            void tax();
            void block(Player &player) override;
            string role() override;
    };
}