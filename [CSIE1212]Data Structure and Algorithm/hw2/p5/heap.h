#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define maxn 2000000
#define ull unsigned long long

typedef struct _Data {
    ull price;
    int stock;
} Data;

typedef struct _Heap {
    Data* arr;
    int sz, capacity;
} Heap;

Heap* newHeap();
void Push(Heap *heap, Data key);
void HeapifyUp(Heap *heap, int id);
void HeapifyDown(Heap *heap, int p);
Data Top(Heap *heap);
void Pop(Heap *heap);


