/*
 * Finding a Motif in DNA
 * http://rosalind.info/problems/subs/
 *
 * Given: Two DNA strings s and t (each of length at most 1 kbp).
 *
 * Return: All locations of t as a substring of s.
 */

#include <stdio.h>

#include "rosalind.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    rosalind_dataset_t ds;  /* dataset          */
    size_t occurence_cnt;
    size_t occurences[1000];
    size_t i;

    /*
     * Read dataset
     */
    rosalind_load_dataset(argc, argv, &ds);
    if((ds.dna_cnt != 2) || (ds.dna[0].dna_len < ds.dna[1].dna_len))
    {
        printf("Error! Found %d DNA strings of lengths %zu and %zu\n",
               ds.dna_cnt, ds.dna[0].dna_len, ds.dna[1].dna_len);
        return(0);
    }

    occurence_cnt = rosalind_search_naive(&ds.dna[0], &ds.dna[1],
                                          occurences, cnt_of_array(occurences));
    for(i = 0; i < occurence_cnt; i++)
    {
        printf("%zu ", occurences[i] + 1);
    }
    printf("\n");
}