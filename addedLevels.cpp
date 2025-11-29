#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;

// Global array to mark fixed cells.
// 1 means fixed, 0 means the changable cells.
//initialize the whole array to 0.
int fixed_positions[9][9] = { 0 };
int score = 0;

//function prototyping.
void printBoard(int board[9][9]);
void initialboard(int board[9][9], int secondboard[9][9]);
bool isValid(int board[9][9], int row, int column, int number);
int userEntry(int secondboard[][9], int& score);
void hint(int arr[9][9], int row, int column, int& score);
bool isComplete(int board[9][9]);



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
        {
            //hint code 
            int row, column;

            cout << "\x1b[1;35m";
            cout << "\n========= HINT CALL =========\n";
            cout << "\x1b[0m";
            cout << "\nEnter the row number (1-9): ";
            cin >> row;
            if (row < 1 || row > 9) { //checks row entry
                cout << "Invalid row input. No such cell exists.\n";
                break;
            }
            cout << "Enter the column number (1-9): ";
            cin >> column;
            if (column < 1 || column > 9) {//checks column entry
                cout << "Invalid column input. No such cell exists.\n";
                break;
            }
            //if conditions are fulfilled call hint function.
            hint(secondboard, row, column, score);
            break;
        }
        case 3:
            cout << endl;
            cout << "\x1b[1;35m";
            cout << "====== FULL SOLUTION ======\n\n";
            cout << "\x1b[0m";
            printBoard(board);
            cout << "\nYOUR FINAL SCORE = " << score << endl;
            break;
        case 4:
            cout << "\x1b[1;35m";
            cout << "\n========= YOU ARE EXITING THE GAME =========\n";
            cout << "\x1b[0m";
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
void printBoard(int board[9][9])
{
    cout << "   1 2 3   4 5 6   7 8 9\n" << endl;
    for (int i = 0; i < 9; i++)
    {
        if (i == 3 || i == 6)
        {
            cout << "  -------+-------+------\n";
        }

        cout << i + 1 << "  ";

        //inner loop for columns
        for (int j = 0; j < 9; j++)
        {
            if (j == 3 || j == 6)
            {
                cout << "| ";
            }

            //  Check if the cell is fixed, if fixed, it makes it coloured
            if (fixed_positions[i][j] == 1) {
                //  ANSI code: for coloured output
                cout << "\x1b[1;35m"; //x1b is the escape seq, 1 for bold, 35 for magenta, m is the terminator
            }

            cout << board[i][j] << " ";

            //  Reset the color for remaining text. 0 is to reset 
            if (fixed_positions[i][j] == 1) {
                cout << "\x1b[0m";
            }
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
            if (board[i][column] == number && i != row)
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
            if (board[row][j] == number && j != column)
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
                //exclude the current cell.

                if (board[i][j] == number && !(i == row && j == column))
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

    // Reset the coloured text
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fixed_positions[i][j] = 0;
        }
    }

    int level;
    cout << "\x1b[1;35m";
    cout << "\n============= WELCOME TO THE SUDOKU GAME ============\n\n";
    cout << "\x1b[0m";
    cout << "You will have a partially filled 9 X 9 board that you will need to complete in order to win.\n";
    cout << "All empty cells are represented by 0.\n";
    cout << "\nChoose the difficulty:\n---> Easy\n---> Medium\n---> Hard\n";
    cout << "\nEnter 1, 2 or 3. ";

    do
    {
        cin >> level;
        switch (level)
        {
        case 1: //level easy. Fill 60% of the board
            //this part makes the board that is given to the user..
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (rand() % 5 <= 2) //if this gives 0, 1 or 2, enter the number in that cell.
                    {
                        secondboard[i][j] = board[i][j];
                        //  Mark this cell as fixed in the third array.
                        fixed_positions[i][j] = 1; //the values taken from second board, non-zero.
                    }
                    else
                    {
                        //make it 0 if rand gives 3 or 4. 0 means the player would fill these cells.
                        secondboard[i][j] = 0;
                    }
                }
            }
            break;

        case 2: //for medium level. Fill 50% of the board
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (rand() % 2 == 0) //if this gives 0, enter the number in that cell.
                    {
                        secondboard[i][j] = board[i][j];
                        //  Mark this cell as fixed in the third array.
                        fixed_positions[i][j] = 1; //the values taken from second board, non-zero.
                    }
                    else
                    {
                        //make it 0 if rand gives 3 or 4. 0 means the player would fill these cells.
                        secondboard[i][j] = 0;
                    }
                }
            }
            break;

        case 3: //for hard level. Fill around 33% of the board.
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (rand() % 3 == 0) //if this gives 0. enter the number in that cell.
                    {
                        secondboard[i][j] = board[i][j];
                        //  Mark this cell as fixed in the third array.
                        fixed_positions[i][j] = 1; //the values taken from second board, non-zero.
                    }
                    else
                    {
                        //make it 0 if rand gives 3 or 4. 0 means the player would fill these cells.
                        secondboard[i][j] = 0;
                    }
                }
            }
            break;
        default:
            cout << "\nInvalid Input. Enter again (1-3). ";
            break;
        }

    } while (level != 1 && level != 2 && level != 3);

    cout << "\x1b[1;35m";
    cout << "\n========= STARTING THE GAME =========\n";
    cout << "\x1b[0m";
    cout << "\n1. Press 1 to make a move. A correct move gives you 10 points. A wrong move takes away 5 points.\n2. Press 2 to request a hint. Each hint reduces your score by 10.\n3. Press 3 to request the full solution.\n4. Press 4 to exit.\n";
    cout << endl;
    cout << "\x1b[1;35m";
    cout << "TIP: ";
    cout << "\x1b[0m";
    cout << "Always start from the place of the board where you have the least unknowns.\n"; 
    cout << "\n\tSCORE = " << score << endl << endl;
    //now this prints the board that the user plays on.
    printBoard(secondboard);
}

int userEntry(int secondboard[][9], int& score) {
    int row, column, number;
    cout << endl;
    cout << "Enter the row number (1-9): ";
    cin >> row;
    cout << "Enter the column number (1-9): ";
    cin >> column;
    row--;
    column--;

    if (row < 0 || column < 0 || row > 8 || column > 8) {
        cout << "\nInvalid Input.\n";
        return 0;
    }
    else if (fixed_positions[row][column] == 1) { // Check the mask instead of the board value
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

        if (isComplete(secondboard)) 
        {
            cout << "\n\x1b[1;35mCONGRATULATIONS! YOU COMPLETED THE SUDOKU!\x1b[0m\n";
            cout << "Your final score = " << score << endl;
            exit(0);   // this ends the program immediately.
        }

    }
    else {
        cout << "\nWRONG MOVE. " << number << " can't be placed here.\n";
        score -= 5;
        return 0; // exits userEntry early
    }

    return 0;
}

void hint(int secondboard[9][9], int row, int column, int& score)
{
    int hint_row = row - 1; //to convert into 0-8
    int hint_column = column - 1;

    // Checks is the cell is fixed.
    if (fixed_positions[hint_row][hint_column] == 1) {
        cout << "Cell (" << row << "," << column << ") is already fixed." << endl;
        return;
    }

    //checks if the cellis empty.
    if (secondboard[hint_row][hint_column] != 0) {
        cout << "Cell (" << row << "," << column << ") is already filled. (by you or a previous hint)." << endl;
        return;
    }

    bool hintfound = false;
    int number, n, temp;
    int array[9] = { 1,2,3,4,5,6,7,8,9 };

    for (int x = 0; x < 9; x++)
    {
        //shuffles the array whenever the hint is called.
        n = rand() % 9;
        temp = array[x];
        array[x] = array[n];
        array[n] = temp;
    }

    for (int k = 0; k < 9; k++)
    {
        number = array[k];
        if (isValid(secondboard, hint_row, hint_column, number))
        {
            hintfound = true;
            secondboard[hint_row][hint_column] = number;
            break;
        }
    }

    if (hintfound)
    {
        score -= 10;
        //tells the user where hint is placed.
        cout << "Number " << number << " is placed at row " << row << " and column " << column << ".\n";
        cout << "\nScore is reduced by 10 points.\n";
        cout << "\n\tSCORE =  " << score << endl << endl;
        printBoard(secondboard);

        if (isComplete(secondboard))
        {
            cout << "\n\x1b[1;35mCONGRATULATIONS! YOU COMPLETED THE SUDOKU!\x1b[0m\n";
            cout << "Your final score = " << score << endl;
            exit(0);   // this ends the program immediately.
        }

    }
    else
    {
        cout << "\nAccording to the current state of board, no number 1-9 is possible in this cell.\n";
        cout << "You may have entered numbers previously, that were valid but WRONG.\n";
        cout << "Please retrace your steps.\n";
    }
}

bool isComplete(int board[9][9]) 
{
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            if (board[i][j] == 0) return false;
            if (!isValid(board, i, j, board[i][j])) return false;
        }
    }
    return true;
}