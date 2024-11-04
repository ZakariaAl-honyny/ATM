#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsShowPlayGameScreen.h"
#include "clsInputValidate.h"
#include "clsUitil.h"

class clsShowMainMenueGameScreen : protected clsScreen
{
private:
	enum enMainMenueScreenOptions {ePlayGame = 1, eExit = 2};

	static short _ReadMainMenueGameScreenOptions()
	{
		short Choice = 0;
		cout << clsUitil::Tabs(3) << "What do you want to do? choose [1 - 2] ? ";
		Choice = clsInputValidate::ReadNumberBetween(1, 2, "\n\t\t\t\t\t What do you want to do? choose [1 - 2] ? ");

		return Choice;
	}

	static void _GoBackToMainMenueGameScreen()
	{
		cout << "\n\n\tPress any key to go back to main game screen...";
		system("pause>0");
		ShowMainMenueGameScreen();
	}

	static void _ShowPlayGameScreen()
	{
		//cout << "\nShow Play Game Screen Will be here soon...\n";
		clsShowPlayGameScreen::showPlayGameScreen();
	}

	static void _Exit()
	{

		cout << "\n!!You are outside the system :-(!!\n";
		cout << "\n\nPress any key to close this windows...";

	}

	static void _PerformMainMenueGameScreenOptions(enMainMenueScreenOptions MainMenueScreenOptions)
	{
		switch (MainMenueScreenOptions)
		{

		case clsShowMainMenueGameScreen::ePlayGame:
		{
			clsStonePaperScissorGame::ResetScreen();
			_ShowPlayGameScreen();
			_GoBackToMainMenueGameScreen();
			break;
		}

		case clsShowMainMenueGameScreen::eExit:
		{
			clsStonePaperScissorGame::ResetScreen();
			_Exit();
			break;
		}
		
		}
	}

public:

	static void ShowMainMenueGameScreen()
	{
		clsStonePaperScissorGame::ResetScreen(); 
		clsScreen::_DrawHeader("\tStone Paper Scissor Game");

		cout << clsUitil::Tabs(3) << "\t----------------------\n";
		cout << clsUitil::Tabs(3) << "\t 1 |   Play Game Now |\n";
		cout << clsUitil::Tabs(3) << "\t----------------------\n\n";
									  
		cout << clsUitil::Tabs(3) << "\t    --------------\n";
		cout << clsUitil::Tabs(3) << "\t     2 |  Exit  |\n";
		cout << clsUitil::Tabs(3) << "\t    --------------\n\n";

		_PerformMainMenueGameScreenOptions((enMainMenueScreenOptions)_ReadMainMenueGameScreenOptions());
	}
	
};

