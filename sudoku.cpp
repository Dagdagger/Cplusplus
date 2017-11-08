#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int SIZE = 9;
const char BLANK = '.';

int charToInt(char c);
char intToChar(int i);
bool validBoard(const char board[SIZE][SIZE]);
void printBoard(const char board[SIZE][SIZE]);
bool isNumber(char c);
void copyBoard(const char input[SIZE][SIZE], char output[SIZE][SIZE]);
bool isOpenSpot(const char board[SIZE][SIZE]);
bool isOpen(const char board[SIZE][SIZE], int row, int col);


// Make this for part A
void readBoard(char board[SIZE][SIZE], string fileName);

// Make this for part B
void saveBoard(char board[SIZE][SIZE], string fileName);

int main()
{
	string dump;
	char b[SIZE][SIZE];
	for(int i=0; i < SIZE; i++)
	{
		for(int j=0; j < SIZE; j++)
		{
			b[i][j] = '.';
		}
	}
	string message = "";
	while(isOpenSpot(b))
	{
		char row, col;
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		printBoard(b);
		cout << message << endl;
		message = "";
		cout << "Where do you wish to play? (or load/save)  ";
		cin >> row;

		if(tolower(row) == 'l')
		{
			cout << "What file do you wish to load?  ";
			getline(cin, dump);
			getline(cin, dump);
			readBoard(b, dump);
			continue;
		}
		else if(tolower(row) == 's')
		{
			cout << "Where do you wish to save?  ";
			getline(cin,dump);
			getline(cin,dump);
			saveBoard(b, dump);
			continue;
		}

		cin >> col;
		getline(cin, dump);

		int rrow, rcol;
		if(tolower(row) >= 'a' && tolower(row) <= 'i')
		{
			rrow = tolower(row)-'a';
			rcol = col-'1';
		}
		else
		{
			rcol = tolower(col)-'a';
			rrow = row-'1';
		}
		if(isOpen(b,rrow,rcol))
		{
			char value;
			cout << "What number should go at "<<row<<col<<"? ";
			cin >> value;
			getline(cin, dump);

			char copy[SIZE][SIZE];
			copyBoard(b, copy);

			if(value < '1' || value > '9')
			{
				message = "You can only play 1 - 9";
			}
			else
			{
				copy[rrow][rcol] = value;

				if(validBoard(copy))
				{
					b[rrow][rcol] = value;
				}
				else
				{
					message = "That is not a valid move";
				}
			}
		}
		else
		{
			message = "You cannot play there";
		}
	}
}

int charToInt(char c)
{
	return c-'1'+1;
}

char intToChar(int i)
{
	return '1'+(i-1);
}

bool validBoard(const char board[SIZE][SIZE])
{
	// whole board formatting check
	for(int row=0; row < SIZE; row++)
	{
		for(int col=0; col < SIZE; col++)
		{
			if(!(isNumber(board[row][col]) || board[row][col] == BLANK))
			{
				return false;
			}
		}
	}

	// row check
	for(int row=0; row < SIZE; row++)
	{
		string letters = "";
		for(int col=0; col < SIZE; col++)
		{
			// if letters doesn't have this character (and its in 1-9)
			if(letters.find(board[row][col])==static_cast<long unsigned>(-1)
				&& isNumber(board[row][col]))
			{
				letters = letters+board[row][col];
			}
			else if(isNumber(board[row][col]))
			{
				return false;
			}
		}
	}

	// col check
	for(int col=0; col < SIZE; col++)
	{
		string letters = "";
		for(int row=0; row < SIZE; row++)
		{
			// if letters doesn't have this character (and its in 1-9)
			if(letters.find(board[row][col])==static_cast<long unsigned>(-1)
				&& isNumber(board[row][col]))
			{
				letters = letters+board[row][col];
			}
			else if(isNumber(board[row][col]))
			{
				return false;
			}
		}
	}

	// 3x3 square checks
	for(int b=0; b < SIZE; b++) // boxes
	{
		string letters = "";
		for(int s=0; s<SIZE; s++) //square in the 3x3
		{
			int row = (b%3)*3 + s%3;
			int col = (b/3)*3 + s/3;

			// if letters doesn't have this character (and its in 1-9)
			if(letters.find(board[row][col])==static_cast<long unsigned>(-1)
			 && isNumber(board[row][col]))
			{
				letters = letters+board[row][col];
			}
			else if(isNumber(board[row][col]))
			{
				return false;
			}

		}
	}

	return true;
}

void printBoard(const char board[SIZE][SIZE])
{
	cout << "  123 456 789\n";
	for(int row=0; row<SIZE; row++)
	{
		cout << static_cast<char>('a'+row) << ' ';
		for(int col=0; col<SIZE; col++)
		{
			cout << board[row][col];
			if(col%3==2 && col != SIZE-1)
			{
				cout <<"|";
			}
		}
		if(row%3==2 && row != SIZE-1)
		{
			cout << "\n  ---+---+---";
		}
		cout << endl;
	}
}

bool isNumber(char c)
{
	return ('1' <= c && c <= '9');
}

void copyBoard(const char input[SIZE][SIZE], char output[SIZE][SIZE])
{
	for(int row=0; row<SIZE;row++)
	{
		for(int col=0; col<SIZE;col++)
		{
			output[row][col] = input[row][col];
		}
	}
}

bool isOpenSpot(const char board[SIZE][SIZE])
{
	for(int rrow=0; rrow < SIZE; rrow++)
	{
		for(int rcol=0; rcol < SIZE; rcol++)
		{
			if(!isNumber(board[rrow][rcol]))
			{
				return true;
			}
		}
	}

	// didn't find an open spot... =(
	return false;
}

bool isOpen(const char board[SIZE][SIZE], int row, int col)
{
	if(row < 0 || col < 0 || col >= SIZE || row >= SIZE)
	{
		return false;
	}

	return board[row][col] < '1' || board[row][col] > '9';
}

// Make this for part A
void readBoard(char board[SIZE][SIZE], string fileName)
{
    char checkboard[SIZE][SIZE];
    bool firstline = false;
    bool secondline = false;

    copyBoard(board,checkboard);
/* Check for file existence */
	ifstream myfile(fileName);
	if(!myfile.good()){
            cout<<"FILE DOES NOT EXIST"<<endl;
	}

/* Copy into the board 2D array by reading the rows in the file
    rows, uses the firstline and secondline
    booleans to skip the line dividers, it is also necessary
    to skip the "|" character that is usually in the 3rd or 7th index
    of the row array.
    */
	if(myfile.good()){
         for(int i = 0; i < SIZE+2; i++)
        {
            string row;
            if (myfile >> row && i != 3 && i != 7) {
                for (int j = 0; j < SIZE; j++)
                {
                    if( i >= 7){
                    i = i-2;
                    secondline = true;
                    }
                    if(i >= 3 && i < 6){
                    i = i-1;
                    firstline = true;
                    }
                    if(j >= 7){
                    board[i][j] = row[j+2];
                    }
                    if(j >= 3 && j < 6 ){
                    board[i][j] = row[j+1];
                    }
                    if(j < 3){
                    board[i][j] = row[j];
                    }
                    if (firstline){
                        i = i+1;
                        firstline = false;
                    }
                    if(secondline){
                        i = i+2;
                        secondline = false;
                    }
                }
                /* outputs the current row being read
                may or may not have to be deleted */
                cout << row << endl;
            }
        }
	myfile.close();
	}
/* checks for board validity;
 if not valid, reverts to the
 board last played
 */
if(!validBoard(board)){
    cout<<"This is not a valid board"<<endl;
    copyBoard(checkboard,board);
}
}


// Make this for part B
void saveBoard(char board[SIZE][SIZE], string fileName)
{
    /* outputs the 2D board array into the file stream,
    relatively straightforward except for the necessary
    line divider and "|" character insertions needed to
    keep the file "format"
    */
	ofstream newfile(fileName);
	for(int row=0; row<SIZE;row++)
	{
	    if (row == 3 || row == 6){
            newfile << "---+---+---" << '\n';
	    }
		for(int col=0; col <= SIZE;col++)
		{
		    if(col == SIZE){
                newfile << '\n';
                continue;
		    }
		    if(col == 3 || col == 6){

                newfile << '|';
		    }
			newfile << board[row][col];
		}
	}
}
