#include <iostream>

using namespace std;

char board[3][3];
char currentPlayer;

void initializeBoard()
{
    char value = '1';

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = value++;
        }
    }
}

void displayBoard()
{
    cout << "\n";

    for(int i = 0; i < 3; i++)
    {
        cout << " ";

        for(int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if(j < 2)
                cout << " | ";
        }

        cout << endl;

        if(i < 2)
            cout << "---|---|---" << endl;
    }

    cout << "\n";
}

bool makeMove(int position)
{
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if(position < 1 || position > 9)
        return false;

    if(board[row][col] == 'X' || board[row][col] == 'O')
        return false;

    board[row][col] = currentPlayer;

    return true;
}

bool checkWin()
{
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == currentPlayer &&
           board[i][1] == currentPlayer &&
           board[i][2] == currentPlayer)
            return true;
    }

    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] == currentPlayer &&
           board[1][i] == currentPlayer &&
           board[2][i] == currentPlayer)
            return true;
    }

    if(board[0][0] == currentPlayer &&
       board[1][1] == currentPlayer &&
       board[2][2] == currentPlayer)
        return true;

    if(board[0][2] == currentPlayer &&
       board[1][1] == currentPlayer &&
       board[2][0] == currentPlayer)
        return true;

    return false;
}

bool checkDraw()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }

    return true;
}

void switchPlayer()
{
    if(currentPlayer == 'X')
        currentPlayer = 'O';
    else
        currentPlayer = 'X';
}

void playGame()
{
    initializeBoard();

    currentPlayer = 'X';

    int move;

    while(true)
    {
        displayBoard();

        cout << "Player " << currentPlayer
             << ", enter position (1-9): ";

        cin >> move;

        if(!makeMove(move))
        {
            cout << "\nInvalid Move! Try Again.\n";
            continue;
        }

        if(checkWin())
        {
            displayBoard();

            cout << "\nPlayer "
                 << currentPlayer
                 << " Wins!\n";

            break;
        }

        if(checkDraw())
        {
            displayBoard();

            cout << "\nGame Draw!\n";

            break;
        }

        switchPlayer();
    }
}

int main()
{
    char replay;

    do
    {
        cout << "\n=============================\n";
        cout << "      TIC TAC TOE GAME\n";
        cout << "=============================\n";

        playGame();

        cout << "\nPlay Again? (Y/N): ";
        cin >> replay;

    } while(replay == 'Y' || replay == 'y');

    cout << "\nThank You For Playing!\n";

    return 0;
}