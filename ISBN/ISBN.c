#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool verify_isbn(char *isbn);

int main()
{
    char isbn[81];
    while (fgets(isbn, sizeof(isbn), stdin))
    {
        isbn[strcspn(isbn, "\n")] = '\0';
        printf("%s %s\n", isbn, verify_isbn(isbn) ? "is correct" : "is incorrect");
    }
    return 0;
}

bool verify_isbn(char *isbn)
{
    int s1 = 0;
    int s2 = 0;
    int count = 0;
    for (int i = 0; i < strlen(isbn); i++)
    {
        if (isbn[i] >= '0' && isbn[i] <= '9')
        {
            count++;
            s1 += isbn[i] - '0';
            s2 += s1;
        }
        else if (count == 9 && isbn[i] == 'X')
        {
            count++;
            s1 += 10;
            s2 += s1;
        }
    }
    return count == 10 && s2 % 11 == 0;
}