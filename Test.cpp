/**
 * Demo program for Coup exercise
 *
 * @author: Dan Davydov
 * @since: 2022-04
 */

#include "Player.hpp"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "Game.hpp"
#include "doctest.h"

using namespace coup;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

const int NAME_LEN = 5;
static Game game_1{};

/**
 * @brief Generate a random name string of size len.
 * 
 * @param len 
 * @return string 
 */
string generateWord(int len)
{

    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                        'r', 's', 't', 'u', 'v', 'w', 'x',
                        'y', 'z'};
    string word = "";
    for (int i = 0; i < len; i++)
    {
        word = word + letters[rand() % 26];
    }

    return word;
}
/**
 * @brief Generate a random player with given name;
 * 
 * @return Player& 
 */
void generateCard(string name){
    int role = rand()%(5);
    switch (role) {
        case 0:
            Duke{game_1, name};
            break;
        case 1:
            Assassin{game_1, name};
            break;
        case 2:
            Ambassador{game_1, name};
            break;
        case 3:
            Captain{game_1, name};
            break;
        case 4:
            Contessa{game_1, name};
            break;
    }
}
/**
 * @brief We set a state of initial gameplay and test it.
 * 
 */
TEST_CASE("Create a new game"){
    //Generate random 6 cards. for the game.
    for(size_t i = 0; i < 6;i++){
        string name = generateWord(NAME_LEN);
        generateCard(name);

        //Means we successfully added roles.
        CHECK_NE(game_1.players().at(i) , "Player");

        //Check player has 0 coins.
        //CHECK(game_1.players().at(i) == 0);
    }
    //for each card, check you cannot add them to the game.
    CHECK_THROWS(Contessa c(game_1, "dan"));
    CHECK_THROWS(Duke d(game_1, "dan"));
    CHECK_THROWS(Assassin a(game_1, "dan"));
    CHECK_THROWS(Ambassador a(game_1, "dan"));
    CHECK_THROWS(Captain c(game_1, "dan"));

    //Check our game has 6 players.
    CHECK(game_1.players().size() == 6);
    //Check its player 1 turn.
    CHECK(game_1.turn() == game_1.players().at(0));
    //Game should have no winner.
    CHECK(game_1.winner() == "");

}
TEST_CASE("Illegal moves")
{   
    Game game_2{};
    Contessa c(game_2, "dan");

    //check starting coins.
    CHECK(c.coins() == 0);

    //Game cannot start with 1 player.
    CHECK_THROWS(c.income());

    //Player cannot overthrow himself.
    CHECK_THROWS(c.coup(c));
    CHECK_THROWS(c.foreign_aid());
    CHECK_THROWS(c.block(c));


}

TEST_CASE("normal game")
{
    Game game_3{};

	Duke duke{game_3, "M"};
	Assassin assassin{game_3, "Y"};
	Ambassador ambassador{game_3, "M"};
	Captain captain{game_3, "R"};
	Contessa contessa{game_3, "G"};

    //lets play a few game... 
    for(int i=0; i<7 ;i++)
    {
        CHECK_NOTHROW(duke.income());
        CHECK_NOTHROW(assassin.income());
        CHECK_NOTHROW(ambassador.income());
        CHECK_NOTHROW(captain.income());
        CHECK_NOTHROW(contessa.income());
    }

}

TEST_CASE("Bad input")
{
   
}
