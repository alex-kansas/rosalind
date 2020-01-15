#if !defined(UTILS_H)
#define UTILS_H

#include <stdint.h>
#include <stdio.h>

#define compiler_assert(e) typedef int dummy##__LINE__[e]
#define cnt_of_array(x) sizeof(x)/sizeof(x[0])

/*
 * The following type is used to represent a Q11.20 fractional number
 */
typedef int32_t q20_t;

/*
 * The following function checks if the specified character is a nucleotide
 */
static __inline int isnucleotide(char c)
{
    return((c == 'A') || (c == 'C') || (c == 'G') || (c == 'T') || (c == 'U'));
}

/*
 * The following function divides two integers and returns a q20_t
 */
static __inline q20_t q20_int_div_int(int32_t x, int32_t y)
{
    return((q20_t)((((int64_t)x) << 20) / y));
}

/*
 * The following function converts a Q11.20 number to a double
 */
static __inline double q20_to_double(q20_t x)
{
    return((double)(x) / 1048576.0);
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