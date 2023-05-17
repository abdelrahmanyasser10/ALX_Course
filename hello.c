#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void hello(char *);

int main(void)
{
  char *name = (char *)malloc(sizeof(char) * 20);
  printf("What's Your name? ");
  fgets(name,20,stdin);
  hello(name);
  return 0;
}

void hello(char *name){
  printf("hello, %s",name);
}
