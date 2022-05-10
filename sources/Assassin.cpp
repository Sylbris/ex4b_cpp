#include "Assassin.hpp"
using namespace std;
using namespace coup;

/**
 * @brief perform a coup in the cost of 3 coins, can be blocked by contessa.
 * 
 * @param p 
 */
void Assassin::coup(Player &p) 
{
    if(_game.get_game_state() == READY || _game.get_game_state() == PLAYING)
    {
        if(p.get_couped())
        {
            throw invalid_argument("Player has already been couped!");
        }
        if(!(_game.check_turn(_name)))
        {
            throw invalid_argument("Its not this players turn now!");
        }
        if(_coins < MIN_COUP_COINS)
        {
            throw invalid_argument("Insufficient coins to make a coup");
        }
        //normal coup
        if(_coins >= MAX_COUP_COINS)
        {
            //////////////////////////////////////// REGULAR COUP ////////////////////////////////////////////
            // Overthrow a player.
            int player_index = _game.remove_player(p.get_name());           
            if(_game.players().size() == 1)
            {    
                _game.set_game_state(FINISHED);
                _game.set_winner(_game.players()[0]);
            }
            p.set_couped(true);
            _can_be_blocked = false;
            update_coins(-MAX_COUP_COINS);
            if(player_index > _game.get_turn())
            {
                _game.update_turn(1);
            }
            else
            {
                _game.update_turn(0);
            }

        }
        else 
        {
            /////////////////// COUP or ASSSASINATE with 3 coins! ///////////////////////////////////
            set_player_on(&p);
            //Overthrow a player.
            int player_index = _game.remove_player(p.get_name());
            if(_game.players().size() == 1)
            {    
                _game.set_game_state(FINISHED);
                _game.set_winner(_game.players()[0]);
            }
            set_last_action(COUP);
            _can_be_blocked = true;
            p.set_couped(true);
            update_coins(-3);
            if(player_index > _game.get_turn())
            {
                _game.update_turn(1);
            }
            else
            {
                _game.update_turn(0);
            }
        }
    }
    else
    {
        throw invalid_argument("Game not ready or playing");
    }
    
}
void Assassin::block(Player &player) {}
string Assassin::role()
{
    return "Assassin";
}
