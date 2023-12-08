// DiceGameFinal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include "MenuOptions.h"

using namespace std;

int dice[40] = {};

int PlayerAmount();
void DiceRoll(), ShowPlayerDice(), GameMain(), ShowEndDice(), DiceAmount(), FaceDice(), Comp(int);

int numPlayers, currentPlayer, compPlayer, maxDice;
int amount = 0, amountPrev = 0;
int face = 0, facePrev = 0;
bool endGame = false;

int main()
{    
    srand(time(0));
    numPlayers = PlayerAmount();
    DiceRoll();
    ShowPlayerDice();
    GameMain();    
}

void Menu()
{

}

int PlayerAmount()
{
    int playerCount = 0;

    while (playerCount == 0) // loop gets how many players there will be
    {
        cout << "How many Players are playing today? (2-8)" << endl;
        cin >> playerCount;
        cout << endl;
        if (playerCount >= 2 && playerCount <= 8)//Makes sure the amount entered is between 2 and 8
        {
            cout << "Lets begin a game with " << playerCount << " players." << endl;
        }
        else // else they will be asked to enter it again.
        {
            cout << "Please enter a number between 2 and 8." << endl;
            playerCount = 0;
            cin.clear();
            cin.ignore();            
        }
    }    
    return playerCount;
}

void DiceRoll() 
{
    int randDiceNum;    

    for (int i = 0; i < 5 * numPlayers; i++) //will roll for each player playing
    {        
         randDiceNum = rand() % 6 + 1;
         dice[i] = randDiceNum;               
    }

    /*for (int j = 0; j < 5 * numPlayers; j++)
    {
        cout << dice[j] << endl;
    }*/
    //Testing for array to fill with numbers.
    maxDice = numPlayers * 5;
}

void ShowPlayerDice() //Shows player their 5 dice to begin.
{
    cout << "Your dice: ";
    for (int i = 0; i < 5; i++)
    {
        cout << dice[i] << ", ";
    }
    cout << endl << endl;
}

void GameMain() //runs main game 
{
     
    char decis = 'B';   

    while (endGame == false) // keeps game going for betting until someone calls a liar
    {                
            DiceAmount();            

            for (int i = 1; i < numPlayers; i++) //Runs though how ever many computer players there are.
            {
                Comp(i);
                currentPlayer = i + 1;

                if (endGame == true)
                {
                    break;
                }

                cout << "Would you like to call them a Liar ? (Type L)." << endl;
                cout << "Or" << endl;
                cout << "Would you like to belive them? (Type B)" << endl;
                cin >> decis;
                cout << endl;

                if (toupper(decis) == 'L') // if entry is L then loop is exited and run to end function.
                {
                    ShowEndDice();                    
                    endGame = true;
                    break;
                }
                else if (toupper(decis) == 'B') // if entry is a b then continue the loop for the computers
                {

                    continue;
                }
                else //if entry is not a L or B input again
                {
                    cout << "invalid entry, Please try again." << endl;
                    endGame = false;
                }
            }                
    }    
}

void DiceAmount()
{
    bool amountDone = false;
    
    while (amountDone == false) //loop  runs to make sure the amount of dice is within maximum and higher then the last.
    {
        cout << "Enter how many dice?" << endl;
        cout << "Keep in mind this has to be higher then previous bet and under the max of " << numPlayers * 5 << endl;
        cin >> amount;
        cout << endl;

        if (amount <= numPlayers * 5)//make sure amount is under maximum
        {
            FaceDice();
            amountDone = true;
        }
        else // if entry is over or under will as again
        {
            cout << "Invalid amount" << endl;
            cout << "Try again." << endl;
            amountDone = false;
        }
    }
}

void FaceDice()
{
    bool faceDone = false;

    while (faceDone == false) //loop runs to make sure the face input is correct.
    {
        cout << "Now enter which dice" << endl;
        cout << "This will be the die face number (1-6)" << endl;
        cin >> face; 
        cout << endl;

        if (face <= 6 && face >= 1) //make sure the face number is bettween 1 and 6
        {
            cout << "you have bet " << amount << " " << face << "'s" << endl;
            cout << endl;
            amountPrev = amount;
            facePrev = face;
            faceDone = true;
        }
        else//if the input isnt correct ask fot it again
        {
            cout << "Invalid die face" << endl;
            cout << "Try again." << endl;
            faceDone = false;
        }
    }
}

void Comp(int player) // Very Simple computer guess code to play as the computer players
{
    int diceCount[7] = {};
    int guessAmount = 0 , guessFace = 0, maxNum = 0, maxFace = 0;
    int ones = 0, twos = 0, threes = 0, fours = 0, fives = 0, sixes = 0;
    bool callLiar = false;

   

    for (int i = (player * 5); i < ((player * 5) + 5); i++) // count up all total dice for player to check.
    {
        switch (dice[i]) //check each die face in the comps hand and add them into current players count.
        {
        case 1:
            ones++;
            break;
        case 2:
            twos++;
            break;
        case 3:
            threes++;
            break;
        case 4:
            fours++;
            break;
        case 5:
            fives++;
            break;
        case 6:
            sixes++;
            break;
        default:
            break;
        }
    }

    for (int i = 0; i <= 6; i++) // takes the count and puts it into array 
        //to be compared with in coming steps for guessing
    {
        switch (i)
        {
        case 1:
            diceCount[i] = ones;
            break;
        case 2:
            diceCount[i] = twos;
            break;
        case 3:
            diceCount[i] = threes;
            break;
        case 4:
            diceCount[i] = fours;
            break;
        case 5:
            diceCount[i] = fives;
            break;
        case 6:
            diceCount[i] = sixes;
            break;
        default:
            break;
        }
    }

    //comp calling out previous guess

    if (amountPrev >= (maxDice * .33))
    {
        callLiar = rand() % 2;        
    }

    if (callLiar == false)
    {
        cout << "Player " << player + 1 << " believes player " << player << "'s guess." << endl << endl;
    }
    else if (callLiar == true)
    {
        cout << "Player " << player + 1 << " says player " << player << "'s a liar!" << endl << endl;
        ShowEndDice();
        endGame = true;
        
    }
    

    /*for (int j = 0; j < 6 * numPlayers; j++)
    {
        cout << diceCount[j] << endl;
    }
    */
    //Testing for array to fill with numbers.

    //making a guess based on hand
    for (int i = 0; i <= 6; i++)
    {
        if (diceCount[i] > maxNum)
        {
            maxNum = diceCount[i];
            maxFace = i;
        }
    }
    if (maxNum > amountPrev)
    {
        guessAmount = amountPrev + (rand() % (amountPrev - (maxNum + 1)));
        guessFace = maxFace;
    }
    else // if its over the number in the comps hand then a random guess will be made
    {
        if (guessAmount < maxDice)
        {
            guessAmount = (rand() % 3 + 1) + amountPrev;
            guessFace = rand() % 6 + 1;
        }
        else
        {
            guessAmount = amountPrev;
            if (guessFace == 6) 
            {
                guessFace = guessFace - (rand() % 5 + 1);
            }
            else if (guessFace == 1)
            {
                guessFace = guessFace + (rand() % 5 + 1);
            }
            else 
            {
                guessFace = rand() % 6 + 1;
            }            
        }        
    }
    /*guessAmount = rand() % (numPlayers * 5) + amountPrev;
    guessFace = rand() % 6 + 1;*/ //old code

    amountPrev = guessAmount;
    facePrev = guessFace;
    
    if (callLiar == false)
    {
        cout << "Player " << player + 1 << " guesses " << guessAmount << " " << guessFace << "'s" << endl << endl;
    }
    
    
}


void ShowEndDice()
{
    int ones = 0, twos = 0, threes = 0, fours = 0, fives = 0, sixes = 0;

    for (int a = 0; a < 5 * numPlayers; a++) // count up all total dice played.
    {
        switch (dice[a]) //check each die face and add them into their ints.
        {
        case 1:
            ones++;
            break;
        case 2:
            twos++;
            break;
        case 3:
            threes++;
            break;
        case 4:
            fours++;
            break;
        case 5:
            fives++;
            break;
        case 6:
            sixes++;
            break;
        default:
            break;
        }
    }

    //win condition
    if (facePrev == 1 && amountPrev >= ones)//check the face and if the value was over on the guess 
    {
        cout << "Player " << currentPlayer + 1 << " Wins! "<< endl << endl;
    }
    else if (facePrev == 2 && amountPrev >= twos)
    {
        cout << "Player " << currentPlayer + 1 << " Wins" << endl << endl;
    }
    else if (facePrev == 3 && amountPrev >= threes)
    {
        cout << "Player " << currentPlayer + 1 << " Wins" << endl << endl;
    }
    else if (facePrev == 4 && amountPrev >= fours)
    {
        cout << "Player " << currentPlayer + 1 << " Wins" << endl << endl;
    }
    else if (facePrev == 5 && amountPrev >= fives)
    {
        cout << "Player " << currentPlayer + 1 << " Wins" << endl << endl;
    }
    else if (facePrev == 6 && amountPrev >= sixes)
    {
        cout << "Player " << currentPlayer + 1 << " Wins" << endl << endl;
    }
    else
    {
        cout << "Player " << currentPlayer << " Wins, Player 1 Loses" << endl << endl;
    }
    
    //end prints\/
    cout << "Total dice" << endl;
    for (int i = 0; i < numPlayers; i++) //grabs the player to be assigned dice.
    {
        cout << "Player " << i + 1 << "'s hand: "; //prints out each players hand
        for (int j = 0; j < 5; j++)
        {
            cout << dice[j + (i * 5)] << ", ";
        }
        cout << endl;        
    }   
    
    cout << endl;
    cout << "There were: " << endl; // Prints out a list of how many of each die there was
    cout << ones << ": Ones" << endl;
    cout << twos << ": Twos" << endl;
    cout << threes << ": Threes" << endl;
    cout << fours << ": Fours" << endl;
    cout << fives << ": Fives" << endl;
    cout << sixes << ": Sixes" << endl;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
