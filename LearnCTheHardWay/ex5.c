// this is including the header file for functions in
// standard IO
#include <stdio.h>

// this is a multiline comment
/* This is a comment. */

// this is the standar main function, with argument
// that can get passed in on the command line
int main(int argc, char *argv[])
{
  // initialize a variable distance of a type int to value 100
  int distance = 100;

  // this is also a comment
  printf("You are %d miles away.\n", distance);

  // return 0 for a non-error exit status
  return 0;
}
