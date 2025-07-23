/*
AUTHORS: Ermish Tabassum
       Hanzala Ahsan

PROJECT: UNO (for 2 players)
*/

//============Libraries==========
#include <conio.h>   //for getch();
#include <cstdlib>   //random function
#include <cstdlib>   // for clearing screen
#include <ctime>     //time seed
#include <fstream>   //for filing
#include <iomanip>   //setw
#include <iostream>  //for cin, cout
#include <windows.h> // for colors
using namespace std;

//=================Ermish Funtions' prototypes===================
void initializedeck(int deck[8][15]);
void dealcards(int cards[8][15], int p1[108], int p2[108], int topcard);
void handleSpecialCard(int specialCardType);
void print_board(int topcard, int p1[108], int p2[108]);
void saveLoadGameResult(int gameNumber, int playing, int& count1, int& count2);

//=================Hanzala Funtions' prototypes==================
void shuffledeck(int deck[8][15]);
bool isvalidplay(int playercard, int topcard);
void playturn(int playing, int p1[108], int p2[108], int playercard,
              int topcard, int deck[8][15], int discardpile[108]);
void updateDiscardPile(int deck[8][15], int discardpile[108], int topcard,
                       int& again);
bool callUno(int p1[108], int p2[108], int playing);

//================Extra supporting Functions=====================
void wild4(int p[108], int deck[8][15]);
void penalty(int p[108], int deck[8][15]);
void setColor(int textColor, int bgColor);
void clearScreen();
void print_hand(int p1[108]);
void print_cards(int topcard);

int global = 0;
int global2 = 0;
int colour = 0;
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;

//========================Main Function==========================
int main() {
    // variable declaration
    char yes;
    int player1[108];
    int player2[108];
    int cards[8][15];
    char play;
    int rewind = 1;
    int gamenumber = 0;
    int count1, count2;
    int playing;
    int discardpile[108];
    // Assigning a value to the discard pile
    for (int i = 0; i < 108; i++) {
        discardpile[i] = -99;
    }

    // printing commands
    setColor(RED, CYAN);
    cout << setw(115) << "       WELCOME TO THE AMAZING GAME OF UNO\n\n";
    setColor(BLUE, GREEN);
    while (rewind == 1) {
        cout << setw(100) << "MAIN MENU\n";
        setColor(WHITE, RED);
        cout << "\n\n\n"
             << setw(100) << " P. PLAY UNO!\n\n"
             << setw(106) << "S. VIEW SCOREBOARD\n\n"
             << setw(94) << "E. EXIT\n";
        setColor(WHITE, BLACK);
        cin >> play;

        // Switch cases to check either user wants to play, exit or view score
        // board.
        switch (play) {
        case 'p':
        case 'P': {
            cout << "Game Instructions: \n1. enter 'c' to throw a card and "
                    "then enter the respective card number \n2. enter 'd' to "
                    "draw a card. \n3. enter 'u' on 2nd last card to call uno "
                 << endl;
            gamenumber++;
            setColor(WHITE, BLACK);
            initializedeck(cards);
            cout << "\n\n";
            srand(time(0));
            int temp;
            shuffledeck(cards);
            int topcard = cards[0][14];
            for (int i = 6; i >= 1; i--)
                for (int j = 14; j >= 0; j--) {
                    if ((topcard > 100 && topcard <= 104) ||
                        (topcard > 104 && topcard <= 108) ||
                        (topcard > 19 && topcard <= 21) ||
                        (topcard > 44 && topcard <= 46) ||
                        (topcard > 69 && topcard <= 71) ||
                        (topcard > 94 && topcard <= 96) ||
                        (topcard > 21 && topcard <= 23) ||
                        (topcard > 46 && topcard <= 48) ||
                        (topcard > 71 && topcard <= 73) ||
                        (topcard > 96 && topcard <= 98) ||
                        (topcard > 23 && topcard <= 25) ||
                        (topcard > 48 && topcard <= 50) ||
                        (topcard > 73 && topcard <= 75) ||
                        (topcard > 98 && topcard <= 100)) {
                        temp = cards[0][14];
                        cards[0][14] = cards[i][j];
                        cards[i][j] = temp;
                        topcard = cards[0][14];
                        cards[0][14] = -55;
                    }
                    cards[0][14] = -55;
                }
            // Proceed to deal cards
            for (int i = 7; i < 108; i++) {
                player1[i] = -1;
                player2[i] = -1;
            }

            dealcards(cards, player1, player2, topcard);
            int playercard = 0;
            playing = rand() % 2 + 1;
            cout << " The player with the first turn is : " << playing << endl;
            playturn(playing, player1, player2, playercard, topcard, cards,
                     discardpile);
            // clear screen
            setColor(WHITE, BLACK);
            break;
        }

        case 's':
        case 'S': {
            saveLoadGameResult(gamenumber, playing, count1, count2);
            break;
        }

        case 'e':
        case 'E': {
            while (true) {
                cout << " DO YOU REALLY WANT TO EXIT ? \n (Y\\N): ";
                cin >> yes;
                if (yes == 'y' || yes == 'Y') {
                    rewind = 2;
                    break; // break inner loop, exit main loop
                } else if (yes == 'n' || yes == 'N') {
                    // wapas menu par le jao
                    break; // break inner loop, continue main loop
                } else {
                    cout << "Invalid input. Please enter Y or N.\n";
                }
            }
            break; // break switch
        }
        default: {
            cout << "INVALID INPUT. TRY AGAIN\n";
            break;
        }
        }
    }

    return 0;
}

//====================Ermish Funtions============================
void initializedeck(int deck[8][15]) {
    // loop for 8 orws and 15 columns and values are assigned
    int value = 1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 15; j++) {
            deck[i][j] = value++;
            if (value >= 110)
                deck[i][j] =
                    -2; // for the cards greater than 110 they have -2 value
        }
    }
}

void dealcards(int cards[8][15], int p1[108], int p2[108], int topcard) {
    // assigning -55 value to cards who are dealed to players
    for (int i = 0; i < 7; i++) {
        p1[i] = cards[0][i];
        cards[0][i] = -55;
    }
    for (int i = 0; i < 7; i++) {
        p2[i] = cards[0][i + 7];
        cards[0][i + 7] = -55;
    }

    int entry = 7;
    p1[entry] = -1;
    p2[entry] = -1;
    setColor(GREEN, BLACK); // Set green text with black background
    cout << "This is Player 1 deck." << endl;
    setColor(WHITE, BLACK); // Reset to default

    // Printing card numbers
    cout << "Card number:-\n";
    cout << setw(5) << " ";
    for (int i = 1; i <= 7; i++)
        cout << i << setw(10);

    cout << "\n\n";

    // DECK 1 printing
    print_hand(p1); // print player 1 deck
    cout << endl << endl;

    // PLAY AREA Printing
    setColor(GREEN, BLACK); // Set green text with black background
    cout << setw(20) << "Play cards!" << endl;
    setColor(WHITE, BLACK); // Reset to default
    print_cards(topcard);   // top card and uno deck
    cout << endl << endl;
    setColor(WHITE, BLACK); // Reset to default

    // DECK 2 printing
    setColor(GREEN, BLACK); // Set green text with black background
    cout << "This is Player 2 deck." << endl;
    setColor(WHITE, BLACK); // Reset to default
    cout << "Card number:-\n";
    cout << setw(5) << " ";
    for (int i = 1; i <= 7; i++)
        cout << i << setw(10);

    cout << "\n\n";

    // DECK 2 Printing
    print_hand(p2);         // print player 2 deck
    setColor(WHITE, BLACK); // Reset to default
}

void handleSpecialCard(int specialCardType) {

    // store the value of player card into special card type
    // skip
    // these all are the skip cards in whole deck for all 4 colours
    if (specialCardType == 21 || specialCardType == 20 ||
        specialCardType == 46 || specialCardType == 45 ||
        specialCardType == 70 || specialCardType == 71 ||
        specialCardType == 96 || specialCardType == 95) {
        global = 1;
    }

    // reverse
    // these all are the Reverse cards in whole deck for all 4 colours
    else if (specialCardType == 23 || specialCardType == 22 ||
             specialCardType == 47 || specialCardType == 48 ||
             specialCardType == 73 || specialCardType == 72 ||
             specialCardType == 97 || specialCardType == 98) {
        global = 1;
    }

    // draw2
    // these all are the draw 2 cards in whole deck for all 4 colours
    else if (specialCardType == 25 || specialCardType == 24 ||
             specialCardType == 50 || specialCardType == 49 ||
             specialCardType == 75 || specialCardType == 74 ||
             specialCardType == 100 || specialCardType == 99) {
        global = 1;
    }

    // wild colour
    // these all are the wild cards in whole deck for all 4 colours
    else if (specialCardType >= 101 && specialCardType <= 104) {
        global2 = 2;
        cout << "Kindly Enter the colour that you want!\n '1' for red\n '2' "
                "for blue\n '3' for yellow\n '4' for green"
             << endl;
        cin >> colour;
        while (colour < 1 || colour > 4) {
            cout << "Invalid Colour!" << endl;
            cout << "\nKindly Enter the colour that you want!\n '1' for red\n "
                    "'2' for blue\n '3' for yellow\n '4' for green"
                 << endl;
            cin >> colour;
        }

        // validation chck so that player does not enter wrong colour
        switch (colour) {
        case 1:
            cout << " You can only throw a red card or a wild card now: ";
            global2 = 2;
            break;
        case 2:
            cout << "You can only throw a blue card now or a wild card: ";
            global2 = 2;
            break;
        case 3:
            cout << "You can only throw a blue card now or a wild card: ";
            global2 = 2;
            break;
        case 4:
            cout << "You can only throw a blue card now or a wild card: ";
            global2 = 2;
            break;
        }
    }

    // Wild Draw 4 colour
    // these all are the wild draw 4 cards in whole deck for all 4 colours
    else if (specialCardType >= 105 && specialCardType <= 108) {
        global = 1;
        global2 = 2;
        cout << "\nKindly Enter the colour that you want!\n '1 for red\n '2' "
                "for blue\n '3' for yellow\n '4' for green"
             << endl;
        cin >> colour;
        while (colour < 1 || colour > 4) {
            cout << "Invalid Colour!" << endl;
            cout << "Kindly Enter the colour that you want!\n '1' for red\n "
                    "'2' for blue\n '3' for yellow\n '4' for green"
                 << endl;
            cin >> colour;
            switch (colour) {
            case 1:
                cout << " You can only throw a red card or a wild card now: ";
                break;
            case 2:
                cout << "You can only throw a blue card now or a wild card: ";
                break;
            case 3:
                cout << "You can only throw a blue card now or a wild card: ";
                break;
            case 4:
                cout << "You can only throw a blue card now or a wild card: ";
                break;
            }
        }
        // validation chck so that player does not enter wrong colour
        // give 4 cards to player 2 and skip its turn
    }
}

void print_board(int topcard, int p1[108], int p2[108]) {
    clearScreen();
    cout << "\n\nPlayer one's hand is \n\n";
    cout << setw(5) << " ";
    for (int i = 0; p1[i] != -1; i++)
        cout << i + 1 << setw(10);
    cout << "\n\n";
    print_hand(p1); // calling this funtion with argument p1 array to print
                    // player 1 hand

    // print top card and UNO card
    print_cards(topcard);

    cout << "\n\nPlayer two's hand is \n\n";
    cout << setw(5) << " ";
    for (int i = 0; p2[i] != -1; i++)
        cout << i + 1 << setw(10);
    cout << "\n\n";
    print_hand(p2); // calling this funtion with argument p2 array to print
                    // player 1 hand
    setColor(WHITE, BLACK); // set colour to default
}

void saveLoadGameResult(int gameNumber, int playing, int& count1, int& count2) {
    int winnerPoints = 50; // Fixed points per win
    int s1 = 0, s2 = 0;
    // individual player scoring
    if (playing == 1) {
        s1 += (winnerPoints * count1);
        count1++;
    } else if (playing == 2) {
        s2 += (winnerPoints * count2);
        count2++;
    }

    // Append game details to the file otherwise data will be rewrite
    ofstream outfile("scoreboard.txt", ios::app); // Open in append mode
    if (outfile.is_open()) {                      // Check if the file is open
        outfile << "Game: " << gameNumber << endl;
        outfile << "Winner: Player " << playing << endl;
        outfile << "Points of winner for this game: " << winnerPoints << endl;
        outfile << "Player 1 score: " << s1 << endl;
        outfile << "Player 2 score: " << s2 << endl;
        outfile << "--------------------------" << endl;
        outfile.close(); // Close the file after writing
        cout << "Game record saved successfully!\n";
    }

    // Display the scoreboard
    ifstream infile("scoreboard.txt"); // Open in read mode
    if (infile.is_open())              // Check if the file is open
    {
        string line; // variable that is use to store each line when it is beign
                     // read from the document
        cout << "\n--- Scoreboard ---\n";
        while (getline(infile, line)) // Read the file line by line
        {
            cout << line << endl;
        }
        infile.close(); // Close the file after reading
    }
}

//====================Hanzala Funtions===========================
void shuffledeck(int deck[8][15]) {
    int k, l, temp;
    // Shuffle the deck
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 15; j++) {
            l = rand() % 8;
            k = rand() % 15;
            temp = deck[i][j];
            deck[i][j] = deck[l][k];
            deck[l][k] = temp;
        }
    }

    // Rearrange the deck to move -2 entries to the end (last row)
    int tempDeck[120]; // Temporary array for all values
    int valid_index = 0, invalid_index = 119;

    // Flatten the deck into a temporary array, separating valid and -2 entries
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 15; j++) {
            if (deck[i][j] == -2) {
                tempDeck[invalid_index--] = -2; // Move -2 entries to the end
            } else {
                tempDeck[valid_index++] =
                    deck[i][j]; // Keep valid entries at the start
            }
        }
    }

    // Copy the rearranged temporary array back into the 2D deck
    valid_index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 15; j++) {
            deck[i][j] = tempDeck[valid_index++];
        }
    }

    // Though the functionlality is complete here, but as the restriction is to
    // make an array of size 108,  I will give the first 108 values to another
    // array
    int shuffledArray[108];
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 15; j++)
            shuffledArray[108];
    int index = 0;
    for (int i = 0; i < 8 && index < 108; i++)
        for (int j = 0; j < 15 && index < 108; j++)
            shuffledArray[index++] = deck[i][j];
}

bool isvalidplay(int playercard, int topcard) {
    // Checks for the Wild card and colour chosen
    if (global2 == 2 && colour == 1) {
        if ((playercard >= 1 && playercard <= 25) || playercard > 100) {
            return true;
        } else
            return false;
    }

    else if (global2 == 2 && colour == 2) {
        if ((playercard >= 26 && playercard <= 50) || playercard > 100) {
            return true;
        } else
            return false;
    }

    else if (global2 == 2 && colour == 3) {
        if ((playercard >= 51 && playercard <= 75) || playercard > 100) {
            return true;
        } else
            return false;
    }

    else if (global2 == 2 && colour == 4) {
        if ((playercard >= 76 && playercard <= 100) || playercard > 100) {
            return true;
        } else
            return false;
    }

    int dummy = 987;
    if (topcard == 1 || topcard == 26 || topcard == 51 || topcard == 76)
        dummy = 0;
    else if (topcard > 1 && topcard <= 10)
        dummy = topcard - 1;
    else if ((topcard > 10 && topcard <= 19))
        dummy = topcard - 10;
    else if (topcard == 20)
        dummy = topcard;
    else if (topcard == 21)
        dummy = topcard - 1;
    else if (topcard == 22)
        dummy = topcard;
    else if (topcard == 23)
        dummy = topcard - 1;
    else if (topcard == 24)
        dummy = topcard;
    else if (topcard == 25)
        dummy = topcard - 1;
    else if (topcard > 26 && topcard <= 35)
        dummy = topcard - 26;
    else if (topcard > 35 && topcard <= 44)
        dummy = topcard - 35;
    else if (topcard == 45)
        dummy = topcard - 25;
    else if (topcard == 46)
        dummy = topcard - 25 - 1;
    else if (topcard == 47)
        dummy = topcard - 25;
    else if (topcard == 48)
        dummy = topcard - 25 - 1;
    else if (topcard == 49)
        dummy = topcard - 25;
    else if (topcard == 50)
        dummy = topcard - 25 - 1;

    else if (topcard > 51 && topcard <= 60)
        dummy = topcard - 51;
    else if (topcard > 60 && topcard <= 69)
        dummy = topcard - 60;
    else if (topcard == 70 || topcard == 72 || topcard == 74)
        dummy = topcard - 50;
    else if (topcard == 71 || topcard == 73 || topcard == 75)
        dummy = topcard - 50 - 1;
    else if (topcard > 76 && topcard <= 85)
        dummy = topcard - 76;
    else if (topcard > 85 && topcard <= 94)
        dummy = topcard - 85;
    else if (topcard == 95 || topcard == 97 || topcard == 99)
        dummy = topcard - 75;
    else if (topcard == 96 || topcard == 98 || topcard == 100)
        dummy = topcard - 75 - 1;

    int dummy2 = 6778;
    if (playercard == 1 || playercard == 26 || playercard == 51 ||
        playercard == 76)
        dummy2 = 0;
    else if (playercard > 1 && playercard <= 10)
        dummy2 = playercard - 1;
    else if (playercard > 10 && playercard <= 19)
        dummy2 = playercard - 10;
    else if (playercard == 20)
        dummy2 = playercard;
    else if (playercard == 21)
        dummy2 = playercard - 1;
    else if (playercard == 22)
        dummy2 = playercard;
    else if (playercard == 23)
        dummy2 = playercard - 1;
    else if (playercard == 24)
        dummy2 = playercard;
    else if (playercard == 25)
        dummy2 = playercard - 1;
    else if (playercard > 26 && playercard <= 35)
        dummy2 = playercard - 26;

    else if (playercard == 45 || playercard == 47 || playercard == 49)
        dummy2 = playercard - 25;

    else if (playercard > 35 && playercard <= 44)
        dummy2 = playercard - 35;
    else if (playercard == 46 || playercard == 48 || playercard == 50)
        dummy2 = playercard - 25 - 1;

    else if (playercard > 51 && playercard <= 60)
        dummy2 = playercard - 51;
    else if (playercard > 60 && playercard <= 69)
        dummy2 = playercard - 60;
    else if (playercard == 70 || playercard == 72 || playercard == 74)
        dummy2 = playercard - 50;
    else if (playercard == 71 || playercard == 73 || playercard == 75)
        dummy2 = playercard - 50 - 1;

    else if (playercard > 76 && playercard <= 85)
        dummy2 = playercard - 76;
    else if (playercard > 85 && playercard <= 94)
        dummy2 = playercard - 85;
    else if (playercard == 95 || playercard == 97 || playercard == 99)
        dummy2 = playercard - 75;
    else if (playercard == 96 || playercard == 98 || playercard == 100)
        dummy2 = playercard - 75 - 1;

    if (playercard > 100)
        return true;
    else if ((topcard >= 1 && topcard <= 25 && playercard >= 1 &&
              playercard <= 25) ||
             (dummy2 == dummy))
        return true;
    else if ((topcard >= 26 && topcard <= 50 &&
              (playercard >= 26 && playercard <= 50)) ||
             (dummy2 == dummy))
        return true;
    else if ((topcard >= 51 && topcard <= 75 && playercard >= 51 &&
              playercard <= 75) ||
             (dummy2 == dummy))
        return true;
    else if ((topcard >= 76 && topcard <= 100 && playercard >= 75 &&
              playercard <= 100) ||
             (dummy2 == dummy))
        return true;

    return false;
}

void playturn(int playing, int p1[108], int p2[108], int playercard,
              int topcard, int deck[8][15], int discardpile[108]) {
    char yes;
    int again = 0;
    int number;
    char a;
    char draw; // for drawing a card
    int dcard; // the card drawn
    discardpile[0] = topcard;

    int rewind = 1;
    int increasearray2size = 0;
    int increasearray1size = 0;
    int term = 8;
    int entries1 = 7;
    int entries2 = 7;
    while ((playing == 1 || playing == 2) && term == 8 && p1[0] != -1 &&
           p2[0] != -1) {
        setColor(WHITE, BLACK);
        if (playing == 1) {
            int check = 0;
            cout << "Player one\n";
            // this will tell us how many cards player one has in hand
            int counter; // this will be used to access the index;
            int increasearray1size = 0;

        repeat:
            int iteration = 0;
            counter = 0;
            while (p1[iteration] != -1) {
                iteration++;
            }
            entries1 = iteration;
            cout << "Enter D to draw a card: \n For throwing a card enter C\n "
                    "\n";
            cin >> a;
            if (a == 'c' || a == 'C') {
                cout << "Enter card Number : ";
                cin >> number;
                while (number < 1 && number > entries1) {
                    cout << "Invalid input\n";
                    cout << "Throw a valid card \n";
                    cin >> number;
                }
            }

            else if (a == 'u' || a == 'U') {
                char uno = 'u';
                if ((uno == 'u' || uno == 'U') &&
                    callUno(p1, p2, playing) == true) {
                    cout << "Player " << playing << " calls UNO";
                } else
                    penalty(p1, deck);
                cout << "Select card number : ";
                cin >> number;
                while (number < 1 && number > entries2) {
                    cout << "Invalid input\n";
                    cout << "Throw a valid card, the card whose colour or "
                            "number matches the top card or throw a wild card "
                            "\n";
                    cin >> number;
                }
            }

            if (a == 'd' || a == 'D') {
                increasearray1size = 0;
                int i = 1;
                int j = 0;

            dealing:
                if (j == 15) {
                    j = 0;
                    i++;
                }

                if (deck[i][j] != -55 && deck[i][j] != -2) {
                    dcard = deck[i][j];
                    deck[i][j] = -55;
                    cout << "\n\n The drawn card is " << dcard;
                    increasearray1size++;
                    j++;
                } else {
                    j++;
                    if (i < 8)
                        goto dealing;
                }

                // Add drawn card to the player's hand array (corrected logic)
                for (int k = 0; k < 50;
                     k++) // Assuming 50 is the max size of the player's hand
                {
                    if (p1[k] == -1) // Find the first empty spot in the array
                    {
                        p1[k] = dcard;
                        break;
                    }
                }

                print_board(topcard, p1, p2);
                entries1++;
                cout << setw(25) << "PLAYER 1: ";
                for (int i = 0; i < entries1; i++) {
                    playercard = p1[i];
                    if (isvalidplay(playercard, topcard) != true) {
                        check++;
                    }
                }

                if (check == entries1) {
                    cout << "You cannot  throw a card\n";
                    playing = 2;
                }

                else {
                    cout << "Enter C to throw a card\n";
                    cin >> a;
                    if (a == 'C' || a == 'c') {
                        cout << "Enter card number : ";
                        cin >> number;

                        while (number < 1 || number > entries1) {
                            cout << "Invalid input. Try Again\n";
                            cout << "Enter a card : \n";
                            cin >> number;
                        }
                    }

                    if (a == 'u' || a == 'U') {
                        char uno = 'u';

                        if ((uno == 'u' || uno == 'U') &&
                            callUno(p1, p2, playing) == true) {
                            cout << "Player " << playing << " calls UNO";
                        } else
                            penalty(p1, deck);
                        cout << "Select card number : ";
                        cin >> number;

                        while (number < 1 && number > entries2) {
                            cout << "Invalid input\n";
                            cout << "Throw a valid card, the card whose colour "
                                    "or number matches the top card or throw a "
                                    "wild card \n";
                            cin >> number;
                        }
                    }
                }
            } else {
                cout << "Invalid input \n";
            }
            if (number >= 1 && number <= entries1 && check < entries1) {
                playercard = p1[number - 1];
                if (isvalidplay(playercard, topcard) != true) {
                    cout
                        << " INVALID CARD\nThrow either the same colour or the "
                           "same number card or wild cards(if you have any)\n";
                    goto repeat;
                }

                topcard = playercard;
                colour = 0;
                global2 = 0;
                if ((topcard > 19 && topcard <= 25) ||
                    (topcard > 44 && topcard <= 50) ||
                    (topcard > 69 && topcard <= 75) ||
                    (topcard > 94 && topcard <= 96) ||
                    (topcard > 96 && topcard <= 108)) {
                    handleSpecialCard(topcard);
                }
                if (topcard > 104 && topcard <= 108) {
                    wild4(p2, deck);
                }

                updateDiscardPile(deck, discardpile, topcard, again);

                for (int i = 0; p1[i] != -1; i++) {
                    p1[i + number - 1] = p1[i + number - 1 + 1];
                }
                cout << "Card number:-\n";
                cout << setw(5) << " ";
                for (int i = 0; p1[i] != -1; i++)
                    cout << i + 1 << setw(10);
                if (topcard == 25 || topcard == 24 || topcard == 50 ||
                    topcard == 49 || topcard == 75 || topcard == 74 ||
                    topcard == 100 || topcard == 99) {
                    penalty(p2, deck);
                }

                print_board(topcard, p1, p2);

                if (global != 1)
                    playing = 2;
                global = 0;

            } else if (a == 'e' || a == 'E') {
                cout << "Exiting current game\n";
                return;
            }
        }

        if (playing == 2) {
            int check = 0;
            setColor(WHITE, BLACK);
            cout << "Player Two's Turn\n";
        repeat2:
            int entries2 = 7;

            int iteration = 0;
            int counter = 0;
            while (p2[iteration] != -1) {

                iteration++;
            }
            entries2 = iteration;
            cout << "Enter D for Drawing a card, Enter C to throw a card "
                    "\n";
            cin >> a;

            if (a == 'c' || a == 'C') {
                cout << "Select card number : ";
                cin >> number;

                while (number < 1 && number > entries2) {
                    cout << "Invalid input\n";
                    cout << "Throw a valid card, the card whose colour or "
                            "number matches the top card or throw a wild card "
                            "\n";
                    cin >> number;
                }
            }

            if (a == 'u' || a == 'U') {

                char uno = 'u';

                if ((uno == 'u' || uno == 'U') &&
                    callUno(p1, p2, playing) == true) {

                    cout << "Player " << playing << " calls UNO";
                } else
                    penalty(p2, deck);

                cout << "Select card number : ";
                cin >> number;

                while (number < 1 && number > entries2) {
                    cout << "Invalid input\n";
                    cout << "Throw a valid card, the card whose colour or "
                            "number matches the top card or throw a wild card "
                            "\n";
                    cin >> number;
                }
            }

            if (a == 'd' || a == 'D') {

                increasearray2size = 0;
                int i = 1;
                int j = 0;

            dealing2:
                if (j == 15) {
                    j = 0;
                    i++;
                }
                if (deck[i][j] != -55 && deck[i][j] != -2) {
                    dcard = deck[i][j];
                    deck[i][j] = -55;
                    cout << "\n\n The drawn card is " << dcard;
                    increasearray2size++;
                    j++;
                } else {
                    j++;
                    if (i < 8)
                        goto dealing2;
                }

                // Add drawn card to the player's hand array
                for (int k = 0; k < 108; k++) {
                    if (p2[k] == -1) { // Find the first empty spot in the array
                        p2[k] = dcard;
                        break;
                    }
                }

                print_board(topcard, p1, p2);
                entries2++;

                cout << setw(25) << "PLAYER 2: ";
                for (int i = 0; i < entries2; i++) {
                    playercard = p2[i];
                    if (isvalidplay(playercard, topcard) != true) {
                        check++;
                    }
                }
                if (check == entries2) {

                    cout << "You cannot  throw a card\n";
                    playing = 1;
                } else {

                    cout << "Enter card Number to throw a card\n\n";
                    cin >> a;

                    if (a == 'c' || a == 'C') {
                        cout << "Select card number : ";
                        cin >> number;

                        while (number < 1 && number > entries2) {
                            cout << "Invalid input\n";
                            cout << "Throw a valid card, the card whose colour "
                                    "or number matches the top card or throw a "
                                    "wild card \n";
                            cin >> number;
                        }
                    }
                    if (a == 'u' || a == 'U') {
                        char uno = 'u';
                        if ((uno == 'u' || uno == 'U') &&
                            callUno(p1, p2, playing) == true) {

                            cout << "Player " << playing << " calls UNO";
                        } else
                            penalty(p2, deck);

                        cout << "Select card number : ";
                        cin >> number;

                        while (number < 1 && number > entries2) {
                            cout << "Invalid input\n";
                            cout << "Throw a valid card, the card whose colour "
                                    "or number matches the top card or throw a "
                                    "wild card \n";
                            cin >> number;
                        }
                    }
                }
            }

            else {
                cout << "Invalid Input";
            }

            if (number >= 1 && number <= entries2 && check < entries2) {

                playercard = p2[number - 1];
                if (isvalidplay(playercard, topcard) != true) {
                    cout
                        << " INVALID CARD\nThrow either the same colour or the "
                           "same number card or wild cards(if you have any)\n";
                    goto repeat2;
                }
                topcard = playercard;
                colour = 0;
                global2 = 0;
                if ((topcard > 19 && topcard <= 25) ||
                    (topcard > 44 && topcard <= 50) ||
                    (topcard > 69 && topcard <= 75) ||
                    (topcard > 94 && topcard <= 96) ||
                    (topcard > 96 && topcard <= 108)) {
                    handleSpecialCard(topcard);
                }

                if (topcard > 104 && topcard <= 108) {
                    wild4(p1, deck);
                }
                updateDiscardPile(deck, discardpile, topcard, again);

                for (int i = 0; p2[i] != -1; i++) {
                    p2[i + number - 1] = p2[i + number - 1 + 1];
                }

                cout << "Card number:-\n";
                cout << setw(5) << " ";
                for (int i = 0; p2[i] != -1; i++)
                    cout << i + 1 << setw(10);

                cout << "\n\n";

                if (topcard == 25 || topcard == 24 || topcard == 50 ||
                    topcard == 49 || topcard == 75 || topcard == 74 ||
                    topcard == 100 || topcard == 99) {
                    penalty(p1, deck);
                }

                print_board(topcard, p1, p2);

                setColor(WHITE, BLACK);

                if (global != 1)
                    playing = 1;
                global = 0;

            } else if (a == 'e' || a == 'E') {
                cout << "Exiting current game\n";
                return;
            }
        }
    }
    if (p1[0] == -1) {
        cout << "Congratulations! Player 1 is the winner" << endl;
    } else if (p2[0] == -1) {
        cout << "Congratulations! Player 2 is the winner" << endl;
    }
}

void updateDiscardPile(int deck[8][15], int discardpile[108], int topcard,
                       int& again) {
    int count = 0;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 15; j++) {
            if (deck[i][j] == -55 || deck[i][j] == -2)
                count++;
        }

    int i = 0;
    while (discardpile[i] != -99 && i < 108) {
        i++;
    }

    if (count == 108) {
        discardpile[0] = topcard;
        for (int j = i - 1; j > 0; --j) {
            int k = rand() % (j + 1);
            // Swaping  discardpile[j] with the value of  discardpile[k]
            int temp = discardpile[j];
            discardpile[j] = discardpile[k];
            discardpile[k] = temp;
        }
    }

    again++;
    discardpile[again] = topcard;
}

bool callUno(int p1[108], int p2[108], int playing) {
    if (playing == 1 && p1[2] == -1) {
        return true;
    } else if (playing == 2 && p2[2] == -1) {
        return true;
    } else
        return false;
}

//================Extra supporting Functions=====================
void wild4(int p[108], int deck[8][15]) {

    int iteration = 0;
    for (int i = 0; p[i] != -1; i++)
        iteration++;
    int addedcards = iteration + 4;
    int drawncard;

    for (int k = iteration; k < addedcards; k++) {
        for (int i = 1; i < 8; i++)
            for (int j = 0; j < 15; j++) {
                if (deck[i][j] != -55 && deck[i][j] != -2) {
                    drawncard = deck[i][j];
                    deck[i][j] = -55;
                    break;
                }
            }
        p[k] = drawncard;
    }
}
void penalty(int p[108], int deck[8][15]) {
    int iteration = 0;
    for (int i = 0; p[i] != -1; i++)
        iteration++;

    int d2count = iteration + 2;
    int drawncard;
    for (int k = iteration; k < d2count; k++) {

        for (int i = 1; i < 8; i++)
            for (int j = 0; j < 15; j++) {
                if (deck[i][j] != -55 && deck[i][j] != -2) {

                    drawncard = deck[i][j];
                    deck[i][j] = -55;
                    break;
                }
            }
        p[k] = drawncard;
    }
}
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void clearScreen() {
    system("CLS"); // For Windows
}
void print_hand(int p1[108]) {

    int number = 0;
    int i = 0;
    while (p1[i] != -1 && i < 108) {

        number++;
        i++;
    }
    int rows_cards = 5;
    int dummy[108];
    for (int i = 0; i <= number; i++) {
        if (p1[i] == 1 || p1[i] == 26 || p1[i] == 51 || p1[i] == 76)
            dummy[i] = 0;
        else if (p1[i] > 1 && p1[i] <= 10)
            dummy[i] = p1[i] - 1;
        else if ((p1[i] > 10 && p1[i] <= 19))
            dummy[i] = p1[i] - 10;
        else if (p1[i] > 26 && p1[i] <= 35)
            dummy[i] = p1[i] - 26;
        else if (p1[i] > 35 && p1[i] <= 44)
            dummy[i] = p1[i] - 35;
        else if (p1[i] > 51 && p1[i] <= 60)
            dummy[i] = p1[i] - 51;
        else if (p1[i] > 60 && p1[i] <= 69)
            dummy[i] = p1[i] - 60;
        else if (p1[i] > 76 && p1[i] <= 85)
            dummy[i] = p1[i] - 76;
        else if (p1[i] > 85 && p1[i] <= 94)
            dummy[i] = p1[i] - 85;
        if (i == number)
            setColor(BLACK, BLACK);
    }

    for (int row = 0; row < rows_cards;
         row++) {                        // Loop through the rows of a card
        for (int i = 0; i < number; i++) // For each card in the hand
        {
            // Set the color based on the card value
            if (p1[i] <= 25)
                setColor(BLACK, RED);
            else if (p1[i] >= 26 && p1[i] <= 50)
                setColor(BLACK, BLUE);
            else if (p1[i] >= 51 && p1[i] <= 75)
                setColor(BLACK, GREEN);
            else if (p1[i] >= 76 && p1[i] <= 100)
                setColor(BLACK, YELLOW);
            else if (p1[i] > 100 && p1[i] <= 104)
                setColor(WHITE, BLACK);
            else if (p1[i] > 104 && p1[i] <= 108)
                setColor(WHITE, BLACK);
            //             if (i==number)
            //            setColor(BLACK, BLACK);

            // Printing the rwos
            if (row == 0)
                cout << setw(10) << " -------- "; // Top row
            else if (row == 1)
                cout << setw(10) << "-       - "; // Empty line inside the card
            else if (row == 2) {
                if (p1[i] > 100 && p1[i] <= 104)
                    cout << setw(10) << "-   W   - "; // Wild card
                else if (p1[i] > 104 && p1[i] <= 108)
                    cout << setw(10) << "-  W4   - "; // Wild +4 card
                else if ((p1[i] > 19 && p1[i] <= 21) ||
                         (p1[i] > 44 && p1[i] <= 46) ||
                         (p1[i] > 69 && p1[i] <= 71) ||
                         (p1[i] > 94 && p1[i] <= 96))
                    cout << setw(5) << "S" << "   - ";
                else if ((p1[i] > 21 && p1[i] <= 23) ||
                         (p1[i] > 46 && p1[i] <= 48) ||
                         (p1[i] > 71 && p1[i] <= 73) ||
                         (p1[i] > 96 && p1[i] <= 98))
                    cout << setw(5) << "R" << "   - ";
                else if ((p1[i] > 23 && p1[i] <= 25) ||
                         (p1[i] > 48 && p1[i] <= 50) ||
                         (p1[i] > 73 && p1[i] <= 75) ||
                         (p1[i] > 98 && p1[i] <= 100))
                    cout << setw(5) << "D" << "2  - ";

                else
                    cout << setw(5) << dummy[i] << "   - "; // Number cards
            } else if (row == 3)
                cout << setw(10)
                     << "-       - "; // Another empty line inside the card
            else if (row == 4)
                cout << setw(10) << " -------- "; // Bottom border
            setColor(BLACK, BLACK);
        }
        cout << endl; // Move to the next row of all cards
    }

    cout << endl; // Extra space after all cards
}
void print_cards(int topcard) {

    int item = 1;
    int dummy;
    int rows = 5;

    for (int i = 0; i < rows; i++) {    // Loop through the rows of a card
        for (int j = 0; j <= item; j++) // For each card in the hand
        {

            if (topcard == 1 || topcard == 26 || topcard == 51 || topcard == 76)
                dummy = 0;
            else if (topcard > 1 && topcard <= 10)
                dummy = topcard - 1;
            else if ((topcard > 10 && topcard <= 19))
                dummy = topcard - 10;
            else if (topcard > 26 && topcard <= 35)
                dummy = topcard - 26;
            else if (topcard > 35 && topcard <= 44)
                dummy = topcard - 35;
            else if (topcard > 51 && topcard <= 60)
                dummy = topcard - 51;
            else if (topcard > 60 && topcard <= 69)
                dummy = topcard - 60;
            else if (topcard > 76 && topcard <= 85)
                dummy = topcard - 76;
            else if (topcard > 85 && topcard <= 94)
                dummy = topcard - 85;

            if (topcard <= 25 && j == 0)
                setColor(BLACK, RED);
            else if (topcard >= 26 && topcard <= 50 && j == 0)
                setColor(BLACK, BLUE);
            else if (topcard >= 51 && topcard <= 75 && j == 0)
                setColor(BLACK, GREEN);
            else if (topcard >= 76 && topcard <= 100 && j == 0)
                setColor(BLACK, YELLOW);
            else if (topcard > 100 && topcard <= 104 && j == 0)
                setColor(WHITE, BLACK);
            else if (topcard > 104 && topcard <= 108 && j == 0)
                setColor(WHITE, BLACK);
            else
                setColor(YELLOW, BLACK);

            // Printing the rwos
            if (i == 0)
                cout << setw(10) << " -------- "; // Top row
            else if (i == 1)
                cout << setw(10) << "-       - "; // Empty line inside the card
            else if (i == 2 && j == 0) {

                if (topcard > 100 && topcard <= 104)
                    cout << setw(10) << "-   W   - "; // Wild card
                else if (topcard > 104 && topcard <= 108)
                    cout << setw(10) << "-  W4   - "; // Wild +4 card
                else if ((topcard > 19 && topcard <= 21) ||
                         (topcard > 44 && topcard <= 46) ||
                         (topcard > 69 && topcard <= 71) ||
                         (topcard > 94 && topcard <= 96))
                    cout << setw(5) << "S" << "   - ";
                else if ((topcard > 21 && topcard <= 23) ||
                         (topcard > 46 && topcard <= 48) ||
                         (topcard > 71 && topcard <= 73) ||
                         (topcard > 96 && topcard <= 98))
                    cout << setw(5) << "R" << "   - ";
                else if ((topcard > 23 && topcard <= 25) ||
                         (topcard > 48 && topcard <= 50) ||
                         (topcard > 73 && topcard <= 75) ||
                         (topcard > 98 && topcard <= 100))
                    cout << setw(5) << "D" << "2  - ";
                else
                    cout << setw(5) << dummy << "    -";
            }
            if (i == 2 && j == 1)
                cout << setw(9) << "-  UNO  -";
            else if (i == 3)
                cout << setw(10)
                     << "-       - "; // Another empty line inside the card
            else if (i == 4)
                cout << setw(10) << " -------- "; // Bottom border
        }
        cout << endl; // Move to the next row of all cards
    }
    cout << endl; // Extra space after all cards
}
