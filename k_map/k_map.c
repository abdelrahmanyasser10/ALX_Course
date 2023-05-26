#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INPUTS 8 // maximum number of inputs

int num_inputs;       // number of inputs
int num_combinations; // number of input combinations
int *inputs;          // array to store input combinations
int *outputs;         // array to store output values
int **map;            // Karnaugh map

void generate_inputs()
{
    int i, j;
    num_combinations = pow(2, num_inputs);
    inputs = (int *)malloc(num_combinations * num_inputs * sizeof(int));
    for (i = 0; i < num_combinations; i++)
    {
        for (j = 0; j < num_inputs; j++)
        {
            inputs[i * num_inputs + j] = (i >> j) & 1;
        }
    }
}

void read_outputs()
{
    int i;
    outputs = (int *)malloc(num_combinations * sizeof(int));
    printf("Enter the logic values of the output for each input combination:\n");
    for (i = 0; i < num_combinations; i++)
    {
        printf("Input combination %d: ", i);
        scanf("%d", &outputs[i]);
    }
}

void print_truth_table()
{
    int i, j;
    printf("Truth Table:\n");
    printf("| ");
    for (i = num_inputs; i > 0; i--)
    {
        printf("A%d | ", i - 1);
    }
    printf("Output |\n");
    for (i = 0; i < num_combinations; i++)
    {
        printf("| ");
        for (j = num_inputs - 1; j >= 0; j--)
        {
            printf("%d  | ", inputs[i * num_inputs + j]);
        }
        printf("%d     |\n", outputs[i]);
    }
}

void generate_map()
{
    int i, j;
    int num_rows = pow(2, (int)ceil(num_inputs / 2.0)); // number of rows in map
    int num_cols = pow(2, num_inputs / 2);              // number of columns in map
    map = (int **)malloc(num_rows * sizeof(int *));
    for (i = 0; i < num_rows; i++)
    {
        map[i] = (int *)malloc(num_cols * sizeof(int));
        for (j = 0; j < num_cols; j++)
        {
            map[i][j] = -1; // initialize map to -1
        }
    }
    for (i = 0; i < num_combinations; i++)
    {
        int row = 0, col = 0;
        for (j = num_inputs - 1; j >= 0; j--)
        {
            if (j >= (num_inputs / 2))
            {
                row = row + (inputs[i * num_inputs + j] << (j - (num_inputs / 2)));
            }
            else
            {
                col = col + (inputs[i * num_inputs + j] << j);
            }
        }
        map[row][col] = outputs[i]; // set map value
    }
}

void print_map()
{
    int i, j;
    printf("Karnaugh Map:\n");
    printf(" ");
    for (i = 0; i < pow(2, num_inputs / 2); i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < pow(2, (int)ceil(num_inputs / 2.0)); i++)
    {
        printf("%d ", i);
        for (j = 0; j < pow(2, num_inputs / 2); j++)
        {
            if (map[i][j] == -1)
            {
                printf("  ");
            }
            else
            {
                printf("%d ", map[i][j]);
            }
        }
        printf("\n");
    }
}

int is_power_of_two(int n)
{
    return (n & (n - 1)) == 0; // check if n is a power of 2
}

void simplify_map()
{
    int i, j, k, l;
    int num_rows = pow(2, (int)ceil(num_inputs / 2.0));
    int num_cols = pow(2, num_inputs / 2);
    int **map_copy = (int **)malloc(num_rows * sizeof(int *));
    for (i = 0; i < num_rows; i++)
    {
        map_copy[i] = (int *)malloc(num_cols * sizeof(int));
        for (j = 0; j < num_cols; j++)
        {
            map_copy[i][j] = map[i][j];
        }
    }
    // Simplify rows
    for (i = 0; i < num_rows; i++)
    {
        for (j = 0; j < num_cols; j++)
        {
            if (map[i][j] != -1)
            {
                for (k = j + 1; k < num_cols; k++)
                {
                    if (map[i][k] == map[i][j])
                    {
                        map[i][k] = -1;
                    }
                    else
                    {
                        break;
                    }
                }
                if (is_power_of_two(j + 1) && j + 1 == k - 1)
                {
                    for (l = 0; l < num_cols; l++)
                    {
                        if (l < j || l >= k)
                        {
                            map[i][l] = -1;
                        }
                    }
                }
            }
        }
    }
    // Simplify columns
    for (j = 0; j < num_cols; j++)
    {
        for (i = 0; i < num_rows; i++)
        {
            if (map[i][j] != -1)
            {
                for (k = i + 1; k < num_rows; k++)
                {
                    if (map[k][j] == map[i][j])
                    {
                        map[k][j] = -1;
                    }
                    else
                    {
                        break;
                    }
                }
                if (is_power_of_two(i + 1) && i + 1 == k - 1)
                {
                    for (l = 0; l < num_rows; l++)
                    {
                        if (l < i || l >= k)
                        {
                            map[l][j] = -1;
                        }
                    }
                }
            }
        }
    }
    // Combine simplified terms
    for (i = 0; i < num_rows; i++)
    {
        for (j = 0; j < num_cols; j++)
        {
            if (map[i][j] != -1)
            {
                int term = i * pow(2, num_inputs / 2) + j;
                for (k = i; k < num_rows; k++)
                {
                    for (l = j; l < num_cols; l++)
                    {
                        if (map[k][l] == map[i][j])
                        {
                            map[k][l] = -1;
                        }
                    }
                }
                printf("%c", term < pow(2, num_inputs - 1) ? 'A' : 'B');
                if (num_inputs > 1)
                {
                    printf("%d", term % (int)pow(2, num_inputs - 1));
                }
                printf(" + ");
            }
        }
    }
    printf("\b\b  \n"); // remove last "+"
}

int main()
{
    int i;
    printf("Enter the number of inputs (maximum %d): ", MAX_INPUTS);
    scanf("%d", &num_inputs);
    if (num_inputs < 1 || num_inputs > MAX_INPUTS)
    {
        printf("Invalid number of inputs.\n");
        return 1;
    }
    generate_inputs();
    read_outputs();
    print_truth_table();
    generate_map();
    print_map();
    printf("Simplified output equation: ");
    simplify_map();
    free(inputs);
    free(outputs);
    for (i = 0; i < pow(2, (int)ceil(num_inputs / 2.0)); i++)
    {
        free(map[i]);
    }
    free(map);
    return 0;
}