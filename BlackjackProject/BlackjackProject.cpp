#include "DeckOfCards.h"
#include <iomanip>
#include <ctime>

namespace dc = DeckOfCards;

void MainMenu();
void InstructionsMenu();
void BeginPlay(bool _bShowHole);
void ClearScreen();

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

void BeginPlay(bool _bShowHole)
{
	// create card structs
	dc::Card ClubAce, ClubTwo, ClubThree, ClubFour, ClubFive, ClubSix, ClubSeven, ClubEight, ClubNine, ClubTen, ClubJack, ClubQueen, ClubKing,
		SpadeAce, SpadeTwo, SpadeThree, SpadeFour, SpadeFive, SpadeSix, SpadeSeven, SpadeEight, SpadeNine, SpadeTen, SpadeJack, SpadeQueen, SpadeKing,
		DiamondAce, DiamondTwo, DiamondThree, DiamondFour, DiamondFive, DiamondSix, DiamondSeven, DiamondEight, DiamondNine, DiamondTen, DiamondJack, DiamondQueen, DiamondKing,
		HeartAce, HeartTwo, HeartThree, HeartFour, HeartFive, HeartSix, HeartSeven, HeartEight, HeartNine, HeartTen, HeartJack, HeartQueen, HeartKing;

	// create an array of all cards
	dc::Card Deck[4][13] =
	{
		{ ClubTwo, ClubThree, ClubFour, ClubFive, ClubSix, ClubSeven, ClubEight, ClubNine, ClubTen, ClubJack, ClubQueen, ClubKing, ClubAce },
		{ SpadeTwo, SpadeThree, SpadeFour, SpadeFive, SpadeSix, SpadeSeven, SpadeEight, SpadeNine, SpadeTen, SpadeJack, SpadeQueen, SpadeKing, SpadeAce },
		{ DiamondTwo, DiamondThree, DiamondFour, DiamondFive, DiamondSix, DiamondSeven, DiamondEight, DiamondNine, DiamondTen, DiamondJack, DiamondQueen, DiamondKing, DiamondAce },
		{ HeartTwo, HeartThree, HeartFour, HeartFive, HeartSix, HeartSeven, HeartEight, HeartNine, HeartTen, HeartJack, HeartQueen, HeartKing, HeartAce }
	};

	dc::Card CopyDeck[52];// make an array that will copy all the values from the original deck. This is just so i dont mess with the original deck. probably could be changed
	int DeckLength{ 51 }, input{ 0 }; // deck length is how many possible cards we can draw. input is just reused for menu inputs
	Players::Info PlayerInfo, DealerInfo; // create info data structs for the player and the dealer
	PlayerInfo.MoneyPot = 100;
	bool bPlaying{ true }, bLost{ false }; // bPlaying is for the whole game loop. bLost is for the hitting and standing loop

	// start of actual gameplay
	dc::InitCardVariables(Deck, CopyDeck);

	while (bPlaying)
	{
		// reset variables for game
		DeckLength = 51;
		PlayerInfo.NumOfCards = 0;
		DealerInfo.NumOfCards = 0;
		PlayerInfo.CurrentBet = 0;
		PlayerInfo.AceCounter = 0;
		DealerInfo.AceCounter = 0;
		PlayerInfo.HandValue = 0;
		DealerInfo.HandValue = 0;
		bLost = false;

		/* Betting phase */
		do
		{
			std::cout << "\n\nInput your bet: ";
			std::cin >> PlayerInfo.CurrentBet;
			if (PlayerInfo.CurrentBet <= 0 or PlayerInfo.CurrentBet > PlayerInfo.MoneyPot)
			{
				std::cout << "\n\nThat is not a valid bet\n";
			}
		} while (PlayerInfo.CurrentBet <= 0 or PlayerInfo.CurrentBet > PlayerInfo.MoneyPot);

		/* Initial dealing of cards */
		dc::ShuffleDeck(200, CopyDeck);

		Players::AddToHand(&PlayerInfo, CopyDeck[DeckLength]);
		DeckLength--;
		Players::AddToHand(&PlayerInfo, CopyDeck[DeckLength]);
		DeckLength--;
		Players::AddToHand(&DealerInfo, CopyDeck[DeckLength]);
		DeckLength--;
		Players::AddToHand(&DealerInfo, CopyDeck[DeckLength]);
		DeckLength--;

		/* Actual Play */
		while (!bLost)
		{
			do
			{
				/* Player chooses whether to Stand or Hit */
				Players::DisplayInfo(PlayerInfo, DealerInfo, _bShowHole);
				std::cout << "1.Hit\t\t2.Stand\n";
				std::cin >> input;
				switch (input)
				{
				case 1: // Hit chosen
					Players::AddToHand(&PlayerInfo, CopyDeck[DeckLength]);
					DeckLength--;
					while (PlayerInfo.AceCounter > 0 and PlayerInfo.HandValue > 21) // if player has aces and is above 21, make them one until no aces left
					{
						PlayerInfo.AceCounter--;
						PlayerInfo.HandValue -= 10;
					}
					if (PlayerInfo.HandValue > 21) // if player is over 21
					{
						Players::DisplayInfo(PlayerInfo, DealerInfo, _bShowHole);
						std::cout << "\n\nYou lost!!\n1.Continue\n2.Quit To Main Menu\n";
						std::cin >> input; // player inputs whether to play again or quit to menu
						do
						{
							switch (input)
							{
							case 2: // continue
								bPlaying = false;
							case 1: // quit
								bLost = true;
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

			_bShowHole = true;

			if (!bLost)
			{
				/* Dealer AI, If under 17 then it will hit, otherwise they will stand */
				while (DealerInfo.HandValue < 17)
				{
					Players::AddToHand(&DealerInfo, CopyDeck[DeckLength]); // hitting
					DeckLength--;
				}

				Players::DisplayInfo(PlayerInfo, DealerInfo, _bShowHole);

				/* win if dealer busts or you have higher hand */
				if (DealerInfo.HandValue < PlayerInfo.HandValue or DealerInfo.HandValue > 21)
				{
					std::cout << "\n\nYou win!!\n";

				}
				/* lose if player has lower hand than dealer */
				else if (DealerInfo.HandValue > PlayerInfo.HandValue)
				{
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
						bLost = true;
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
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\b\b\b\b\b\b\b\b\b\b\b\b\b";
}

