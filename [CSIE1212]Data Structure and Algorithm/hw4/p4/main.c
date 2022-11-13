#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define max(a, b) a > b ? a : b
#define maxn 100000 + 10
#define ll long long

typedef struct Treap
{
    int pri, sz;
    struct Treap *l, *r;
    ll v, sum, ass;
    ll max_cnt, maxx, second_maxx;
    int rev;
} Treap;

void write(ll n)
{
    if (n > 9) write(n / 10);
    putchar_unlocked(n % 10 + '0');
}

int read() 
{
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;        
        ch = getchar();               
    }
    while (ch >= '0' && ch <= '9') { 
        x = x * 10 + (ch - '0');
        ch = getchar(); 
    }
    return x * w;
}

Treap* newTreap(ll v)
{
    Treap* t = malloc(sizeof(Treap));
    t->l = t->r = NULL;
    t->pri = rand();
    t->sz = t->max_cnt = 1;
    t->rev = 0;
    t->ass = t->second_maxx = -1;
    t->v = t->sum = t->maxx = v;
    return t;
}

int size(Treap* t)
{
    return t ? t->sz : 0;
}

ll getSum(Treap* t)
{
    return t ? t->sum : 0;
}

void pushdown(Treap* t)
{
    if (t)
    {
        if (t->rev)
        {
            Treap *tmp = t->l;
            t->l = t->r;
            t->r = tmp;
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
            t->rev = 0;
        }
        if (t->ass != -1)
        {
            #define min(a, b) a < b ? a : b
            t->v = t->v > t->ass ? t->ass : t->v;
            if (t->l && t->l->maxx > t->ass)
            {
                t->l->sum -= (t->l->maxx - t->ass) * t->l->max_cnt;
                t->l->maxx = t->l->ass = t->ass;
            }
            if (t->r && t->r->maxx > t->ass)
            {
                t->r->sum -= (t->r->maxx - t->ass) * t->r->max_cnt;
                t->r->maxx = t->r->ass = t->ass;
            }
            t->ass = -1;
        }
    }
}

void pullup(Treap* t)
{
    t->sz = 1;
    t->sum = t->maxx = t->v;
    t->second_maxx = -1;
    t->max_cnt = 1;
    if (t->l)
    {
        pushdown(t->l);
        t->sz += (t->l ? t->l->sz : 0);
        t->sum += (t->l ? t->l->sum : 0);
        if (t->maxx > t->l->maxx)
        {
            t->second_maxx = t->l->maxx;
        }
        else if (t->maxx < t->l->maxx)
        {
            t->second_maxx = max(t->l->second_maxx, t->maxx);
            t->maxx = t->l->maxx;
            t->max_cnt = t->l->max_cnt;
        }
        else
        {
            t->second_maxx = t->l->second_maxx;
            t->max_cnt += t->l->max_cnt;
        }
    }
    if (t->r)
    {
        pushdown(t->r);
        t->sz += (t->r ? t->r->sz : 0);
        t->sum += (t->r ? t->r->sum : 0);
        if (t->maxx > t->r->maxx)
        {
            t->second_maxx = max(t->r->maxx, t->second_maxx);
        }
        else if (t->maxx < t->r->maxx)
        {
            t->second_maxx = max(t->r->second_maxx, t->maxx);
            t->maxx = t->r->maxx;
            t->max_cnt = t->r->max_cnt;
        }
        else
        {
            t->second_maxx = max(t->second_maxx, t->r->second_maxx);
            t->max_cnt += t->r->max_cnt;
        }
    }
}

Treap* merge(Treap* t1, Treap* t2)
{
    if (!t1 || !t2) return t1 ? t1 : t2;
    if (t1->pri <= t2->pri)
    {
        pushdown(t2);
        t2->l = merge(t1, t2->l);
        pullup(t2);
        return t2;
    }
    else
    {
        pushdown(t1);
        t1->r = merge(t1->r, t2);
        pullup(t1);
        return t1;
    }
}

void split(Treap* t, Treap** l, Treap** r, int num)
{
    if (!t)
    {
        *l = *r = NULL;
        return;
    }
    else
    {
        pushdown(t);
        if (size(t->l) + 1 <= num)
        {
            *l = t;
            split(t->r, &((*l)->r), r, num - (size(t->l) + 1));
        }
        else
        {
            *r = t;
            split(t->l, l, &((*r)->l), num);
        }
        pullup(t);
    }
}

void build(Treap** t, int n)
{
    static Treap *sta[maxn], *tt, *last;
    int top = 0;
    int val;
    for (int i = 0; i < n; i++)
    {
        val = read();
        tt = newTreap(val);
        last = NULL;
        while (top && sta[top]->pri > tt->pri)
        {
            pullup(sta[top]);
            last = sta[top];
            sta[top--] = NULL;
        }
        if (top)
        {
            sta[top]->r = tt;
        }
        tt->l = last;
        pullup(tt);
        sta[++top] = tt;
    }
    while(top)
    {
        pullup(sta[top--]);
    }
    *t = sta[1];
}

void getIntervalSum(Treap** t, int l, int r)
{
    Treap *t1 = NULL, *t2 = NULL, *t3 = NULL;
    split(*t, &t2, &t3, r);
    split(t2, &t1, &t2, l - 1);
    write(t2->sum);
    putchar_unlocked('\n');
    *t = merge(t1, merge(t2, t3));
}

void insert(Treap** t, int pos, ll v)
{
    Treap *t1 = NULL, *t2 = NULL;
    split(*t, &t1, &t2, pos);
    *t = merge(t1, merge(newTreap(v), t2));
}

void _remove(Treap** t, int pos)
{
    Treap *t1 = NULL, *t2 = NULL, *t3 = NULL;
    split(*t, &t2, &t3, pos);
    split(t2, &t1, &t2, pos - 1);
    pushdown(t2);
    *t = merge(t1, t3);
}

void reverse(Treap** t, int l, int r)
{
    if (l != r)
    {
        Treap *t1 = NULL, *t2 = NULL, *t3 = NULL;
        split(*t, &t2, &t3, r);
        split(t2, &t1, &t2, l - 1);
        t2->rev ^= 1;
        *t = merge(t1, merge(t2, t3));
    }
}

void swap_interval(Treap** t, int l, int r, int x, int y)
{
    Treap *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *t5 = NULL;
    split(*t, &t4, &t5, y);
    split(t4, &t3, &t4, x - 1);
    split(t3, &t2, &t3, r);
    split(t2, &t1, &t2, l - 1);
    *t = merge(t1, merge(t4, merge(t3, merge(t2, t5))));
}

void tag(Treap** t, ll k)
{
    Treap* treap = *t;
    if (!(treap)) return;
    if (treap->maxx < k)
    {
        return;
    }
    if (treap->second_maxx < k)
    {
        treap->sum -= (treap->maxx - k) * treap->max_cnt;
        treap->ass = treap->maxx = k;
        return;
    }
    treap->ass = k;
    pushdown(treap);
    tag(&(treap->l), k);
    tag(&(treap->r), k);
    pullup(treap);
}

void _assign(Treap** t, int l, int r, ll k)
{
    Treap *t1 = NULL, *t2 = NULL, *t3 = NULL;
    split(*t, &t2, &t3, r);
    split(t2, &t1, &t2, l - 1);
    tag(&t2, k);
    *t = merge(t1, merge(t2, t3));
}

int main()
{
    int N, Q;
    N = read(), Q = read();
    Treap *t;
    build(&t, N);
    int op, p, l, r, x, y, k;
    for (int i = 0; i < Q; i++)
    {
        op = read();
        switch (op)
        {
        case 1: // insert k to pth
            p = read(), k = read();
            insert(&t, p, k);
            break;

        case 2: // delete pth
            p = read();
            _remove(&t, p);
            break;    

        case 3: // reverse [l, r]
            l = read(), r = read();
            reverse(&t, l, r);
            break;   

        case 4: // swap [l, r], [x, y]
            l = read(), r = read(), x = read(), y = read();
            if (x < l)
            {
                int _ = x;
                x = l;
                l = _;
                _ = y;
                y = r;
                r = _;
            }
            swap_interval(&t, l, r, x, y);
            break;

        case 5: // assign ele in [l, r] that greater than k to be k
            l = read(), r = read(), k = read();
            _assign(&t, l, r, k);
            break;
        case 6: // output sum of [l, r]
            l = read(), r = read();
            getIntervalSum(&t, l, r);
            break;

        }
    }
}