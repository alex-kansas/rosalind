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
    rosalind_dataset_t ds;  /* dataset                                                  */
    char sc[MAX_DNA_SIZE];  /* reverse complement of the DNA string                     */
    char map[256];          /* maps complementary symbols to each other;                */
                            /*  using only 4 of the elements to trade memory for speed  */
    size_t cnt;             /* counter                                                  */
    char * psc;             /* pointer into reverse compliment string                   */
    char const * pdna;      /* pointer into the DNA string                              */

    /*
     * Read dataset
     */
    rosalind_load_dataset(argc, argv, &ds);
    if(ds.dna_cnt != 1)
    {
        printf("Error! Found %d DNA strings", ds.dna_cnt);
        return(0);
    }
    else if(ds.dna[0].dna_len >= cnt_of_array(sc))
    {
        printf("Error! DNA string is too long (%zu)", ds.dna[0].dna_len);
        return(0);
    }

    /*
     * Initialize map.
     * This really should be static const, but this way is less typing.
     */
    memset(map, ' ', sizeof(map));
    map['A'] = 'T';
    map['C'] = 'G';
    map['G'] = 'C';
    map['T'] = 'A';

    /*
     * Compute reverse complement of the DNA string
     */
    psc = sc;
    pdna = ds.dna[0].dna + (ds.dna[0].dna_len - 1);
    for(cnt = ds.dna[0].dna_len; cnt; cnt--)
    {
        *psc++ = map[*pdna--];
    }

    /*
     * Add NUL terminator becase we didn't memset the whole.
     * Note that we already checked to make sure that NUL will fit in the buffer.
     */
    *psc = 0;

    /*
     * Output result
     */
    printf("%s", sc);
    return(0);
}
