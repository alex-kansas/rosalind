/*
 * Translating RNA into Protein
 * http://rosalind.info/problems/prot/
 *
 * Given: An RNA string s corresponding to a strand of mRNA (of length at most 10 kbp).
 *
 * Return: The protein string encoded by s.
 */

#include <stdio.h>
#include "rosalind.h"

static const char * const codon_table =
    "FFLLSSSSYY\n\nCC\nW"
    "LLLLPPPPHHQQRRRR"
    "IIIMTTTTNNKKSSRR"
    "VVVVAAAADDEEGGGG";

int main(int argc, char *argv[])
{
    rosalind_dataset_t ds;  /* dataset (will be destroyed)  */
    char * ps;              /* protein string               */
    int cnt;                /* RNA basepair down-counter    */
    binary_dna_t * rna;     /* RNA array                    */

    /* Load dataset */
    rosalind_load_dataset(argc, argv, &ds);
    if(ds.dna_cnt != 1)
    {
        printf("Error! Found %d RNA strings", ds.dna_cnt);
        return(0);
    }

    /* Each codon is 3 nucleobases.  Check if we have a whole number of codons. */
    rna = ds.dna[0].dna;
    cnt = ds.dna[0].dna_len;
    if((cnt % 3) != 0)
    {
        printf("Error! Must be a multiple of 3, %d is not", cnt);
        return(0);
    }

    /* Translate in place */
    ps = (char *)rna;
    while(cnt > 0)
    {
        uint8_t codon = (rna[0] << 4) + (rna[1] << 2) + rna[2];
        *ps = codon_table[codon & 0x3F];
        ps  += 1;
        rna += 3;
        cnt -= 3;
    }

    *ps = 0;
    printf("%s", (char const *)ds.dna[0].dna);
}