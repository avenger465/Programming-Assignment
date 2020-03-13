#include <fstream>
#include <iostream>
using namespace std;

const int SizeofwordsToFindArray1D = 18;
const int SizeofwordsToSearchArray1D = 14;
const int SizeofwordsToFindArray2D = 48;
const int WordsToSearchArray2DRows = 4;
const int WordsToSearchArray2DColumns = 14;

void OpenFile(ifstream& infile, string text);
void ReadFile(ifstream &infile, char insertArray[]);
void ReadFile2D(ifstream &infile, char insertArray[WordsToSearchArray2DRows][WordsToSearchArray2DColumns]);
bool Menu();
void ReadInPuzzle1();
void ReadInPuzzle2();
void SearchPuzzle1();
void SearchPuzzle2();
void WriteToFile1();
void WriteToFile2();
void OutputSearch1();

char wordsToFindArray1D[SizeofwordsToFindArray1D];
char wordsToSearchArray1D[SizeofwordsToSearchArray1D];

char wordsToFindArray2D[SizeofwordsToFindArray2D];
char wordsToSearchArray2D[WordsToSearchArray2DRows][WordsToSearchArray2DColumns];


bool wordsFound[6] = {false, false, false, false, false, false};
int wordIndex[6];

int main()
{
	char answer;
	bool programLoop = true;
	bool found = false;
	int index = 0;
	while (programLoop)
	{
		if (Menu())
		{
			ReadInPuzzle1();
			SearchPuzzle1();
			OutputSearch1();
			WriteToFile1();
		}
		else
		{
			ReadInPuzzle2();
			SearchPuzzle2();
			WriteToFile2();
		}
		cout << "Restart(Y/N)? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			programLoop = true;
		}
		else if (answer == 'n' || answer == 'N')
		{
			programLoop = false;
		}

	}


	//system("pause");

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

void ReadFile(ifstream &infile, char insertArray[])
{
	int i = 0;
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

void ReadFile2D(ifstream &infile, char insertArray[WordsToSearchArray2DRows][WordsToSearchArray2DColumns])
{
	int i = 0;
	int j = 0;
	while (!infile.eof())
	{
		char ch;
		infile >> ch;
		if (!infile.eof())
		{
			if (j == 14)
			{
				i++;
				j = 0;
			}
			insertArray[i][j] = ch;
			j++;
		}
	}
}

bool Menu()
{
	cout << "What do you want to search" << endl << "1) Puzzle 1" << endl << "2) Puzzle 2  ";
	char answer;
	cin >> answer;
	if (answer == '1')
	{
		return true;
	}
	else if (answer == '2')
	{
		return false;
	}
}

void ReadInPuzzle1()
{
	string searchTextFile1D = "search1.txt";
	string scrambledText1D = "text1.txt";
	ifstream searchText1D;
	OpenFile(searchText1D, searchTextFile1D);
	ifstream text1D;
	OpenFile(text1D, scrambledText1D);
	ReadFile(searchText1D, wordsToFindArray1D);
	ReadFile(text1D, wordsToSearchArray1D);
	searchText1D.close();
	text1D.close();
}

void ReadInPuzzle2()
{
	string searchTextFile2D = "search2D.txt";
	string scrambledText2D = "text2D.txt";
	ifstream searchText2D;
	ifstream text2D;
	OpenFile(searchText2D, searchTextFile2D);
	OpenFile(text2D, scrambledText2D);
	ReadFile(searchText2D, wordsToFindArray2D);
	ReadFile2D(text2D, wordsToSearchArray2D);
	searchText2D.close();
	text2D.close();
}

void SearchPuzzle1()
{
	for (int i = 0; i < sizeof(wordsToSearchArray1D); i++)
	{
		for (int j = 0; j < sizeof(wordsToFindArray1D); j+=3)
		{
			if (wordsToSearchArray1D[i] == wordsToFindArray1D[j] && wordsToSearchArray1D[i +1] == wordsToFindArray1D[j +1]  && wordsToSearchArray1D[i+ 2] == wordsToFindArray1D[j + 2])
			{
				cout << wordsToFindArray1D[j] << wordsToFindArray1D[j+1] << wordsToFindArray1D[j+2] << " Found at " << i << endl;
				wordsToSearchArray1D[i] = '.';
				wordsToSearchArray1D[i+1] = '.';
				wordsToSearchArray1D[i+2] = '.';
			}
		}
	}
}

void OutputSearch1()
{
	int j = 0;
	for (int i = 0; i < 6; i++)
	{
		if (wordsFound[i] == true)
		{
			cout << wordsToFindArray1D[j] << wordsToFindArray1D[j + 1] << wordsToFindArray1D[j + 2] << " Found at " << wordIndex[i] << endl;
		}
		else
		{
			cout << wordsToFindArray1D[j] << wordsToFindArray1D[j + 1] << wordsToFindArray1D[j + 2] << " Not Found" << endl;
		}
		j += 3;
	}
}

void SearchPuzzle2()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			for (int k=0; k<sizeof(wordsToFindArray2D); k+=3)
			{
				if (wordsToSearchArray2D[i][j] == wordsToFindArray2D[k] && wordsToSearchArray2D[i][j + 1] == wordsToFindArray2D[k + 1] && wordsToSearchArray2D[i][j + 2] == wordsToFindArray2D[k + 2])
				{
					cout << wordsToSearchArray2D[i][j] << wordsToSearchArray2D[i][j + 1] << wordsToSearchArray2D[i][j + 2] << " Found, " << "line " << i << " location " << j  + 2<< endl;
					if (wordsToSearchArray2D[i][j] == 'c')
					{
						wordsToSearchArray2D[i+1][j + 2] = '.';
					}
					wordsToSearchArray2D[i][j] = '.';
					wordsToSearchArray2D[i][j + 1] = '.';
					wordsToSearchArray2D[i][j + 2] = '.';
				}
				else if ((wordsToSearchArray2D[i][j] == wordsToFindArray2D[k + 2] && wordsToSearchArray2D[i][j + 1] == wordsToFindArray2D[k + 1] && wordsToSearchArray2D[i][j + 2] == wordsToFindArray2D[k]) ||
						 (wordsToSearchArray2D[i][j] == wordsToFindArray2D[k + 2] && wordsToSearchArray2D[i][j + 2] == wordsToFindArray2D[k]))
				{
					
					cout << wordsToSearchArray2D[i][j + 2] << wordsToSearchArray2D[i][j + 1]  << wordsToSearchArray2D[i][j] << " Found, " << "line " << i << " location " << j + 2 << endl;
					if (wordsToSearchArray2D[i][j] == 't')
					{
						wordsToSearchArray2D[i][j + 2] = '.';
						wordsToSearchArray2D[i][j + 1] = '.';
					}
					if (wordsToSearchArray2D[i][j] == 't' && wordsToSearchArray2D[i + 1][j] == 'a' && wordsToSearchArray2D[i + 2][j] == 'b')
					{
						cout << wordsToSearchArray2D[i + 2][j] << wordsToSearchArray2D[i + 1][j] << wordsToSearchArray2D[i][j] << " Found, " << "line " << i + 2 << " location " << j << endl;
						wordsToSearchArray2D[i + 2][j] = '.';
						wordsToSearchArray2D[i + 1][j] = '.';
						wordsToSearchArray2D[i][j] = '.';
					}
					wordsToSearchArray2D[i][j + 2] = '.';
					wordsToSearchArray2D[i][j] = '.';
				}
				else if (wordsToSearchArray2D[i][j] == wordsToFindArray2D[k] && wordsToSearchArray2D[i + 1][j] == wordsToFindArray2D[k + 1] && wordsToSearchArray2D[i+ 2][j] == wordsToFindArray2D[k + 2])
				{
					cout << wordsToSearchArray2D[i][j] << wordsToSearchArray2D[i+1][j] << wordsToSearchArray2D[i+2][j] << " Found, " << "line " << i << " location " << j << endl;
					wordsToSearchArray2D[i][j] = '.';
					wordsToSearchArray2D[i+1][j] = '.';
					wordsToSearchArray2D[i+2][j] = '.';
				}
				else if (wordsToSearchArray2D[i][j] == wordsToFindArray2D[k] && wordsToSearchArray2D[i + 1][j - 1] == wordsToFindArray2D[k + 1] && wordsToSearchArray2D[i + 2][j - 2] == wordsToFindArray2D[k + 2])
				{
					wordsToSearchArray2D[i][j] = '.';
					wordsToSearchArray2D[i + 1][j - 1] = '.';
					wordsToSearchArray2D[i + 2][j - 2] = '.';
				}
			}
			
		}
	}
}

void WriteToFile1()
{
	ofstream outputToFile1("text1Filtered.txt");
	if (!outputToFile1)
	{
		cout << "Cannot open output file" << endl;
	}
	for (int i = 0; i < 14; i++)
	{
		outputToFile1 << wordsToSearchArray1D[i];
	}
	outputToFile1.close();
	cout << endl << "Successfully writen to text1Filtered.txt" << endl;
	system("pause");
}

void WriteToFile2()
{
	ofstream outputToFile2("text2Filtered.txt");
	if (!outputToFile2)
	{
		cout << "Cannot open output file" << endl;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			outputToFile2 << wordsToSearchArray2D[i][j];
		}
		outputToFile2 << endl;
	}
	outputToFile2.close();
	cout << endl << "Successfully writen to text2Filtered.txt" << endl;
	system("pause");
}