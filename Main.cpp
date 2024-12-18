/****************************************************************************
 * Project:   CS225_Casino_Project
 * Author:    Connor Shackleford and Joseph Neubert
 * Purpose:   Project that simulates a casino and allows for multiple games and betting on fake money.
 * Version:   1.0 Nov 13, 2024
 * Resources: W3 School and StackOverflow for research
 *******************************************************************************/

 // Import libraries and header files
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "User.h"
#include "Player.h"
using namespace std;

// Function prototypes for each casino game
void playBlackJack(Deck& deck, User& User);
void playRoulette(User& User);
void playSlots(User& User);

// Main
int main() {
    srand(time(0));
    Deck cardDeck;
    User user("Placeholder");

    // To create or scan in the user profile, their name, and their balance
    bool playCondition = true;
    bool userDownloaded = false;
    bool userDownloadedFromFile = false;
    int flag1 = 0;
    while (!userDownloaded) {
        cout << "Welcome to the casino! If you are a returning player, please type '1'. If you're new, type '2'." << endl;
        cin >> flag1;

        if (flag1 == 1) {
            bool userFound = false;
            string inputName;
            while (!userFound) {
                cout << "Type the name of your saved user. Type '1' to create a new user." << endl;
                cin >> inputName;
                if (inputName == "1") {
                    cout << "What would you like your name to be?" << endl;
                    cin >> inputName;
                    user.changeUserName(inputName, "savedData.txt");
                    userFound = true;
                    userDownloaded = true;
                    break;
                }
                userFound = user.getUserInfo("savedData.txt", inputName);
                userDownloaded = userFound;
                userDownloadedFromFile = true;
            }
        }
        else if (flag1 == 2) {
            string inputName;
            cout << "What would you like your name to be?" << endl;
            cin >> inputName;
            user.changeUserName(inputName, "savedData.txt");
            break;
        }
        else {
            cout << "That was an invalid option. Please try again." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }

    // To create a "main menu" for the casino to select options/games
    int flag2 = 0;
    while (playCondition) {
        cout << "You are now in the casino's lobby. Type '1' to play blackjack, type '2' to play roulette, type '3' to play the slot machine, type 4 to check your current balance, type 5 to exit the casino." << endl;
        cin >> flag2;
        if (user.getBalance() < 5) {
            cout << "You have no Money. Exiting Casino." << endl;
            playCondition = false;
        }
        if (user.gamesPlayed > 10 && user.gamesWon / user.gamesPlayed > .8) {
            cout << "You have been banned for cheating. Two men in suits just tossed you into the gutter" << endl;
            playCondition = false;
        }
        if (flag2 == 1) {
            playBlackJack(cardDeck, user);
        }
        else if (flag2 == 2) {
            playRoulette(user);
        }
        else if (flag2 == 3) {
            playSlots(user);
        }
        else if (flag2 == 4) {
            cout << "Your balance is " << user.getBalance() << "." << endl;
        }
        else if (flag2 == 5) {
            playCondition = false;
        }

        else {
            cout << "That was an invalid option. Please try again." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        
    }

    // To save user data once the user exits the casino program
    string saveData;
    cout << "To save your information for next time, type 'Save'. Otherwise, your data will be lost." << endl;
    cin >> saveData;
    if (saveData == "Save" || saveData == "save") {
        user.saveUserInfo("savedData.txt", userDownloadedFromFile);
        cout << "Data saved. Come back soon!" << endl;
    }
    else {
        cout << "Data lost. Come back soon!" << endl;
    }
    return 0;
}

// Function in order to play Blackjack
void playBlackJack(Deck& deck, User& User) {
    cout << "BLACKJACK" << endl;
    string decision;
    int bet;
    bool Playing = true;
    Player Dealer(10000000);
    int playerSum;
    int dealerSum;

    while (Playing) {
        playerSum = 0;
        dealerSum = 0;
        if (User.getBalance() < 5) {
            cout << "You have no Money. Exiting Casino." << endl;
            Playing = false;
            break;
        }
        deck.shuffleDeck();
        User.clearHand();
        Dealer.clearHand();

        while (true) {
            cout << "How much will you bet? There is a $10 minimum." << endl;
            cin >> bet;
            if (!cin || bet > User.getBalance() || bet < 10) {
                cout << "The bet is invalid. Try again." << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else {
                break;
            }
        }
        ++User.gamesPlayed;

        User.receiveCard(deck, deck.index);
        Dealer.receiveCard(deck, deck.index);
        User.receiveCard(deck, deck.index);
        Dealer.receiveCard(deck, deck.index);

        cout << "You receive:\n";
        for (int i = 0; i < User.getHandSize(); ++i) {
            cout << User.getCard(i) << endl;
        }

        playerSum = User.calculateHandValue();
        cout << "Your hand value: " << playerSum << endl;

        cout << "Dealer shows: " << Dealer.getCard(0) << endl;


        bool playerTurn = true;
        while (playerTurn) {
            cout << "Hit or Stay? ";
            cin >> decision;

            if (decision == "Hit" || decision == "hit") {
                User.receiveCard(deck, deck.index);
                cout << "You receive: " << User.getCard(User.getHandSize() - 1) << endl;

                playerSum = User.calculateHandValue();
                cout << "Your hand value: " << playerSum << endl;

                if (playerSum > 21) {
                    cout << "Bust! You lose." << endl;
                    playerTurn = false;
                    Playing = false;
                    User.modifyBalance(bet, 2);
                }
                if (playerSum == 21) {
                    Playing = false;
                    playerTurn = false;
                    cout << "You Win!" << endl;
                    User.modifyBalance(bet, 1);
                    ++User.gamesWon;
                }
            }
            else if (decision == "Stay" || decision == "stay") {
                playerTurn = false;
            }
            else {
                cout << "Invalid input. Please enter 'Hit' or 'Stay'." << endl;
            }
        }

        if (playerSum <= 21) {
            dealerSum = Dealer.calculateHandValue();
            cout << "Dealer's hand: ";
            for (int i = 0; i < Dealer.getHandSize(); ++i) {
                cout << Dealer.getCard(i) << " ";
            }
            cout << "\nDealer's hand value: " << dealerSum << endl;

            while (dealerSum < 17) {
                cout << "Dealer hits." << endl;
                Dealer.receiveCard(deck, deck.index);
                dealerSum = Dealer.calculateHandValue();

                cout << "Dealer's hand value: " << dealerSum << endl;
                if (dealerSum > 21) {
                    cout << "Dealer busts! You win!" << endl;
                    Playing = false;
                    User.modifyBalance(bet, 1);
                    ++User.gamesWon;
                }
            }

            if (dealerSum <= 21 && playerSum <= 21) {
                if (playerSum > dealerSum) {
                    cout << "You win!" << endl;
                    User.modifyBalance(bet, 1);
                    ++User.gamesWon;
                }
                else if (playerSum < dealerSum) {
                    cout << "Dealer wins!" << endl;
                    User.modifyBalance(bet, 2);
                }
                else {
                    cout << "It's a tie!" << endl;
                }
            }
        }

        cout << "New balance is " << User.getBalance() << "." << endl;
        if (User.getBalance() < 5) {
            cout << "You have no Money. Exiting Casino." << endl;
            Playing = false;
        }
        cout << "Do you want to play again? (yes or no) ";
        string replay;
        cin >> replay;
        if (replay == "yes" || replay == "Yes") {
            Playing = true;
        }
        else {
            Playing = false;
        }
    }
}

// Function in order to play on the roulette wheel
void playRoulette(User& User) {
    cout << "ROULETTE" << endl;
    int bet;
    bool playing = true;
    int rouletteNumber;
    int betType;

    while (playing) {
        if (User.getBalance() < 5) {
            cout << "You have no Money. Exiting Casino." << endl;
            playing = false;
        }
        while (true) {
            cout << "How much will you bet? There is a $5 minimum." << endl;
            cin >> bet;
            if (!cin || bet > User.getBalance() || bet < 5) {
                cout << "The bet is invalid. Try again." << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else {
                break;
            }
        }
        ++User.gamesPlayed;
        cout << "What are you betting on for roulette? Type '1' to bet on a single number, type '2' to bet on even or odd, type '3' to bet on a dozen numbers, or type '4' to bet on 1-18 / 19-36." << endl;
        cin >> betType;
        if (betType == 1) {
            int betType1;
            while (true) {
                cout << "What number do you want to bet on?" << endl;
                cin >> betType1;
                if (betType1 > 36 || betType < 0 || !cin) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "The number you select must be between 0 to 36. Please alter your number." << endl;
                }
                else {
                    break;
                }
            }

            cout << "You selected " << betType1 << ". The roulette wheel now spins..." << endl;
            rouletteNumber = rand() % 37;
            cout << "The roulette wheel has hit " << rouletteNumber << "." << endl;
            if (rouletteNumber == betType1) {
                cout << "You win! You will receive a 35:1 payout!" << endl;
                User.modifyBalance(bet * 36, 1);
                cout << "New balance is " << User.getBalance() << "." << endl;
                ++User.gamesWon;
            }
            else {
                cout << "You lose!" << endl;
                User.modifyBalance(bet, 2);
                cout << "New balance is " << User.getBalance() << "." << endl;
            }
        }

        else if (betType == 2) {
            string betType2;
            bool isEven;
            while (true) {
                cout << "Type 'even' or 'odd' to make your bet." << endl;
                cin >> betType2;
                if (betType2 == "even" || betType2 == "Even") {
                    isEven = true;
                    break;
                }
                else if (betType2 == "odd" || betType2 == "Odd") {
                    isEven = false;
                    break;
                }
                else {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "That was an invalid option. Please try again." << endl;
                }
            }

            cout << "You selected " << betType2 << ". The roulette wheel now spins..." << endl;
            rouletteNumber = rand() % 37;
            cout << "The roulette wheel has hit " << rouletteNumber << "." << endl;
            int rouletteNumberIsEven = rouletteNumber % 2;
            if (rouletteNumber == 0) {
                cout << "You lose!" << endl;
                User.modifyBalance(bet, 2);
                cout << "New balance is " << User.getBalance() << "." << endl;
            }
            else if (isEven && rouletteNumberIsEven == 0) {
                cout << "You win! You will receive a 1:1 payout!" << endl;
                User.modifyBalance(bet, 1);
                cout << "New balance is " << User.getBalance() << "." << endl;
                ++User.gamesWon;
            }
            else if (!isEven && rouletteNumberIsEven == 1) {
                cout << "You win! You will receive a 1:1 payout!" << endl;
                User.modifyBalance(bet, 1);
                cout << "New balance is " << User.getBalance() << "." << endl;
                ++User.gamesWon;
            }
            else {
                cout << "You lose!" << endl;
                User.modifyBalance(bet, 2);
                cout << "New balance is " << User.getBalance() << "." << endl;
            }
        }

        else if (betType == 3) {
            int betType3;
            string betType3String;
            while (true) {
                cout << "Type '1' to bet on 1-12, type '2' to bet on 13-24, or type '3' to bet on 25-36." << endl;
                cin >> betType3;
                if (betType3 == 1) {
                    betType3String = "1-12";
                    break;
                }
                else if (betType3 == 2) {
                    betType3String = "13-24";
                    break;
                }
                else if (betType3 == 3) {
                    betType3String = "25-36";
                    break;
                }
                else {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "That was an invalid option. Please try again." << endl;
                }
            }

            cout << "You selected " << betType3String << ". The roulette wheel now spins..." << endl;
            rouletteNumber = rand() % 37;
            cout << "The roulette wheel has hit " << rouletteNumber << "." << endl;
            if (betType3 == 1 && (rouletteNumber >= 1 && rouletteNumber <= 12)) {
                cout << "You win! You will receive a 2:1 payout!" << endl;
                User.modifyBalance(bet * 2, 1);
                cout << "New balance is " << User.getBalance() << "." << endl;
                ++User.gamesWon;
            }
            else if (betType3 == 2 && (rouletteNumber >= 13 && rouletteNumber <= 24)) {
                cout << "You win! You will receive a 2:1 payout!" << endl;
                User.modifyBalance(bet * 2, 1);
                cout << "New balance is " << User.getBalance() << "." << endl;
                ++User.gamesWon;
            }
            else if (betType3 == 3 && (rouletteNumber >= 25 && rouletteNumber <= 36)) {
                cout << "You win! You will receive a 2:1 payout!" << endl;
                User.modifyBalance(bet * 2, 1);
                cout << "New balance is " << User.getBalance() << "." << endl;
                ++User.gamesWon;
            }
            else {
                cout << "You lose!" << endl;
                User.modifyBalance(bet, 2);
                cout << "New balance is " << User.getBalance() << "." << endl;
            }
        }

        else if (betType == 4) {
            int betType4;
            string betType4String;
            while (true) {
                cout << "Type '1' to bet on 1-18, or type '2' to bet on 19-36." << endl;
                cin >> betType4;
                if (betType4 == 1) {
                    betType4String = "1-18";
                    break;
                }
                else if (betType4 == 2) {
                    betType4String = "19-36";
                    break;
                }
                else {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "That was an invalid option. Please try again." << endl;
                }
            }

            cout << "You selected " << betType4String << ". The roulette wheel now spins..." << endl;
            rouletteNumber = rand() % 37;
            cout << "The roulette wheel has hit " << rouletteNumber << "." << endl;
            if (betType4 == 1 && (rouletteNumber >= 1 && rouletteNumber <= 18)) {
                cout << "You win! You will receive a 1:1 payout!" << endl;
                User.modifyBalance(bet, 1);
                cout << "New balance is " << User.getBalance() << "." << endl;
                ++User.gamesWon;
            }
            else if (betType4 == 2 && (rouletteNumber >= 19 && rouletteNumber <= 36)) {
                cout << "You win! You will receive a 1:1 payout!" << endl;
                User.modifyBalance(bet, 1);
                cout << "New balance is " << User.getBalance() << "." << endl;
                ++User.gamesWon;
            }
            else {
                cout << "You lose!" << endl;
                User.modifyBalance(bet, 2);
                cout << "New balance is " << User.getBalance() << "." << endl;
            }
        }

        else {
            cout << "That was an invalid option. Please try again." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        if (User.getBalance() < 5) {
            cout << "You have no Money. Exiting Casino." << endl;
            playing = false;
        }
        cout << "Do you want to play again? (yes or no) ";
        string replay;
        cin >> replay;
        if (replay == "yes" || replay == "Yes") {
            playing = true;
        }
        else {
            playing = false;
        }
    }
}

// Function to use a slot machine
void playSlots(User& User) {
    cout << "SLOT MACHINE" << endl;
    string slotMachineSymbols[4] = { "Cherry", "Apple", "Watermelon", "7" };
    bool playing = true;
    int bet;

    while (playing) {
        if (User.getBalance() < 5) {
            cout << "You have no Money. Exiting Casino." << endl;
            playing = false;
        }
        ++User.gamesPlayed;
        while (true) {
            cout << "How much will you bet? Once you enter the quantity, you will hit the machine's lever. There is no minimum." << endl;
            cin >> bet;
            if (!cin || bet > User.getBalance() || bet <= 0) {
                cout << "The bet is invalid. Try again." << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else {
                break;
            }
        }

        int slot1 = rand() % 4;
        int slot2 = rand() % 4;
        int slot3 = rand() % 4;
        cout << slotMachineSymbols[slot1] << " " << slotMachineSymbols[slot2] << " " << slotMachineSymbols[slot3] << endl;

        if (slot1 == 3 && slot2 == 3 && slot3 == 3) {
            cout << "You got three lucky numbers in a row! You will receive a 7:1 payout!" << endl;
            User.modifyBalance(bet * 8, 1);
            cout << "New balance is " << User.getBalance() << "." << endl;
            ++User.gamesWon;
        }
        else if (slot1 == slot2 && slot2 == slot3) {
            cout << "You got three objects in a row! You will receive a 2:1 payout!" << endl;
            User.modifyBalance(bet * 2, 1);
            cout << "New balance is " << User.getBalance() << "." << endl;
            ++User.gamesWon;
        }
        else {
            cout << "Too bad! You don't win anything." << endl;
            User.modifyBalance(bet, 2);
            cout << "New balance is " << User.getBalance() << "." << endl;
        }

        cout << "Do you want to play again? (yes or no) ";
        string replay;
        cin >> replay;
        if (replay == "yes" || replay == "Yes") {
            playing = true;
        }
        else {
            playing = false;
        }
    }
}
