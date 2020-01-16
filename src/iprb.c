/*
 * Given: Three positive integers k, m, and n, representing a population containing k+m+n
 * organisms: k individuals are homozygous dominant for a factor, m are heterozygous, and n are
 * homozygous recessive.
 *
 * Return: The probability that two randomly selected mating organisms will produce an individual
 * possessing a dominant allele (and thus displaying the dominant phenotype). Assume that any two
 * organisms can mate.
 *
 * Note: Using fixed point arithmetic for demonstration purposes.
 */

#define ONE     (1<<30)     /* 1 expressed as Q1.30     */
#define HALF    (ONE >> 1)  /* 1/2 expressed as Q1.30   */

#include "utils.h"

/*
 * Compute proability that the second gene is recessive
 */
static q30_t psecondrec(
        int i,      /* first parent index   */
        int *kmn,   /* population           */
        int t);     /* total population size*/


int main(int argc, char *argv[])
{
    int kmn[3]; /* numbers read from the file   */
    int t;      /* total number of individuals  */
    q30_t p;    /* probability                  */

    /*
     * Define probabilities of picking a recessive gene from AA, Aa, and aa respectively
     */
    static const q30_t prec[3] = { 0, HALF, ONE };

    /*
     * Read givens from file
     */
    if(3 != utils_read_ints_from_file(argc, argv, kmn, cnt_of_array(kmn)))
    {
        printf("Error! Invalid input\n");
        return(0);
    }

    t = kmn[0] + kmn[1] + kmn[2];
    if(t < 2)
    {
        printf("Error! At least two individuals are required\n");
        return(0);
    }

    /*
     * P(both genes are recessive) = P(first gene is recessive) * P(second gene is recessive)
     *
     * P(both genes are recessive)
     *   = P(first parent is AA) * 0   * P(second gene is recessive if first parent is AA)
     *   + P(first parent is Aa) * 1/2 * P(second gene is recessive if first parent is Aa)
     *   + P(first parent is aa) * 1   * P(second gene is recessive if first parent is aa)
     */
    p = q30_mul(q30_mul(q30_div(kmn[1], t), HALF), psecondrec(1, kmn, t))
      + q30_mul(        q30_div(kmn[2], t)       , psecondrec(2, kmn, t));

    /*
     * P(posessing dominant allele) = 1 - P(both genes are recessive)
     */
    p = ONE - p;

    /*
     * Output the result
     */
    printf("%.5f\n", q30_to_double(p));
}


/*
 * Compute proability that the second gene is recessive
 */
static q30_t psecondrec(
        int i,      /* first parent index   */
        int *kmn,   /* population           */
        int t)      /* total population size*/
{
    q30_t p = 0;

    /* check if first parent exists */
    if(kmn[i] <= 0)
    {
        return(0);
    }

    /* Remove first parent from the population */
    kmn[i]--;
    t--;

    /*
     * P(second gene is recessive) = P(second parent is AA) * 0
     *                             + P(second parent is Aa) * 1/2
     *                             + P(second parent is aa) * 1
     */
    p = q30_mul(q30_div(kmn[1], t), HALF) + q30_div(kmn[2], t);

    /* Restore first parent to the population */
    kmn[i]++;

    return(p);
}