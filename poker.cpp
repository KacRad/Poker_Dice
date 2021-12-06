#include "poker.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <bits/stdc++.h>
#include <unistd.h>

/*Defining the order of figures from lowest to highest*/
#define BUST            0
#define ONE_PAIR        1
#define TWO_PAIR        2
#define THREE_OF_A_KIND 3
#define STRAIGHT        4
#define FULL_HOUSE      5
#define FOUR_OF_A_KIND  6
#define FIVE_OF_A_KIND  7 

std::string higher_dice;

void Dice::get_name(){
    std::cout << "Enter your name: " << std::endl;
    getline(std::cin, name);
}

void Dice::print_name(){
    std::cout << name;
}

void Dice::greet(){ 
    system("clear");
    std::cout << "Greetings " << name << "!" << std::endl << std::endl << "Press Enter to roll the dice!" << std::endl;
    getchar();
}

void Dice::farewell(){
    system("clear");
    std::cout << "Goodbye " << name << "!" << std::endl 
    << "You won " << rounds_won << " out of " << rounds_played << " rounds. Congratulations!"
    << std::endl << "Thank you for your time." << std::endl;
}

/*Assigns random values from1 to 6 into the drawn_dice vector*/
void Dice::roll_dice(){
    drawn_dice.clear();
    srand(time(NULL));
    int currently_cast_dice;
    for(int i = 0; i < 5; i++){
        currently_cast_dice = rand() % 6 + 1;
        drawn_dice.push_back(currently_cast_dice);
    }
}

/*prints current dice*/
void Dice::print_dice(){
    for(int i=0; i<(int)drawn_dice.size(); i++){
        std::cout << "  | " << drawn_dice[i] << " |  ";
    }
    std::cout << std::endl;
}

/*change_dice method asks the player to replace the dice and if confirmed
allows to change the dice chosen by the player by drawing them again*/
void Dice::change_dice(){
    std::string decision;
    int dice_to_change = 0;
    int index;
    std::cout << "Would you like to replace any dice?" << std::endl;
    std::cout << "type 'Y' for yes, 'N' for no." << std::endl;
    std::cin >> decision;
    while(decision[0] != 'Y' && decision[0] != 'y' && decision[0] != 'N' && decision[0] != 'n'){
        std::cout << "Wrong input!" << std::endl;
        std::cout << "to replace dice type 'Y', to remain current dice type 'N'." << std::endl;
        std::cin >> decision;
    }
    if(decision[0] == 'Y' || decision[0] == 'y'){
        system("clear");
        print_dice();
        std::cout << "How many dice would you like to replace: ";
        std::cin >> dice_to_change;
        while(dice_to_change < 1 || dice_to_change > 5){
            std::cout << "Wrong input! Enter number from 1 to 5: ";
            std::cin >> dice_to_change;
        }
        srand(time(NULL));
        system("clear");
        std::cout << "Enter the index of replaced dice from 1 (first dice) to 5 (last dice)" << std::endl;
        print_dice();
        for(int i = 1; i <= dice_to_change; i++){
            std::cout << "Replacement no. " << i << ". Enter index: ";
            std::cin >> index;
            while(index < 1 || index > 5){
                std::cout << "Wrong index value! Try again: ";
                std::cin >> index;
            }
            drawn_dice[index-1] = rand() % 6 + 1;
        }
        std::cout << std::endl << "Success! Dice replaced! " << std::endl;
    }
}

/*get_figure() checks how many different dice are drawn to assume the figure 
for example: 4 different dice out of 5 - it's obviously a pair,
as well as only one type of dice out of 5 has to be a Flush (Five of a kind)
No matter the specific dice values.*/
void Dice::get_figure(){
    sort(drawn_dice.begin(), drawn_dice.end());
    int different_dice_counter = 0;
    for (int i = 0; i < (int)drawn_dice.size(); i++){
        if(drawn_dice[i] != drawn_dice[i+1]){
            different_dice_counter++;
        }
    }
    int a, b, c, counter;
    switch (different_dice_counter){
        case 4: 
            figure = "One pair";
            points = ONE_PAIR;
        break;

        case 3: 
            for(int i=0; i < (int)(drawn_dice.size() - 2); i++){
                a = drawn_dice[i];
                b = drawn_dice[i+1];
                c = drawn_dice[i+2];
                if(a == b && a == c){
                    figure = "Three of a kind";
                    points = THREE_OF_A_KIND;
                    break;
                }else {
                    figure = "Two pair";
                    points = TWO_PAIR;
                }
            }
        break;

        case 5: 
            counter = 1;
            for(int i = 0; i < (int)(drawn_dice.size() - 1); i++){
                if(drawn_dice[i] != (drawn_dice[i+1] - 1)){
                    counter = 0;
                }
                if(counter == 1){
                    figure = "Straight";
                    points = STRAIGHT;
                }else{
                    figure = "Bust";
                    points = BUST;
                }
            }
        break;

        case 2: 
            counter = 0;
            a = drawn_dice.front();
            for(int i = 0; i < (int)drawn_dice.size(); i++){
                if(a == drawn_dice[i]){
                    counter++;
                }
            }
            if(counter == 1 || counter == 4){
                figure = "Four of a kind";
                points = FOUR_OF_A_KIND;
            } else {
                figure = "Full house";
                points = FULL_HOUSE;
            }
        break;

        case 1:
            figure = "Five of a kind (Flush)";
            points = FIVE_OF_A_KIND;
        break;
    }
}

void Dice::print_figure(){
    std::cout << figure;
}

void Dice::won_round(){
    rounds_won++;
}

void Dice::end_round(){
    rounds_played++;
}

//Copy constructor
Dice::Dice(const Dice& initial_cast){
    name = initial_cast.name;
    drawn_dice = initial_cast.drawn_dice;
}

Dice::Dice(){
    name = "No name";
    drawn_dice = {0, 0, 0, 0, 0};
    figure = "None";
    points = 0;
    result = 0;
    rounds_played = 0;
    rounds_won = 0;
}

Dice::Dice(std::string s){
    name = s;
    drawn_dice = {0, 0, 0, 0, 0};
    figure = "None";
    points = 0;
    result = 0;
    rounds_played = 0;
    rounds_won = 0;
}

Dice::~Dice(){
    //nothing to destroy for now
}

/*The get_winner function returns 1 if player wins, 2 if player loses and 3 if it's a tie*/
int get_winner(const Dice& Player, const Dice& Opponent){
    if(Player.points > Opponent.points){
        return 1;
    }else if(Player.points < Opponent.points){
        return 2;
    }else{
        /*in case figures are the same, check exact figure values to get the result*/
        switch(Player.points){
            case ONE_PAIR:
                return tie_pair(Player, Opponent);
            break;

            case TWO_PAIR:
                return tie_two_pair(Player, Opponent);
            break;

            case THREE_OF_A_KIND:
                return tie_three_of_a_kind(Player, Opponent);
            break;

            case STRAIGHT:
                return tie_straight(Player, Opponent);
            break;

            case FOUR_OF_A_KIND:
                return tie_four_of_a_kind(Player, Opponent);
            break;

            case FULL_HOUSE:
                return tie_full_house(Player, Opponent);
            break;

            case FIVE_OF_A_KIND:
                return tie_five_of_a_kind(Player, Opponent);
            break;

            default:
            return tie_bust(Player, Opponent);
        }
    }
}

/*Prints the result if player wins*/ 
void print_player_win(const Dice& Player, const Dice& Opponent){
    higher_dice = "";
    int p_points = Player.points; 
    int o_points = Opponent.points;
    if(p_points == o_points){
        higher_dice = "higher dice ";
    }
    std::cout << std::endl << Player.name << " won with "<< higher_dice << Player.figure << " against " << Opponent.figure << "!" << std::endl;
    std::cout << Player.name << " won " << Player.rounds_won << " out of " << Player.rounds_played << " rounds!" << std::endl;
}

/*Prints the result if player loses*/
void print_player_fail(const Dice& Player, const Dice& Opponent){
    higher_dice = "";
    int p_points = Player.points; 
    int o_points = Opponent.points;
    if(p_points == o_points){
        higher_dice = "higher dice ";
    }
    std::cout << std::endl << Player.name << " lost with " << Player.figure << " against " << higher_dice << Opponent.figure << "!" << std::endl;
    std::cout << Player.name << " lost " << Opponent.rounds_won << " out of " << Player.rounds_played << " rounds!" << std::endl;
}

/*Prinst the result in case of a tie*/
void print_tie(const Dice& Player, const Dice& Opponent){
    std::cout << std::endl << "Tie! No points!" << std::endl;
    std::cout << Player.name << " won " << Player.rounds_won << " out of "<< Player.rounds_played<< " rounds!" <<  std::endl;
}

/*Functions called by the get_winner() functions in case the figures are the same
returns the same values - 1 if player wins, 2 if player loses, 3 in case of a tie*/
int tie_bust(const Dice& Player, const Dice& Opponent){ // sum all dice values, the highest number wins
    int player_chance = 0;
    int opponent_chance = 0;
    for(int i = 0; i < (int)Player.drawn_dice.size(); i++){
        player_chance += Player.drawn_dice[i];
        opponent_chance += Opponent.drawn_dice[i];
    }
    if(player_chance > opponent_chance){
        return 1;
    }else if(player_chance < opponent_chance){
        return 2;
    }else{
        return 3;
    }
}

int tie_pair(const Dice& Player, const Dice& Opponent){
    int player_chance, opponent_chance; 
    /*Check which pair is higher*/
    for(int i = 0; i < (int)(Player.drawn_dice.size()-1); i++){
        if(Player.drawn_dice[i] == Player.drawn_dice[i+1]){
            player_chance = Player.drawn_dice[i];
        }
        if(Opponent.drawn_dice[i] == Opponent.drawn_dice[i+1]){
            opponent_chance = Opponent.drawn_dice[i];
        }
    }
    if(player_chance > opponent_chance){
        return 1;
    }else if(player_chance < opponent_chance){
        return 2;
    }else{
        /*if pairs are equal, sum all the dice values to get the winner*/
        for(int i = 0; i < (int)Player.drawn_dice.size(); i++){
                player_chance += Player.drawn_dice[i];
                opponent_chance += Opponent.drawn_dice[i];
        }
        if(player_chance > opponent_chance){
            return 1;
        }else if(player_chance < opponent_chance){
            return 2;
        }else{
            return 3;
        }
    }
}

int tie_two_pair(const Dice& Player, const Dice& Opponent){
    int player_first_pair_value = 0, player_second_pair_value = 0, opponent_first_pair_value = 0, opponent_second_pair_value = 0;
    int player_chance = 0, opponent_chance = 0;

    /*first: get the value of each pair of dice for both player and opponent*/
    for(int i = 1; i < (int)(Player.drawn_dice.size()-1); i++){
        if(Player.drawn_dice[i-1] == Player.drawn_dice[i] && player_first_pair_value == 0){
            player_first_pair_value = Player.drawn_dice[i];
        }else if(Player.drawn_dice[i] == Player.drawn_dice[i+1] && player_first_pair_value != 0){
            player_second_pair_value = Player.drawn_dice[i];
        }
        if(Opponent.drawn_dice[i-1] == Opponent.drawn_dice[i] && opponent_first_pair_value == 0){
            opponent_first_pair_value = Opponent.drawn_dice[i];
        }else if(Opponent.drawn_dice[i] == Opponent.drawn_dice[i+1] && opponent_first_pair_value != 0){
            opponent_second_pair_value = Opponent.drawn_dice[i];
        }
    }
    /*now we sum the pair values to check which player has the highest score*/
    if((player_first_pair_value + player_second_pair_value) > (opponent_first_pair_value + opponent_second_pair_value)){
        return 1;
    }else if((player_first_pair_value + player_second_pair_value) < (opponent_first_pair_value + opponent_second_pair_value)){
        return 2;
    }else{ 
        //if pairs are of the same value, sum all the dice to get the winner
        for(int i = 0; i < (int)Player.drawn_dice.size(); i++){
            player_chance += Player.drawn_dice[i];
            opponent_chance += Opponent.drawn_dice[i];
        }
        if(player_chance > opponent_chance){
            return 1;
        }else if(player_chance < opponent_chance){
            return 2;
        }else{
            return 3;
        }
    }
}

int tie_three_of_a_kind(const Dice& Player, const Dice& Opponent){
    int player_chance, opponent_chance; 
    /*Check which figure is higher*/
    for(int i = 0; i < (int)(Player.drawn_dice.size()-1); i++){
        if(Player.drawn_dice[i] == Player.drawn_dice[i+1]){
            player_chance = Player.drawn_dice[i];
        }
        if(Opponent.drawn_dice[i] == Opponent.drawn_dice[i+1]){
            opponent_chance = Opponent.drawn_dice[i];
        }
    }
    if(player_chance > opponent_chance){
        return 1;
    }else if(player_chance < opponent_chance){
        return 2;
    }else{
        /*if figures are equal, sum all the dice values to get the winner*/
        for(int i = 0; i < (int)Player.drawn_dice.size(); i++){
                player_chance += Player.drawn_dice[i];
                opponent_chance += Opponent.drawn_dice[i];
        }
        if(player_chance > opponent_chance){
            return 1;
        }else if(player_chance < opponent_chance){
            return 2;
        }else{
            return 3;
        }
    }
}

int tie_straight(const Dice& Player, const Dice& Opponent){
    /*there are only two types of straights, the higher first (or any other dice of the same index) dice value wins, otherwise it's a tie*/
    if(Player.drawn_dice[0] > Opponent.drawn_dice[0]){
        return 1;
    }else if(Player.drawn_dice[0] < Opponent.drawn_dice[0]){
        return 2;
    }else{
        return 3;
    }
}

int tie_full_house(const Dice& Player, const Dice& Opponent){
    /*if both players get full house, the higher sum of all the dice wins*/
    int player_chance = 0;
    int opponent_chance = 0;
    for(int i = 0; i < (int)Player.drawn_dice.size(); i++){
        player_chance += Player.drawn_dice[i];
        opponent_chance += Opponent.drawn_dice[i];
    }
    if(player_chance > opponent_chance){
        return 1;
    }else if(player_chance < opponent_chance){
        return 2;
    }else{
        return 3;
    }
}

int tie_four_of_a_kind(const Dice& Player, const Dice& Opponent){
    int player_chance = 0;
    int opponent_chance = 0;
    //First we check who has the higher figure
    for(int i = 0; i < (int)(Player.drawn_dice.size()-1); i++){
        if(Player.drawn_dice[i] == Player.drawn_dice[i+1]){
            player_chance = Player.drawn_dice[i];
        }
        if(Opponent.drawn_dice[i] == Opponent.drawn_dice[i+1]){
            opponent_chance = Opponent.drawn_dice[i];
        }
    }
    if(player_chance > opponent_chance){
        return 1;
    }else if(player_chance < opponent_chance){
        return 2;
    }else{
        //if both figures are equal, we sum all the dice values to get the winner
        for(int i = 0; i < (int)Player.drawn_dice.size(); i++){
            player_chance += Player.drawn_dice[i];
            opponent_chance += Opponent.drawn_dice[i];
        }
        if(player_chance > opponent_chance){
            return 1;
        }else if(player_chance < opponent_chance){
            return 2;
        }else{
            return 3;
        }
    }
}

int tie_five_of_a_kind(const Dice& Player, const Dice& Opponent){
    /*similarily to straight, there are only two types of flush, 
    the higher first dice value wins, otherwise it's a tie*/
    if(Player.drawn_dice[0] > Opponent.drawn_dice[0]){
        return 1;
    }else if(Player.drawn_dice[0] < Opponent.drawn_dice[0]){
        return 2;
    }else{
        return 3;
    }
}
