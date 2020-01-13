#include <stdio.h>

#define compiler_assert(e) typedef int dummy##__LINE__[e]
#define cnt_of_array(x) sizeof(x)/sizeof(x[0])

int read_dataset(int argc, char *argv[], char *ptr, size_t size);
