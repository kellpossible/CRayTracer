#include "Random.h"
//external dependency:
#include <stdlib.h>
#include <sys/time.h>

void RandomSeed(int thread_n, RandomBuffer *random_buffer)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    *random_buffer = RandomCreate((unsigned int)(tv.tv_sec * thread_n + tv.tv_usec));
}

RandomBuffer RandomCreate(unsigned int seed){
    return RandomMwcCreate(seed);
}
