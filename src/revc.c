/*
 * http://rosalind.info/problems/revc/
 *
 * Given: A DNA string s of length at most 1000 bp.
 *
 * Return: The reverse complement sc of s.
 *
 * Assumes ASCII.
 */

#include <stdio.h>
#include <string.h>

#include "rosalind.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    rosalind_dataset_t ds;  /* dataset                      */
    size_t cnt;             /* counter                      */
    binary_dna_t * head;    /* pointer into the DNA string  */
    binary_dna_t * tail;    /* pointer into the DNA string  */

    /*
     * Read dataset
     */
    rosalind_load_dataset(argc, argv, &ds);
    if(ds.dna_cnt != 1)
    {
        printf("Error! Found %d DNA strings", ds.dna_cnt);
        return(0);
    }

    /*
     * Compute reverse complement of the DNA string in place
     */
    head = ds.dna[0].dna;
    tail = ds.dna[0].dna + (ds.dna[0].dna_len - 1);
    cnt  = ds.dna[0].dna_len / 2;
    while(cnt--)
    {
        char c  = com2char[*head & BINARY_DNA_MASK];
        *head++ = com2char[*tail & BINARY_DNA_MASK];
        *tail-- = c;
    }

    if(ds.dna[0].dna_len & 1)
    {
        *head = com2char[*head];
    }
    /*
     * Output result
     */
    printf("%s\n", ds.dna[0].dna);
    return(0);
}
