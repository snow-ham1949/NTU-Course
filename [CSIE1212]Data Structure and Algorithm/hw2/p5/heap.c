#include "heap.h"

int Parent(int i)
{
    return (i - 1) / 2;
}

int Left(int i)
{
    return 2 * i + 1;
}

int Right(int i)
{
    return 2 * i + 2;
}

Heap* newHeap()
{
    Heap* heap = calloc(1, sizeof(Heap));
    heap->arr = calloc(maxn, sizeof(Data));
    heap->sz = 0;
    return heap;
}

void HeapifyUp(Heap *heap, int id)
{
    if (id && heap->arr[Parent(id)].price > heap->arr[id].price)
    {
        Data tmp = heap->arr[Parent(id)];
        heap->arr[Parent(id)] = heap->arr[id];
        heap->arr[id] = tmp;
        HeapifyUp(heap, Parent(id));
    }
}

void HeapifyDown(Heap *heap, int p)
{
    int l = Left(p), r = Right(p);
    int minn = p;
    if (l < heap->sz && heap->arr[l].price < heap->arr[minn].price)
    {
        minn = l;
    }
    if (r < heap->sz && heap->arr[r].price < heap->arr[minn].price)
    {
        minn = r;
    }

    if (minn != p)
    {
        Data tmp = heap->arr[minn];
        heap->arr[minn] = heap->arr[p];
        heap->arr[p] = tmp;
        HeapifyDown(heap, minn);
    }
}

Data Top(Heap *heap)
{
    return heap->arr[0];
}

void Pop(Heap *heap)
{
    heap->arr[0] = heap->arr[heap->sz - 1];
    heap->sz--;
    HeapifyDown(heap, 0);
}

void Push(Heap *heap, Data key)
{
    heap->arr[heap->sz] = key;
    HeapifyUp(heap, heap->sz);
    heap->sz++;
}