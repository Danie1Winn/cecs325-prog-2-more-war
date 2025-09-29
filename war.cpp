// Name: Daniel Winn
// Class (CECS 325-02)
// Project Name (Prog 2 - More WAR)
// Due Date (09/18/2025)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector> // New import required for vectors

using namespace std; // Allows for shortcuts

// Card Class (from card.h and card.cpp)
class Card {
public:
    // Constructor to create a card with a specific rank and suit
    Card(char r, char s) {
        rank = r;
        suit = s;
    }

    // Default constructor needed for array creation
    Card() {
        // Initializes a card with no assigned rank or suit. Left empty; Deck will create the actual cards.
    }

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
            case 'A':
            return 1;
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
                myDeck.push_back(Card(ranks[r], suits[s]));
            }
        }
    }

    // Deals a single card from the top of the deck
    Card deal() {
        Card dealtCard = myDeck[topCard];
        topCard++;
        return dealtCard;
    }

    // Displays all 52 cards in the deck
    void display() {
        for (int i=0; i<52; i++) {
            myDeck[i].display();
            cout << ",";

            if ((i+1)%13==0) {
                cout << endl;
            }
        }
    }

    // Shuffles the cards in the deck
    void shuffle() {
        topCard = 0;

        for (int i=51; i>0; i--) {
            int j = rand() % (i+1);

            Card temp = myDeck[i];
            myDeck[i] = myDeck[j];
            myDeck[j] = temp;
        }
    }

private:
    Card myDeck[52];
    int topCard;
};

// Main Function (from war.cpp)
int main () {
    srand(time(0));

    string playerOne, playerTwo;
    int playerOneWins = 0;
    int playerTwoWins = 0;
    int ties = 0;

    cout << "Enter the name of the first player: ";
    cin >> playerOne;
    cout << "Enter the name of the second player: ";
    cin >> playerTwo;
    cout << endl;

    Deck gameDeck;

    cout << "Original Deck" << endl;
    gameDeck.display();
    cout << endl;

    gameDeck.shuffle();
    cout << "Shuffled Deck" << endl;
    gameDeck.display();
    cout << endl;

    for (int i=0; i<26; i++) {
        cout << "Game " << (i+1) << endl;
        cout << "____________________\n" << endl;

        Card p1Card = gameDeck.deal();
        Card p2Card = gameDeck.deal();

        cout << "\t" << playerOne << " - ";
        p1Card.display();
        cout << endl;

        cout << "\t" << playerTwo << " - ";
        p2Card.display();
        cout << endl;

        int result = p1Card.compare(p2Card);

        if (result==1) {
            cout << playerOne << " - Winner" << endl;
            playerOneWins++;
        }
        else if (result==-1) {
            cout << playerTwo << " - Winner" << endl;
            playerTwoWins++;
        }
        else {
            cout << "Tie game" << endl;
            ties++;
        }
        std::cout << std::endl;
    }


    cout << "Final Scores" << endl;
    cout << "______________________________\n" << endl;
    cout << "\t" << playerOne << "\t vs. \t" << playerTwo << endl;
    cout << "Wins\t" << playerOneWins <<  "\t\t" << playerTwoWins << endl;
    cout << "Losses\t" << playerTwoWins << "\t\t" << playerOneWins << endl;
    cout << "Ties\t" << ties << "\t\t" << ties << endl;

    return 0;
}