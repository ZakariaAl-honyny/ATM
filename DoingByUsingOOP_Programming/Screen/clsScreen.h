#pragma once
#include <iostream>
#include "clsUitil.h"
using namespace std;

class clsScreen
{

protected:

	static void _DrawHeader(string Title, string SubTitle = "")
	{
		cout << clsUitil::Tabs(3) <<"___________________________________\n\n";
		cout << clsUitil::Tabs(3) << Title << "\n";
		

		if (SubTitle != "")
		{
			cout << clsUitil::Tabs(3) << SubTitle << "\n";
		}

		cout << clsUitil::Tabs(3) << "___________________________________\n\n";
	}

};

