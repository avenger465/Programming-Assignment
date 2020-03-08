#include <fstream>
#include <iostream>
using namespace std;

const int Size = 18;
void OpenFile(ifstream& infile, string text);
void ReadFile(ifstream &infile, char insertArray[Size]);
void OutputResults();
char wordsToFindArray[18];
char wordsToSearchArray[14];
bool wordsFound[6] = {false, false, false, false, false, false};
int wordIndex[6];

int main()
{
	bool found = false;
	int index = 0;
	string text1 = "search1.txt";
	string text2 = "text1.txt";
	ifstream searchText;
	OpenFile(searchText, text1);
	ifstream text;
	OpenFile(text, text2);
	ReadFile(searchText, wordsToFindArray);
	ReadFile(text, wordsToSearchArray);
	searchText.close();
	text.close();
	system("pause");
	//string type array;
	/*for (int i =0; i < sizeof(wordsToFindArray); i++)
	{
		cout << wordsToFindArray[i];
	}
	system("pause");*/

	for (int i = 0; i < sizeof(wordsToSearchArray); i++)
	{
		if (wordsToSearchArray[i] == wordsToFindArray[0])
		{
			if (wordsToSearchArray[i + 1] == wordsToFindArray[1])
			{
				if (wordsToSearchArray[i+2] == wordsToFindArray[2])
				{
					index = i;
					wordsFound[0] = true;
					wordIndex[0] = index;
				}
			}
		}
		else if (wordsToSearchArray[i] == wordsToFindArray[3])
		{
			if (wordsToSearchArray[i + 1] == wordsToFindArray[4])
			{
				if (wordsToSearchArray[i + 2] == wordsToFindArray[5])
				{
					index = i;
					wordsFound[1] = true;
					wordIndex[1] = index;
				}
			}
		}
		else if (wordsToSearchArray[i] == wordsToFindArray[6])
		{
			if (wordsToSearchArray[i + 1] == wordsToFindArray[7])
			{
				if (wordsToSearchArray[i + 2] == wordsToFindArray[8])
				{
					index = i;
					wordsFound[2] = true;
					wordIndex[2] = index;
				}
			}
		}
		else if (wordsToSearchArray[i] == wordsToFindArray[9])
		{
			if (wordsToSearchArray[i + 1] == wordsToFindArray[10])
			{
				if (wordsToSearchArray[i + 2] == wordsToFindArray[11])
				{
					index = i;
					wordsFound[3] = true;
					wordIndex[3] = index;
				}
			}
		}
		else if (wordsToSearchArray[i] == wordsToFindArray[12])
		{
			if (wordsToSearchArray[i + 1] == wordsToFindArray[13])
			{
				if (wordsToSearchArray[i + 2] == wordsToFindArray[14])
				{
					index = i;
					wordsFound[4] = true;
					wordIndex[4] = index;
				}
			}
		}
		else if (wordsToSearchArray[i] == wordsToFindArray[15])
		{
			if (wordsToSearchArray[i + 1] == wordsToFindArray[16])
			{
				if (wordsToSearchArray[i + 2] == wordsToFindArray[17])
				{
					index = i;
					wordsFound[5] = true;
					wordIndex[5] = index;
				}
			}
		}
	}
	OutputResults();
	system("pause");

}


void OpenFile(ifstream& infile, string text)
{
	infile.open(text);
	if (!infile)
	{
		cout << "ERROR: ";
		cout << "Can't open file";
	}
}

void ReadFile(ifstream &infile, char insertArray[Size])
{
	int i = 0;
	//infile >> noskipws;
	while (!infile.eof())
	{
		char ch;
		infile >> ch;
		if (!infile.eof())
		{
			insertArray[i] = ch;
			i++;
		}
	}
}
void OutputResults()
{
	int j = 0;
	for (int i = 0; i < sizeof(wordsToFindArray); i += 3)
	{
		if (wordsFound[j] == true)
		{
			cout << wordsToFindArray[i] << wordsToFindArray[i + 1] << wordsToFindArray[i + 2] << " Found at " << wordIndex[j] << endl;
			j++;
		}
		else
		{
			cout << wordsToFindArray[i] << wordsToFindArray[i + 1] << wordsToFindArray[i + 2] << " Not Found" << endl;
		}
		//cout << wordsFound[i] << "at" << wordIndex[i] << endl;
	}
}