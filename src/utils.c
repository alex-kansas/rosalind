#include <ctype.h>
#include <string.h>

#include "utils.h"

/*
 * Utility to read a buffer from file.
 * Reads from a file specified by the command arguments to a specified output buffer.
 * Returns number of character read.
 * Does not memset output buffer to zero.
 */
size_t utils_read_file(
        int argc,                   /* number of command line arguments */
        char *argv[],               /* command line arguments           */
        char *buf,                  /* output buffer                    */
        size_t buf_len)             /* buffer size                      */
{
    FILE *f;
    size_t size_read;

    if(argc < 2)
    {
        printf("Error! Please provide a dataset\n");
        return(0);
    }

    f = fopen(argv[1], "r");
    if(!f)
    {
        printf("Error! Unable to open file %s\n", argv[1]);
        return(0);
    }

    size_read = fread(buf, sizeof(char), buf_len/sizeof(char), f);
    fclose(f);

    if(size_read >= buf_len/sizeof(char))
    {
        printf("Error! Buffer to small\n");
        return(0);
    }

    return(size_read);
}


/*
 * Utility to read integers from file.
 * File is specified by the command arguments.
 * Returns number of integers read.
 * Checks if the integers are positive.
 */
unsigned int utils_read_ints_from_file(
        int argc,                   /* number of command line arguments */
        char *argv[],               /* command line arguments           */
        int * out,                  /* output buffer                    */
        unsigned int maxcnt)        /* max number of ints to read       */
{
    unsigned int cnt;
    FILE *f;

    if(argc < 2)
    {
        printf("Error! Please provide a dataset\n");
        return(0);
    }

    f = fopen(argv[1], "r");
    if(!f)
    {
        printf("Error! Unable to open file %s\n", argv[1]);
        return(0);
    }


    for(cnt = 0; cnt < maxcnt; cnt++, out++)
    {
        if(1 != fscanf(f, "%d", out))
        {
            break;
        }

        if(*out < 0)
        {
            printf("Error! Negative integer detected: %d\n", *out);
            break;
        }
    }

    fclose(f);
    return(cnt);
}