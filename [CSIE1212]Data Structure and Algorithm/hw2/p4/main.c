#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#define maxN 1000000 + 10

// #define DEBUG

int N, Q, S, R;
bool vis[maxN] = {false};

typedef struct _Node
{
    int data;
    struct _Node *np;
} Node;

typedef struct _LinkedList
{
    int sz;
    Node *head, *tail;
} List;

List** adj;

Node* newNode(int data)
{
    Node *node = malloc(sizeof(Node));
    node->data = data, node->np = NULL;
    return node;
}

List* newList()
{
    List *list = malloc(sizeof(List));
    list->sz = 0;
    list->head = list->tail = NULL;
    return list;
}

Node* xor(Node *a, Node *b)
{
    return (Node *)((uintptr_t)(a) ^ (uintptr_t)(b));
}

void Push(List* list, Node* node)
{
    node->np = xor(list->tail, NULL);

    if (!list->tail) // empty list
    {
        list->head = list->tail = node;
    }
    else
    {
        list->tail->np = xor(list->tail->np, node);
        list->tail = node;
    }
    list->sz++;
}

void Pop(List* list)
{
    Node *node = list->tail;
    Node *prev = xor(node->np, NULL);
    if (!prev)
    {
        list->head = list->tail = NULL;
    }
    else
    {
        prev->np = xor(prev->np, node);
        list->tail = prev;
    }
    list->sz--;
}

void printList(List* list)
{
    Node *cur = list->head, *pre = NULL, *nxt;
    while (cur)
    {
        printf("%d ", cur->data);
        nxt = xor(cur->np, pre);
        pre = cur;
        cur = nxt;
    }
    puts("");
}

int dfs(int cur_node, int len, int path[]) 
{
    if (cur_node == S)
    {
        return len;
    }

    vis[cur_node] = true;

    List *list = adj[cur_node];
    Node *cur = list->head, *pre = NULL, *nxt;
    while (cur)
    {
        int city = cur->data;
        assert(city != 0);
        if (vis[city])
        {
            nxt = xor(cur->np, pre);
            pre = cur;
            cur = nxt;
            continue;
        }
        path[len] = city;
        int length = dfs(city, len + 1, path);
        if (length > 0)
        {
            return length;
        }
        vis[city] = false;
        path[len] = -1;
        nxt = xor(cur->np, pre);
        pre = cur;
        cur = nxt;
    }

    return 0;
}

void set_path(int cur_node, int src, int ans[])
{
    List *list = adj[cur_node];
    Node *cur = list->head, *pre = NULL, *nxt;
    while (cur)
    {
        int city = cur->data;
        assert(city != 0);
        if (ans[city] == -1)
        {
            ans[city] = src;
            set_path(city, src, ans);
        }
        nxt = xor(cur->np, pre);
        pre = cur;
        cur = nxt;
    }
}

int main()
{
    scanf("%d %d %d %d", &N, &Q, &S, &R);

    adj = (List **)malloc(sizeof(List *) * (N + 5));

    for (int i = 1; i <= N; i++)
    {
        adj[i] = newList();
    }

    for (int i = 0; i < N - 1; i++)
    {
        int s, e;
        scanf("%d %d", &s, &e);
        Node *node_e = newNode(e), *node_s = newNode(s);
        Push(adj[s], node_e);
        Push(adj[e], node_s);
    }

#ifdef  DEBUG
    for (int i = 1; i <= N; i++)
    {
        List *list = adj[i];
        printf("node #%d: ", i);
        printList(list);
    }
#endif  //DEBUG

    int path[N + 5];
    path[0] = R;
    int len = dfs(R, 1, path);

    int ans[N + 5];
    for (int i = 1; i <= N; i++)
    {
        ans[i] = -1;
    }
    for (int i = 0; i < len; i++)
    {
        ans[path[i]] = path[i];
    }

#ifdef  DEBUG
    for (int i = 1; i <= N; i++)
    {
        printf("%d ", ans[i]);
    }
    puts("");
#endif  //DEBUG

    for (int i = 0; i < len; i++)
    {
        set_path(path[i], path[i], ans);
    }


    int c;
    for (int i = 0; i < Q; i++)
    {
        scanf("%d", &c);
        printf("%d\n", ans[c]);
    }

    return 0;
}