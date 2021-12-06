/*This is a simple poker dice game. The player rolls 5 dice. After the cast the player has an opportunity to 
roll any dice once again to replace it/them. After that the dice are sorted and the figure is assigned.
Figures are similar to the ones known from poker with some exceptions. All the figures and their rank
in the game are defined in the poker.cpp file. 
Players figure is compared to the non-player-character figure, the highest rank (or number of points 
in case of a tie ) wins the round. 
The copy constructor is used to store players primary cast before the player changes dice.
The game ends when the player decides to.*/ 

#include "poker.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <bits/stdc++.h>
#include <unistd.h>

int main(void){
    std::string play_again = "Y"; //used in a loop to play the game until the player decides to quit

    //welcome message
    std::cout << "--== Welcome to the Poker Dice game! ==--" << std::endl << std::endl;
    std::cout << "Let's get started!" << std::endl << std::endl;
    
    //names:
    std::string npc = "Opponent";
    std::string player = "Player";

    //create Dice objects using a constructor
    Dice Player(player);
    Dice Opponent(npc);

    //loop until player quits

    system("clear");
    Player.get_name(); //player cin name
    Player.greet();

    while(play_again == "Y" || play_again == "y"){

        system("clear");
        Player.roll_dice();
        std::cout << "You rolled: ";
        Player.print_dice();

        std::cout << std::endl << std::endl;
        sleep(1);

        Dice Dice_pre_change(Player); //copy current dice with a copy constructor to back them up before changing
        Player.change_dice(); 

        system("clear");

        std::cout << std::endl << "You had: " << std::endl;
        Dice_pre_change.print_dice();
        std::cout << std::endl << "Your current dice: " << std::endl;
        Player.print_dice();

        sleep(2);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl << "Press Enter to continue..." << std::endl;
        getchar();

        /*The dice are drawn and changed (or stayed untouched), now we're ready to 
        sort it and match figures with each layout with get_figure()*/ 
        Player.get_figure();
        system("clear");
        Player.print_dice();
        std::cout << std::endl << "Your figure is... " << std::endl;
        sleep(2);
        Player.print_figure();
        std::cout << "!" << std::endl << std::endl;

        sleep(1);

        /*Now it's time to draw opponent's dice
        No need to change this time since it's an npc*/
        Opponent.roll_dice();
        Opponent.get_figure();
        Opponent.print_name();
        std::cout << " has got... ";
        std::cout << std::endl;
        sleep(2);
        Opponent.print_figure();
        std::cout << "!" << std::endl;
        Opponent.print_dice();
        std::cout << std::endl << std::endl;
        sleep(2);
        
        /*Now that we have both dice layouts we can compare them by the get_winner() function
        it returns 1 for player win, 2 for opponent win and 3 for tie*/
        switch (get_winner(Player, Opponent)){
            case 1:
                Player.won_round();
                Player.end_round(); 
                Opponent.end_round();
                print_player_win(Player, Opponent);
                break;
            case 2:
                Opponent.won_round();
                Player.end_round(); 
                Opponent.end_round();
                print_player_fail(Player, Opponent);
                break;
            case 3:
                Player.end_round(); 
                Opponent.end_round();
                print_tie(Player, Opponent);
                break;
        }

        std::cout << std::endl << "Would you like to play another round?" << std::endl;
        std::cout << "Type 'Y' for yes, 'N' for no." << std::endl;
        std::cin >> play_again;

        while(play_again[0] != 'Y' && play_again[0] != 'y' && play_again[0] != 'N' && play_again[0] != 'n'){
            std::cout << "Wrong input!" << std::endl;
            std::cout << "to play another round type 'Y', type 'N' wo quit." << std::endl;
            std::cin >> play_again;
        }
    }

    Player.farewell();
    return 0;
}