#include "Duke.hpp"
using namespace std;
using namespace coup;
/**
 * @brief allows duke to take a tax of 3 coins from the bank ,
 * cannot be blocked.
 * 
 */
void Duke::tax()    
{   
    if(_game.get_game_state() == PLAYING || _game.get_game_state() == READY)
    {
        if(_game.check_turn(_name))
        {   
            if(_game.get_game_state() == READY)
            {
                _game.set_game_state(PLAYING);
            }
            _coins+=3;
            _game.update_turn(1);
        }
        else 
        {
            throw invalid_argument("Its not this players turn now!");
        }
    }
    else
    {
        throw invalid_argument("Game hasn't started yet or finished");
    }

}
void Duke::block(Player &player)
{
    if(player.get_last_action() != FOREIGN_AID)
    {
        throw invalid_argument("can only block foreign aid");
    }
    //Return the coins to the bank.
    player.update_coins(-2);
    player.set_last_action(BLOCKED);
}
string Duke::role()
{
    return "Duke";
}