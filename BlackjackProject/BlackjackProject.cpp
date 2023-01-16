#include "DeckOfCards.h"
#include <iomanip>
#include <conio.h>
#include <ctime>

/*Change console text color*/
#ifdef _WIN32
	#define REDTEXT system("Color 04");
	#define WHITETEXT system("Color 0F");
	#define GREENTEXT system("Color 0A");
#else
	#define REDTEXT ;
	#define WHITETEXT ;
	#define GREENTEXT ;
#endif

#define CLRSCR std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

void MainMenu();
void InstructionsMenu();
void BeginPlay(bool _bDebug);

int main()
{
	srand(time(NULL)); // random seed
	MainMenu();
}

void BeginPlay(bool _bDebug)
{
	// create card data structs for all cards
	Card ClubAce, ClubTwo, ClubThree, ClubFour, ClubFive, ClubSix, ClubSeven, ClubEight, ClubNine, ClubTen, ClubJack, ClubQueen, ClubKing,
		SpadeAce, SpadeTwo, SpadeThree, SpadeFour, SpadeFive, SpadeSix, SpadeSeven, SpadeEight, SpadeNine, SpadeTen, SpadeJack, SpadeQueen, SpadeKing,
		DiamondAce, DiamondTwo, DiamondThree, DiamondFour, DiamondFive, DiamondSix, DiamondSeven, DiamondEight, DiamondNine, DiamondTen, DiamondJack, DiamondQueen, DiamondKing,
		HeartAce, HeartTwo, HeartThree, HeartFour, HeartFive, HeartSix, HeartSeven, HeartEight, HeartNine, HeartTen, HeartJack, HeartQueen, HeartKing;

	// create a 2d array of all cards, divided up into groups of their suits
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
	/* bPlaying is for the whole game loop.bLost is for the hittingand standing loop.
	bFinishActions is for checking whether the player has finished their actions.
	bValidBet is whether the inputted bet is valid */
	bool bPlaying{ true }, bLost{ false }, bFinishActions{ false }, bValidBet{ false };


	/* these integers act as indecies for elements in the Deck array.
	this allows me to shuffle its elements without changing the data inside the original Deck array */
	int pointDeck[]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

	ShuffleDeck(200, pointDeck); // shuffling the cards ready for new game

	InitCardVariables(Deck);


	while (bPlaying)
	{
		/* reset variables for game */
		PlayerInfo.NumOfCards = 0;
		DealerInfo.NumOfCards = 0;
		PlayerInfo.CurrentBet = 0;
		PlayerInfo.AceCounter = 0;
		DealerInfo.AceCounter = 0;
		PlayerInfo.HandValue = 0;
		DealerInfo.HandValue = 0;
		bLost = false;
		bValidBet = false;

		/* Betting phase */
		do
		{
			std::cout << "\nYour money:" << PlayerInfo.MoneyPot << "\nInput your bet: ";
			std::cin >> PlayerInfo.CurrentBet;
			if (PlayerInfo.CurrentBet > 0 and PlayerInfo.CurrentBet <= PlayerInfo.MoneyPot)
			{
				PlayerInfo.MoneyPot -= PlayerInfo.CurrentBet;
				bValidBet = true;
			}
			else
			{
				std::cout << "\nThat is not a valid bet\n";
			}
		} while (!bValidBet);

		/* Deal cards to player and dealer */
		AddToHand(&PlayerInfo, Deck[0][pointDeck[0]]); // adds card to the players hand. The Card input is the the element of Deck at the first element in pointDeck
		WrapDeck(pointDeck);						   // takes the top card and puts it at the back of the deck.
		AddToHand(&PlayerInfo, Deck[0][pointDeck[0]]);
		WrapDeck(pointDeck);
		AddToHand(&DealerInfo, Deck[0][pointDeck[0]]);
		WrapDeck(pointDeck);
		AddToHand(&DealerInfo, Deck[0][pointDeck[0]]);
		WrapDeck(pointDeck);


		/* Actual Play */
		while (!bLost)
		{
			bFinishActions = false;

			/* this do while loop asks the player to pick an action. When the player hits, the players hand value is checked.
			* the loop ends if the players hand value is over 21 OR the player stands */
			do //(while (!bFinishActions))
			{	
				/* if debug mode is on, print out the deck (pointDeck) */
				if (_bDebug)
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
				CLRSCR;

				switch (input)
				{
				/* hit */
				case 1:
					AddToHand(&PlayerInfo, Deck[0][pointDeck[0]]);
					WrapDeck(pointDeck);

					while (PlayerInfo.AceCounter > 0 and PlayerInfo.HandValue > 21) // if player has aces and is above 21, make them one until no aces left
					{
						PlayerInfo.AceCounter--;
						PlayerInfo.HandValue -= 10;
					}
					if (PlayerInfo.HandValue > 21)
					{
						bFinishActions = true;
						
					}
					break;
				/* stand */
				case 2:
					bFinishActions = true;
					break;
				/* invalid input */
				default:
					std::cout << "\nInvalid Choice. Try Again\n\n";
					break;

				}

			} while (!bFinishActions);

			if (!bLost)
			{
			/* Dealer AI, If under 17 then it will hit, otherwise they will stand */
				/* hitting */
				while (DealerInfo.HandValue < 17 and PlayerInfo.HandValue < 21)
				{
					AddToHand(&DealerInfo, Deck[0][pointDeck[0]]);
					WrapDeck(pointDeck);
				}

				DisplayInfo(PlayerInfo, DealerInfo, true, true);

				/* win if dealer busts or you have higher hand */
				if ((DealerInfo.HandValue < PlayerInfo.HandValue or DealerInfo.HandValue > 21) and PlayerInfo.HandValue <= 21)
				{
					PlayerInfo.MoneyPot += PlayerInfo.CurrentBet * 2;
					GREENTEXT;
					std::cout << "\n\nYou win!!\n";

				}

				/* lose if player has lower hand than dealer */
				else if (DealerInfo.HandValue > PlayerInfo.HandValue or PlayerInfo.HandValue > 21)
				{
					REDTEXT;
					std::cout << "\n\nYou lost!!\n";

				}

				/* In all other cases (Hands are equal) tie */
				else
				{
					PlayerInfo.MoneyPot += PlayerInfo.CurrentBet;
					std::cout << "\n\nIts a tie!!\n";
				}


				if (PlayerInfo.MoneyPot > 0)
				{
					std::cout << "1.Continue\n2.Quit To Main Menu\n";

					do
					{
						/* Player chooses to continue or quit */
						std::cin >> input;
						switch (input)
						{
							/* quit */
						case 2:
							bPlaying = false;
							/* continue */
						case 1:
							bLost = true;
							WHITETEXT;
							CLRSCR;
							break;
							/* invalid input */
						default:
							std::cout << "\nInvalid Choice. Try Again\n\n";
							break;
						}
					} while (input != 1 and input != 2);
				}
				else
				{
					std::cout << "\nYou ran out of money!\nGame Over!\nPress any button to continue...\n";
					input = _getch();
					bLost = true;
					bPlaying = false;
					WHITETEXT;
					CLRSCR;
				}
			}
		}
		if (!bPlaying)
		{
			MainMenu();
		}
	}
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
		CLRSCR;
		BeginPlay(false);
		break;
	case 2:
		CLRSCR;
		InstructionsMenu();
		break;
	case 3:
		CLRSCR;
		BeginPlay(true);
		break;
	case 4:
		break;
	default:
		std::cout << "Invalid Input, try again.\n";
		std::cin;
		CLRSCR;
		MainMenu();
		break;
	}
}

void InstructionsMenu()
{
	int input;
	std::cout << "2 cards are dealt to the player and dealer.\nYou decide whether to hit (take another card) or stand (end turn).\nThe highest value wins, but if you go over 21 you lose.\n\nPress enter to continue...";
	input = _getch();
	CLRSCR;
	MainMenu();
}