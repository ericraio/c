#include <stdio.h>
// Include a new header file so we can gain access to isalpha and isblank
#include <ctype.h>

// forward declaration //
int can_print_it(char ch);
// Tell C that you will be using some functions later in your program,
// with out having to actually define them, this is "forward declaration"
// and it solves the chicken-and-egg problem of needing to use a function 
// before you've defined it
void print_letters(char arg[]);

// Defined the print_arguments which knows how to print the same
// array of string that main typically gets.
void print_arguments(int argc, char *argv[])
{
  int i = 0;

  for (i = 0; i < argc; i++) {
    print_letters(argv[i]);
  }
}

// define the next function print_letters that is called by print_arguments
// and knows how to print each of the character and their code
void print_letters(char arg[])
{
  int i = 0;
  for (i = 0; arg[i] != '\0'; i++) {
    char ch = arg[i];

    if (can_print_it(ch)) {
      printf("'%c' == %d ", ch, ch);
    }
  }

  printf("\n");
}

// define can_print_int which simply returns the trueth value (0
// or 1) of isalpha(ch) || isblank(ch) back to its caller print_letters
int can_print_it(char ch)
{
  return isalpha(ch) || isblank(ch);
}

// finally main simply calls print_arguments to make the whole chain of function calls go
int main(int argc, char *argv[])
{
  print_arguments(argc, argv);
  return 0;
}
