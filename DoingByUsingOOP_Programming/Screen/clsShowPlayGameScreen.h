#pragma once
#include "clsScreen.h"
#include "clsStonePaperScissorGame.h"

class clsShowPlayGameScreen : protected clsScreen
{
private:

	static short ReadHowmanyRounds()
	{

		short GameRounds = 0;

		cout << "\nHow many rounds do you want to play from 1 to 10 ? ";
		GameRounds = clsInputValidate::ReadNumberBetween(1, 10, "\nHow many rounds do you want to play from 1 to 10 ? ");

		return GameRounds;

	}

	static clsStonePaperScissorGame::enGameChoice ReadPlayer1Choice()
	{
		short Choice;

		cout << "\nYour choise [1]:Stone, [2]:Paper, [3]:Scissor ? ";
		Choice = clsInputValidate::ReadNumberBetween(1, 3, "\nYour choise [1]:Stone, [2]:Paper, [3]:Scissor ? ");

		return (clsStonePaperScissorGame::enGameChoice)Choice;
	}

	static void _PrintRoundResults(clsStonePaperScissorGame StonePaperScissorGame)
	{
		cout << "\n______________Round [" << StonePaperScissorGame.RoundInfo.RoundNumber << "] _________\n";
		cout << "\nPlayer1 choice : " << clsStonePaperScissorGame::ChoiceName(StonePaperScissorGame.RoundInfo.Player1Choice);
		cout << "\nComputer choice: " << clsStonePaperScissorGame::ChoiceName(StonePaperScissorGame.RoundInfo.ComputerChoice);
		cout << "\nround Winner   : " << clsStonePaperScissorGame::WinnerName(StonePaperScissorGame.RoundInfo.RoundWinner);
		cout << "\n_________________________________\n\n";

		clsStonePaperScissorGame::SetWinnerScreenColor(StonePaperScissorGame.RoundInfo.RoundWinner);
	}

	static void _PlayRound(clsStonePaperScissorGame& StonePaperScissorGame, short RoundNumber)
	{

		cout << "\nRound [" << RoundNumber << "] begins: \n";
		StonePaperScissorGame.RoundInfo.RoundNumber = RoundNumber;
		ReadPlayer1Choice();
		StonePaperScissorGame.GetComputerChoice();
		StonePaperScissorGame.WhoWonTheRound();

		//Increase win/Draw counters
		StonePaperScissorGame.IncreaseWinDrawCounters();

		_PrintRoundResults(StonePaperScissorGame);

	}

	static void _PlayGame(clsStonePaperScissorGame& StonePaperScissorGame)
	{

		for (short GameRounds = 1; GameRounds <= StonePaperScissorGame.GameRounds; GameRounds++)
		{
			_PlayRound(StonePaperScissorGame, GameRounds);
		}

	}

	static void showGameOverScreen()
	{
		cout << clsUitil::Tabs(2) << "______________________________________________\n\n";
		cout << clsUitil::Tabs(2) << "          +++ G a m e  O v e r +++\n";
		cout << clsUitil::Tabs(2) << "______________________________________________\n\n";
	}

	static void ShowFinalGameResults(clsStonePaperScissorGame StonePaperScissorGame)
	{

		showGameOverScreen();

		cout << clsUitil::Tabs(2) << "___________________ [ Game results ] _______________________\n" << endl;
		cout << clsUitil::Tabs(2) << "Player1 Winner Times : " << StonePaperScissorGame.Player1WinTimes << "\n";
		cout << clsUitil::Tabs(2) << "Computer Winner Times: " << StonePaperScissorGame.ComputerWinTimes << "\n";
		cout << clsUitil::Tabs(2) << "Draw Times           : " << StonePaperScissorGame.DrawTimes << "\n";
		cout << clsUitil::Tabs(2) << "End Winner           : " << clsStonePaperScissorGame::WinnerName(StonePaperScissorGame.GameWinner) << "\n";
		cout << clsUitil::Tabs(2) << "____________________________________________________________\n" << endl;

		clsStonePaperScissorGame::SetWinnerScreenColor(StonePaperScissorGame.GameWinner);
	}

	static void _StartGame()
	{

		char PlayAgain = 'Y';
		do
		{
			clsStonePaperScissorGame::ResetScreen();
			clsScreen::_DrawHeader("\t   Play Game Screen");


			clsStonePaperScissorGame StonePaperScissorGame(ReadHowmanyRounds());
			_PlayGame(StonePaperScissorGame);

			StonePaperScissorGame.WhoWonTheGame();
			ShowFinalGameResults(StonePaperScissorGame);

			cout << endl << clsUitil::Tabs(2) << "Do you want to play again ? Y/N ? ";
			cin >> PlayAgain;

		} while (PlayAgain == 'Y' || PlayAgain == 'y');

	}

public:

	static void showPlayGameScreen()
	{

		_StartGame();

	}

};

