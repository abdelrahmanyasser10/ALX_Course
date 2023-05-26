#include <stdio.h>
#include <stdbool.h>

int main()
{
    int N, k;
    while (scanf("%d %d", &N, &k) == 2 && N != 0 && k != 0)
    {
        int grant[N];
        for (int i = 0; i < N; i++)
            grant[i] = 0;
        int store = 0;
        int nextStore = 1;
        int student = 0;
        bool done[N];
        for (int i = 0; i < N; i++)
            done[i] = false;
        int count = 0;
        while (count < N)
        {
            if (!done[student])
            {
                if (store == 0)
                {
                    store = nextStore;
                    nextStore++;
                    if (nextStore > k)
                        nextStore = 1;
                }
                if (grant[student] + store >= 40)
                {
                    store -= (40 - grant[student]);
                    grant[student] = 40;
                    done[student] = true;
                    printf("%d  ", student + 1);
                    count++;
                }
                else
                {
                    grant[student] += store;
                    store = 0;
                }
            }
            student++;
            if (student >= N)
                student = 0;
        }
        printf("\n");
    }
    return 0;
}
