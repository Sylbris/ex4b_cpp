#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>

// CONSTS
const int MAX_COUP_COINS = 7;
const int MIN_COUP_COINS = 3;

const int COUP_COST = 7;
const int DOUBLE_SALARY = 2;
const int MAX_COIN_CAP = 10;

const int MIN_PLAYERS = 1;
const int MAX_PLAYERS = 6;
const int MIN_PLAYERS_TO_PLAY = 2;

namespace coup {
    /**
     * @brief An enum for different game states.
     * GAME will wait for mininum 2 players,
     * then game will be in ready mode.
     * 
     * When a winner is declared ,
     * game will move to FINISHED.
     * 
     */
    enum Game_State
    {   
            WAITING_PLAYERS,
            READY,
            PLAYING,
            FINISHED
    };

    class Game {
        //Will hold all our players, Whenever a player joins we add him to the map.
        std::vector<std::string> _player_list;
        //holds the winner of the game.
        std::string _winner;
        //will contain a number between 0-5 (as there can only be max 6 players.)
        size_t _turn = 0;
        size_t _round = 0;
        Game_State _game_state;

        public:
            Game(){ _game_state = WAITING_PLAYERS;}
            std::vector<std::string> players();
            std::string turn();
            
            //////////////GETTERS AND SETTERS///////////////////////////////////////////////
            const std::string& winner() const;
            void set_winner(const std::string& winner);
            void update_turn(int amount);
            bool check_turn(const std::string& name);
            void add_player(const std::string& name);
            int remove_player(const std::string& name);
            void add_player_with_index(const std::string& name, int index);
            void set_game_state(Game_State gs);
            Game_State get_game_state() const;
            int get_turn() const;
            
    };
}