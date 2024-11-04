#pragma once
#include <iostream>
#include <string>
#include "clsUitil.h"
#include "clsInputValidate.h"
using namespace std;

class clsStonePaperScissorGame
{
private:

	enum enGameChoice;
	enum enWinner;

	short _GameRounds = 0;
	short _Player1WinTimes = 0;
	short _ComputerWinTimes = 0;
	short _DrawTimes = 0;
	enWinner _GameWinner;

	struct clsRoundInfo
	{

		short RoundNumber = 0;
		enGameChoice Player1Choice = enGameChoice::Stone;
		enGameChoice ComputerChoice = enGameChoice::Stone;
		enWinner RoundWinner = enWinner::Draw;

	};

public:

	enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
	enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

	clsRoundInfo RoundInfo;

	clsStonePaperScissorGame(short GameRounds)
	{

		_GameRounds = GameRounds;
		_Player1WinTimes = 0;
		_ComputerWinTimes = 0;
		_DrawTimes = 0;
		_GameWinner = enWinner::Draw;

	}

	~clsStonePaperScissorGame()
	{

	}

	void SetGameRounds(short GameRounds)
	{
		_GameRounds = GameRounds;
	}

	short GetGameRounds()
	{
		return _GameRounds;
	}

	__declspec(property(get = GetGameRounds, put = SetGameRounds)) short GameRounds;

	void SetPlayer1WinTimes(short Player1WinTimes)
	{
		_Player1WinTimes = Player1WinTimes;
	}

	short GetPlayer1WinTimes()
	{
		return _Player1WinTimes;
	}

	__declspec(property(get = GetPlayer1WinTimes, put = SetPlayer1WinTimes)) short Player1WinTimes;

	void SetComputerWinTimes(short ComputerWinTimes)
	{
		_ComputerWinTimes = ComputerWinTimes;
	}

	short GetComputerWinTimes()
	{
		return _ComputerWinTimes;
	}

	__declspec(property(get = GetComputerWinTimes, put = SetComputerWinTimes)) short ComputerWinTimes;

	void SetDrawTimes(short DrawTimes)
	{
		_DrawTimes = DrawTimes;
	}

	short GetDrawTimes()
	{
		return _DrawTimes;
	}

	__declspec(property(get = GetDrawTimes, put = SetDrawTimes)) short DrawTimes;

	void SetGameWinner(enWinner GameWinner)
	{
		_GameWinner = GameWinner;
	}

	enWinner GetGameWinner()
	{
		return _GameWinner;
	}

	__declspec(property(get = GetGameWinner, put = SetGameWinner)) enWinner GameWinner;

	static string ChoiceName(enGameChoice Choice)
	{
		string arrGameChoises[3] = { "Stone", "Paper", "Scissor" };
		return arrGameChoises[Choice - 1];
	}

	static string WinnerName(enWinner Winner)
	{
		string Choises[3] = { "Player1", "Computer", "[No Winner]" };
		return Choises[Winner - 1];
	}

	

	void GetComputerChoice()
	{
		RoundInfo.ComputerChoice = (enGameChoice)clsUitil::RandomNumber(1, 3);
	}

	void WhoWonTheRound()
	{

		if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		{
			RoundInfo.RoundWinner = enWinner::Draw;
			return;
		}

		switch (RoundInfo.Player1Choice)
		{
		case enGameChoice::Stone:
		{

			if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			{
				RoundInfo.RoundWinner = enWinner::Computer;
				return;
			}

			break;
		}
		case enGameChoice::Paper:
		{

			if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
			{
				RoundInfo.RoundWinner = enWinner::Computer;
				return;
			}

			break;
		}
		case enGameChoice::Scissor:
		{

			if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			{
				RoundInfo.RoundWinner = enWinner::Computer;
				return;
			}

			break;
		}

		}

		//if you reach here then player1 is the winner
		RoundInfo.RoundWinner = enWinner::Player1;

	}

	static void SetWinnerScreenColor(enWinner Winner)
	{
		switch (Winner)
		{
		case enWinner::Player1:
			system("color 2F");// turn screen to green
			break;
		case enWinner::Computer:
			system("color 4F");// turn screen to red
			cout << "\a";
			break;
		case enWinner::Draw:
			system("color 6F");// turn screen to yellow
			break;
		}
	}

	void IncreaseWinDrawCounters()
	{
		//Increase win/Draw counters
		if (RoundInfo.RoundWinner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
	}

	void WhoWonTheGame()
	{
		if (Player1WinTimes > ComputerWinTimes)
			GameWinner = enWinner::Player1;
		else if (ComputerWinTimes > Player1WinTimes)
			GameWinner = enWinner::Computer;
		else
			GameWinner = enWinner::Draw;
	}

	static void ResetScreen()
	{
		system("cls"); // Clear Screen
		system("color 0F"); // turn screen to black color
	}

};