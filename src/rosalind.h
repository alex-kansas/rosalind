#if !defined(ROSALIND_H)
#define ROSALIND_H

#include <stddef.h>

#define MAX_DNA_SIZE        (1024)
#define MAX_DNA_CNT         (16)
#define MAX_DATASET_SIZE    (MAX_DNA_SIZE * MAX_DNA_CNT)

typedef enum
{
    NT_A,
    NT_C,
    NT_G,
    NT_T,
    NT_U,
    NT_CNT
} nt_t;

/*
 * The following structure defines a dataset commonly used in the Project Rosalind problems.
 */
typedef struct
{
    char *id;                       /* pointer to the NUL-terminated id string  */
    char *dna;                      /* pointer to the NUL-terminated DNA string */
    size_t dna_len;                 /* DNA sring length (aka total nucleotide)  */
    unsigned int nt_cnts[NT_CNT];   /* count of each of the nucleotides         */
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

#endif /* ROSALIND_H */