// ECGR 2103 Final Code
// Buse Arpacay, Ayan Caligacal, Nick Wilcox
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void resetGameBoard(int gameBoard[14]) {
	for (int i = 0; i < 14; i++) {
		if (i % 7 == 0) {
			gameBoard[i] = 0;
		} else {
			gameBoard[i] = 4;
		}
	}
}

bool continuationSelection(int gameBoard[14]) {
	char continuation;
	bool selecting = true;
	while (selecting) {
		cin >> continuation;
		if (continuation == 'y' || continuation == 'n') {
			selecting = false;
		} else {
			cout << "Invalid input. Please enter y if you would like to play "
					"again and n if you are finished playing."
				 << endl;
		}
	}
	if (continuation == 'n') {
		cout << "Goodbye!";
		return false;
	} else {
		cout << "reseting the game board" << endl;
		resetGameBoard(gameBoard);
		return true;
	}
}

void DispGameBoard(int gameBoard[14]) {
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			cout << "______________________" << endl;
			cout << "|"
				 << "  ";
			for (int j = 1; j < 7; j++) {
				cout << gameBoard[j] << "  ";
			}
			cout << "|";
			cout << endl;
		} else if (i == 1) {
			cout << "|" << gameBoard[0] << "                  " << gameBoard[7]
				 << "|" << endl;
		}

		else {
			cout << "|"
				 << "  ";
			for (int n = 8; n < 14; n++) {
				cout << gameBoard[n] << "  ";
			}
			cout << "|" << endl;
			cout << "______________________" << endl;
		}
	}
}

int main() {
	cout << "Welcome to Mancala! Here are the rules." << endl;
	cout << "MANCALA DIRECTIONS" << endl; // This is kind of weird when it runs
										  // because its just a wall of text lol
	cout << "Lay out the board horizontally between the two players, the side "
			"closest to each player will be the side they control."
		 << endl;
	cout << "Each side has 6 pits with 4 beads in each, the mancala to the "
			"right belongs to player 1, the mancala to the left belongs to "
			"player 2."
		 << endl;
	cout << "During your turn, you will pick a pit, and drop 1 bead into each "
			"next pot in a counter-clockwise fashion until you run out."
		 << endl;
	cout << "If you land on an empty bead, stop, it is the other players turn."
		 << endl;
	cout << "If you land on your mancala, pick a new pit and start your turn "
			"again. If you land on a pit with beads, pick them up and continue."
		 << endl;
	cout << "Be sure not to place any beads into the other players mancala."
		 << endl;
	cout << "When there are no longer beads on either players side, the other "
			"player should pick the beads remaining on their side, and place "
			"them in their mancala."
		 << endl;
	cout << "The beads in each mancala will then be counted, and the player "
			"with more beads in their mancala will be declared the winner. "
			"Player 1 will go first."
		 << endl;
	cout << "Would you like to begin playing? Type 'Yes' or 'yes' to continue."
		 << endl;
	string continuation;
	string player1;		// used for name of player 1
	string player2;		// used for name of player 2
	char onePlayerName; // used to seed the random number generator using player
						// 1's name
	bool currentGame = true; // runs the main game loop
	bool selecting = true;
	int turn = 0;
	int playerOneTotal;
	int playerTwoTotal;
	int hand;			// stores the number of beads the user has in their hand
	int selectedCup;	// stores location of cup the user selects and moves
						// through the board to keep track of cups.
	int selectedCupTwo; // stores location of cup chosen for player 2, which
						// helps determine currentCupValue
	int board[14] = {
		0, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4}; // game board setup.
	int seed = 0;

	cin >> continuation;

	if (continuation == "yes" || continuation == "Yes") {
		cout << "Player 1, What is your name?" << endl;
		cin >> player1;
		cout << "First player is " << player1 << endl;

		cout << "Player 2, What is your name?" << endl;
		cin >> player2;
		cout << "Second player is " << player2 << endl;

		for (int j = 0; j < player1.length(); j++) {
			seed +=
				(int)player1.at(j); // adds ascii value of every char in each
									// players name to create a seed for RNG.
			seed += (int)player2.at(j);
		}
		srand(seed);
		turn = rand() % 2;
		if (turn == 0) {
			cout << player1 << " will go first." << endl;
		}
		if (turn == 1) {
			cout << player2 << " will go first." << endl;
		}

		while (currentGame) // Main game loop
		{
			DispGameBoard(board); // shows the game board before every turn
			if (turn % 2 == 0)	// player 1's game loop.
			{
				cout << "It is " << player1
					 << "'s turn please select a cup number (1-6)";
				cin >> selectedCup; // the cup that the player chooses, the
									// beads in said cup will be put into the
									// players "hand"
				hand = board[selectedCup]; // Takes all beads from cup and puts
										   // them into their hand.
				board[selectedCup] =
					0; // since the player took the beads out of that cup, the
					   // value of the beads in that cup will be 0
				int currentCupValue;
				currentCupValue = selectedCup -
					1; // since the player took the beads out of that cup, the
					   // value of the beads in that cup will be 0
				while (hand > 0) // turn loop for player 1.
				{
					if (currentCupValue > 1 &&
						currentCupValue <=
							6) // for player ones row, the beads circle in a
							   // counter clockwise motion by decrimenting
					{
						board[currentCupValue] = board[currentCupValue] +
							1; // value of each position on the board increments
							   // as we continue
						hand = hand -
							1; // value of the hand is decrimenting, when you
							   // have no more beads left, the loop stops
						currentCupValue = currentCupValue -
							1; // decreases to move counter-clockwise
					} else if (currentCupValue == 1) // end of upper row, to
													 // avoid awkward issues
													 // with the loop running
													 // well, it was best to use
													 // a seperate if/else
													 // statement
					{
						board[currentCupValue] = board[currentCupValue] + 1;
						hand = hand - 1;
						currentCupValue = 0;
					} else if (
						currentCupValue >= 8 &&
						currentCupValue < 13) // bottom row
					{
						board[currentCupValue] = board[currentCupValue] + 1;
						hand = hand - 1;
						currentCupValue = currentCupValue +
							1; // increases to continue moving counterclockwise
					} else if (currentCupValue == 13) // end of this row, as
													  // opposed to a continuous
													  // increment to 14, the
													  // currentCupValue is set
													  // to 6 (not 7, thats the
													  // other players mancala)
					{
						board[currentCupValue] = board[currentCupValue] + 1;
						hand = hand - 1;
						currentCupValue =
							6; // has to skip 7 -- NOT player1s MANCALA
					} else if (currentCupValue == 0) // special rules for
													 // landing in your own
													 // mancala
					{
						board[currentCupValue] = board[currentCupValue] + 1;
						hand = hand - 1;
						if (hand == 0) // when the player lands on 0, they are
									   // allowed to take another turn
						{
							DispGameBoard(board);
							cout << player1
								 << " choose another mancala from (1-6)"
								 << endl;
							cin >> selectedCup;
							hand = board[selectedCup];
							board[selectedCup] = 0;
							currentCupValue = selectedCup -
								1; // remember, pits from 1-6 decriment
							board[currentCupValue] = board[currentCupValue] + 1;
							currentCupValue =
								selectedCup - 1; // decriment afterwards to
												 // imitate entire loop
						} else {
							currentCupValue =
								8; // otherwise, they just move on to 8
						}
					}
				}
				turn++; // Changes the value of turn from even to odd.
			}

			playerOneTotal = board[1] + board[2] + board[3] + board[4] +
				board[5] +
				board[6]; // checks if the total of either side of board
						  // (negatives aren't possible -> it has to just be
						  // empty) equals 0, which would render the game over
			playerTwoTotal = board[8] + board[9] + board[10] + board[11] +
				board[12] + board[13];
			if (playerOneTotal == 0 ||
				playerTwoTotal == 0) // and if the game is over
			{
				cout << "The game is over!" << endl;
				if (board[0] >
					board[7]) // these if/else statements determine who wins
				{
					cout << "Player 1 wins! Would you like to play again?(y/n)"
						 << endl;
					currentGame = continuationSelection(board);
				} else if (board[7] > board[0]9) {
					cout << "Player 2 wins! Would you like to play again?(y/n)"
						 << endl;
					currentGame = continuationSelection(board);
				} else if (board[0] == board[7]) {
					cout << "Tie! Would you like to play again?(y/n)";
					currentGame = continuationSelection(board);
				}
				if (!currentGame) {
					break;
				}
				turn++;
			}
			DispGameBoard(board);

			if (turn % 2 == 1) {
				cout << "It is " << player2
					 << "'s turn please select a cup number (8-13)"; // change
																	 // this to
																	 // players
																	 // name.
				int currentCupValueTwo;
				cin >> selectedCupTwo;
				hand = board[selectedCupTwo]; // Takes all beads from cup and
											  // puts them into their hand.
				board[selectedCupTwo] = 0;
				currentCupValueTwo = selectedCupTwo + 1;
				while (hand > 0) // turn loop for player 1
				{
					if (currentCupValueTwo >= 8 &&
						currentCupValueTwo <
							13) // for player twos row, the beads circle in a
								// counter clockwise motion by incrementing
					{
						board[currentCupValueTwo] =
							board[currentCupValueTwo] + 1;
						hand = hand - 1;
						currentCupValueTwo =
							currentCupValueTwo + 1;		 // 8-13 increments
					} else if (currentCupValueTwo == 13) // program reaches 13
														 // during loop
					{
						board[currentCupValueTwo] =
							board[currentCupValueTwo] + 1;
						hand = hand - 1;
						currentCupValueTwo =
							7; // 7 is player 2s mancala, to the right
					} else if (
						currentCupValueTwo ==
						14) // the code will add one if you choose 13, its
							// necessary to counteract that with a different
							// else if statement to prevent a complete glitch
					{
						currentCupValueTwo = 7;
						board[currentCupValueTwo] =
							board[currentCupValueTwo] + 1;
						hand = hand - 1;
						currentCupValueTwo = 7; // player 2s mancala = 7
					} else if (
						currentCupValueTwo > 1 && currentCupValueTwo <= 6) {
						board[currentCupValueTwo] =
							board[currentCupValueTwo] + 1;
						hand = hand - 1;
						currentCupValueTwo = currentCupValueTwo - 1;
					} else if (currentCupValueTwo == 1) {
						board[currentCupValueTwo] =
							board[currentCupValueTwo] + 1;
						hand = hand - 1;
						currentCupValueTwo = 8;
					} else if (currentCupValueTwo == 7) // special rules for
														// landing in your own
														// mancala
					{
						board[currentCupValueTwo] =
							board[currentCupValueTwo] + 1;
						hand = hand - 1;
						if (hand == 0) {
							DispGameBoard(board);
							cout << player2
								 << " choose another mancala from (8-13)"
								 << endl;
							cin >> selectedCupTwo;
							hand = board[selectedCupTwo];
							board[selectedCupTwo] = 0;
							currentCupValueTwo = selectedCupTwo + 1;
							board[currentCupValueTwo] =
								board[currentCupValueTwo] + 1;
							currentCupValueTwo = currentCupValueTwo + 1;
						} else {
							currentCupValueTwo = 6;
						}
					}
				}
				turn++;
			}

			playerOneTotal = board[1] + board[2] + board[3] + board[4] +
				board[5] + board[6]; // once again, checks for if the game is
									 // over at EVERY turn
			playerTwoTotal = board[8] + board[9] + board[10] + board[11] +
				board[12] + board[13];

			if (playerOneTotal == 0 || playerTwoTotal == 0) {
				cout << "The game is over!" << endl;
				if (board[0] > board[7]) {
					cout << "Player 1 wins! Would you like to play again?(y/n)"
						 << endl;
					currentGame = continuationSelection(board);
				} else if (board[7] > board[0]) {
					cout << "Player 2 wins! Would you like to play again?(y/n)"
						 << endl;
					currentGame = continuationSelection(board);
				} else if (board[0] == board[7]) {
					cout << "Tie! Would you like to play again?(y/n)";
					currentGame = continuationSelection(board);
				}
				if (!currentGame) {
					break;
				}
			}
		}
	}

	// Determines the winner and asks for continuation.

	else {
		cout << "Goodbye!" << endl;
	}

	return 0;
}
