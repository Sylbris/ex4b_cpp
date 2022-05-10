#include "Contessa.hpp"
using namespace std;
using namespace coup;

void Contessa::block(Player &player)
{
    if(player.role() == "Assassin" && player.get_last_action() == COUP && player.get_can_be_blocked())
    {
        //add player back to game.
        player.get_player_on()->set_couped(false);
        //add player back to game.
        int index = player.get_player_on()->get_players_turn() -1;
        _game.add_player_with_index(player.get_player_on()->get_name(), index);
        if(_game.get_turn() > index)
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
        throw invalid_argument("Cannot block this!");
    }
}
string Contessa::role()
{
    return "Contessa";
}