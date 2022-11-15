#pragma once
#include <iostream>
#include <iomanip>

namespace DeckOfCards
{
	enum SuitType { Club, Spade, Diamond, Heart };
	enum ValueTypes { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

	struct Card
	{
		char NameOfCard[10] = {0}; // Name of the card as a null terminated char array. 10 value is random
		SuitType Suit{ Club }; // the suit of the card
		ValueTypes CardRank{ Two }; // the rank of the card
		int ActualValue{ 0 }; // the actual value of the card

	};
	
	void InitCardVariables(Card _Deck[4][13], Card _CopyDeck[52]); // sets up the deck with appropriate and unique values (basically fills in details for every card in a deck)
	void ShuffleDeck(int _ShuffleResolution, Card _Deck[]); // This Function shuffles the _Deck around. Increase shuffle resolution for more randomness
}

namespace dc = DeckOfCards;

namespace Players
{
	struct Info
	{
		dc::Card Hand[10]; // 10 is random number. Unlinkely that your hand will reach this number of cards
		int MoneyPot{ 0 }; // how much money the player has (Dealer also has this value but its unused. Could really use some classes :p)
		int HandValue{ 0 }; // how much all the card values add up to
		int CurrentBet{ 0 }; // how much you are currently betting
		int NumOfCards{ 0 }; // how many cards in your hand
		int AceCounter{ 0 }; // how many aces that have the value 11
	};
	void DisplayInfo(Info _PlayerInfo, Info _DealerInfo, bool _bDebug, bool _bShowDealerValue); // display important information about gamestate
	void AddToHand(Info* _PlayerInfo, dc::Card _Card); // adds a card to the hand
}