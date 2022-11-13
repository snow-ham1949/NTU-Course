#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define maxcmd 10

// #define DEBUG

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

int m, n, k;
List** room_group_order;
List*** room;
int** usable_room;

Node* newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->np = NULL;
    return node;
}

List* newList()
{
    List *list = (List *)malloc(sizeof(List));
    list->sz = 0;
    list->head = list->tail = NULL;
    return list;
}

Node* xor(Node *a, Node *b)
{
    return (Node *)((uintptr_t)(a) ^ (uintptr_t)(b));
}

void PushTail(List *list, Node *node)
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

void Pop(List *list, bool at_tail)
{
    if (at_tail) // pop tail
    {
        assert(list->tail != NULL);
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
    }
    else // pop head
    {
        assert(list->head != NULL);
        Node *node = list->head;
        Node *next = xor(node->np, NULL);

        if (!next)
        {
            list->head = list->tail = NULL;
        }
        else
        {
            next->np = xor(next->np, node);
            list->head = next;
        }
    }
    list->sz--;
}

void Reverse(List *list)
{
    Node *node = list->head;
    list->head = list->tail;
    list->tail = node;
}

void Connect(List *a, List *b)
{
    // connect b to a's tail
    a->tail->np = xor(a->tail->np, b->head);
    b->head->np = xor(b->head->np, a->tail);
    a->tail = b->tail;
    a->sz += b->sz;
    b->sz = 0;
}

void Enter(int bathroom, int group, Node *node)
{
    List *list = room[bathroom][group];
    if (list->sz == 0)
    {
        Node *node = newNode(group);
        PushTail(room_group_order[bathroom], node);
    }
    PushTail(room[bathroom][group], node);
}

void Go(int bathroom)
{
    List *group_list = room_group_order[bathroom];
    int g = group_list->head->data;
    List *list = room[bathroom][g];
    Pop(list, false);

    if (list->sz == 0)
    {
        Pop(group_list, false);
    }
}

void Leave(int bathroom)
{
    List *group_list = room_group_order[bathroom];
    int g = group_list->tail->data;
    List *list = room[bathroom][g];
    Pop(list, true);

    if (list->sz == 0)
    {
        Pop(group_list, true);
    }
}

void Close(int bathroom)
{
    int pre = usable_room[bathroom][0], nxt = usable_room[bathroom][1];
    usable_room[pre][1] = nxt, usable_room[nxt][0] = pre;
    int new_room = pre;

    List *list = room_group_order[bathroom];

    if (list->sz == 0)
    {
        return;
    }
    // clear
    list->sz = 0;

    // start connecting
    Reverse(list);
    Node *curr = list->head, *prev = NULL, *next;
    while (curr)
    {
        int g = curr->data;
        List *new_list = room[new_room][g], *old_list = room[bathroom][g];
        Reverse(old_list);
        if (new_list->sz == 0)
        {
            room[new_room][g] = old_list;
            Node *node = newNode(g);
            PushTail(room_group_order[new_room], node);
        }
        else
        {
            Connect(new_list, old_list);
        }

        next = xor(prev, curr->np);
        prev = curr;
        curr = next;
    }
}

void PrintList(List *list)
{
    Node *curr = list->head, *prev = NULL, *next;
    while (curr)
    {
        printf("%d ", curr->data);
        next = xor(prev, curr->np);
        prev = curr;
        curr = next;
    }
}

void PrintRoom()
{
    for (int r = 0; r < m; r++)
    {
#ifdef  DEBUG
        printf("room #%d: ", r);
#endif  //DEBUG
        List *list = room_group_order[r];
        if (list->sz == 0)
        {
            puts("");
            continue;
        }

        Node *curr = list->head, *prev = NULL, *next;
        while (curr)
        {
            int g = curr->data;
            PrintList(room[r][g]);
            next = xor(prev, curr->np);
            prev = curr;
            curr = next;
        }
        puts("");
    }
#ifdef  DEBUG
    puts("");
#endif  //DEBUG
}

int main()
{

    scanf("%d %d %d", &m, &n, &k);

    // initialize
    room_group_order = (List **)malloc(sizeof(List *) * m);
    room = (List ***)malloc(sizeof(List **) * m);
    for (int i = 0; i < m; i++)
    {
        room[i] = (List **)malloc(sizeof(List *) * k);
    }
    usable_room = (int **)malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
    {
        usable_room[i] = (int *)malloc(sizeof(int) * 2);
    }

    for (int i = 0; i < m; i++)
    {
        room_group_order[i] = newList();
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            room[i][j] = newList();
        }
    }

    for (int i = 0; i < m; i++)
    {
        usable_room[i][0] = (i - 1 + m) % m;
        usable_room[i][1] = (i + 1) % m;
    }

    char cmd[maxcmd];
    int group, id, bathroom;
    for (int i = 0; i < n; i++)
    {
        scanf("%s", cmd);
        if (!strcmp(cmd, "enter"))
        {
            scanf("%d %d %d", &group, &id, &bathroom);
            Node *node = newNode(id);
            Enter(bathroom, group, node);
        }
        else if (!strcmp(cmd, "go"))
        {
            scanf("%d", &bathroom);
            Go(bathroom);
        }
        else if (!strcmp(cmd, "leave"))
        {
            scanf("%d", &bathroom);
            Leave(bathroom);
        }
        else
        {
            scanf("%d", &bathroom);
            Close(bathroom);
        }

#ifdef  DEBUG
        PrintRoom();
#endif  //DEBUG
    }

    PrintRoom();

    return 0;
}