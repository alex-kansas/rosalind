/*
 * http://rosalind.info/problems/fib/
 *
 * Given: Positive integers n <= 40 and k <= 5.
 *
 * Return: The total number of rabbit pairs that will be present after n months,
 * if we begin with 1 pair and in each generation, every pair of reproduction-age rabbits
 * produces a litter of k rabbit pairs (instead of only 1 pair).
 *
 * F[1] = 1
 * F[2] = 1
 * F[n] = F[n-1] + k*(F[n-2]), for n > 2
 *
 */

#include <stdint.h>
#include <stdlib.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    FILE *f;
    size_t dlen;        /* dataset size         */
    unsigned int n = 0; /* number of months     */
    unsigned int k = 0; /* litter size          */
    uint64_t F[41];     /* Fibonacci sequence   */
    int i;              /* sequence index       */

    /*
     * Read n and k from a file
     */
    if(argc < 2)
    {
        printf("Error! Please provide a dataset\n");
        return(0);
    }

    f = fopen(argv[1], "r");
    if(!f)
    {
        printf("Error! Unable to open file %s\n", argv[1]);
        return(0);
    }

    if(2 != fscanf(f, "%u %u", &n, &k))
    {
        printf("Error! Unable to read n and k from file %s", argv[1]);
        return(0);
    }

    if(n >= cnt_of_array(F))
    {
        printf("Error! N (%u) exceeds max (%lu)\n", n, cnt_of_array(F) - 1);
        return(0);
    }

    if(k > 5)
    {
        printf("Error! K (%u) exceeds max (5)\n", k);
        return(0);
    }

    /*
     * Compute Fibonacci sequence
     */
    F[0] = 1;
    F[1] = 1;

    for(i = 2; i < n; i++)
    {
        F[i] = F[i-1] + k * F[i-2];
    }

    /*
     * Output the last element
     */
    printf("%lu\n", F[i-1]);
    return(0);
}
