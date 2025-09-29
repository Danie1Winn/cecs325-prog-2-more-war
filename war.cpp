// Name: Daniel Winn
// Class (CECS 325-02)
// Project Name (Prog 2 - More WAR)
// Due Date (09/30/2025)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector> // New import needed for std::vector
#include <stdexcept> // New import needed for std::runtime_error

using namespace std; // Allows for shortcuts

// Player struct used to store player name and stats
struct Player {
    string name;
    int win = 0;
    int lose = 0;
    int tie = 0;
};

// Card Class (from card.h and card.cpp)
class Card {
public:
    // Constructor to create a card with a specific rank and suit
    Card(char r, char s) {
        rank = r;
        suit = s;
    }

    /* Removed the default Card() constructor, as it is not needed for the vector implementation
     *Card() {
     *   // Initializes a card with no assigned rank or suit. Left empty; Deck will create the actual cards.
     *}
     */

    // Displays the card to the console
    void display() {
        if (rank == 'T') {
            cout << "10" << suit;
        }
        else {
            cout << rank << suit;
        }
    }

    // Compares this card's rank to another card's rank
    int compare(Card otherCard) {
        int myValue = this -> getValue();
        int otherValue = otherCard.getValue();

        if (myValue > otherValue) {
            return 1; // myValue wins
        }
        else if (myValue < otherValue) {
            return -1; // otherValue wins
        }
        else {
            return 0; // Tie
        }
    }

private:
    char rank;
    char suit;

    // Gets the numerical value of the card's rank for comparison
    int getValue() {
        switch (rank) {
            case 'A':
            return 14;
            case 'K':
            return 13;
            case 'Q':
            return 12;
            case 'J':
            return 11;
            case 'T':
            return 10;
            case '9':
            return 9;
            case '8':
            return 8;
            case '7':
            return 7;
            case '6':
            return 6;
            case '5':
            return 5;
            case '4':
            return 4;
            case '3':
            return 3;
            case '2':
            return 2;
            default:
            return 0;
        }
    }
};

// Deck Class (from deck.h and deck.cpp)
class Deck{
public:
    // Constructor that creates a standard 52-card deck
    Deck() {
        char suits [] = {'C', 'S', 'D', 'H'}; // Clubs, spades, diamonds, hearts
        char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        //topCard = 0;
        //int cardIndex = 0;

        for (int s=0; s<4; s++) {
            for (int r=0; r < 13; r++) {
                //myDeck[cardIndex] = Card(ranks[r], suits[s]);
                //cardIndex++;
                // Changed constructor to push new Card objects to the end of the vector.
                myDeck.push_back(Card(ranks[r], suits[s]));
            }
        }
    }

    // New isEmpty() method that returns if the deck is empty
    bool isEmpty() {
        return myDeck.empty();
    }

    // Deals a single card from the top of the deck
    Card deal() {
        // New if statement, checks if the deck is empty and raises an exception if so.
        if (isEmpty()) {
            throw std::runtime_error("Error - Deck is empty");
        }
        //Card dealtCard = myDeck[topCard];
        // Changed to retrieve the card from the end of the vector.
        Card dealtCard = myDeck.back();
        //topCard++;
        // Removes the final card in the vector.
        myDeck.pop_back();
        return dealtCard;
    }

    // Displays all 52 cards in the deck
    void display() {
        // Now usees the vector's size to display the deck
        for (int i=0; myDeck.size(); i++) {
            myDeck[i].display();
            cout << ",";

            if ((i+1)%13==0) {
                cout << endl;
            }
        }
    }

    // Shuffles the cards in the deck
    void shuffle() {
        //topCard = 0;
        // Now uses the vector's size to shuffle
        for (int i = myDeck.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);

            Card temp = myDeck[i];
            myDeck[i] = myDeck[j];
            myDeck[j] = temp;
        }
    }

private:
    //Card myDeck[52];
    //int topCard;
    // Changed the deck to be a vector of Card objects rather than an array.
    vector<Card> myDeck;
};

// Main Function (from war.cpp)
int main () {
    srand(time(0));

    //string playerOne, playerTwo;
    //int playerOneWins = 0;
    //int playerTwoWins = 0;
    //int ties = 0;
    // Changed individually stored player string and int variables to be stored within Player structs
    Player playerOne;
    Player playerTwo;
    // int to store the number of games the user chooses to play
    int gamesToPlay;

    cout << "Enter the name of the first player: ";
    cin >> playerOne.name;
    cout << "Enter the name of the second player: ";
    cin >> playerTwo.name;
    cout << endl;

    // Prompts the user to retrieve the number of games they want to play.
    cout << "How many games will they play?: ";
    cin >> gamesToPlay;
    cout << endl;

    Deck gameDeck;

    cout << "Original Deck" << endl;
    gameDeck.display();
    cout << endl;

    gameDeck.shuffle();
    cout << "Shuffled Deck" << endl;
    gameDeck.display();
    cout << endl;

    try {
        // Loop runs for the number of games the user entered
        for (int i=0; i < gamesToPlay; i++) {
            cout << "Game " << (i+1) << endl;
            cout << "____________________\n" << endl;

            Card p1Card = gameDeck.deal();
            Card p2Card = gameDeck.deal();

            cout << "\t" << playerOne.name << " - ";
            p1Card.display();
            cout << endl;

            cout << "\t" << playerTwo.name << " - ";
            p2Card.display();
            cout << endl;

            int result = p1Card.compare(p2Card);

            if (result==1) {
                cout << playerOne.name << " - Winner" << endl;
                playerOne.win++;
                playerTwo.lose++;
            }
            else if (result==-1) {
                cout << playerTwo.name << " - Winner" << endl;
                playerTwo.win++;
                playerOne.lose++;
            }
            else {
                cout << "Tie game" << endl;
                playerOne.tie++;
                playerTwo.tie++;
            }
            cout << endl;
        }
    }
    // Catch block if the above try throws a runetime_error
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    cout << "Final Scores" << endl;
    cout << "______________________________\n" << endl;
    cout << "\t" << playerOne.name << "\t vs. \t" << playerTwo.name << endl;
    cout << "Wins\t" << playerOne.win <<  "\t\t" << playerTwo.win << endl;
    cout << "Losses\t" << playerOne.lose << "\t\t" << playerTwo.lose << endl;
    cout << "Ties\t" << playerOne.tie << "\t\t" << playerTwo.tie << endl;

    return 0;
}