#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;
int score = 0;

//function prototyping.
void printBoard(int board[9][9]);
bool isValid(int board[9][9], int row, int column, int number);
void initialboard(int board[9][9], int secondboard[9][9]);
int userEntry(int secondboard[][9], int& score);

int main()
{
	srand(time(0));
	int board[9][9] = { 0 }; //make an array for the sudoku board.
	int secondboard[9][9] = { 0 }; //the generated board is copied here.
	//call the initial board function until the board is generated, until the element at the last cell becomes non zero.
	while (board[8][8] == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				board[i][j] = 0;
			}
		}
		initialboard(board, secondboard);
	}
	int choice;
	do {
		cout << "\nEnter 1, 2, 3 or 4 to proceed. ";
		cin >> choice;

		switch (choice) {
		case 1:
			userEntry(secondboard, score);
			cout << "\n\tSCORE = " << score << endl;
			break;
		case 2:
			//hint code here
			break;
		case 3:
			cout << endl;
			cout << "====== FULL SOLUTION ======\n\n";
			printBoard(board);
			cout << "\nYOUR FINAL SCORE = " << score << endl;
			break;
		case 4:
			cout << "\n===== YOU ARE EXITING THE GAME =====\n";
			cout << "\n\tSCORE = " << score << endl;
			break;
		default:
			cout << "Invalid Input. Enter again (1-4).\n";
		}

		cout << endl;

	} while (choice != 4 && choice != 3);

	return 0;
}

//function definitions
void printBoard(int board[9][9]) {
	cout << "   1 2 3   4 5 6   7 8 9\n" << endl;
	for (int i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6)
		{
			cout << "   ------+-------+------\n";
		}

		cout << i + 1 << "  ";

		//inner loop for columns
		for (int j = 0; j < 9; j++)
		{

			if (j == 3 || j == 6)
			{
				cout << "| ";
			}
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
bool isValid(int board[9][9], int row, int column, int number)
{
	//set a flag that becomes false as soon as any check is not satisfied.
	bool isValid = true;

	//checking column condition.
	if (isValid)
	{
		for (int i = 0; i < 9 && isValid; i++)
		{
			if (board[i][column] == number)
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
			if (board[row][j] == number)
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
				if (board[i][j] == number)
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

void initialboard(int board[9][9], int secondboard[9][9])
{
	int number;
	int n, temp, counter;
	int array[9] = { 1,2,3,4,5,6,7,8,9 };
	//shuffle the array.

	for (int i = 0; i < 9; i++)
	{
		counter = 0;
		for (int j = 0; j < 9; j++)
		{
			for (int x = 0; x < 9; x++)
			{
				//shuffles the array before a new column begins.
				n = rand() % 9;
				temp = array[x];
				array[x] = array[n];
				array[n] = temp;
			}

			for (int k = 0; k < 9; k++)
			{
				number = array[k]; //between 1 and 9.
				if (isValid(board, i, j, number))
				{
					board[i][j] = number;
					break;
					//when it finds the right number, the control is given to the j loop and it moves to the next column.
				}
				if (k == 8)
				{
					for (int d = 0; d < 9; d++)
					{
						board[i][d] = 0;
					}
					//restart the column loop.
					j = -1;
					counter++;
					if (counter > 100)
					{
						return;
					}
				}
			}
		}
	}

	//this prints the filled sudoku board, which is actually the solution.
	printBoard(board);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (rand() % 3 == 0) //if this gives 0, enter the number in that cell.
			{
				secondboard[i][j] = board[i][j];
			}
			else
			{
				//make it 0 if rand gives 1 or 2.
				secondboard[i][j] = 0;
			}
		}
	}

	cout << "\nWELCOME TO THE SUDOKU GAME!!!\n";
	cout << "You have a partially filled 9 X 9 board that you need to complete in order to win.\n";
	cout << "All empty cells are represented by 0.\n";
	cout << "\n1. Press 1 to make a move. A correct move gives you 10 points. A wrong move takes away 5 points.\n2. Press 2 to request a hint. Each hint reduces your score by 10.\n3. Press 3 to request the full solution.\n4. Press 4 to exit.\n";
	cout << endl;
	cout << "\tSCORE = " << score << endl << endl;
	//now this prints the board that the user plays on.
	printBoard(secondboard);
}
int userEntry(int secondboard[][9], int& score) {
	int row, column, number;
	cout << endl;
	cout << "Enter the row number(1-9): ";
	cin >> row;
	cout << "Enter the column number(1-9): ";
	cin >> column;
	row--;
	column--;

	if (row < 0 || column < 0 || row > 8 || column > 8) {
		cout << "\nInvalid Input.\n";
		return 0;
	}
	else if (secondboard[row][column] != 0) {
		cout << "\nThis place is fixed. Try another position.\n";
		return 0;
	}
	cout << "Enter the number (1-9): ";
	cin >> number;
	if (number < 1 || number > 9) {
		cout << "\nInvalid Input. You can only enter numbers 1-9.\n";
		return 0;
	}

	if (isValid(secondboard, row, column, number)) {
		secondboard[row][column] = number;
		cout << "\nNumber placed successfully.\n";
		cout << endl;
		score += 10; //points for correct placement.
		printBoard(secondboard);
	}
	else {
		cout << "\nWRONG MOVE. " << number << " can't be placed here.\n";
		score -= 5;
		return 0; // exits userEntry early
	}

	return 0;
}