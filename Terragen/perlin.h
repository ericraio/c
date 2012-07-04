#pragma once
#ifndef PERLIN_H_INCLUDED
#define PERLIN_H_INCLUDED

// Defines a type that creates a struct initializing 3 double int using
// vec3 as the typedef name space
typedef struct __vec3 {
  double x;
  double y;
  double z;
} vec3;

// Initializes the v3_new function that takes 3 double int arguments.
vec3 v3_new(double, double, double);

//
// Initializes the v3_from_angle function that takes 3 double int arguments.
vec3 v3_from_angle(double, double, double);

// Initializes the v3_unit function that takes 2 double int arguments
//
vec3 v3_unit(double, double);

//
// Initializes the v3_length function that passes in the vect3 struct as the argument
double v3_length(vec3);

// Initializes the v3_normalize function that takes the vec3 struct as an argument
//
vec3 v3_normalize(vec3);

// Initializes the v3_negate function that takes the vec3 struct as an argument
//
vec3 v3_negate(vec3);

// Intializes the v3_add function as a vec3 struct that takes 2 vec3 structs as arguments
//
vec3 v3_add(vec3, vec3);

// Intializes the v3_sub function as a vec3 struct that takes 2 vec3 structs as arguments
// and returns a vec3 struct
//
vec3 v3_sub(vec3, vec3);

// Intializes the v3_dot function as a vec3 struct that takes 2 vec3 structs as arguments
// and returns a double int
//
double v3_dot(vec3, vec3);

// Defines a new type called vec3_field that intitializes 3 ints
// Width, Height, and Depth to create the field
// Lastly, initializes a struct and defines a pointer called data that 
// points to the vec3 struct in memory, this returns the vec3_field struct
//
typedef struct __vec3_field {
  int width;
  int height;
  int depth;
  vec3 *data;
} vec3_field;

// Initializes vec3_field struct with a pointer function called v3f_new which
// takes 3 ints as arguments, this will return vec3_field struct
//
vec3_field *v3f_new(int, int, int);

// Initialize vec3_field struct with a pointer function called v3f_random_unity that
// takes 3 int arguments
//
vec3_field *v3f_random_unity(int, int, int);

// Initializes a function that returns nothing called v3f_destroy that takes a
// pointer of a vec3field struct
//
void v3f_destroy(vec3_field *destroy);

// Initializes a function with type vec3 called v3f_get that takes an address of vec3_field and 3 ints
//
vec3 v3f_get(vec3_field *, int, int, int);

// Initializes a function that returns nothing called v3f_set that takes an address of a vec3_field 
// as the first argument, 3 ints, and a vec3
//
void v3f_set(vec3_field *, int, int, int, vec3);

// Defines a type called heightmap that is a struct with 2 ints and a pointer to a double 
// int called data
//
typedef struct __heightmap {
  int width;
  int height;
  double *data
} heightmap;

// Initializes a function pointer that takes in 2 arguments as ints
//
heightmap *hm_new(int, int);

// Initializes a hm_destroy function that doesn't return anything and takes an 
// address of a heightmap struct
//
void hm_destroy(heightmap *);

// Initializes a double int function called hm_get that takes a pointer to a heightmap struct
// and 2 ints
//
double hm_get(heightmap *, int, int);

// Initiliazes a hm_set function that doesn't return anything that takes 2 pointers of a heightmap
// struct, 2 ints, and a double int
//
void hm_set(heightmap *, int, int, double);

// Initializes a hm_add_scale function that doesn't return anything and initializes 2 pointers of
// heightmap structs and a double int
//
void hm_add_scale(heightmap *, heightmap *, double);

// Initilizes a pointer function with type heightmap that takes 2 int arguments, 
// a pointer to vec3_field and a doubleint as arguments
//
heightmap *hm_perlin_noise(int, int, vec3_field *, double);

// End the if condition
#endif
