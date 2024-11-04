#pragma once

#include <iostream>
#include <string>
#include "clsString.h"

class clsInputValidate
{
public:
	template <typename T>
	static T IsNumberBetween(T Number, T From, T To)
	{
		
		if (Number >= From && Number <= To)
			return true;
		else
			return false;

	}

	bool IsStringLengthBetween(string S1, int FromLength, int ToLength)
	{
		if (S1.length() < FromLength || S1.length() > ToLength)
		{
			return false;
		}
		return true;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//Date >= From && Date <= To
		if (clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)
			&&
			clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
		{
			return true;
		}

		//Date >= To && Date <= From
		if (clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)
			&&
			clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
		{
			return true;
		}

		return false;

	}

	
	template <typename T>
	static T ReadNumber(string ErrorMessage = "Invalid number, enter again\n")
	{
		T Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}

		return Number;

	}

	template <typename T>
	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Numer is not within range, enter again:\n")
	{
		T Number = ReadNumber<T>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>();
		}
		return Number;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string S1 = "";
		// Usage of std::ws will extract all the whitespace character
		getline(cin >> ws, S1);
		return S1;
	}
};

