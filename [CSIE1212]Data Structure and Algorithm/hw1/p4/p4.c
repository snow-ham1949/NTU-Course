#include <stdio.h>
#include <string.h>

#define maxn 1000000 + 10
#define ll long long int

char s[maxn];

// #define DEBUG

ll DFS(int l, int r)
{
    int cnt = 0;

    // +, -
    for (int i = r; i >= l; i--)
    {
        if (s[i] == ')') cnt++;
        if (s[i] == '(') cnt--;

        if (s[i] == '+' && cnt == 0)
        {
            return DFS(l, i - 1) + DFS(i + 1, r);
        }

        if (s[i] == '-' && cnt == 0)
        {
            return DFS(l, i - 1) - DFS(i + 1, r);
        }
    }

    // *, /, %
    for (int i = r; i >= l; i--)
    {
        if (s[i] == ')') cnt++;
        if (s[i] == '(') cnt--;

        if (s[i] == '*' && cnt == 0)
        {
            return DFS(l, i - 1) * DFS(i + 1, r);
        }

        if (s[i] == '/' && cnt == 0)
        {
            ll a = DFS(l, i - 1), b = DFS(i + 1, r);
            ll k = a / b;
            if (a >= k * b)
            {
                return k;
            }
            else
            {
                return k - 1;
            }
        }

        if (s[i] == '%' && cnt == 0)
        {
            return DFS(l, i - 1) % DFS(i + 1, r);
        }
    }

    if (s[l] == '(' && s[r] == ')') return DFS(l + 1, r - 1);
    ll digit = 0;
    for (int i = l; i <= r; i++)
    {
        digit = digit * 10 + (s[i] - '0');
    }

    return digit;
}

int main()
{
    scanf("%s", s);
    int n = strlen(s);
    // ll res = DFS(0, n - 2);
    // printf("Print: %lld\n", res);
    int l = 0, r = 1;
    ll num = 0;
    while (r < n)
    {
        if (s[r] == '=')
        {
            num = DFS(l, r - 1);
            printf("Print: %lld\n", num);
            char str[maxn];
            sprintf(str, "%lld", num);
            int len = strlen(str);
#ifdef  DEBUG
            printf("str: %s\n", str);
#endif  //DEBUG
            memmove(&s[r - len + 1], str, len);
            l = r - len + 1;
            r = l + 1;
        }
        else
        {
            r++;
        }
    }

    return 0;
}