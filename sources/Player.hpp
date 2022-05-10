#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Game.hpp"

namespace coup {

    // An enum depicting certain actions a player can take.
    enum Action
    {
        INCOME,
        FOREIGN_AID,
        COUP,
        TAX,
        STEAL,
        BLOCKED,
        TRANSFER
    };

    class Player {

        protected:
            std::string _name;
            int _player_turn; //in each round indicate this player turn;
            int _coins = 0;
            Game& _game;
            Action _last_action;
            bool _has_been_couped = false;
            Player *_player_on; //stores a pointer to another player,this can be used incase we perform some action
            //on another player, and wish to revert that action.
            bool _can_be_blocked = false;
            
        public:
            //Constructor with default settings.
            Player(Game& g, std::string n): _game(g), _name(n)
            {
                _game.add_player(_name);
                _player_turn = (int)_game.players().size();
            }
            void income();
            void foreign_aid();
            virtual void coup(Player &p);
            virtual std::string role();
            

            const int& coins() const;
            void update_operation();
            //Blocks the last action performed by player.
            virtual void block(Player &player);
            void update_coins(int amount);
            bool get_block_status();
            std::string get_name();
            
            ////////////////////////////////////Getters & Setters//////////////////////////////////////////////
            Action get_last_action();
            void set_last_action(Action la);

            void set_player_on(Player* other);
            Player* get_player_on();

            void set_couped(bool _couped);
            bool get_couped() const;

            void set_players_turn(int turn);
            int get_players_turn() const;
            int max_coins_to_take(int amount) const;

            bool get_can_be_blocked() const;
            void set_can_be_blocked(bool blocked);
    };

}