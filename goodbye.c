#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void goodbye(char *);

int main(void)
{
  char *name = (char *)malloc(sizeof(char) * 20);
  printf("What's Your name? ");
  fgets(name,20,stdin);
  goodbye(name);
  return 0;
}

void goodbye(char *name){
  printf("goodbye, %s",name);
}
