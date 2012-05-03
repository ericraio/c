// includes standard io library
#include <stdio.h>

// the start of a normal C program
int main(int argc, char *argv[])
{
  // sets up the bugs variable with the integer type for fake data
  int bugs = 100;
  // sets up the bug_rate variable with the double type for fake data
  double bug_rate = 1.2;

  // prints out these 2 variables, nothing new here
  printf("You have %d bugs imaginary rate of %f.\n",
      bugs, bug_rate);

  // Declare a huge number usinga new type long for storing big numbers
  long universe_of_defects = 1L * 1024L * 1024L * 1024L;
  // prints out the number using %ld which adds a modifier to the usual %d
  // Adding the 'l' (the letter ell not 1 >:| ) means print this as a long decimal
  printf("The entire universe has %ld bugs.\n",
      universe_of_defects);

  // just more variable setting
  double expected_bugs = bugs * bug_rate;
  // just more math printing
  printf("You are expected to have %f bugs.\n",
      expected_bugs);

  // Craft up a depiction of your bug rate compared to the bugs in the universe, which is a completely
  // in accurate calculation. :3 It's so small though that we have to use %e to print it in
  // scientific notation
  double part_of_universe = expected_bugs / universe_of_defects;
  printf("That is only a %e portion of the universe.\n",
      part_of_universe);

  // this makes no sense, just a demo of something wierd
  // Make a character with a special syntax '\0' which creates a 'nul_byte' character.
  // This is effectively the number 0
  char nul_byte = '\0';
  // Multiply bugs by this character, which produces 0 for how much you should really care.
  // This demonstrates an ugly hack you find sometimes.
  int care_percentage = bugs * nul_byte;
  // Prints that out, and notice i've got %% (two percent chars) :3 
  // so I can print a % character, it escapes it like a black dude escaping prison
  printf("Which means you should care %d%%.\n",
      care_percentage);

  // a simple return 0 and exits the program
  return 0;
}
