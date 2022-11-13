#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int arr[5] = {5, 5, 1, 5, 2};

    int n = 5;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] <= n)
        {
            arr[abs(arr[i]) - 1] *= (-1);
        }
    }

    int missing = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0)
        {
            missing = i + 1;
            break;
        }
    }

    printf("miss: %d\n", missing);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
