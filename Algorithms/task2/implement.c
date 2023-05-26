#include <stdio.h>

int main()
{
    int n;
    printf("n: ");
    scanf("%d", &n);
    int sum = 0;
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        printf("x%d: ", i + 1);
        scanf("%d", &x);
        sum += x * x;
    }
    printf("sum = %d\n", sum);
    return 0;
}