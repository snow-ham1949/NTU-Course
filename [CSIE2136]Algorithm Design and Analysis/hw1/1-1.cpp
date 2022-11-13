#include <iostream>
#include <math.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;
const int maxn = 100000 + 6;

int disk_pos[maxn];
int n;
ll step;

ll power(ll x, int y)
{
    x %= mod;
    ll res = 1;
    while (y)
    {
        if (y & 1)
        {
            res = (res * x) % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

void move(int src, int tmp, int des, int id)
{
    if (disk_pos[id] == tmp)
    {
        //printf("Case 1, step: %lld\n", step);
        printf("-1");
        exit(0);
    }
    else if (disk_pos[id] == des)
    {
        //printf("Case 2, step: %lld\n", step);
        if (id == 1)
        {
            return;
        }
        move(tmp, src, des, id - 1);
    }
    else
    {
        //printf("Case 3, step: %lld\n", step);
        if (id == 1)
        {
            disk_pos[id] = des;
            step++;
            step %= mod;
            return;
        }
        move(src, des, tmp, id - 1);
        disk_pos[id] = des;
        //printf("Case 3 continue, step: %lld\n", step);
        step += (power(2, id - 1) % mod);
        step %= mod;
        // move(tmp, src, des, id - 1);
    }
}

int main()
{

    scanf("%d", &n);

    for (int i = 1; i <= 3; i++)
    {
        int num;
        scanf("%d", &num);
        for (int j = 0; j < num; j++)
        {
            int id;
            scanf("%d", &id);
            disk_pos[id] = i;
        }
    }

    step = 0;
    move(1, 2, 3, n);

    printf("%lld", step);

    return 0;
}