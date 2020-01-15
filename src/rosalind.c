/*
 * This file contains functions used for soliving Project Rosalind problems.
 * http://rosalind.info/problems/list-view/
 *
 * ASCII encoding is assumed.
 *
 * Dynamic memory is not used for demonstration purposes.
 *
 * Error checking is implemented for demonstration purposes.
 *
 * We are using size_t for sizes and counters just to match standard library function
 * signatures.  It is really not necessary, unsigned int would work just as well.
 */

#include <ctype.h>
#include <stddef.h>
#include <string.h>

#include "rosalind.h"

#include "utils.h"

/*
 * Forward declarations of the static functions
 */
static size_t parse_dna(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len,             /* dataset buffer size              */
        rosalind_dna_t *dna);       /* output DNA info here             */

static size_t parse_rec(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len,             /* dataset buffer size              */
        rosalind_dna_t *dna);       /* output DNA info here             */

static size_t skip_whitespace(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len);            /* dataset buffer size              */


/*
 * The following function reads a dataset from a file specified by command arguments and
 * scans it.
 */
void rosalind_load_dataset(
        int argc,                   /* number of command line arguments */
        char *argv[],               /* command line arguments           */
        rosalind_dataset_t *ds)     /* output dataset here              */
{
    size_t pos;                     /* cursor                           */

    /*
     * Load dataset from file
     */
    memset(ds, 0, sizeof(rosalind_dataset_t));
    ds->buf_len = utils_read_file(argc, argv, ds->buf, sizeof(ds->buf));

    /*
     * Scan dataset for DNA strings
     */
    pos = 0;
    while((pos < ds->buf_len) && (ds->dna_cnt < cnt_of_array(ds->dna)))
    {
        pos += skip_whitespace(ds->buf + pos, ds->buf_len - pos);
        pos += parse_rec(ds->buf + pos, ds->buf_len - pos, &ds->dna[ds->dna_cnt]);

        /*
         * Increment record count if a record was found
         */
        if(ds->dna[ds->dna_cnt].dna_len > 0)
        {
            ds->dna_cnt += 1;
        }
    }

    /*
     * Check if we processed the whole dataset
     */
    if(pos < ds->buf_len)
    {
        printf("Error! Too many DNA strings\n");
    }
}


/*
 * The follwing function scans DNA string, counting it's nucleotides.
 * Skips trailing whitespace.
 * Assumes leading whitespace has already been skipped.
 * Returns number of characters consumed.
 */
static size_t parse_dna(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len,             /* dataset buffer size              */
        rosalind_dna_t *dna)        /* output DNA info here             */
{
    size_t pos;                     /* cursor                           */
    int error;                      /* error indicator                  */

    /*
     * Initialize the accumulators
     */
    dna->dna_len = 0;
    memset(dna->nt_cnts, 0, sizeof(dna->nt_cnts));

    /*
     * Scan the DNA string
     */
    for(pos = 0, error = 0; (pos < buf_len) && !isspace(buf[pos]) && !error; pos++)
    {
        switch(buf[pos])
        {
            case 'A':
                dna->dna_len++;
                dna->nt_cnts[NT_A]++;
                break;

            case 'C':
                dna->dna_len++;
                dna->nt_cnts[NT_C]++;
                break;

            case 'G':
                dna->dna_len++;
                dna->nt_cnts[NT_G]++;
                break;

            case 'T':
                dna->dna_len++;
                dna->nt_cnts[NT_T]++;
                break;

            default:
                printf("Error! Invalid DNA string: %s\n", buf);
                error = 1;
                break;
        }
    }


    /*
     * If an error occurred, clear out the accumulators, and skip to next whitespace character.
     */
    if(error)
    {
        dna->dna_len = 0;
        memset(dna->nt_cnts, 0, sizeof(dna->nt_cnts));
        for(; (pos < buf_len) && !isspace(buf[pos]); pos++);
    }

    /*
     * If we found a valid DNA string, set DNA pointer.
     * If ID has not been set, set ID to DNA.
     */
    else if(dna->dna_len > 0)
    {
        dna->dna = buf;
        if(!dna->id)
        {
            dna->id = dna->dna;
        }
    }

    /*
     * Skip trailing whitespace
     */
    pos += skip_whitespace(buf + pos, buf_len - pos);

    return(pos);
}


/*
 * The following function parses optional ID string.
 * ID is an printable string that starts with '>' and ends with whitespace.
 * Skips trailing whitespace.
 * Assumes leading whitespace has already been skipped.
 * Returns number of characters consumed.
 */
static size_t parse_id(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len,             /* dataset buffer size              */
        rosalind_dna_t *dna)        /* output DNA info here             */
{
    size_t pos = 0;                 /* cursor                           */

    if(buf_len > 1)
    {
        if(buf[0] == '>')
        {
            dna->id = &buf[1];
            for(pos = 1; (pos < buf_len) && (buf[pos] >= '!') && (buf[pos] <= '~'); pos++);
        }
    }

    pos += skip_whitespace(buf + pos, buf_len - pos);
    return(pos);
}


/*
 * The following function parses the next record in the dataset.
 * Skips trailing whitespace.
 * Assumes leading whitespace has already been skipped.
 * Returns number of characters consumed
 */
static size_t parse_rec(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len,             /* dataset buffer size              */
        rosalind_dna_t *dna)        /* output DNA info here             */
{
    size_t pos = parse_id(buf, buf_len, dna);
    pos += parse_dna(buf + pos, buf_len - pos, dna);
    return(pos);
}


/*
 * The following function skips whitespace, replacing it with NUL.
 * Returns number of characters consumed.
 */
static size_t skip_whitespace(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len)             /* dataset buffer size              */
{
    size_t pos;                     /* cursor                           */
    for(pos = 0; (pos < buf_len) && isspace(buf[pos]); pos++)
    {
        buf[pos] = 0;
    }
    return(pos);
}