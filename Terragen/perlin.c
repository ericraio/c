#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "perlin.h"

////
// Vector
////

// Defines a function called v3_new that returns a vec3 struct that takes in 3 double int arguments
// the struct defined assigns the 3 arguments to 3 fields in the struct
//
vec3 v3_new(double x, double y, double z) {
  vec3 ret;
  ret.x = x;
  ret.y = y;
  ret.z = z;
  return ret;
}

// Defines a function called v3_from_ange that returns a vec3 struct that takes in 3 double int arguments
// this intializes 3 double int variables with the first one multiplying the cosine of angle with angle 2
// the second variable is the sine of angle and the last variable multiplies cosine of angle
// with the sine of angle2, this will return a function that defines a struct. The v3_new function takes in
// each of the local variables and for each parameter multiply it by the length argument.
//
vec3 v3_from_angle(double angle, double angle2, double length) {
  double
    x = cos(angle) * cos(angle2),
    y = sin(angle),
    z = cos(angle) * sin(angle2);
  return v3_new(x * length, y * length, z * length);
}

// Defines a function called v3_unit that takes 2 double int arguments called angle and angle2
// this function will return the v3_from_angle function  that defines the struct
//
vec3 v3_unit(double angle, double angle2) {
  return v3_from_angle(angle, angle2, 1);
}

// Defines a function called v3_negate that takes 1 struct argument called v,
// and returns back a v3_new function that takes 3 arguments.
// each argument is the negative value of each field of the v struct
//
vec3 v3_negate(vec3 v) {
  return v3_new(-v.x, -v.y, -v.z);
}

// Defines a function called v3_add that takes 2 vec3 struct arguments called v1 and v2
// this returns a v3_new struct that takes 3 parameters, Each parameter will add the v1 struct 
// and the v2 struct by each of the corresponding fields.
//
vec3 v3_add(vec3 v1, vec3 v2) {
  return v3_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// Defines a function called v3_sub that takes 2 vec3 struct arguments v1 and v2, which returns a v3_add
// function which also takes 2 arguments the first parameter is v1 and the second parameter 
// is the v3_negate function passing in v2.
//
vec3 v3_sub(vec3 v1, vec3 v2) {
  return v3_add(v1, v3_negate(v2));
}

// Defines a double int function that takes 2 struct arguments
// this function will multiply each x, y, and z between the 2 structs then add them together
//
double v3_dot(vec3 v1, vec3 v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Defines a double int function that takes 1 argument as a vec3 struct
// and returns the square root of v3_dot function that takes in 2 structs as arguments.
//
double v3_length(vec3 v) {
  return sqrt(v3_dot(v, v));
}

// Defines a function called v3_normalize that takes one struct as an argument
// and returns a struct. This function will create a double int variable called l that is assigned to
// the v3_length function that will take the parameter v as an argument
// Lastly, this will return the v3_new function with 3 parameters of the v struct argument. Each paramenter of this function 
// will devide each field of the struct by l.
//
vec3 v3_normalize(vec3 v) {
  double l = v3_length(v);
  return v3_new(v.x / l, v.y / l, v.z / l);
}


////
// Vector Field
////

// Defines a struct pointer function that takes in 3 int arguments of width height and depth. This will return a pointer to a struct.
// On line 100, creates a struct pointer called vf that is assigned to a malloc with the size of vec3_field struct, this then gets 
// typecasted as a pointer to the vec3_field struct. Line 103-105 assigns vf fields to the int arguments.
//
// The vf data field is assigned to malloc with the product of width, height, depth and the size of vec3 struct. This gets typecasted
// to a struct that points to a vec3. The for loop, loops over the product of width height and depth. For each loop, vf data indexed incremented by one
// zeros out each struct of the field with the v3_new function. Lastly, returns the vf struct.
//
vec3_field *v3f_new(int width, int height, int depth) {
  vec3_field *vf = (vec3_field *) malloc(sizeof(vec3_field));
  vf->width = width;
  vf->height = height;
  vf->depth = depth;
  vf->data = (vec3 *) malloc(width * height * depth * sizeof(vec3));
  for (int i = 0; i < width * height * depth; i++) {
    vf->data[i] = v3_new(0, 0, 0);
  }
  return vf;
}

// Defines a pointer function called v3f_random_unit that points to vec3_field struct that takes 3 int arguments with width, height and depth
// The vec3_field pointer called vf is assigned to the v3f_new function that takes in width, height, and depth. The for loop will loop up to the product of width
// height and depth, assigning both double int r1 and r2 variables to the rand() function in stdlib. They are typecasted to a float divided by RAND_MAX typecased 
// to a float. r1 and r2 are both reassigned to their value multiplied by pi and 2. vf data indexed by i is assigned to the v3_unit function that is passed the new values of r1 and r2.
// returns back the vf pointer.
//
vec3_field *v3f_random_unit(int width, int height, int depth) {
  vec3_field *vf = v3f_new(width, height, depth);
  for (int i = 0; i < width * height * depth; i++) {
    double r1 = (float) rand() / (float) RAND_MAX;
    double r2 = (float) rand() / (float) RAND_MAX;
    r1 = r1 * 3.1415 * 2;
    r2 = r2 * 3.1415 * 2;
    vf->data[i] = v3_unit(r1, r2);
  }
  return vf;
}

// Defines a function called v3f_destroy that doesn't return anything that takes a pointer to vec3_field struct called vf. This function frees up vf data and vf
//
void v3f_destroy(vec3_field *vf) {
  free(vf->data);
  free(vf);
}

// Defines a function called v3f_get that is a type struct that takes 4 parameters, a pointer to a struct, and 3 ints x, y and z.
// the wh variable with type int is assigned to the vf struct pointing to width multiplied vf struct pointing to height. 
// The function returns the vf struct pointing to data with the index of z multiplied by wh and y multiplied by vf pointing to width plus x.
//
vec3 v3f_get(vec3_field *vf, int x, int y, int z) {
  int wh = vf->width * vf->height;
  return vf->data[z * wh + y * vf->width + x];
}

// Defines a function called v3f_set that doesn't return anything that takes 4 arguments a struct pointer, 3 ints x y and z, and the vec3 struct,
// the wh variable with type int is assigned to the vf struct pointing to width multiplied vf struct pointing to height. 
// the v struct is assigned to The vf struct pointing to data with the index of z multiplied by wh and y multiplied by vf pointing to width plus x.
//
void v3f_set(vec3_field *vf, int x, int y, int z, vec3 v) {
  int wh = vf->width * vf->height;
  vf->data[z * wh + y * vf->width + x] = v;
}

////
// Heightmap
////

// A function that points to a struct which takes 2 int arguments, width and height. mallocs the size of heightmap and points it to a heightmap struct then assigns
// this to the hm variable that pointes to a heightmap struct. hm struct pointing to width is assigned to the width arguments. hm struct pointing to height
// gets assigned to the height argument. hm pointing to data gets assied to the malloc of width times height times the size of double int, then this gets typecasted to
// point to double int. The for loop loops over hm pointing to data zeroing out each increment of data. Lastly, returns hm.
//
heightmap *hm_new(int width, int height) {
  heightmap *hm = (heightmap *) malloc(sizeof(heightmap));
  hm->width = width;
  hm->height = height;
  hm->data = (double *) malloc(width * height * sizeof(double));
  for(int i = 0; i < width * height; i++) {
    hm->data[i] = 0;
  }
  return hm;
}

// function hm_destroy is a type void so it doesn't return anything, it takes in an that points to heightmap as an arguments and assign it to hm, this will free hm's data attribute
// and then free hm
//
void hm_destroy(heightmap *hm) {
  free(hm->data);
  free(hm);
}

// Function hm_get is a type double that takes in 3 arguments first being an address of a struct that points to heightmap and the other 2 are ints of x and y
// this function returns a heightmap that points to data indexed at y times heightmap's width plus x
//
double hm_get(heightmap *hm, int x, int y) {
  return hm->data[y * hm->width + x];
}

void hm_set(heightmap *hm, int x, int y, double v) {
  hm->data[y * hm->width + x];
}

void hm_add_scale(heightmap *hm1, heightmap *hm2, double ratio) {
  if (hm1->width != hm2->width || hm1->height != hm2->height) {
    return;
  }
  for (int i = 0; i < hm1->width * hm1->height; i++) {
    hm1->data[i] = hm1->data[i] + hm2->data[i] * ratio;
  }
}

static double __curve(double t)
  {return 3 * t*t - 2 * t*t*t;}
static double __interpolate(double t, double x, double y)
  {t = __curve(t); return(1 - t) * x + t * y;}
heightmap *hm_perlin_noise(int width, int height, vec3_field *vf, double layer) {
  heightmap *hm = hm_new(width, height);
  int vfw = vf->width - 1;
  int vfh = vf->height - 1;
  int tileWidth = width / vfw;
  int tileHeight = height / vfh;
  double relZ = layer;
  for(int y = 0; y < height; y++) for(int x = 0; x < width; x++) {
    int tileX = x / tileWidth;
    int tileY = y / tileHeight;
    double relX = (double)(x % tileWidth) / tileWidth;
    double relY = (double)(y % tileHeight) / tileHeight;
    vec3
      v000 = v3_normalize(v3_new(relX    , relY    , relZ    )),
      v100 = v3_normalize(v3_new(relX - 1, relY    , relZ    )),
      v010 = v3_normalize(v3_new(relX    , relY - 1, relZ    )),
      v110 = v3_normalize(v3_new(relX - 1, relY - 1, relZ    )),
      v001 = v3_normalize(v3_new(relX    , relY    , relZ - 1)),
      v101 = v3_normalize(v3_new(relX - 1, relY    , relZ - 1)),
      v011 = v3_normalize(v3_new(relX    , relY - 1, relZ - 1)),
      v111 = v3_normalize(v3_new(relX - 1, relY - 1, relZ - 1));
    vec3
      c000 = v3f_get(vf, tileX    , tileY    , 0),
      c100 = v3f_get(vf, tileX + 1, tileY    , 0),
      c010 = v3f_get(vf, tileX    , tileY + 1, 0),
      c110 = v3f_get(vf, tileX + 1, tileY + 1, 0),
      c001 = v3f_get(vf, tileX    , tileY    , 1),
      c101 = v3f_get(vf, tileX + 1, tileY    , 1),
      c011 = v3f_get(vf, tileX    , tileY + 1, 1),
      c111 = v3f_get(vf, tileX + 1, tileY + 1, 1);
    double
      n000 = v3_dot(v000, c000),
      n100 = v3_dot(v100, c100),
      n010 = v3_dot(v010, c010),
      n110 = v3_dot(v110, c110),
      n001 = v3_dot(v001, c001),
      n101 = v3_dot(v101, c101),
      n011 = v3_dot(v011, c011),
      n111 = v3_dot(v111, c111);
    double
      nx00 = __interpolate(relX, n000, n100),
      nx10 = __interpolate(relX, n010, n110),
      nx01 = __interpolate(relX, n001, n101),
      nx11 = __interpolate(relX, n011, n111);
    double
      nxy0 = __interpolate(relY, nx00, nx10),
      nxy1 = __interpolate(relY, nx01, nx11);
    double
      nxyz = __interpolate(relZ, nxy0, nxy1);
    hm_set(hm, x, y, nxyz);
  }
  return hm;
}
