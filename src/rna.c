/*
 * http://rosalind.info/problems/rna/
 *
 * Given: A DNA string t having length at most 1000 nt.
 *        Input dataset is read from a file whose name is give as a command line argument.
 *
 * Return: The transcribed RNA string of t.
 *         Result is written to the file named rna_result.txt
 *
 * Notes: Scanning a string and replacing characters is very simple, and easy, but we will
 *        use rosalind_load_dataset for demonstration purposes.
 *
 *        This necessitates a second pass through the string.  An alternative would be to
 *        have rosalind_load_dataset call a function pointer for every character, but that
 *        would be more expensive and complex than a second pass.
 */

#include <stdio.h>

#include "rosalind.h"

int main(int argc, char *argv[])
{
    rosalind_dataset_t ds;
    rosalind_load_dataset(argc, argv, &ds);

    if(ds.dna_cnt == 1)
    {
        size_t pos;
        for(pos = 0; pos < ds.dna[0].dna_len; pos++)
        {
            if(ds.dna[0].dna[pos] == 'T')
            {
                ds.dna[0].dna[pos] = 'U';
            }
        }

        printf("%s\n", ds.dna[0].dna);
    }
    else
    {
        printf("Error! Found %d DNA strings", ds.dna_cnt);
    }

    return 0;
}
