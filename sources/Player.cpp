#include "Player.hpp"
using namespace std;
using namespace coup;

/**
 * @brief Take one coin from the bank.
 *
 */
void Player::income()
{
    //A move can only be made if in READY or PLAYING MODE.
    if(_game.get_game_state() == READY || _game.get_game_state() == PLAYING)
    {
        //if a player is out of the game he cannot make a move.
        if(_has_been_couped)
        {
            throw invalid_argument("Player has been couped");
        }
        //Check if this is the players turn.
        if (_game.check_turn(_name))
        {
            //if player at coin cap , he must perform a coup.
            if (_coins >= MAX_COIN_CAP)
            {
                throw invalid_argument("Must perform a coup!");
            }
            if(_game.get_game_state() == READY)
            {
                _game.set_game_state(PLAYING);
            }
            _coins++;
            _game.update_turn(1);

            // add the last action, remember nothing can block an income.
            _last_action = INCOME;
        }
        else
        {
            throw invalid_argument("Its not this players turn now !");
        }
    }
    else
    {
        throw invalid_argument("Game not ready!");
    }   
}
/**
 * @brief Perform the foreign aid operation.
 *
 */
void Player::foreign_aid()
{
    if(_game.get_game_state() == READY || _game.get_game_state() == PLAYING)
    {
        if(_game.get_game_state() == READY)
        {
            _game.set_game_state(PLAYING);
        }
        if (!_game.check_turn(_name))
        {
        
            throw invalid_argument("Its not this players turn now!");
        }
        if (_coins >= MAX_COIN_CAP)
        {
                throw invalid_argument("Must perform a coup!");
        }
        _last_action = FOREIGN_AID;
        _coins += DOUBLE_SALARY;
        _game.update_turn(1);
    }
    else
    {
        throw invalid_argument("Not enough players");
    }

}
/**
 * @brief Overthrow a player from the game.
 *
 * @param p
 */
void Player::coup(Player &p)
{
    if(_game.get_game_state() == READY || _game.get_game_state() == PLAYING)
    {
        if(p.get_couped())
        {
            throw invalid_argument("Player has already been couped!");
        }
        if(_game.get_game_state() == READY)
        {
            _game.set_game_state(PLAYING);
        }
        if (p._name == this->_name)
        {
            throw invalid_argument("Cannot coup yourself!");
        }

        if (_coins < COUP_COST)
        {
            throw invalid_argument("Insufficient coins to make a coup");
        }

        // Overthrow a player.
        int player_index = _game.remove_player(p.get_name());
        if(_game.players().size() == MIN_PLAYERS)
        {    
            _game.set_game_state(FINISHED);
            _game.set_winner(_game.players()[0]);
        }
        p.set_couped(true);
        update_coins(-COUP_COST);
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
        throw invalid_argument("Game is not ready or finished!");
    }
}
/**
 * @brief returns a player's role.
 * 
 * @return string 
 */
string Player::role()
{
    return "Player";
}
/**
 * @brief returns amount of coins a player has.
 * 
 * @return int 
 */
const int& Player::coins() const
{
    return _coins;
}
void Player::update_operation()
{
}
/**
 * @brief Update players coins with the amount specified, keep in mind
 * amount is always positive.
 * and a players coin can never go under 0!
 *
 * @param amount
 */
void Player::update_coins(int amount)
{

    if (_coins + amount < 0)
    {
        _coins = 0;
    }
    else
    {
        _coins += amount;
    }
}
// Blocks the last action performed by player.
void Player::block(Player &player)
{
    if (player._name == this->_name)
    {
        throw invalid_argument("Cannot block yourself!");
    }
    if (player._last_action == INCOME)
    {
        throw invalid_argument("Cannot block an income action");
    }

    if (player._last_action == TAX && player.role() == "Duke")
    {
        throw invalid_argument("Cannot stop the Duke from taking taxes!");
    }
}
/**
 * @brief returns a players name.
 *
 * @return std::string
 */
std::string Player::get_name()
{
    return _name;
}
/**
 * @brief return the last action a player has performed.
 *
 * @return Action
 */
Action Player::get_last_action()
{
    return _last_action;
}
/**
 * @brief Update a player last action.
 * 
 */
void Player::set_last_action(Action la)
{
    _last_action = la;
}
/**
 * @brief If we performs an action on a certain player, 
 * allows us to keep ref to that player.
 * 
 * @param other 
 */
void Player::set_player_on(Player* other)
{
    _player_on = other;
}
/**
 * @brief Get the player we performed an action on.
 * 
 * @return Player* 
 */
Player* Player::get_player_on()
{
    return _player_on;
}
/**
 * @brief changes a players abillity to be couped.
 * 
 * @param _couped 
 */
void Player::set_couped(bool _couped)
{
    _has_been_couped = _couped;
}
/**
 * @brief check is aplayer can be couped.
 * 
 * @return true 
 * @return false 
 */
bool Player::get_couped() const
{
    return _has_been_couped;
}
void Player::set_players_turn(int turn)
{
    _player_turn = turn;
}
int Player::get_players_turn() const
{
    return _player_turn;
}
int Player::max_coins_to_take(int amount) const
{
    if(_coins >= amount)
    {
        return amount;
    }
    return _coins;
}
bool Player::get_can_be_blocked() const
{
    return _can_be_blocked;
}
void Player::set_can_be_blocked(bool blocked)
{
    _can_be_blocked = blocked;
}