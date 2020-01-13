/*
 * http://rosalind.info/problems/fib/
 * 
 * Given: Positive integers n <= 40 and k <= 5.
 * 
 * Return: The total number of rabbit pairs that will be present after n months, 
 * if we begin with 1 pair and in each generation, every pair of reproduction-age rabbits 
 * produces a litter of k rabbit pairs (instead of only 1 pair).
 * 
 * F[n] = F[n-1] + k*(F[n-2])
 */

#include <stdint.h>
#include <stdlib.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    int n;      /* number of months     */
    int k;      /* litter size          */
    uint64_t F[41];  /* Fibonacci sequence   */
    int i;      /* sequence index       */
    
    /*
     * Get n and k from command line arguments
     */
    if(argc < 3)
    {
        printf("Please specify n and k\n");
        return(0);
    }
    
    n = atoi(argv[1]);
    k = atoi(argv[2]);
    
    if(n >= cnt_of_array(F))
    {
        printf("Please use n <= 40 (currently %d)\n", n);
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
