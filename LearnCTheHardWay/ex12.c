#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  if (argc == 1) {
    // argc is an integer compared against 1
    // argc is the count of arguments
    printf("You only have one fucking argument. You fucking suck\n");
    printf("%i\n", argc);
    // && is considered to be a boolean operator
  } else if (argc > 1 && argc < 4) {
    printf("Here is your fucking arguments:\n");

    // this for loop will print out all the arguments
    // it sets i to zero
    // if is less than the argument count run the code
    // then increment i plus one with ++
    for (i = 0; i < argc; i++) {
      // this code will run if i is less than argc count
      printf("%s ", argv[i]);
    }
    printf("\n");
    // this is to print this shit out
    printf("%i\n", argc);
  } else {
    // the else clause will run this code if the if condition test or the else if condition test fail
    printf("%i\n", argc);
    printf("You have too many arguments. You fucking suck.\n");
  }

  return 0;
}
