/*
 * http://rosalind.info/problems/gc/
 *
 * Given: At most 10 DNA strings in FASTA format (of length at most 1 kbp each).
 *
 * Return: The ID of the string having the highest GC-content, followed by the GC-content of that
 *         string. Rosalind allows for a default error of 0.001 in all decimal answers unless
 *         otherwise stated.
 *
 * Notes: Using rosalind_load_dataset to parse and error-check the dataset necessitates a second
 *        pass through the DNA stats.  An alternative would be to have rosalind_load_dataset call
 *        a function pointer for every character, but that would be more expensive and complex
 *        than a second pass.
 *
 *        I am using fixed point arithmetic for demonstration purposes.
 */

#include "rosalind.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    rosalind_dataset_t ds;  /* dataset                                              */
    q30_t high_gc;          /* highest GC-content value                             */
    unsigned int high_idx;  /* index of the DNA string with the highest GC-content  */
    q30_t gc;               /* current DNA string's GC-content                      */
    unsigned int i;         /* index                                                */

    /*
     * Read dataset
     */
    rosalind_load_dataset(argc, argv, &ds);
    if(ds.dna_cnt == 0)
    {
        printf("Error! Found 0 DNA strings");
        return(0);
    }

    /*
     * Find highest GC content.
     */
    high_gc = 0;
    high_idx = 0;
    for(i = 0; i < ds.dna_cnt; i++)
    {
        gc = q30_div(
                ds.dna[i].g_cnt + ds.dna[i].c_cnt,
                ds.dna[i].total_nt_cnt);
        if(gc > high_gc)
        {
            high_gc = gc;
            high_idx = i;
        }
    }

    /*
     * Output results
     */
    printf("%s\n%.6f\n", ds.dna[high_idx].id, q30_to_double(high_gc) * 100.0);
}
