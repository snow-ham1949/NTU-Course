#include <stdio.h>
#include <string.h>
#include <time.h>

#define MINN -50
#define MAXN 50

int main() {
    int storage[MAXN - MINN + 1] = {0};
    int *ary = &(storage[50]);

    for (int i = MINN; i <= MAXN; ++i) {
        ary[i] = i;
    }

    for (int i = MINN; i <= MAXN; ++i) {
        printf("%d ", ary[i]);
    }

    return 0;
}
