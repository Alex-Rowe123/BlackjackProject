#include "DeckOfCards.h"

void InitCardVariables(Card _Deck[4][13]) // This function sets the variables for all the data inside the card struct
{

	for (int i{ 0 }; i < 4; i++) // Loop through all possible suits. CardNum is to count the number of cards
	{
		for (int j{ 0 }; j < 13; j++) // Loop through all possible ranks. Increment Cardnum
		{
			_Deck[i][j].Suit = SuitType(i); // Set the suit for the card struct
			_Deck[i][j].CardRank = ValueTypes(j); // Set the rank for the card struct

			if (_Deck[i][j].CardRank == 12) // If the Card Rank enum value is 12 (Card is an ace), set Actual Value to 11
			{
				_Deck[i][j].ActualValue = 11;
			}
			else if (_Deck[i][j].CardRank <= 8) // If the Card Rank enum value is less than 9 (Card has a value of less than jack), then the Value of the card is the loop iteration + 2
			{
				_Deck[i][j].ActualValue = _Deck[i][j].CardRank + 2;
			}
			else if (_Deck[i][j].CardRank > 8) // If the Card Rank enum value is more than 8 (Card is jack or higher but not ace), then value of the card is set to 10
			{
				_Deck[i][j].ActualValue = 10;
			}
		}
	}
}

void ShuffleDeck(int _ShuffleResolution,int* _Deck)
{
	int temp;
	for (int i{ 0 }; i < _ShuffleResolution; i++) // repeat shuffle
	{
		for (int j{ 0 }; j < 51; j++) // if random number is odd then swap the index with the one in front
		{
			int randNum{ 0 };
			randNum = (rand() % 2); // Get random number and see if there is a remainder
			if (randNum) // if randNum is odd number
			{
				/*Swaps array elements*/
				temp = _Deck[j+1];
				_Deck[j + 1] = _Deck[j];
				_Deck[j] = temp;
			}
		}
	}
}

void DisplayInfo(Info _PlayerInfo, Info _DealerInfo, bool _bShowHole, bool _bShowDealerValue)
{
	const char SuitDictionary[4][8] = { "Club", "Spade", "Diamond", "Heart" };
	const char ValueDictionary[13][6] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	/* Display the dealers info */
	std::cout << "\nDealers Hand:\n";
	
	for (int i{ 0 }; i < _DealerInfo.NumOfCards; i++)
	{
		if (_bShowHole == false and i == 0) { std::cout << "Hole Card\t"; } // if debug mode is false hide the first card in hand
		else { std::cout << ValueDictionary[_DealerInfo.Hand[i].CardRank] << " of " << SuitDictionary[_DealerInfo.Hand[i].Suit] << "s" << std::setw(10); }
		if (!(i % 2)) { std::cout << '\n'; } // create grid
	}

	if (_bShowDealerValue)
	{
		std::cout << "\n\nThe dealers card value is: " << _DealerInfo.HandValue << '\n';
	}

	/* Display the players info */
	std::cout << "\n\n\nYour money: " << _PlayerInfo.MoneyPot << "\t\tYour current bet: " << _PlayerInfo.CurrentBet << '\n' << "Your Hand:\n";
	
	for (int i{ 0 }; i < _PlayerInfo.NumOfCards; i++)
	{
		std::cout << ValueDictionary[_PlayerInfo.Hand[i].CardRank] << " of " << SuitDictionary[_PlayerInfo.Hand[i].Suit] << "s" << std::setw(10);
		if ((i % 2)) { std::cout << '\n'; } // create grid
	}

	std::cout << "\n\nYour total card value is: " << _PlayerInfo.HandValue << '\n';
}

void AddToHand(Info* _PlayerInfo, Card _Card)
{
	_PlayerInfo->Hand[_PlayerInfo->NumOfCards] = _Card; // add card to hand
	_PlayerInfo->NumOfCards++; // increase num of cards counter
	_PlayerInfo->HandValue += _Card.ActualValue; // increase hand value
	if (_Card.CardRank == Ace)
	{
		_PlayerInfo->AceCounter++;
	}
}
