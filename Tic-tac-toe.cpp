#include <iostream>
#include <vector>

using namespace std;

class TicTacToe
{
private:
    vector<vector<char>> board;
    char currentPlayer;

    void printBoard()
    {
        for (auto &row : board)
        {
            for (auto &cell : row)
            {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }

    bool checkWin()
    {
        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; ++i)
        {
            if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
                (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer))
            {
                return true;
            }
        }
        if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
            (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer))
        {
            return true;
        }
        return false;
    }

public:
    TicTacToe() : board(3, vector<char>(3, ' ')), currentPlayer('X') {}

    void play()
    {
        int row, col;
        int moves = 0;

        while (true)
        {
            printBoard();
            cout << "Player " << currentPlayer << ", enter row and column (0, 1, or 2): ";
            cin >> row >> col;

            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ')
            {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            board[row][col] = currentPlayer;
            moves++;

            if (checkWin())
            {
                printBoard();
                cout << "Player " << currentPlayer << " wins!" << endl;
                return;
            }

            if (moves == 9)
            {
                printBoard();
                cout << "It's a draw!" << endl;
                return;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
};

int main()
{
    TicTacToe game;
    game.play();
    return 0;
}
