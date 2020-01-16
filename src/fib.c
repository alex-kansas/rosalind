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
    int n;          /* number of months                 */
    int k;          /* litter size                      */
    int64_t F[41];  /* Fibonacci sequence               */
    int i;          /* sequence index                   */
    int nk[2];      /* number of months and litter size */

    /*
     * Read n and k from a file
     */
    if(2 != utils_read_ints_from_file(argc, argv, nk, cnt_of_array(nk)))
    {
        printf("Error! Invalid input\n");
        return(0);
    }

    n = nk[0];
    k = nk[1];

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
