#pragma once

#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsUitil
{

public:

	enum enCharType {
		SamallLetter = 1, CapitalLetter = 2, Digit = 3,
		MixChars = 4, SepcialCharcter = 5
	};

	static void Srand()
	{
		//Seeds the random number generator in C++, called only once
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		//Function to generate a random number
		int randNum = rand() % (To - From + 1) + From;
		return randNum;
	}

	static char GetRandomCharcter(enCharType CharType)
	{
		//update this method to accept mixchars
		if (CharType == enCharType::MixChars)
		{
			//Capital/Samll/Digits only
			CharType = (enCharType)RandomNumber(1, 3);
		}

		switch (CharType)
		{
		case enCharType::SamallLetter:
		{
			return char(RandomNumber(97, 122));
			break;
		}
		case enCharType::CapitalLetter:
		{
			return char(RandomNumber(65, 90));
			break;
		}
		case enCharType::Digit:
		{
			return char(RandomNumber(48, 57));
			break;
		}
		case enCharType::SepcialCharcter:
		{
			return char(RandomNumber(33, 47));
			break;
		}
		}

	}

	static string GenerateWord(enCharType CharType, short Length)
	{
		string Word = "";

		for (int i = 1; i <= Length; i++)
		{
			Word = Word + GetRandomCharcter(CharType);
		}
		return Word;
	}

	static string GenerateKey(enCharType CharType)
	{
		string Key = "";

		Key = GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4);

		return Key;
	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{
		for (int i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Key [" << i << "] ";
			cout << GenerateKey(CharType) << endl;
		}
	}

	static void FillArrayWithRandomNumbers(int arr[], int arrLength, int RandNumFrom, int RandNumTo)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = RandomNumber(RandNumFrom, RandNumTo);
	}

	static void FillArrayWithRandomWrods(string arr[], int arrLength, enCharType CharType, int WordLength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, WordLength);
	}

	static void FillArrayWithRandomKeys(string arr[], int arrLength, enCharType CharType)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}

	template <typename T>
	static void Swap(T& A, T& B)
	{
		T Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate::SwapDates(Date1, Date2);
	}

	static void ShuffleArray(int arr[], int arrLength)
	{
		for (int i = 0; i <= arrLength - 1; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void ShuffleArray(string arr[], int arrLength)
	{
		for (int i = 0; i <= arrLength - 1; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static string Tabs(short NumberOfTabs)
	{
		string t = "";

		for (short i = 1; i < NumberOfTabs; i++)
		{
			t = t + "\t ";
			cout << t;
		}
		return t;
	}

	static string EncryptText(string Text, short EncryptionKey=2)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey=2)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - EncryptionKey);
		}
		return Text;
	}

	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "",
				"One", "Two", "Three", "Four", "Five", "Six", "Seven",
					"Eight", "Nine", "Ten", "ELeven", "Twelve", "Thirteen", "Fourteen",
					   "Fifteen", "Sixteen",  "Seventeen", "Eighteen", "Nineteen" };

			return arr[Number];
		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return NumberToText(Number / 100) + " Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + " Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + " Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return NumberToText(Number % 1000000000) + " Billions " + NumberToText(Number % 1000000000);
		}
	}

};