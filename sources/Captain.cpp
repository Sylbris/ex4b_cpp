#include "Captain.hpp"
using namespace std;
using namespace coup;

/**
 * @brief Steal 2 coins from another player,
 * can be blocked by either another captain or an ambassador.
 * 
 * @param p 
 */
void Captain::steal(Player& p)
{   
    if(!(_game.check_turn(_name)))
    {
        throw invalid_argument("Its not this players turn now!");
    }

    _last_action = STEAL;
    int max_coins = p.max_coins_to_take(2);
    update_coins(max_coins);
    p.update_coins(-max_coins);
    set_player_on(&p);
    _game.update_turn(1);
}
/**
 * @brief a captain can stop another captain from stealing.
 * 
 * @param player 
 */
void Captain::block(Player &player) 
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
string Captain::role()
{
    return "Captain";
}