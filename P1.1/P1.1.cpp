#include <iostream>
using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Scissors };
enum enWinner { NoWinner = 1, User = 2, Computer = 3 };

struct stGameResults
{
	int round = 0, UserWin = 0, noWinner = 0, computerWin = 0;
};
struct stRoundInfo
{
	short RoundNumber = 0;
	short Player1Choice = 0;
	short ComputerChoice = 0;
	enWinner Winner;
	string WinnerName;
};
int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}
int ReadNumber1TO3()
{
	int num;
	cin >> num;
	while (num < 1 || num>3)
	{
		cout << "Enter number from 1 to 3 ?\n";
		cin >> num;
	}
	return num;

}

void ComputerChoice(stRoundInfo& RoundInfo)
{
	RoundInfo.ComputerChoice = RandomNumber(1, 3);
}

enWinner WhoWon(stRoundInfo& RoundInfo)
{

	if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice)
	{
		return enWinner::NoWinner;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
			return enWinner::Computer;
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;
	}

	return enWinner::User;

}
string WhatChoose(int Choose)
{
	if (Choose == enGameChoice::Paper)
		return "Paper";
	else if (Choose == enGameChoice::Scissors)
		return "Scissors";
	else
		return "Stone";
}
string WinnerName(int WinnerName)
{
	switch (WinnerName)
	{
	case enWinner::Computer:
		return "Computer";
	case enWinner::NoWinner:
		return "No Winner";
	case enWinner::User:
		return "Player 1";

	}


}


void PrintColor(enWinner winner)
{
	if (winner == enWinner::NoWinner)
	{
		system("color 6F");

	}
	else if (winner == enWinner::User)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << "\a";
	}
}
void PrintWinnerInBox(stRoundInfo RoundInfo)
{
	PrintColor(RoundInfo.Winner);
	cout << "____________________Round : " << RoundInfo.RoundNumber << "____________________\n";
	cout << "Player choice : " << WhatChoose(RoundInfo.Player1Choice) << endl;
	cout << "Computer choice :" << WhatChoose(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner\t : [" << WinnerName(RoundInfo.Winner) << "]" << endl;
	cout << "__________________________________________________\n\n\n";
}
void Player1Choice(stRoundInfo& RoundInfo)
{
	cout << "Your choice :  [1]:Stone, [2]Paper, [3]:Scissors ?\n";
	RoundInfo.Player1Choice = ReadNumber1TO3();
}
void WinCounter(stGameResults& GameResults, int WhoWon)
{
	if (WhoWon == enWinner::NoWinner)
		GameResults.noWinner++;
	else if (WhoWon == enWinner::User)
		GameResults.UserWin++;
	else
		GameResults.computerWin++;
}
void Rounds(stGameResults& GameResults)
{
	stRoundInfo RoundInfo;
	GameResults.round++;
	RoundInfo.RoundNumber = GameResults.round;
	Player1Choice(RoundInfo);
	ComputerChoice(RoundInfo);
	RoundInfo.Winner = (WhoWon(RoundInfo));
	PrintWinnerInBox(RoundInfo);
	WinCounter(GameResults, RoundInfo.Winner);

}
int HowManyRounds()
{
	cout << "How many rounds ? ";
	int HowMany;
	cin >> HowMany;
	return HowMany;
}
string FinalWinner(stGameResults GameResults)
{
	if (GameResults.computerWin > GameResults.UserWin)
	{
		PrintColor(enWinner::Computer);
		return "Computer";
	}
	else if (GameResults.UserWin > GameResults.computerWin)
	{
		PrintColor(enWinner::User);
		return "User";
	}
	else if (GameResults.UserWin == GameResults.computerWin)
	{
		PrintColor(enWinner::NoWinner);
		return "No Winner";
	}

}
void FinalBox(stGameResults& GameResults)
{
	cout << "                  _______________________________________________________________\n\n";
	cout << "                                            G a m e  O v e r                       \n";
	cout << "                  _______________________________________________________________\n\n";
	cout << "                  _________________________ [Game Results ]______________________\n\n";
	cout << "                  Game Rounds        : " << GameResults.round << endl;
	cout << "                  Player won times   : " << GameResults.UserWin << endl;
	cout << "                  Computer won times : " << GameResults.computerWin << endl;
	cout << "                  Draw times         : " << GameResults.noWinner << endl;
	cout << "                  FinalWinner        : " << FinalWinner(GameResults) << endl;
	cout << "                  _______________________________________________________________\n\n";

}
void Game()
{
	stGameResults GameResults;
	int repetition = HowManyRounds();
	for (int i = 0; i < repetition; i++)
	{
		Rounds(GameResults);
	}
	FinalBox(GameResults);

}
void CleanSreen()
{
	system("cls");
	system("color f");
}
void StartGame()
{
	char playAgain;
	do
	{
		CleanSreen();
		Game();
		std::cout << "Do you went play agatin if yes enter y ? \n";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}
