#include "utils.h"

/*
 * Utility to read a dataset from file.
 * Reads from a file specified by the command arguments to a specified output buffer
 */
int read_dataset(int argc,      /* number of command line arguments */
                 char *argv[],  /* command line arguments           */
                 char *ptr,     /* output buffer                    */
                 size_t size)   /* output buffer size               */
{
    FILE *f;
    
    if(argc < 2)
    {
        printf("Please supply dataset file name\n");
        return(-1);
    }
    
    f = fopen(argv[1], "r");
    if(!f)
    {
        printf("Unable to open file %s", argv[1]);
        return(-1);
    }
    
    size = fread(ptr, sizeof(char), size/sizeof(char), f);
    fclose(f);
    return(size);
}
