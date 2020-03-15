//Calling the libraries to be used in the program
#include <fstream>
#include <iostream>
using namespace std;

//Variables that will define the variable sizes
const int SizeofwordsToFindArray1D = 18;
const int SizeofwordsToSearchArray1D = 14;
const int SizeofwordsToFindArray2D = 48;
const int WordsToSearchArray2DRows = 4;
const int WordsToSearchArray2DColumns = 14;

//Function prototype calls 
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

//definitions of the arrays used for the 1D puzzle
char wordsToFindArray1D[SizeofwordsToFindArray1D];
char wordsToSearchArray1D[SizeofwordsToSearchArray1D];

//definitions of the arrays used for the 2D puzzle
char wordsToFindArray2D[SizeofwordsToFindArray2D];
char wordsToSearchArray2D[WordsToSearchArray2DRows][WordsToSearchArray2DColumns];


bool wordsFound[6] = {false, false, false, false, false, false};
int wordIndex[6];

//The main function used in the program 
int main()
{
	//declarations of variables to be used in the program
	char goThroughLoopChar;
	bool programLoop = true;
	bool found = false;
	int index = 0;

	//Loop to go through the program and ask the user which puzzle they want to do.
	//The program will then go through the puzzle inputed and perform the search
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
		cin >> goThroughLoopChar;
		if (goThroughLoopChar == 'y' || goThroughLoopChar == 'Y')
		{
			programLoop = true;
		}
		else if (goThroughLoopChar == 'n' || goThroughLoopChar == 'N')
		{
			programLoop = false;
		}

	}
}

//Function to open files and perform a check for any errors while opening the files
void OpenFile(ifstream& infile, string text)
{
	//Opens the file 
	infile.open(text);

	//Checks if the file could not be opened
	if (!infile)
	{
		cout << "ERROR: ";
		cout << "Can't open file";
	}
}

//Function to read in the data from the files used in 1D arrays
void ReadFile(ifstream &infile, char insertArray[])
{
	//Initiales the index of the array being read into
	int arrayIndex = 0;

	//Reads in each character from the file and puts that character in the current index
	//while the end of the file has not been reached
	while (!infile.eof())
	{

		char ch;
		infile >> ch;
		if (!infile.eof())
		{
			insertArray[arrayIndex] = ch;
			arrayIndex++;
		}
	}
}

//Function to read in the data from the files used in the 2D arrays
void ReadFile2D(ifstream &infile, char insertArray[WordsToSearchArray2DRows][WordsToSearchArray2DColumns])
{
	//Initiales the indexes of the array being read into
	int arrayRow = 0;
	int arrayColumn = 0;

	//Reads in each character from the file and puts that character in the current index 
	//while the end of the file has not been reached
	while (!infile.eof())
	{
		char ch;
		infile >> ch;
		if (!infile.eof())
		{

			//Checks if the end of the current row in the array has been reached
			//and then resets the column index back to zero
			if (arrayColumn == 14)
			{
				arrayRow++;
				arrayColumn = 0;
			}
			insertArray[arrayRow][arrayColumn] = ch;
			arrayColumn++;
		}
	}
}

//Function to display the main menu to the user and provide an input method for the user
bool Menu()
{
	//Initiales the variable to be used for the users input
	char choosePuzzle;

	//Displays a prompt for the user to answer and reads in that input
	cout << "What do you want to search" << endl << "1) Puzzle 1" << endl << "2) Puzzle 2  ";
	cin >> choosePuzzle;

	//Returns the required value depending on the users input
	if (choosePuzzle == '1')
	{
		return true;
	}
	else if (choosePuzzle == '2')
	{
		return false;
	}
}

//Function to read in the required files into their respective arrays
void ReadInPuzzle1()
{
	//Initiales the required filenames
	string searchTextFile1D = "search1.txt";
	string scrambledText1D = "text1.txt";
	ifstream searchText1D;
	ifstream text1D;

	//Calls the OpenFile function to open the required files and to check if they can be opened
	OpenFile(searchText1D, searchTextFile1D);
	OpenFile(text1D, scrambledText1D);

	//Calls the ReadFile function to read the files into their respective arrays
	ReadFile(searchText1D, wordsToFindArray1D);
	ReadFile(text1D, wordsToSearchArray1D);

	//Closes the files to reduce the number of errors that can occur
	searchText1D.close();
	text1D.close();
}

//Function to read in the required files into their respective arrays
void ReadInPuzzle2()
{
	//Initiales the required filenames
	string searchTextFile2D = "search2D.txt";
	string scrambledText2D = "text2D.txt";
	ifstream searchText2D;
	ifstream text2D;

	//Calls the OpenFile function to open the required files and to check if they can be opened
	OpenFile(searchText2D, searchTextFile2D);
	OpenFile(text2D, scrambledText2D);

	//Calls the ReadFile function to read the files into their respective arrays
	ReadFile(searchText2D, wordsToFindArray2D);
	ReadFile2D(text2D, wordsToSearchArray2D);

	//Closes the files to reduce the number of errors that can occur
	searchText2D.close();
	text2D.close();
}

//Function to search through the puzzle array looking for the words
void SearchPuzzle1()
{
	// goes through each character in the wordsToSearchArray1D and checks if it is equal to 
	// the search term
	for (int i = 0; i < sizeof(wordsToSearchArray1D); i++)
	{
		for (int j = 0; j < sizeof(wordsToFindArray1D); j+=3)
		{
			if (wordsToSearchArray1D[i] == wordsToFindArray1D[j] && wordsToSearchArray1D[i +1] == wordsToFindArray1D[j +1]  && wordsToSearchArray1D[i+ 2] == wordsToFindArray1D[j + 2])
			{
				//Outputs that the word has been found and replaces its characters with fullstops: '.', in the array
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
				//Check for words going forward
				if (wordsToSearchArray2D[i][j] == wordsToFindArray2D[k] && wordsToSearchArray2D[i][j + 1] == wordsToFindArray2D[k + 1] && wordsToSearchArray2D[i][j + 2] == wordsToFindArray2D[k + 2])
				{
					cout << wordsToSearchArray2D[i][j] << wordsToSearchArray2D[i][j + 1] << wordsToSearchArray2D[i][j + 2] << " Found, " << "line " << i << " location " << j  + 2<< endl;
					/*if (wordsToSearchArray2D[i][j] == 'c')
					{
						wordsToSearchArray2D[i+1][j + 2] = '.';
					}*/
					wordsToSearchArray2D[i][j] = '.';
					wordsToSearchArray2D[i][j + 1] = '.';
					wordsToSearchArray2D[i][j + 2] = '.';
				}
				//Check for words going backward
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
						wordsToSearchArray2D[i][j] = '.';
						wordsToSearchArray2D[i + 1][j] = '.';
						wordsToSearchArray2D[i + 2][j] = '.';
					}
					wordsToSearchArray2D[i][j + 2] = '.';
					wordsToSearchArray2D[i][j] = '.';
				}
				//Check for words going vertical
				else if (wordsToSearchArray2D[i][j] == wordsToFindArray2D[k] && wordsToSearchArray2D[i + 1][j] == wordsToFindArray2D[k + 1] && wordsToSearchArray2D[i+ 2][j] == wordsToFindArray2D[k + 2])
				{
					cout << wordsToSearchArray2D[i][j] << wordsToSearchArray2D[i+1][j] << wordsToSearchArray2D[i+2][j] << " Found, " << "line " << i << " location " << j << endl;
					wordsToSearchArray2D[i][j] = '.';
					wordsToSearchArray2D[i+1][j] = '.';
					wordsToSearchArray2D[i+2][j] = '.';
				}
				//check for words going diagonal left
				else if (wordsToSearchArray2D[i][j] == wordsToFindArray2D[k] && wordsToSearchArray2D[i + 1][j - 1] == wordsToFindArray2D[k + 1] && wordsToSearchArray2D[i + 2][j - 2] == wordsToFindArray2D[k + 2])
				{
					cout << wordsToSearchArray2D[i][j] << wordsToSearchArray2D[i + 1][j - 1] << wordsToSearchArray2D[i + 2][j - 2] << " Found, " << "line " << i << " location " << j << endl;
					wordsToSearchArray2D[i][j] = '.';
					wordsToSearchArray2D[i + 1][j - 1] = '.';
					wordsToSearchArray2D[i + 2][j - 2] = '.';
				}
			}
			
		}
	}
}

//Function to write the updated array into the 'text1Filtered.txt' file.
void WriteToFile1()
{
	//Opens the file to be written into and performs a check whether the file could be opened
	ofstream outputToFile1("text1Filtered.txt");
	if (!outputToFile1)
	{
		cout << "Cannot open output file" << endl;
	}

	//Runs through the array and writes each character into the file 
	for (int i = 0; i < 14; i++)
	{
		outputToFile1 << wordsToSearchArray1D[i];
	}

	//Closes the file to reduce the number of errors that can occur
	outputToFile1.close();

	//Lets the user know that the file was written to successfully
	cout << endl << "Successfully writen to text1Filtered.txt" << endl;
	system("pause");
}

//Function to write the updated array into the 'text2Filtered.txt' file.
void WriteToFile2()
{
	//Opens the file to be written into and performs a check whether the file could be opened
	ofstream outputToFile2("text2Filtered.txt");
	if (!outputToFile2)
	{
		cout << "Cannot open output file" << endl;
	}

	//Runs through the 2D array and writes each character into the file in a grid-like pattern
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			outputToFile2 << wordsToSearchArray2D[i][j];
		}
		outputToFile2 << endl;
	}
	
	//Closes the file to reduce the number of errors that can occur
	outputToFile2.close();

	//Lets the user know that the file was written to successfully 
	cout << endl << "Successfully writen to text2Filtered.txt" << endl;
	system("pause");
}