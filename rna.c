/*
 * http://rosalind.info/problems/rna/
 * 
 * Given: A DNA string t having length at most 1000 nt.
 *        Input dataset is read from a file whose name is give as a command line argument.
 * 
 * Return: The transcribed RNA string of t.
 *         Result is written to the file named rna_result.txt
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    char s[1000+2];     /* work buffer                              */
    int slen;           /* length of s (incuding EOL and NULL)      */
    int i;

    /*
     * Read dataset from a file
     */
    slen = read_dataset(argc, argv, s, sizeof(s));
    if(slen < 0)
    {
        return(0);
    }
    
    /*
     * Replace all occurrences of 'T' with 'U'
     */
    for(i = 0; i < slen; i++)
    {
        if(s[i] == 'T')
        {
            s[i] = 'U';
        }
    }
    
    /*
     * Add NUL terminator becase we didn't memset the whole array before reading it
     */
    if(i < cnt_of_array(s))
    {
        s[i] = 0;
    }
    
    /*
     * Output result
     */
    printf("%s", s);
    return(0);
}
