#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
	string _Value;

public:

	clsString()
	{
		_Value = "";
	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}

	string GetValue()
	{
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	}

	short Length()
	{
		return _Value.length();
	}

	static string UpperFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = toupper(S1[i]);
			}

			IsFirstLetter = ((S1[i] == ' ' ? true : false));
		}
		return S1;
	}

	void UpperFirstLetterOfEachWord()
	{
		//no need to return value, this function will directly update the object value
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = tolower(S1[i]);
			}

			IsFirstLetter = ((S1[i] == ' ' ? true : false));
		}
		return S1;
	}

	void LowerFirstLetterOfEachWord()
	{
		//no need to return value, this function will directly update the object value
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string S1)
	{

		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}
		return S1;
	}

	void UpperAllString()
	{
		//no need to return value, this function will directly update the object value
		_Value = UpperAllString(_Value);
	}

	static string LowerAllString(string S1)
	{

		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}

	void LowerAllString()
	{
		//no need to return value, this function will directly update the object value
		_Value = LowerAllString(_Value);
	}

	static char InvertLetterCase(char C1)
	{
		// using short Hand If
		return isupper(C1) ? tolower(C1) : toupper(C1);
	}

	static string InvertAllStringLettersCase(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = InvertLetterCase(S1[i]);
		}
		return S1;
	}

	void InvertAllStringLettersCase()
	{
		//no need to return value, this function will directly update the object value
		_Value = InvertAllStringLettersCase(_Value);
	}

	enum enWhatToCount { SmallLetters = 0, CapitlLetters = 1, PunctuationMarks = 2, space = 3, All = 4 };

	static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
	{

		if (WhatToCount == enWhatToCount::All)
		{
			return S1.length();
		}

		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{

			if (WhatToCount == enWhatToCount::CapitlLetters && isupper(S1[i]))
			{
				Counter++;
			}
			else if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
			{
				Counter++;
			}
			else if (WhatToCount == enWhatToCount::PunctuationMarks && ispunct(S1[i]))
			{
				Counter++;
			}
			else if (WhatToCount == enWhatToCount::space && isspace(S1[i]))
			{
				Counter++;
			}
		}
		return Counter;
	}

	static short CountCapitlLetters(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{

			if (isupper(S1[i]))
				Counter++;

		}
		return Counter;
	}

	short CountCapitlLetters()
	{
		return CountCapitlLetters(_Value);
	}

	static short CountSmallLetters(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{

			if (islower(S1[i]))
				Counter++;

		}
		return Counter;
	}

	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short CountPunctuationMarks(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{

			if (ispunct(S1[i]))
				Counter++;

		}
		return Counter;
	}

	short CountPunctuationMarks()
	{
		return CountPunctuationMarks(_Value);
	}

	static short CountSpace(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{

			if (isspace(S1[i]))
				Counter++;

		}
		return Counter;
	}

	short CountSpace()
	{
		return CountSpace(_Value);
	}

	static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}

		}
		return Counter;
	}

	short CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Letter)
	{
		Letter = tolower(Letter);
		return ((Letter == 'a') || (Letter == 'e') || (Letter == 'o') || (Letter == 'u') || (Letter == 'i'));
	}

	static short CountVowels(string S1)
	{
		short Counter = 0;

		for (int i = 0; i < S1.length(); i++)
		{

			if (IsVowel(S1[i]))
				Counter++;

		}

		return Counter;
	}

	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static void PrintVowels(string S1)
	{

		cout << "\nVowels in string  are: ";
		for (int i = 0; i < S1.length(); i++)
		{

			if (IsVowel(S1[i]))
				cout << S1[i] << "   ";

		}
	}

	void PrintVowels()
	{
		return PrintVowels(_Value);
	}

	static void PrintEachWordInString(string S1)
	{
		string delim = " "; // delimiter

		cout << "\nYour string words are: \n\n";
		short Pos = 0;
		string sWord; // define a string variable

		// use find() function to get the position of the delimiter
		while ((Pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, Pos); // store the word
			if (sWord != "")
			{
				cout << sWord << endl;
			}

			S1.erase(0, Pos + delim.length()); // erase() until position and move to next word.
		}

		if (S1 != "")
		{
			cout << S1 << endl; // it print last word of the string
		}
	}

	void PrintEachWordInString()
	{
		return PrintEachWordInString(_Value);
	}

	static short CountWords(string S1)
	{
		string delim = " "; // delimiter

		short Pos = 0;
		string sWord; // define a string variable
		short Counter = 0;

		// use find() function to get the position of the delimiter
		while ((Pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, Pos); // store the word
			if (sWord != "")
			{
				Counter++;
			}

			S1.erase(0, Pos + delim.length()); // erase() until position and move to next word.
		}

		if (S1 != "")
		{
			Counter++; // it Count last word of the string
		}

		return Counter;
	}

	short CountWords()
	{
		return CountWords(_Value);
	}

	static vector<string> Split(string S1, string delimiter = " ")
	{
		vector<string> vString;

		short Pos = 0;
		string sWord; // define a string variable

		// use find() function to get the position of the delimiter
		while ((Pos = S1.find(delimiter)) != std::string::npos)
		{
			sWord = S1.substr(0, Pos); // store the word
			if (sWord != "")
			{
				vString.push_back(sWord);
			}

			S1.erase(0, Pos + delimiter.length()); // erase() until position and move to next word.
		}

		if (S1 != "")
		{
			vString.push_back(S1);// it push last word of the string
		}

		return vString;

	}

	vector<string> Split(string delimiter = " ")
	{
		return Split(_Value, delimiter);
	}

	static string TrimLeft(string S1)
	{

		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - 1);// storage the remiander string after trim left
			}
		}
		return "";
	}

	string TrimLeft()
	{
		return TrimLeft(_Value);
	}

	static string TrimRight(string S1)
	{

		for (short i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);// storage the remiander string after trim right
			}
		}
		return "";
	}

	string TrimRight()
	{
		return TrimRight(_Value);
	}

	static string Trim(string S1)
	{
		return (TrimRight(TrimLeft(S1)));
	}

	string Trim()
	{
		return Trim(_Value);
	}

	static string JoinString(vector<string>& vString, string delimiter = " ")
	{
		string S1 = "";

		for (string& s : vString)
		{
			S1 = S1 + s + delimiter;
		}

		return S1.substr(0, S1.length() - delimiter.length());
	}

	static string JoinString(string arrString[], short arrLength, string delimiter = " ")
	{
		string S1 = "";

		for (int i = 0; i < arrLength; i++)
		{
			S1 = S1 + arrString[i] + delimiter;
		}

		return S1.substr(0, S1.length() - delimiter.length());
	}

	static string ReverseWordsInString(string S1)
	{

		vector<string> vString;

		vString = Split(S1, " ");
		string S2 = "";

		vector<string>::iterator  iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;

			S2 += *iter + " ";

		}

		S2 = S2.substr(0, S2.length() - 1);

		return S2;

	}

	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

	static string ReplaceWord(string S1, string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		vector<string> vString = Split(S1, " ");
		for (string& s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = sReplaceTo;
				}
			}
			else
			{
				if (LowerAllString(s) == LowerAllString(StringToReplace))
				{
					s = sReplaceTo;
				}
			}
		}

		return JoinString(vString, " ");
	}

	string ReplaceWord(string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		return ReplaceWord(_Value, StringToReplace, sReplaceTo, MatchCase);
	}

	static string RemovePunctuations(string S1)
	{

		string S2 = "";

		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}

		return S2;
	}

	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}


};