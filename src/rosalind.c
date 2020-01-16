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
     * Load dataset from file.
     */
    memset(ds, 0, sizeof(rosalind_dataset_t));
    ds->buf_len = utils_read_file(argc, argv, ds->buf, sizeof(ds->buf));

    /*
     * Make sure the laste character is always NUL.
     * utils_read_file is supposed to do that, but for robustness purposes, let's just write
     * a NUL to the last element
     */
    ds->buf[sizeof(ds->buf) - 1] = 0;

    /*
     * Scan dataset for DNA strings
     */
    pos = skip_whitespace(ds->buf, ds->buf_len);
    while((pos < ds->buf_len) && (ds->dna_cnt < cnt_of_array(ds->dna)))
    {
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
 * Assumes leading whitespace has already been skipped.
 * Returns number of characters consumed.
 */
static size_t parse_dna(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len,             /* dataset buffer size              */
        rosalind_dna_t *dna)        /* output DNA info here             */
{
    size_t pos;                     /* cursor                           */

    /*
     * Initialize the accumulators
     *
     * To demonstrate a fast counting method, we will use an array of 256 integers to accumulate
     * symbol counts.
     * With the size of strings that we are using it doesn't really make a difference (might
     * even make it worse because we have to memset the whole array), but with really large
     * datasets this could speed things up by avoiding branching.
     *
     * If we were concerned with memset taking too long, we could initilalize just whitespace and
     * nucleotide entries.
     */
    compiler_assert(sizeof(char) == 1);
    unsigned int cnt[256];
    memset(&cnt, 0, sizeof(cnt));

    /*
     * If ID has not been set, set it to the DNA string itself
     */
    dna->dna = buf;
    if(!dna->id)
    {
        dna->id = buf;
    }

    /*
     * Scan the DNA string
     * '>' identifies the start of id of the next string
     */
    for(pos = 0; pos < buf_len; pos++, buf++)
    {
        char c = *buf;
        if(c == '>')
        {
            break;
        }

        cnt[c]++;
    }

    /*
     * Update output structure.
     */
    dna->dna_len = pos;
    dna->a_cnt   = cnt['A'];
    dna->c_cnt   = cnt['C'];
    dna->g_cnt   = cnt['G'];
    dna->t_cnt   = cnt['T'];
    dna->total_nt_cnt = dna->a_cnt + dna->c_cnt + dna->g_cnt + dna->t_cnt;

    /*
     * Check if counts add up.  If they don't then we encountered some rogue symbols and this
     * string is not valid.
     */
    if(  ((dna->total_nt_cnt + cnt[' '] + cnt['\n']) != dna->dna_len)
      || (dna->total_nt_cnt == 0))
    {
        printf("Error! Invalid DNA string: %s\n", dna->id);
        memset(dna, 0, sizeof(rosalind_dna_t));
    }

    /*
     * Replace trailing whitespace with NUL
     * We don't want too replace whitespace with NUL white we are scanning the DNA string
     * in case there is whitespace in the middle of the string.
     */
    while((dna->dna_len > 0) && isspace(*--buf))
    {
        *buf = 0;
        dna->dna_len--;
    }

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
            for(pos = 1; (pos < buf_len) && !isspace(buf[pos]); pos++);
        }
    }

    pos += skip_whitespace(buf + pos, buf_len - pos);
    return(pos);
}


/*
 * The following function parses the next record in the dataset.
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