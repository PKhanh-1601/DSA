//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 2 - Homework 4
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = '_';

void printBoard(const vector<vector<char> >& board)
{
    for (size_t i = 0; i < board.size(); ++i)
    {
        for (size_t j = 0; j < board[i].size(); ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isMovesLeft(const vector<vector<char> >& board)
{
    for (size_t i = 0; i < board.size(); ++i)
    {
        for (size_t j = 0; j < board[i].size(); ++j)
        {
            if (board[i][j] == EMPTY) return true;
        }
    }
    return false;
}

int evaluate(const vector<vector<char> >& board)
{
    for (size_t i = 0; i < board.size(); ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == PLAYER) return -10;
            if (board[i][0] == AI) return 10;
        }
    }
    for (size_t col = 0; col < 3; ++col)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            if (board[0][col] == PLAYER) return -10;
            if (board[0][col] == AI) return 10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == PLAYER) return -10;
        if (board[0][0] == AI) return 10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == PLAYER) return -10;
        if (board[0][2] == AI) return 10;
    }
    return 0;
}

int minimax(vector<vector<char> >& board, int depth, bool isMax)
{
    int score = evaluate(board);
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(board)) return 0;

    if (isMax)
    {
        int best = numeric_limits<int>::min();
        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = 0; j < 3; ++j)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    else
    {
        int best = numeric_limits<int>::max();
        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = 0; j < 3; ++j)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char> >& board)
{
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove(-1, -1);
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;
                if (moveVal > bestVal)
                {
                    bestMove = pair<int, int>(i, j);
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main()
{
    vector<vector<char> > board(3, vector<char>(3, EMPTY));
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    printBoard(board);
    while (true)
    {
        int row, col;
        cout << "Enter your move (row and column: 0-based index): ";
        cin >> row >> col;

        if (board[row][col] != EMPTY)
        {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = PLAYER;
        if (evaluate(board) == -10)
        {
            printBoard(board);
            cout << "You win!" << endl;
            break;
        }
        if (!isMovesLeft(board))
        {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
        pair<int, int> aiMove = findBestMove(board);
        board[aiMove.first][aiMove.second] = AI;
        cout << "AI played:" << endl;
        printBoard(board);
        if (evaluate(board) == 10)
        {
            cout << "AI wins!" << endl;
            break;
        }
        if (!isMovesLeft(board))
        {
            cout << "It's a draw!" << endl;
            break;
        }
    }
    return 0;
}
