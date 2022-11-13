#include <stdio.h>
#include <string.h>

#define maxn 25 + 6

// #define DEBUG

int ans[maxn][maxn];
int row_clue[maxn][maxn], row_clue_num[maxn], column_clue[maxn][maxn], column_clue_num[maxn];
int n, m;

void printAns();

int dfs(int x, int y);

int check_row(int x);

int check_column(int y);

int main() 
{
    memset(ans, -1, sizeof(ans[0][0]) * maxn * maxn);

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) 
    {
        scanf("%d", &(row_clue_num[i]));
        for (int j = 0; j < row_clue_num[i]; ++j) 
        {
            scanf("%d", &(row_clue[i][j]));
        }
    }

    for (int i = 0; i < m; ++i) 
    {
        scanf("%d", &(column_clue_num[i]));
        for (int j = 0; j < column_clue_num[i]; ++j) 
        {
            scanf("%d", &(column_clue[i][j]));
        }
    }

    int f = dfs(0, 0);

    return 0;
}

void printAns() 
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (ans[i][j] == 1) {
                putchar('o');
            } else {
                putchar('_');
            }
        }
        puts("");
    }

    return;
}

int dfs(int x, int y) 
{
    if (x == n) 
    {
        if (!check_column(y)) 
        {
#ifdef  DEBUG
            printf("%d column failed.\n", y);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    printf("%d ", ans[i][j]);
                }
                puts("");
            }
            puts("");
#endif  //DEBUG
            return 0;
        }
        x = 0, y++;
        if (y == m) {  // end
            for (int i = 0; i < n; ++i) 
            {
                if (!check_row(i)) 
                {
#ifdef  DEBUG
                    printf("%d row failed.\n", i);
#endif  //DEBUG 
                    return 0;
                }
            }
            printAns();
            return 1;
        }
    }

    ans[x][y] = 1;
    if (dfs(x + 1, y)) 
    {
        return 1;
    } 
    else 
    {
        ans[x][y] = 0;
        if (dfs(x + 1, y)) 
        {
            return 1;
        } 
        else 
        {
            ans[x][y] = -1;
        }
    }

    return 0;
}

int check_row(int x) 
{
    int tmp[maxn];
    memset(tmp, 0, sizeof(tmp));
    int prev = ans[x][0], seg = (prev == 1 ? 1 : 0), num = (prev == 1 ? 1 : 0);
    // 1 1 0 1 1
    for (int i = 1; i < m; i++)
    {
        if (ans[x][i] == 1)
        {
            if (prev)
            {
                num++;
            }
            else
            {
                num = 1;
                seg++;
            }
        }
        else
        {
            if (prev)
            {
                tmp[seg - 1] = num;
                num = 0;
            }
        }
        prev = ans[x][i];
    }

    if (prev)
    {
        tmp[seg - 1] = num;
    }

    if (seg != row_clue_num[x])
    {
        return 0;
    }

    for (int i = 0; i < seg; i++)
    {
        if (tmp[i] != row_clue[x][i])
        {
            return 0;
        }
    }

    return 1;
}

int check_column(int y) 
{
    int tmp[maxn];
    memset(tmp, 0, sizeof(tmp));
    int prev = ans[0][y], seg = (prev == 1 ? 1 : 0), num = (prev == 1 ? 1 : 0);
    // 0
    // 1
    // 0
    // 1
    for (int i = 1; i < n; i++)
    {
        if (ans[i][y] == 1)
        {
            if (prev)
            {
                num++;
            }
            else
            {
                num = 1;
                seg++;
            }
        }
        else
        {
            if (prev)
            {
                tmp[seg - 1] = num;
                num = 0;
            }
        }
        prev = ans[i][y];
    }

    if (prev)
    {
        tmp[seg - 1] = num;
    }

    if (seg != column_clue_num[y])
    {
        return 0;
    }

    for (int i = 0; i < seg; i++)
    {
        if (tmp[i] != column_clue[y][i])
        {
            return 0;
        }
    }

    return 1;  
}
/*
4 4
2 1 1
2 1 1
2 1 1
1 4
2 1 2
2 1 1
2 1 2
2 1 1
*/

/*
5 5
1 4
1 2
1 3
1 2
1 4
2 1 1
2 3 1
3 1 1 1
2 1 3
2 1 1
*/
