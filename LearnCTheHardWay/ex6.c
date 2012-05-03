// includes library for standard io
#include <stdio.h>

/// the usual start of a C program
int main(int argc, char *argv[])
{
  // setting the type int for the distance variable 
  int distance = 100;
  // setting the type float for the power variable
  float power = 2.345f;
  // setting the type double for the super_power variable
  double super_power = 56789.4532;
  // setting the type char for the initial variable
  char initial = 'A';
  // setting the type char for the first name variable
  char first_name[] = "Zed";
  // setting the type char for the last name variable
  char last_name[] = "Shaw";

  // printing out the distance integer in the string
  printf("You are %d miles away.\n", distance);
  // printing out the power float in the string
  printf("You have %f levels of power.\n", power);
  // printing out the super_power float in the string
  printf("You have %f awesome super powers.\n", super_power);
  // printing out the initial character in the string
  printf("I have an initial %c.\n", initial);
  // printing out the first name characters in the string
  printf("I have a first name %s.\n", first_name);
  // printing out the last name characters in the string
  printf("I have a last name %s.\n", last_name);
  // printing out the characters first name the character intial and the characters last name in the string
  printf("My whole name is %s %c. %s.\n",
      first_name, initial, last_name);

  // return 0 for the end of the program
  return 0;
}
