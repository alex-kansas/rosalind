/*
 * Problem: Given two strings s and t of equal length, the Hamming distance between s and t is the
 * number of corresponding symbols that differ in s.
 *
 * Given: Two DNA strings s and t of equal length (not exceeding 1 kbp).
 *
 * Return: The Hamming distance
 *
 */

#include <stdio.h>

#include "rosalind.h"

int main(int argc, char *argv[])
{
    rosalind_dataset_t ds;  /* dataset          */
    unsigned int pos;       /* cursor           */
    unsigned int dh;        /* hamming distance */

    /*
     * Read dataset
     */
    rosalind_load_dataset(argc, argv, &ds);
    if((ds.dna_cnt != 2) || (ds.dna[0].dna_len != ds.dna[1].dna_len))
    {
        printf("Error! Found %d DNA strings of lengths %zu and %zu\n",
               ds.dna_cnt, ds.dna[0].dna_len, ds.dna[1].dna_len);
        return(0);
    }

    /*
     * Compute Hamming distance
     */
    dh = 0;
    for(pos = 0; pos < ds.dna[0].dna_len; pos++)
    {
        dh += (ds.dna[0].dna[pos] != ds.dna[1].dna[pos]);
    }

    printf("%d\n", dh);

    return(0);
}