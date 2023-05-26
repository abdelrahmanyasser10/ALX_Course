/*start program
initialize sum = 0
use a loop keeps runing while the entered value is not less than zero
    input x
    if x < 0:
       break
    sum = sum + x

print sum
end program
*/

#include <stdio.h>
#include <stdbool.h>

int main()
{
  int sum = 0;
  int x = 0;
  while (true)
  {
    printf("x: ");
    scanf("%d", &x);
    if (x < 0)
      break;
    sum += x;
  }

  printf("sum = %d\n", sum);
  return 0;
}
