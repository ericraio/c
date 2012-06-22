#include <stdio.h>

int main(int argc, char  *argv[])
{
  // argc is the number of arguments
  // argv is the array to the strings
  // it's an array of strings
  if (argv[0][2] == 'e') {
    int i = 0;
    while(i < argc) {
      printf("arg %d: %s\n", i, argv[i]);
      i++;
    }
  }

  // let's make our own array of strings
  char *states[] = {
    "California", "Oregon",
    "Washington", "Texas"
  };

  int num_states = 4;
  int i = 0;
  while(i<num_states) {
    printf("state %d: %s\n", i, states[i]);
    i++;
  }


  return 0;
}
