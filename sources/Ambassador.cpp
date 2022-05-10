#include "Ambassador.hpp"
using namespace std;
using namespace coup;
/**
 * @brief transfer a coin from player1 to player2.
 * 
 * @param p1 
 * @param p2 
 */
void Ambassador::transfer(Player& p1, Player& p2)
{
    if(!(_game.check_turn(_name)))
    {   
        throw invalid_argument("Its not this players turn now!");
    }
    if(p1.coins() == 0)
    {
        throw invalid_argument("Not enough coins to transfer!");
    }
    //Transfer a coin from p1 to p2.
    int max_coins = p1.max_coins_to_take(1);
    p1.update_coins(-max_coins);
    p2.update_coins(max_coins);
    //set last action.
    _last_action = TRANSFER;
    _game.update_turn(1);
}
/**
 * @brief Can block another captains steal operation.
 * 
 * @param player 
 */
void Ambassador::block(Player &player)
{
    if(player.role() != "Captain")
    {
        throw invalid_argument("Can only block other captains!");
    }
    if(player.get_last_action() != STEAL)
    {
        throw invalid_argument("Can only block a steal operation!");
    }
    //We successfully block the player which is a captain from stealing!
    player.update_coins(-2);
    player.set_last_action(BLOCKED);
    player.get_player_on()->update_coins(2);
}
string Ambassador::role()
{
    return "Ambassador";
}