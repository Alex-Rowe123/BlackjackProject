#include "DeckOfCards.h"
#include <iomanip>
#include <windows.h>
#include <ctime>
/*Change console text color*/
#define REDTEXT system("Color 04");
#define WHITETEXT system("Color 0F");
#define GREENTEXT system("Color 0A");

void MainMenu();
void InstructionsMenu();
void BeginPlay(bool _bDebug);
void ClearScreen();
void Shrink(int*& _array, int _size); // shrink is a function that takes a dynamic array and a desired size and shrinks the array to the desired size, discarding any extra elements

int main()
{
	srand(time(NULL)); // random seed
	MainMenu();
}

void MainMenu()
{
	int input;
	std::cout << "Welcome to blackjack. Input one of the numbers to pick an option.\n";
	std::cout << "1.Play\n 2.Instructions\n 3.Debug\n 4.Quit\n";
	std::cin >> input;
	switch (input)
	{
	case 1:
		ClearScreen();
		BeginPlay(false);
		break;
	case 2:
		ClearScreen();
		InstructionsMenu();
		break;
	case 3:
		ClearScreen();
		BeginPlay(true);
		break;
	case 4:
		break;
	default:
		std::cout << "Invalid Input, try again.\n";
		std::cin;
		ClearScreen();
		MainMenu();
		break;
	}
}

void InstructionsMenu()
{
	std::cout << "Blah blah blah"; // pls change this
	std::cin;
	ClearScreen();
	MainMenu();
}

void BeginPlay(bool _bDebug)
{
	// create card structs
	Card ClubAce, ClubTwo, ClubThree, ClubFour, ClubFive, ClubSix, ClubSeven, ClubEight, ClubNine, ClubTen, ClubJack, ClubQueen, ClubKing,
		SpadeAce, SpadeTwo, SpadeThree, SpadeFour, SpadeFive, SpadeSix, SpadeSeven, SpadeEight, SpadeNine, SpadeTen, SpadeJack, SpadeQueen, SpadeKing,
		DiamondAce, DiamondTwo, DiamondThree, DiamondFour, DiamondFive, DiamondSix, DiamondSeven, DiamondEight, DiamondNine, DiamondTen, DiamondJack, DiamondQueen, DiamondKing,
		HeartAce, HeartTwo, HeartThree, HeartFour, HeartFive, HeartSix, HeartSeven, HeartEight, HeartNine, HeartTen, HeartJack, HeartQueen, HeartKing;

	// create an array of all cards
	Card Deck[4][13] =
	{
		{ ClubTwo, ClubThree, ClubFour, ClubFive, ClubSix, ClubSeven, ClubEight, ClubNine, ClubTen, ClubJack, ClubQueen, ClubKing, ClubAce },
		{ SpadeTwo, SpadeThree, SpadeFour, SpadeFive, SpadeSix, SpadeSeven, SpadeEight, SpadeNine, SpadeTen, SpadeJack, SpadeQueen, SpadeKing, SpadeAce },
		{ DiamondTwo, DiamondThree, DiamondFour, DiamondFive, DiamondSix, DiamondSeven, DiamondEight, DiamondNine, DiamondTen, DiamondJack, DiamondQueen, DiamondKing, DiamondAce },
		{ HeartTwo, HeartThree, HeartFour, HeartFive, HeartSix, HeartSeven, HeartEight, HeartNine, HeartTen, HeartJack, HeartQueen, HeartKing, HeartAce }
	};

	int input{ 0 }; // deckLen is length of CopyDeck array. input is just reused for menu inputs
	Info PlayerInfo, DealerInfo; // create info data structs for the player and the dealer
	PlayerInfo.MoneyPot = 100;
	bool bPlaying{ true }, bLost{ false }; // bPlaying is for the whole game loop. bLost is for the hitting and standing loop

	// start of actual gameplay
	InitCardVariables(Deck);


	while (bPlaying)
	{
		// reset variables for game
		PlayerInfo.NumOfCards = 0;
		DealerInfo.NumOfCards = 0;
		PlayerInfo.CurrentBet = 0;
		PlayerInfo.AceCounter = 0;
		DealerInfo.AceCounter = 0;
		PlayerInfo.HandValue = 0;
		DealerInfo.HandValue = 0;
		bLost = false;
		int deckLen{ 51 };
		/* pointDeck is a dynamic array with integers for its elements.these integers act as indecies for elements in the Deck array.
		this allows me to change the size of the array and shuffle its elements without changing the data inside the original Deck array */
		int* pointDeck = new int[52]
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

		/* Betting phase */
		do
		{
			std::cout << "\nInput your bet: ";
			std::cin >> PlayerInfo.CurrentBet;
			if (PlayerInfo.CurrentBet <= 0 or PlayerInfo.CurrentBet > PlayerInfo.MoneyPot)
			{
				std::cout << "\nThat is not a valid bet\n";
			}
		} while (PlayerInfo.CurrentBet <= 0 or PlayerInfo.CurrentBet > PlayerInfo.MoneyPot);

		ShuffleDeck(200, pointDeck); // shuffling the cards

		AddToHand(&PlayerInfo, Deck[pointDeck[deckLen - 3]/13][pointDeck[deckLen - 3]%13]); // adds card to the players hand. index stored in pointDeck is converted into 2d
		AddToHand(&PlayerInfo, Deck[pointDeck[deckLen - 2]/13][pointDeck[deckLen - 2]%13]);
		AddToHand(&DealerInfo, Deck[pointDeck[deckLen - 1]/13][pointDeck[deckLen - 1]%13]);
		AddToHand(&DealerInfo, Deck[pointDeck[deckLen]/13][pointDeck[deckLen]%13]);
		deckLen -= 3;
		Shrink(*&pointDeck, deckLen);

		/* Actual Play */
		while (!bLost)
		{
			do
			{
				if (_bDebug) // if debug mode is on, print out the pointDeck
				{
					std::cout << '\n';
					for (int i = 0; i < 52; i++)
					{
						std::cout << pointDeck[i] << ' ';
					}
					std::cout << '\n';
				}

				/* Player chooses whether to Stand or Hit */
				DisplayInfo(PlayerInfo, DealerInfo, _bDebug , false);
				std::cout << "1.Hit\t\t2.Stand\n";
				std::cin >> input;
				ClearScreen();
				switch (input)
				{
				case 1: // Hit chosen
					AddToHand(&PlayerInfo, Deck[pointDeck[deckLen-1]/13][pointDeck[deckLen-1]%13]);
					deckLen--;
					Shrink(*&pointDeck, deckLen);
					while (PlayerInfo.AceCounter > 0 and PlayerInfo.HandValue > 21) // if player has aces and is above 21, make them one until no aces left
					{
						PlayerInfo.AceCounter--;
						PlayerInfo.HandValue -= 10;
					}
					if (PlayerInfo.HandValue > 21) // if player is over 21
					{
						DisplayInfo(PlayerInfo, DealerInfo, true, true);
						REDTEXT;
						std::cout << "\n\nYou lost!!";
						std::cout << "\n1.Continue\n2.Quit To Main Menu\n";
						std::cin >> input; // player inputs whether to play again or quit to menu
						do
						{
							switch (input)
							{
							case 2: // continue
								bPlaying = false;
							case 1: // quit
								delete[] pointDeck;
								bLost = true;
								WHITETEXT;
								ClearScreen();
								break;
							}
						} while (input != 1 and input != 2);
					}
				case 2: // Stand chosen
					break;
				default: // Invalid input
					std::cout << "\nInvalid Choice. Try Again\n\n";
					break;
				}
			} while (input != 2 and !bLost);

			if (!bLost)
			{
				/* Dealer AI, If under 17 then it will hit, otherwise they will stand */
				while (DealerInfo.HandValue < 17)
				{
					AddToHand(&DealerInfo, Deck[pointDeck[deckLen-1] / 13][pointDeck[deckLen-1] % 13]); // hitting
					deckLen--;
					Shrink(*&pointDeck, deckLen);

				}

				DisplayInfo(PlayerInfo, DealerInfo, true, true);

				/* win if dealer busts or you have higher hand */
				if (DealerInfo.HandValue < PlayerInfo.HandValue or DealerInfo.HandValue > 21)
				{
					GREENTEXT;
					std::cout << "\n\nYou win!!\n";

				}
				/* lose if player has lower hand than dealer */
				else if (DealerInfo.HandValue > PlayerInfo.HandValue)
				{
					REDTEXT;
					std::cout << "\n\nYou lost!!\n";

				}
				/* In all other cases (Hands are equal) tie */
				else
				{
					std::cout << "\n\nIts a tie!!\n";
				}
				std::cout << "1.Continue\n2.Quit To Main Menu\n";
				do
				{
					// Player chooses to continue or quit
					std::cin >> input;
					switch (input)
					{
					case 2: // quit
						bPlaying = false;
					case 1: // continue
						delete[] pointDeck;
						bLost = true;
						WHITETEXT;
						ClearScreen();
						break;
					default:
						std::cout << "\nInvalid Choice. Try Again\n\n";
						break;
					}
				} while (input != 1 and input != 2);
			}
		}
		if (!bPlaying)
		{
			MainMenu();
		}
	}
}

void ClearScreen()
{
	std::cout << "\033[2J\033[1;1H";
}

void Shrink(int*& _array, int _size)
{
	int* tempArr = new int[_size] {}; // create new empty dynamic int array of _size
	for (int i{ 0}; i < _size; i++) // copy contents of original array to new array
	{
		tempArr[i] = _array[i];
	}
	delete[] _array; // deallocates the elements of the original but keeps the pointer
	_array = tempArr; // original array now points to the new array in the heap. tempArr doesnt need to be deleted as it will soon become out of scope
}
