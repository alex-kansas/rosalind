/*
 * http://rosalind.info/problems/dna/
 *
 * Given: A DNA string s of length at most 1000 nt.
 *
 * Return: Four integers (separated by spaces) counting the respective number of times that
 * the symbols 'A', 'C', 'G', and 'T' occur in s.
 *
 * For demonstration purposes, this is slightly more involved than just counting characters.
 *
 */

#include <stdio.h>

#include "rosalind.h"

int main(int argc, char *argv[])
{
    rosalind_dataset_t ds;
    rosalind_load_dataset(argc, argv, &ds);

    if(ds.dna_cnt == 1)
    {
        printf("%u %u %u %u\n",
               ds.dna[0].nt_cnts[NT_A],
               ds.dna[0].nt_cnts[NT_C],
               ds.dna[0].nt_cnts[NT_G],
               ds.dna[0].nt_cnts[NT_T]);
    }
    else
    {
        printf("Error! Found %d DNA strings", ds.dna_cnt);
    }

    return 0;
}
