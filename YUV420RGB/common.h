#include <fstream>
#include <iostream>
#include <cstdint>
#include <ostream>
#include <assert.h>
#include <algorithm>

#define MAX(X, Y) (X > Y ? (X) : (Y)) 
#define MAX3(X, Y, Z) (X > Y ? (X > Z ? (X) : (Z)) : (Z > Y ? (Z) : (Y)))

#define CLIP(n, min, max) (n > min ? (n < max ? (n) : (max)) : (min))