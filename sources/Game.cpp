#include "Game.hpp"

using namespace std;
using namespace coup;


/**
 * @brief return a list of players.
 * 
 * @return vector<string> 
 */
vector<string> Game::players()
{
    return _player_list;
}
/**
 * @brief which turn is it to play.
 * 
 * @return string 
 */
string Game::turn()
{
return _player_list[_turn];
}
/**
 * @brief returns the winner if he exists.
 * 
 * @return string 
 */
const std::string& Game::winner() const
{
    if(_winner.empty())
    {
        throw invalid_argument("There is no winner yet!");
    }
    return _winner;
}
void Game::set_winner(const std::string& winner)
{
    _winner = winner;
}
/**
 * @brief Check if it is that players turn.
 * 
 * @param name 
 * @return true 
 * @return false 
 */
bool Game::check_turn(const std::string& name)
{   
    return _player_list[_turn] == name;
}
/**
 * @brief after each player, we pass to next turn.
 * 
 */
void Game::update_turn(int amount)
{
    _turn+=(size_t)amount;
    _turn %= _player_list.size();
}
/**
 * @brief Add a player to the game
 * 
 * @param name 
 */
void Game::add_player(const std::string& name)
{   
    //Cannot add player after game is finished.
    if(_game_state == FINISHED)
    {
        throw invalid_argument("Game is finished, we have a winner");
    }
    //Cannot add players once game is started.
    if(_game_state == PLAYING)
    {
        throw invalid_argument("Game has already started, cannot add players");
    }
    //Game is at full capacity.
    if(_player_list.size() == MAX_PLAYERS)
    {
        throw invalid_argument("Game is full!");
    }
    _player_list.push_back(name);

    //We added a player, now check if have min 2 players to start the game.
    if(_player_list.size() > MIN_PLAYERS_TO_PLAY)
    {
        set_game_state(READY);
    }
    
}
/**
 * @brief Remove a player from the game,
 * and return its index.
 * 
 * @param name 
 */
int Game::remove_player(const std::string& name)
{
    //Cannot remove players once game is finished!
    if(_game_state == FINISHED)
    {
        throw invalid_argument("Game is finished, we have a winner");
    }
    
    for(int i=0; i<_player_list.size();i++)
    {
        if(_player_list[(size_t)i] == name)
        {
            _player_list.erase(_player_list.begin()+i);
            return i;
        }
    }
    return -1;
}
/**
 * @brief add a player back to list with index.
 * used to put a player back in the game.
 * 
 * @param name 
 * @param index 
 */
void Game::add_player_with_index(const std::string& name, int index)
{   
    auto iterator = _player_list.begin() + index;
   _player_list.insert( iterator , name);
}
/**
 * @brief Change game state.
 * 
 * @param gs 
 */
void Game::set_game_state(Game_State gs)
{
    _game_state = gs;
}
/**
 * @brief Get game state.
 * 
 * @return Game_State 
 */
Game_State Game::get_game_state() const
{
    return _game_state;
}
/**
 * @brief used to check whos turn is it.
 * 
 * @return int 
 */
int Game::get_turn() const
{
    return _turn;
}