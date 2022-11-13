#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// #define DEBUG

#ifdef  DEBUG
#include <time.h>
#endif  //DEBUG

struct node {
  int val, dep, lc, rc;
} *tree; 

int n, m, tot, *root, *fa;
int *ans;

int build(int l, int r)
{
    int now = ++tot;
    if (l == r)
    {
        tree[now].val = fa[l];
        tree[now].dep = 1;
        return now;
    }
    int mid = (l + r) >> 1;
    tree[now].lc = build(l, mid);
    tree[now].rc = build(mid + 1, r);
    return now;
}

int update(int pre, int l, int r, int pos, int new)
{
    int now = ++tot;
    tree[now] = tree[pre];
    if (l == r)
    {
        tree[now].val = new;
        #define max(a, b) a > b ? a : b
        tree[new].dep = max(tree[new].dep, tree[now].dep + 1);
        return now;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) tree[now].lc = update(tree[pre].lc, l, mid, pos, new);
    else tree[now].rc = update(tree[pre].rc, mid + 1, r, pos, new);
    return now;
}

int query(int now, int l, int r, int pos)
{
    if (l == r) return tree[now].val;
    int mid = (l + r) >> 1;
    if (pos <= mid) return query(tree[now].lc, l, mid, pos);
    else return query(tree[now].rc, mid + 1, r, pos);
}

int find(int now, int pos)
{
    int p = query(now, 1, n, pos);
    return p == pos ? p : find(now, p);
}

void merge(int now, int x, int y)
{
    x = find(root[now - 1], x), y = find(root[now - 1], y);
    if (x == y)
    {
        ans[now] = ans[now - 1];
    }
    else
    {
        ans[now] = ans[now - 1] - 1;
    }
    if (tree[x].dep < tree[y].dep)
    {
        root[now] = update(root[now - 1], 1, n, x, y);
    }
    else
    {
        root[now] = update(root[now - 1], 1, n, y, x);
    }
}

void write(int x) {
    int sta[35];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) putchar_unlocked(sta[--top] + 48);  // 48 是 '0'
}

int read() {
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

int main()
{
#ifdef  DEBUG
    clock_t start, end;
    start = clock();
#endif  //DEBUG
    // scanf("%d%d", &n, &m);
    n = read(), m = read();
    // assert(m < 1000);
    tree = malloc(sizeof(struct node) * (4 * n + m * 22));
    fa = malloc(sizeof(int) * (n + 5));
    root = malloc(sizeof(int) * (m + 5));
    ans = malloc(sizeof(int) * (m + 5));

    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
    root[0] = build(1, n);
    ans[0] = n;
    char cmd[10];
    int a, b, k;
    // ans[0] = n;
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", cmd);
        
        if (!strcmp(cmd, "merge"))
        {
            a = read(), b = read();
            merge(i, a, b);
        }
        else if (!strcmp(cmd, "query"))
        {
            root[i] = root[i - 1];
            ans[i] = ans[i - 1];
            write(ans[i]);
            puts("");
        }
        else
        {
            k = read();
            root[i] = root[k];
            ans[i] = ans[k];
        }
    }

#ifdef  DEBUG
    end = clock();
    printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
#endif  //DEBUG

    return 0;
}