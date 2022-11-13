#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define mod 98120979115476339
#define maxn 1000000 + 10
#define ll long long

// #define DEBUG

typedef struct _Info{
    ll hash;
    int id;
} Info;

int cmp(const void *a, const void *b)
{
    Info *x = (Info *)a, *y = (Info *)b;
    if (x->hash < y->hash)
    {
        return -1;
    }
    else if (x->hash == y->hash && x->id < y->id)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

ll p_pow[maxn];
Info final_hash[maxn];
ll **hash;
char str[maxn];

int main()
{
    int k, l, flag;
    scanf("%d%d%d", &k, &l, &flag);

    p_pow[0] = 1;
    for (int i = 1; i < l; i++)
    {
        #define p 94
        p_pow[i] = (p_pow[i - 1] * p) % mod;
    }

    hash = (ll **)malloc(sizeof(ll *) * k);
    for (int i = 0; i < k; i++)
    {
        hash[i] = (ll *)malloc(sizeof(ll) * l);
    }
 
    for (int i = 0; i < k; i++)
    {
#ifdef  DEBUG
        printf("%dth string hash: ", i);
#endif  //DEBUG
        // scanf("%s", str);
        int c;
        c = getchar_unlocked();
        c = getchar_unlocked();
        hash[i][0] =  (c - '!' + 1) % mod;
        final_hash[i].hash = hash[i][0];
#ifdef  DEBUG
        printf("%lld ", final_hash[i].hash);
#endif  //DEBUG
        for (int j = 1; j < l; j++)
        {
            c = getchar_unlocked();
            hash[i][j] = (c - '!' + 1) * p_pow[j] % mod;
            final_hash[i].hash += hash[i][j];
#ifdef  DEBUG
        printf("%lld ", final_hash[i].hash);
#endif  //DEBUG
        }
        final_hash[i].id = i;
#ifdef  DEBUG
        puts("");
#endif  //DEBUG
    }          

    ll similar_cnt = 0, cnt = 1;
    int ans[2];
    qsort(final_hash, k, sizeof(Info), cmp);
    ll cur_hash = final_hash[0].hash;
    for (int i = 1; i < k; i++)
    {
        if (cur_hash == final_hash[i].hash)
        {
            cnt++;
        }
        else
        {
            similar_cnt -= ((cnt * (cnt - 1) / 2) * (l - 1));
            cur_hash = final_hash[i].hash;
            cnt = 1;
        }
    }
    similar_cnt -= ((cnt * (cnt - 1) / 2) * (l - 1));
#ifdef  DEBUG
    printf("\nafter removing duplicate: %lld\n", similar_cnt);
#endif  //DEBUG
    for (int del_ch = 0; del_ch < l; del_ch++)
    {
        cnt = 0;
        for (int i = 0; i < k; i++)
        {
            final_hash[i].hash -= hash[final_hash[i].id][del_ch];
        }
        qsort(final_hash, k, sizeof(Info), cmp);
        Info cur;
        cur.hash = final_hash[0].hash, cur.id = final_hash[0].id;
        for (int i = 1; i < k; i++)
        {
            if (cur.hash == final_hash[i].hash)
            {
                ans[0] = cur.id;
                ans[1] = final_hash[i].id;
                cnt++;
                similar_cnt += cnt;
#ifdef  DEBUG
            printf("found similar at removing %dth character, found pair(%d, %d), hash value: %lld\n", del_ch, ans[0], ans[1], cur_hash);
#endif  //DEBUG
            }
            else
            {
                cnt = 0;
                cur = final_hash[i];
            }
        }
        for (int i = 0; i < k; i++)
        {
            final_hash[i].hash += hash[final_hash[i].id][del_ch];
        }
    }

    similar_cnt ? puts("Yes") : puts("No");
    if (flag)
    {
        if (similar_cnt) printf("%lld\n", similar_cnt);
    }
    else
    {
        if (similar_cnt) printf("%d %d\n", ans[0], ans[1]);
    }

    return 0;
}