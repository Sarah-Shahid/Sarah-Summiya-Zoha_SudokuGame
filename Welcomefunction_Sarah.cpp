//+10 points for each correct placement
//−5 for an invalid move
//−10 for each hint
//−20 if the full solution is requested

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

//function prototyping.
void printBoard(int sudokuboard[][9]);
void welcome(int sudokuboard[][9], bool fixed[9][9], int score); //does it need this parameter??
bool isValid(int sudokuboard[][9], int rows, int columns, int move); //int move is the user's input here.
void userEntry(int sudokuboard[][9], bool fixed[][9], int& score);

using namespace std;

int main()
{
    srand(time(0));
    int score = 0; //initial score is set to 0.
    int sudokuboard[9][9]; // 9 X 9 array for the game.
    //make another array to keep track of all your cells that are defined, initially fix all cells to false.
    //so that user is not allowed to change these cells.
    bool fixed[9][9] = { false }; //this fixes all 81 cells of this array to false, as initially the sudoku board is not filled.

    welcome(sudokuboard, fixed, score);

    int choice;
    do {
        cout << "\nEnter 1, 2, 3 or 4 to proceed.\n";
        cin >> choice;

        switch (choice) {
        case 1:
            userEntry(sudokuboard, fixed, score);
            break;
        case 2:
            //hint code here
            break;
        case 3:
            //full solution code here
            break;
        case 4:
            cout << "Game Exit\n";
            break;
        default:
            cout << "Invalid Input. Enter again (1-4)\n";
        }

        cout << endl;
        cout << "\tSCORE = " << score << endl;

    } while (choice != 4);

    return 0;
}

void printBoard(int sudokuboard[][9]) {
    cout << "   0 1 2   3 4 5   6 7 8\n" << endl;
    for (int i = 0; i < 9; i++)
    {
        if (i == 3 || i == 6)
        {
            cout << "   ------+-------+------\n";
        }

        cout << i << "  ";

        //inner loop for columns
        for (int j = 0; j < 9; j++)
        {
            if (j == 3 || j == 6)
            {
                cout << "| ";
            }
            cout << sudokuboard[i][j] << " ";
        }
        cout << endl;
    }
}

//function to print the initial board.
void welcome(int sudokuboard[][9], bool fixed[9][9], int score)
{
    cout << "WELCOME to the SUDOKU GAME!!!\n";
    cout << "You will have a partially filled 9 X 9 board that you need to complete in order to win.\n";
    cout << "All empty cells are represented by 0.\n";
    cout << "1. Press 1 to enter a command.\n2. Press 2 to request a hint. Each hint reduces your score by 10.\n3. Press 3 to request the full solution.\n4. Press 4 to exit.\n";
    cout << endl;
    cout << "\tSCORE = 0" << endl << endl;

    int random;
    int number;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            random = rand() % 2 + 1;
            if (random == 1) //randomly fill the board only if number comes out to be 1. so probability is 50%.
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
        }
    }
    printBoard(sudokuboard);
}

//function to check if the board is being filled correctly.
bool isValid(int sudokuboard[][9], int row, int column, int number)
{
    bool valid = true;

    //checking column condition.
    for (int i = 0; i < 9 && valid; i++)
    {
        if (sudokuboard[i][column] == number)
        {
            valid = false; //not valid.
        }
    }

    //checking row condition, no repetition in that row.
    for (int j = 0; j < 9 && valid; j++)
    {
        if (sudokuboard[row][j] == number)
        {
            valid = false;
        }
    }

    //check for the repetition in the 3 X 3 grid.
    int newrow = row - (row % 3);
    int newcolumn = column - (column % 3);
    for (int i = newrow; i <= newrow + 2 && valid; i++)
    {
        for (int j = newcolumn; j <= newcolumn + 2 && valid; j++)
        {
            if (sudokuboard[i][j] == number)
            {
                valid = false;
            }
        }
    }

    return valid;
}

void userEntry(int sudokuboard[][9], bool fixed[][9], int& score) {
    int row, column, number;
    cout << endl;
    cout << "Enter the row number(0-8) : ";
    cin >> row;
    cout << "Enter the column number(0-8) : ";
    cin >> column;

    if (row < 0 || column < 0 || row > 8 || column > 8) {
        cout << "Invalid input\n";
    }
    else if (fixed[row][column]) {
        cout << "This place is fixed.Try another position\n";
    }
    else {
        cout << "Enter the number (1-9) : ";
        cin >> number;
        if (number > 9 || number < 1) {
            cout << "Invalid input\n";
        }
        else if (isValid(sudokuboard, row, column, number)) {
            sudokuboard[row][column] = number;
            cout << "Number placed successfully\n";
            cout << endl;
            score += 15; //points for correct placement
        }
        else {
            cout << "This number can not be entered according to sudoku rules.\n";
        }
    }

    printBoard(sudokuboard);
}