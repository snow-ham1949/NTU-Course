#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define maxm 1000000 + 10

typedef struct Node{
    int id, group;
    struct Node *np;
} Node;

typedef struct Linked_List {
    int sz;
    Node *head, *tail;
} LL;

int room_sz[maxm], usable_room[maxm][2];
LL *queue[maxm] = {NULL}, *group[maxm] = {NULL};

Node* newNode(int group, int id)
{
    Node *node = malloc(sizeof(Node));
    node->group = group, node->id = id;
    node->np = NULL;
    return node;
}

LL* newList()
{
    LL *list = malloc(sizeof(LL));
    list->head = list->tail = NULL;
    list->sz = 0;
    return list;
}

Node* xor(Node* a, Node* b)
{
    return (Node *)((uintptr_t) a ^ (uintptr_t) b);
}

void Insert(LL* list, Node* node)
{
    if (!list->tail)
    {
        list->head = list->tail = node;
        node->np = NULL;
        list->sz++;
    }
    else
    {
        node->np = xor(list->tail, NULL);
        list->tail->np = xor(node, xor(list->tail->np, NULL));
        list->tail = node;
        list->sz++;
    }
}

void Delete(LL* list, bool at_tail)
{
    if (at_tail)
    {
        Node* node = list->tail;
        Node* prev = xor(node->np, NULL);
        if (!prev)
        {
            list->head = NULL;
        }
        else
        {
            prev->np = xor(node, xor(prev->np, NULL));
        }
        list->tail = prev;
    }
    else
    {
        Node* node = list->head;
        Node* next = xor(node->np, NULL);
        if (!next)
        {
            list->tail = NULL;
        }
        else
        {
            next->np = xor(node, xor(next->np, NULL));
        }
        list->head = next;
    }
}

void Connect(LL* a, LL* b)
{
    a->tail->np = xor(b->head, xor(a->tail->np, NULL));
    b->head->np = xor(a->tail, xor(b->head->np, NULL));
    a->tail = b->tail;
    a->sz += b->sz;
    b->sz = 0;
}

void display(LL *list)
{
    Node *cur = list->head, *pre = NULL, *nxt;
    while (cur)
    {
        printf("%d ", cur->id);
        nxt = xor(pre, cur->np);
        pre = cur;
        cur = nxt;
    }
    puts("");
}

int main()
{
    LL *list = newList();
    bool at_tail = true;
    for (int i = 0; i < 10; i++)
    {
        Node *n = newNode(i, i);
        Insert(list, n);
    }

    LL *tmp_list = newList();
    for (int i = 10; i < 20; i++)
    {
        Node *n = newNode(i, i);
        Insert(tmp_list, n);
    }

    Connect(list, tmp_list);
    display(list);

    return 0;
}
