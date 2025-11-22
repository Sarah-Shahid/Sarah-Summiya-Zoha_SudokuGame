//+10 points for each correct placement
//−5 for an invalid move
//−10 for each hint
//−20 if the full solution is requested

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
//function prototyping.
void welcome(int sudokuboard[][9], bool fixed [9][9], int score); //does it need this parameter??
bool isValid(int sudokuboard[][9], int rows, int columns, int move); //int move is the user's input here.

using namespace std;
int main ()
{
	srand(time(0));
	int score = 0; //initial score is set to 0.
	int sudokuboard[9][9]; // 9 X 9 array for the game.
	//make another array to keep track of all your cells that are defined, initially fix all cells to false.
    //so that user is not allowed to change these cells.
	bool fixed[9][9] = { false }; //this fixes all 81 cells of this array to false, as initially the sudoku board is not filled.
	welcome(sudokuboard, fixed, score);
	cout << "\nEnter 1, 2, 3 or 4 to proceed.\n";
	
	
	return 0;
}

//function to print the initial board.
void welcome(int sudokuboard[][9], bool fixed[9][9], int score)
{
		cout << "WELCOME to the SUDOKU GAME!!!\n";
		cout << "You will have a partially filled 9 X 9 board that you need to complete in order to win.\n";
		cout << "All empty cells are represented by 0.\n";
		cout << "1. Press 1 to enter a command.\n2. Press 2 to request a hint. Each hint reduces your score by 10.\n3. Press 3 to request the full solution.\n4. Press 4 to exit.\n";
		cout << endl;
		cout << "\tSCORE = " << score << endl << endl;

		int random;
		int number;
		cout << "   1 2 3   4 5 6   7 8 9\n" << endl;
		for (int i = 0; i < 9; i++)
		{
			if (i == 3 || i == 6)
			{
				cout << "   ------+-------+------\n";
			}
			//typecasting to print alphas.
			cout << char('A' + i) << "  ";
			
			//inner loop for columns
			for (int j = 0; j < 9; j++)
			{

				if (j == 3 || j == 6)
				{
					cout << "| ";
				}
				random = rand() % 5 + 1;
				if (random <= 2) //randomly fill the board only if number comes out to be 1 or 2.
				{
					number = rand() % 9 + 1;
					if (isValid(sudokuboard, i, j, number))
					{
						sudokuboard[i][j] = number;
						fixed[i][j] = true;
					}
					else
					{
						sudokuboard[i][j] = 0;
					}
				}
				else
				{
					sudokuboard[i][j] = 0;
				}
				cout << sudokuboard[i][j] << " ";
			}
			cout << endl;
		}
}
//function to check if the board is being filled correctly.
bool isValid(int sudokuboard[][9], int row, int column, int number)
{
	//set a flag that becomes false as soon as any check is not satisfied.
	bool isValid = true;
	
	//checking column condition.
	if (isValid)
	{
		for (int i = 0; i < 9 && isValid; i++)
		{
			if (sudokuboard[i][column] == number)
			{
				isValid = false; //not valid.
			}
		}
	}

	//checking row condition, no repetition in that row.
	if (isValid)
	{
		for (int j = 0; j < 9 && isValid; j++)
		{
			if (sudokuboard[row][j] == number)
			{
				isValid = false;
			}
		}
	}
	//check for the repetition in the 3 X 3 grid.
	int newrow;
	int newcolumn; 
	if (isValid)
	{
		newrow = row - (row % 3);
		newcolumn = column - (column % 3);
		//now we have the top left of our 3 X 3 grid.
		for (int i = newrow; i <= newrow + 2 && isValid; i++)
		{
			for (int j = newcolumn; j <= newcolumn + 2 && isValid; j++)
			{
				if (sudokuboard[i][j] == number)
				{
					//number already present in the 3 X 3 grid.
					isValid = false;
				}
			}
		}
	}
	if (isValid)
	{
		return true;
	}
	else
	{
		return false;
	}
}