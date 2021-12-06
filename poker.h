#ifndef POKER_H
#define POKER_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <bits/stdc++.h>

class Dice{
    private:
    std::string name;
    std::vector<int> drawn_dice;
    std::string figure;
    int points;
    int result;
    int rounds_played;
    int rounds_won;

    public:
    void get_name();        //user input - name
    void print_name();      //cout name
    void greet();           //greets player at the start of a round
    void roll_dice();       //assigns random numbers (1-6) to vector<int> drawn_dice
    void print_dice();      //cout current dice stored in vector<int> drawn_dice
    void change_dice();     //enables the player to change chosen number of dice
    void get_figure();      //sorts vector<int> drawn_dice, checks figures, assigns them to string figure variable and assigns points for figures in the int points variable
    void print_figure();    //cout figure
    void won_round();       //adds +1 to int rounds_won if the round was won
    void end_round();       //adds +1 to int rounds_played variable
    void farewell();        //says goodbye

    //Constructors:
    Dice();
    Dice(std::string s);

    /*Copy constructor to store the first cast of dice before using the change_dice() method*/
    Dice(const Dice& initial_cast);

    /*the get_winner() function compares figures from each class, the higher rank of figures wins,
    in case figures are the same, it compares the dice values of the figures, if they're the same,
    it sums the values of all the dice to get the higher score.*/
    friend int get_winner(const Dice& Player, const Dice& Opponent); 

    friend void print_player_win(const Dice& Player, const Dice& Opponent);  //print result if player wins
    friend void print_player_fail(const Dice& Player, const Dice& Opponent); //print result if opponent wins
    friend void print_tie(const Dice& Player, const Dice& Opponent);         //print result in case of a tie

    //functions used by the get_winner function in case of a tie
    friend int tie_bust(const Dice& Player, const Dice& Opponent);
    friend int tie_pair(const Dice& Player, const Dice& Opponent);
    friend int tie_two_pair(const Dice& Player, const Dice& Opponent);
    friend int tie_three_of_a_kind(const Dice& Player, const Dice& Opponent);
    friend int tie_straight(const Dice& Player, const Dice& Opponent);
    friend int tie_full_house(const Dice& Player, const Dice& Opponent);
    friend int tie_four_of_a_kind(const Dice& Player, const Dice& Opponent);
    friend int tie_five_of_a_kind(const Dice& Player, const Dice& Opponent);

    ~Dice(); //destructor is empty
};

#endif /*POKER_H*/