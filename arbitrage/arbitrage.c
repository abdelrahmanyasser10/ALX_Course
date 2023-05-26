`#include<stdio.h>
#include <stdbool.h>

#define MAXN 20

    int n;
double rates[MAXN + 1][MAXN + 1];
double profit[MAXN + 1][MAXN + 1][MAXN + 1];
int next[MAXN + 1][MAXN + 1][MAXN + 1];

void print_path(int i, int j, int s)
{
    if (s == 0)
    {
        printf("%d", i);
    }
    else
    {
        print_path(i, next[i][j][s], s - 1);
        printf(" %d", j);
    }
}

bool find_arbitrage()
{
    for (int s = 1; s <= n; s++)
    {
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    double p = profit[i][k][s - 1] * rates[k][j];
                    if (p > profit[i][j][s])
                    {
                        profit[i][j][s] = p;
                        next[i][j][s] = k;
                    }
                }
            }
        }
    }

    for (int s = 1; s <= n; s++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (profit[i][i][s] > 1.01)
            {
                print_path(i, i, s);
                printf("\n");
                return true;
            }
        }
    }

    return false;
}

int main()
{
    while (scanf("%d", &n) == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                {
                    rates[i][j] = 1.0;
                }
                else
                {
                    scanf("%lf", &rates[i][j]);
                }
                profit[i][j][0] = rates[i][j];
            }
        }

        if (!find_arbitrage())
        {
            printf("no arbitrage sequence exists\n");
        }
    }

    return 0;
}
