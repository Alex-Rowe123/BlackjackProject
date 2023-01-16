#pragma once
#include <iostream>
#include <iomanip>


enum SuitType { Club, Spade, Diamond, Heart };
enum ValueTypes { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

struct Card
{
	SuitType Suit{ Club }; // the suit of the card
	ValueTypes CardRank{ Two }; // the rank of the card
	int ActualValue{ 0 }; // the actual value of the card
};
	

/// <summary>
/// Takes the Deck and initializes all the values to be the correct suit and rank.
/// </summary>
/// <param name="_Deck"></param>
void InitCardVariables(Card _Deck[4][13]);

/// <summary>
/// Takes the deck and shuffles it. The _ShuffleResolution decides how many times the algorithm should run.
/// Ive found 200 is a good number.
/// </summary>
/// <param name="_ShuffleResolution"></param>
/// <param name="_Deck"></param>
void ShuffleDeck(int _ShuffleResolution, int* _Deck);

/// <summary>
/// Moves the elements in the deck one index forward and takes the final element and moves it to index 0
/// </summary>
/// <param name="_Deck"></param>
void WrapDeck(int* _Deck);




struct Info
{
	Card Hand[12]; // 12 is the maximum amount of cards someone could get in a game of blackjack with one deck
	int MoneyPot{ 0 }; // how much money the player has
	int HandValue{ 0 }; // how much all the card values add up to
	int CurrentBet{ 0 }; // how much you are currently betting
	int NumOfCards{ 0 }; // how many cards in your hand
	int AceCounter{ 0 }; // how many aces that have the value 11
};

/// <summary>
/// Takes the info structs for both the player and dealer and displays its contents to the screen.
/// The _bShowHole shows the dealers hole card and _bShowDealerValue shows the dealers hand value
/// </summary>
/// <param name="_PlayerInfo"></param>
/// <param name="_DealerInfo"></param>
/// <param name="_bShowHole"></param>
/// <param name="_bShowDealerValue"></param>
void DisplayInfo(Info _PlayerInfo, Info _DealerInfo, bool _bDebug, bool _bShowDealerValue);

/// <summary>
/// Takes the _Card input and adds it onto the end of the _PlayerInfo.Hand array
/// </summary>
/// <param name= "_PlayerInfo" ></param>
/// <param name= "_Card" > </param>
void AddToHand(Info* _PlayerInfo, Card _Card);