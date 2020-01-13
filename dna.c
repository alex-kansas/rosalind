/*
 * http://rosalind.info/problems/dna/
 * 
 * Given: A DNA string s of length at most 1000 nt.
 * 
 * Return: Four integers (separated by spaces) counting the respective number of times that 
 * the symbols 'A', 'C', 'G', and 'T' occur in s.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    char s[1000+2];             /* a DNA string s of length at most 1000 nt             */
    unsigned int counts[256];   /* counts of each letter; we are trading memory speed   */
    int slen;                   /* length of s (incuding EOL and NULL)                  */
    int i;

    compiler_assert(sizeof(char) == 1);

    /*
     * Read dataset from a file
     */
    slen = read_dataset(argc, argv, s, sizeof(s));
    if(slen < 0)
    {
        return(0);
    }
    
    /*
     * Count symbols
     */    
    memset(&counts, 0, sizeof(counts));
    for(i = 0; i < slen; i++)
    {
        counts[(uint8_t)s[i]]++;
    }
    
    printf("%d %d %d %d\n", 
           counts[(uint8_t)'A'], 
           counts[(uint8_t)'C'], 
           counts[(uint8_t)'G'], 
           counts[(uint8_t)'T']);
    
    return 0;
}
