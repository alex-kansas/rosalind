#if !defined(UTILS_H)
#define UTILS_H

#include <stdint.h>
#include <stdio.h>

#define compiler_assert(e) typedef int dummy##__LINE__[e]
#define cnt_of_array(x) sizeof(x)/sizeof(x[0])

/*
 * The following type is used to represent a Q1.30 fractional number
 */
typedef int32_t q30_t;

/*
 * The following function checks if the specified character is a nucleotide
 */
static __inline int isnucleotide(char c)
{
    return((c == 'A') || (c == 'C') || (c == 'G') || (c == 'T') || (c == 'U'));
}

/*
 * The following function divides two integers and returns a q30_t
 * This works with any fixed point inputs as long as they are in the same format.
 */
static __inline q30_t q30_div(int32_t x, int32_t y)
{
    int64_t temp = (int64_t)x << 30;
    if((x >= 0) == (y >= 0))
    {
        temp += y / 2;
    }
    else
    {
        temp -= y / 2;
    }
    return((q30_t)(temp / y));
}

/*
 * The following function converts a Q1.30 number to a double
 */
static __inline double q30_to_double(q30_t x)
{
    return((double)(x) / 1073741824.0);
}

/*
 * Utility to read a buffer from file.
 * Reads from a file specified by the command arguments to a specified output buffer.
 * Returns number of character read.
 */
size_t utils_read_file(
        int argc,                   /* number of command line arguments */
        char *argv[],               /* command line arguments           */
        char *buf,                  /* output buffer                    */
        size_t buf_len);            /* buffer size                      */

#endif /* UTILS_H */