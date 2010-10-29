#ifndef Random_h
#define Random_h

//wrapper for any random number generator I can find
//so it will be easy to swap them around
#include "RandomMwc.h"

typedef struct RandomMwc RandomBuffer;

void RandomSeed(int seed, RandomBuffer*);
RandomBuffer RandomCreate(unsigned int seed);

#endif
