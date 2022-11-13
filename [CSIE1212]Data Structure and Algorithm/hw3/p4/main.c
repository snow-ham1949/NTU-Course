#include <stdio.h>
#include <string.h>
#include <time.h>

// #define DEBUG

#define maxn 10000000 + 10
#define ll long long
ll lps[2 * maxn];
char s[maxn], rev[maxn], concat[2 * maxn];

ll kmp(char *s, ll n, ll on)
{
    int id = 1, len = 0;
    memset(lps, 0, sizeof(int) * 2 * maxn);
    while (id < n)
    {
        if (s[id] == s[len])
        {
            len++;
            lps[id] = len;
            id++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[id] = 0;
                id++;
            }
        }
    }

    return on - lps[n - 1];
}

int main()
{
    // clock_t start, end;
    // start = clock();
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        rev[i] = s[n - i - 1];
    }

    for (int i = 0; i < n; i++)
    {
        concat[i] = s[i];
        concat[i + n + 1] = rev[i];
    }
    concat[n] = ' ';

    ll m = 2 * (ll)n + 1;
    ll ans_front = kmp(concat, m, (ll)n);
    for (int i = 0; i < n; i++)
    {
        concat[i] = rev[i];
        concat[i + n + 1] = s[i];
    }
    concat[n] = ' ';
    ll ans_back = kmp(concat, m, (ll)n);
#ifdef  DEBUG
    printf("%d %d\n", ans_front, ans_back);
#endif  //DEBUG
    if (ans_front < ans_back)
    {
        printf("%lld\n", ans_front);
        for (int i = n - 1; i > n - 1 - ans_front; i--)
        {
            printf("%c", s[i]);
        }
        printf("%s\n", s);
    }
    else if (ans_front > ans_back)
    {
        printf("%lld\n", ans_back);
        printf("%s", s);
        for (int i = ans_back - 1; i >= 0; i--)
        {
            printf("%c", s[i]);
        }
        puts("");
    }
    else
    {
        printf("%lld\n", ans_front);
        if (ans_front)
        {
            for (int i = n - 1; i > n - 1 - ans_front; i--)
            {
                printf("%c", s[i]);
            }
            printf("%s\n%s", s, s);
            for (int i = ans_back - 1; i >= 0; i--)
            {
                printf("%c", s[i]);
            }
            puts("");
        }
        else
        {
            printf("%s", s);
        }

    }
    // end = clock();
    // printf("%Lf\n", (end - start) / (long double)CLOCKS_PER_SEC * 1000);

    return 0;
}