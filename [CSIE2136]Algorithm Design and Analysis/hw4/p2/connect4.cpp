/* reference: https://github.com/KeithGalli/Connect4-Python*/

#include "connect4.h"
#include <bits/stdc++.h>

using namespace std;

#define pb(a) push_back(a)

typedef long long ll;

typedef struct Data
{
    ll score;
    int column;
} Data;

enum TYPE
{
    EMPTY,
    MY_COLOR,
    YP_COLOR,
};

const int ROW = 6;
const int COLUMN = 7;
const int pos_dr[4] = {0, -1, -2, -3};
const int pos_dc[4] = {0, 1, 2, 3};
const int neg_dr[4] = {0, 1, 2, 3};
const int neg_dc[4] = {0, 1, 2, 3};

/*
    MY Board
    0 |             |
    1 |             |
    2 |             |
    3 |             |
    4 |             |
    5 |             |
       0 1 2 3 4 5 6
*/

vector<vector<int> > board;
bool IsValidColumn(vector<vector<int> > &board, int column);
vector<int> GetValidColumns(vector<vector<int> > &board);
bool Winning(vector<vector<int> > &board, int color);
ll GetScore(vector<int> &array, int player);
ll CalculateScore(vector<vector<int> > &board, int player);
int GetRow(vector<vector<int> > &board, int column);
void Drop(vector<vector<int> > &board, int row, int column, int player);
vector<vector<int> > CopyBoard(vector<vector<int> > &board);
Data MiniMax(vector<vector<int> > &board, int depth, ll alpha, ll beta, bool maximize);

int decide(int yp_move)
{
    int col, row;
    if (yp_move == -1)
    {
        board.clear();
        board.resize(ROW, vector<int>(COLUMN, EMPTY));
        col = 3;
        row = GetRow(board, col);
        Drop(board, row, col, MY_COLOR);
        return col;
    }
    else
    {
        row = GetRow(board, yp_move);
        Drop(board, row, yp_move, YP_COLOR);
        col = MiniMax(board, 6, LLONG_MIN, LLONG_MAX, true).column;
        if (col != -1 && IsValidColumn(board, col))
        {
            row = GetRow(board, col);
            Drop(board, row, col, MY_COLOR);
            return col;
        }
    }
}

bool IsValidColumn(vector<vector<int> > &board, int column)
{
    return board[ROW - 1][column] == EMPTY;
}

vector<int> GetValidColumns(vector<vector<int> > &board)
{
    vector<int> valid_columns;
    for (int i = 0; i < COLUMN; i++)
    {
        if (IsValidColumn(board, i))
        {
            valid_columns.pb(i);
        }
    }
    return valid_columns;
}

bool Winning(vector<vector<int> > &board, int color)
{
    bool flag = 1;
    // horizontal
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COLUMN - 3; c++)
        {
            flag = 1;
            for (int k = 0; k < 4; k++)
            {
                if (board[r][c + k] != color)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                return flag;
            }
        }
    }

    // vertical
    for (int r = 0; r < ROW - 3; r++)
    {
        for (int c = 0; c < COLUMN; c++)
        {
            flag = 1;
            for (int k = 0; k < 4; k++)
            {
                if (board[r + k][c] != color)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                return flag;
            }
        }
    }

    // positive slope
    for (int r = 3; r < ROW; r++)
    {
        for (int c = 0; c < COLUMN - 3; c++)
        {
            flag = 1;
            for (int k = 0; k < 4; k++)
            {
                if (board[r + pos_dr[k]][c + pos_dc[k]] != color)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                return flag;
            }
        }
    }

    // negtive slope
    for (int r = 0; r < ROW - 3; r++)
    {
        for (int c = 0; c < COLUMN - 3; c++)
        {
            flag = 1;
            for (int k = 0; k < 4; k++)
            {
                if (board[r + neg_dr[k]][c + neg_dc[k]] != color)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                return flag;
            }
        }
    }

    return 0;
}

ll GetScore(vector<int> &array, int player)
{
    ll score = 0;
    int opp_player = YP_COLOR;
    if (player == YP_COLOR)
    {
        opp_player = MY_COLOR;
    }

    int p = 0, opp = 0, empty = 0;
    for (int i : array)
    {
        if (i == player)
        {
            p++;
        }
        else if (i == opp_player)
        {
            opp++;
        }
        else
        {
            empty++;
        }
    }

    if (p == 4)
    {
        score += 100;
    }
    else if (p == 3 and empty == 1)
    {
        score += 83;
    }
    else if (p == 2 and empty == 2)
    {
        score += 42;
    }

    if (opp == 3 and empty == 1)
    {
        score -= 14;
    }
    else if (opp == 4)
    {
        score -= 1000;
    }

    return score;
}

ll CalculateScore(vector<vector<int> > &board, int player)
{
    ll score = 0;

    // center
    for (int i = 0; i < ROW; i++)
    {
        if (board[i][COLUMN / 2] == player)
        {
            score++;
        }
    }
    score *= 3;

    vector<int> window;
    // horizontal
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COLUMN - 3; c++)
        {
            window.clear();
            for (int k = 0; k < 4; k++)
            {
                window.pb(board[r][c + k]);
            }
            score += GetScore(window, player);
        }
    }

    // vertical
    for (int r = 0; r < ROW - 3; r++)
    {
        for (int c = 0; c < COLUMN; c++)
        {
            window.clear();
            for (int k = 0; k < 4; k++)
            {
                window.pb(board[r + k][c]);
            }
            score += GetScore(window, player);
        }
    }

    // positive slope
    for (int r = 3; r < ROW; r++)
    {
        for (int c = 0; c < COLUMN - 3; c++)
        {
            window.clear();
            for (int k = 0; k < 4; k++)
            {
                window.pb(board[r + pos_dr[k]][c + pos_dc[k]]);
            }
            score += GetScore(window, player);
        }
    }

    // negtive slope
    for (int r = 0; r < ROW - 3; r++)
    {
        for (int c = 0; c < COLUMN - 3; c++)
        {
            window.clear();
            for (int k = 0; k < 4; k++)
            {
                window.pb(board[r + neg_dr[k]][c + neg_dc[k]]);
            }
            score += GetScore(window, player);
        }
    }

    return score;
}

int GetRow(vector<vector<int> > &board, int column)
{
    for (int row = 0; row < ROW; row++)
    {
        if (board[row][column] == EMPTY)
        {
            return row;
        }
    }
}

void Drop(vector<vector<int> > &board, int row, int column, int player)
{
    board[row][column] = player;
}

vector<vector<int> > CopyBoard(vector<vector<int> > &board)
{
    vector<vector<int> > tmp_board(ROW, vector<int>(COLUMN));
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COLUMN; c++)
        {
            tmp_board[r][c] = board[r][c];
        }
    }
    return tmp_board;
}

Data MiniMax(vector<vector<int> > &board, int depth, ll alpha, ll beta, bool maximize)
{
    Data data;
    vector<int> valid_columns = GetValidColumns(board);
    if (Winning(board, YP_COLOR))
    {
        data.column = -1, data.score = LLONG_MIN;
        return data;
    }
    else if (Winning(board, MY_COLOR))
    {
        data.column = -1, data.score = LLONG_MAX;
        return data;
    }
    else if (int(valid_columns.size()) == 0)
    {
        data.column = -1, data.score = 0;
        return data;
    }

    if (depth == 0)
    {
        data.column = -1, data.score = CalculateScore(board, MY_COLOR);
        return data;
    }

    if (maximize)
    {
        data.score = LLONG_MIN, data.column = valid_columns[0];
        for (int column : valid_columns)
        {
            int row = GetRow(board, column);
            vector<vector<int> > tmp_board = CopyBoard(board);
            Drop(tmp_board, row, column, MY_COLOR);
            ll score = MiniMax(tmp_board, depth - 1, alpha, beta, false).score;
            if (score > data.score)
            {
                data.score = score, data.column = column;
            }
            alpha = max(alpha, data.score);
            if (alpha >= beta)
            {
                break;
            }
        }
        return data;
    }
    else
    {
        data.score = LLONG_MAX, data.column = valid_columns[0];
        for (int column : valid_columns)
        {
            int row = GetRow(board, column);
            vector<vector<int> > tmp_board = CopyBoard(board);
            Drop(tmp_board, row, column, YP_COLOR);
            ll score = MiniMax(tmp_board, depth - 1, alpha, beta, true).score;
            if (score < data.score)
            {
                data.score = score, data.column = column;
            }
            beta = min(beta, data.score);
            if (alpha >= beta)
            {
                break;
            }
        }
        return data;
    }
}