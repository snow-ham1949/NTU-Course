#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define maxlen 5
#define maxn 1000000 + 10
int m;

// #define DEBUG

typedef struct Node
{
    int id, group;
    struct Node* nxt;
    struct Node* prev;
} Node;

Node* rooms_tail[maxn] = {NULL}; // record the position of the last person in every group
Node* rooms_head[maxn] = {NULL};
int room_sz[maxn]; // -1 if close

Node* newNode(int id, int group)
{
    Node* node = (Node *)malloc(sizeof(Node));
    node->id = id, node->group = group;
    node->prev = node->nxt = NULL;
    return node;
}

void Enter(int room, Node* node)
{
    if (room_sz[room] == 0)
    {
        rooms_tail[room] = node;
        rooms_head[room] = node;
    }
    else
    {
        Node* tail = rooms_tail[room];
        while (tail != NULL && tail->group != node->group)
        {
            tail = tail->prev;
        }
        if (!tail)
        {
            Node* original_tail = rooms_tail[room];
            original_tail->nxt = node;
            node->prev = original_tail;
            rooms_tail[room] = node;
        }
        else
        {     
            if (tail->nxt)
            {
                Node *next = tail->nxt;
                tail->nxt = node;
                node->prev = tail;
                node->nxt = next;
                next->prev = node;
            }
            else
            {
                tail->nxt = node;
                node->prev = tail;
                rooms_tail[room] = node;
            }      
        }          
    }
    room_sz[room]++;
}

void Leave(int room)
{
    if (room_sz[room] > 1)
    {
        Node* newtail = rooms_tail[room]->prev;
        newtail->nxt = NULL;
        rooms_tail[room] = newtail;
        // free(tail);
    }
    else
    {
        rooms_tail[room] = NULL;
        rooms_head[room] = NULL;
    }
    room_sz[room]--;
}

void Go(int room)
{
    if (room_sz[room] == 1)
    {
        rooms_tail[room] = NULL;
        rooms_head[room] = NULL;
    }
    else
    {
        Node* next = rooms_head[room]->nxt;
        rooms_head[room] = next;
        next->prev = NULL;
    }
    room_sz[room]--;
}

void Close(int room)
{
    room_sz[room] = -1;
    Node *tail = rooms_tail[room], *pre = tail->prev;
    rooms_head[room] = rooms_tail[room] = NULL;
    while (room_sz[room] == -1)
    {
        room = (room - 1 + m) % m;
    }
    while (tail)
    {
        pre = tail->prev;
        tail->nxt = tail->prev = NULL;
        Enter(room, tail);
        tail = pre;
        pre = pre->prev;
    }
    
}

void print_condition()
{
    for (int i = 0; i < m; i++)
    {
#ifdef  DEBUG
        printf("room %d:", i);
#endif  //DEBUG
        if (room_sz[i] <= 0)
        {
            puts("");
        }
        else
        {
            Node* head = rooms_head[i];
            while (head)
            {
                printf("%d ", head->id);
                head = head->nxt;
            }
            printf("\n");
        }
    }
#ifdef  DEBUG
    puts("");
#endif  //DEBUG
}

int main()
{
    int n, k;
    scanf("%d %d %d", &m, &n, &k);
    char cmd[maxlen];
    int id, group, room;
    memset(room_sz, 0, sizeof(int)*maxn);

    for (int i = 0; i < n; i++)
    {
        scanf("%s", cmd);
        if (!strcmp(cmd, "enter"))
        {
            scanf("%d %d %d", &group, &id, &room);
            Node* node = newNode(id, group);
            Enter(room, node);
        }
        else if (!strcmp(cmd, "leave"))
        {
            scanf("%d", &room);
            Leave(room);
        }
        else if (!strcmp(cmd, "go"))
        {
            scanf("%d", &room);
            Go(room);
        }
        else // close
        {
            scanf("%d", &room);
            Close(room);
        }

#ifdef  DEBUG
        print_condition();
#endif  //DEBUG
    }       

    print_condition();
    
    return 0;
}