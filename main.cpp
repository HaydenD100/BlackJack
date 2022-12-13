/*
Made by Hayden
Simple BlackJack betting game made in c++
*/






#include <iostream>
#include<vector>
#include <random>
#include<time.h>


using namespace std;
class card
{
public:
	int Value = 0;
	int Type = 0;

	card(int value, int type)
	{
		Value = value;
		Type = type;
	}
};

void DisplayCards(vector<card> playerDeck)
{
	cout << "===================Your Cards===================\n";
	for (int cards = 0; cards < playerDeck.size(); cards++)
	{
		if (playerDeck.at(cards).Value == 11) 
			cout << "Jack of ";
		if (playerDeck.at(cards).Value == 12) 
			cout << "Queen of ";
		if (playerDeck.at(cards).Value == 13) 
			cout << "King of ";

		if (playerDeck.at(cards).Value < 11 && playerDeck.at(cards).Value != 1)
			cout << playerDeck.at(cards).Value << " of ";
		if (playerDeck.at(cards).Value == 1)
			cout << "Ace of ";

		if (playerDeck.at(cards).Type == 1) 
			cout << "Hearts\n";
		if (playerDeck.at(cards).Type == 2) 
			cout << "Diamonds\n";
		if (playerDeck.at(cards).Type == 3) 
			cout << "Clubs\n";
		if (playerDeck.at(cards).Type == 4) 
			cout << "Spades\n";
	}
	cout << "================================================\n";
}

int CheckValue(vector<card> playerDeck) 
{
	int value = 0;
	int aces = 0;
	for (int cards = 0; cards < playerDeck.size(); cards++)
	{
		
		if (playerDeck.at(cards).Value > 10)
			value = value + 10;

		if (playerDeck.at(cards).Value > 1 && playerDeck.at(cards).Value < 11)
			value = value + playerDeck.at(cards).Value;

		if (playerDeck.at(cards).Value = 1)
			aces++;
	};
	while(aces > 0)
	{
		if ((value = value + 11) > 21)
			value++;
		if ((value = value + 11) == 21 && aces == 1)
			value = value + 11;

		if ((value = value + 11) < 21)
			value = value + 11;
		aces--;
	}
	return value;
}

int main() 
{


	vector<card> baseDeck;
	vector<card> shuffledDeck;
	vector<card> dealerDeck;
	vector<card> playerDeck;

	char input;

	int Money = 100;
	int Bet = 0;

	int randNum = 0;
	int type = 1;



	card temp(1,1);
	baseDeck.push_back(temp);
	while (baseDeck.size() <= 52) {
		
		
		for (int a = 1; a <= 13; a++)//1 = hearts 2 = diamonds 3 = clubs 4 = spades
		{
			card TempCard(a,type);
			baseDeck.push_back(TempCard);
		}

		type++;
	}
	cout << "Welcome To BlackJack\n";
	cout << "Press Enter To Start\n";
	cin.ignore();
	while (true)
	{
		dealerDeck.clear();
		playerDeck.clear();
		shuffledDeck.clear();

		srand(time(0));
		while (shuffledDeck.size() <= 52)
		{
			randNum = rand() % (52 + 1 - 0) + 0;
			shuffledDeck.push_back(baseDeck.at(randNum));
		}


		


		dealerDeck.push_back(shuffledDeck.back());
		shuffledDeck.pop_back();
		dealerDeck.push_back(shuffledDeck.back());
		shuffledDeck.pop_back();

		playerDeck.push_back(shuffledDeck.back());
		shuffledDeck.pop_back();
		playerDeck.push_back(shuffledDeck.back());
		shuffledDeck.pop_back();
		cout << "Blance:" << Money << endl;
		cout << "Bet Amount:";
		cin >> Bet;
		while (!(Bet <= Money && Bet > 0))
		{
			cout << "Incorrect Bet\n";
			cout << "Blance:" << Money << endl;
			cout << "Bet Amount:\n";
			cin >> Bet;
		}
		Money = Money - Bet;

		while (true)
		{
			cout << "Type \"h\" to Hit, \"s\" Stay or \"c\" to Check Cards:";
			cin >> input;
			if (input == 'h')
			{
				playerDeck.push_back(shuffledDeck.back());
				shuffledDeck.pop_back();
				if (playerDeck.back().Value == 11)
					cout << "Jack of ";
				if (playerDeck.back().Value == 12)
					cout << "Queen of ";
				if (playerDeck.back().Value == 13)
					cout << "King of ";

				if (playerDeck.back().Value < 11)
					cout << playerDeck.back().Value << " of ";


				if (playerDeck.back().Type == 1)
					cout << "Hearts\n";
				if (playerDeck.back().Type == 2)
					cout << "Diamonds\n";
				if (playerDeck.back().Type == 3)
					cout << "Clubs\n";
				if (playerDeck.back().Type == 4)
					cout << "Spades\n";

				if (CheckValue((playerDeck)) > 21)
				{
					cout << "BUST\n";
					break;
				}


			}
			if (input == 's')
			{
				if (CheckValue((dealerDeck)) <= 16)
				{
					dealerDeck.push_back(shuffledDeck.back());
					shuffledDeck.pop_back();
					if (CheckValue((dealerDeck)) > 21) {
						cout << "Dealer Over 21\n";
						break;
					}
				}

				if (CheckValue((dealerDeck)) > CheckValue(playerDeck))
				{
					cout << "Dealer Wins\n";
					break;
				}
				if (CheckValue((dealerDeck)) < CheckValue(playerDeck))
				{
					cout << "Player Wins\n";
					cout << "You win $" << (Bet * 0.5) << endl;
					Money = Money + (Bet * 0.5) + Bet;
					break;
				}
				if (CheckValue((dealerDeck)) == CheckValue(playerDeck))
				{
					cout << "Tie\n";
					Money = Money + Bet;
					break;
				}
			}
			if (input == 'c')
			{
				DisplayCards(playerDeck);
				if (CheckValue((playerDeck)) == 21)
				{
					cout << "BlackJack\n";
					cout << "You win $" << (Bet * 0.75) << endl;
					Money = Money + (Bet * 0.75) + Bet;
					break;
				}
			}
		}
	}
	return 0;
}



