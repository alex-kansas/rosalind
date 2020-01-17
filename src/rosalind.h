#if !defined(ROSALIND_H)
#define ROSALIND_H

#include <stddef.h>
#include <stdint.h>

#define MAX_DNA_SIZE        (1024)
#define MAX_DNA_CNT         (16)
#define MAX_DATASET_SIZE    (MAX_DNA_SIZE * MAX_DNA_CNT)

/*
 * There are four different nucleotides: T, C, A, and G.  In RNA T is replaced with U.
 * These can be represented with a 2-bit number.
 * Assigned numeric values are not arbitrary -- these particular values allow complements be be
 * computed by xor'ing with 2.
 */
typedef uint8_t binary_dna_t;
enum { U=0, C=1, A=2, G=3, T = U, BINARY_DNA_MASK = 0x03 };

static char const * const rna2char = "UCAG";
static char const * const dna2char = "TCAG";
static char const * const com2char = "AGTC";

/*
 * The following structure defines a dataset commonly used in the Project Rosalind problems.
 */
typedef struct
{
    char *id;                       /* pointer to the NUL-terminated id string  */
    binary_dna_t *dna;              /* pointer to an array of 2-bit numbers each*/
                                    /*  representing a single nucleotide        */
    size_t dna_len;                 /* DNA sring length (aka total nucleotide)  */
    unsigned int a_cnt;             /* A-count                                  */
    unsigned int c_cnt;             /* C-count                                  */
    unsigned int g_cnt;             /* G-count                                  */
    unsigned int t_cnt;             /* T-count                                  */
} rosalind_dna_t;

typedef struct
{
    char buf[MAX_DATASET_SIZE];     /* dataset buffer                           */
    size_t buf_len;                 /* number of characters in the buffer       */
    rosalind_dna_t dna[MAX_DNA_CNT];/* scanned DNA data                         */
    unsigned int dna_cnt;           /* number of detected DNA strings           */
} rosalind_dataset_t;

/*
 * The following function reads a dataset from a file specified by command arguments.
 */
void rosalind_load_dataset(
        int argc,                   /* number of command line arguments */
        char *argv[],               /* command line arguments           */
        rosalind_dataset_t *ds);    /* output dataset here              */

/*
 * Function   : rosalind_search_naive
 * Description: Finds all occurrences of DNA string needle in DNA string haystack using the naive
 *              string-matching algorithm
 */
size_t rosalind_search_naive(
        rosalind_dna_t const * haystack,
        rosalind_dna_t const * needle,
        size_t * occurrences,
        size_t max_occurences);

#endif /* ROSALIND_H */