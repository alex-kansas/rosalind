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
        rosalind_dna_t *dna,        /* output DNA info here             */
        char term);                 /* terminator                       */

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
        if(ds->dna[ds->dna_cnt].dna)
        {
            if(!ds->dna[ds->dna_cnt].id)
            {
                ds->dna[ds->dna_cnt].id = "unnamed string";
            }
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
 * Function   : rosalind_search_naive
 * Description: Finds all occurrences of DNA string needle in DNA string haystack using the naive
 *              string-matching algorithm
 */
size_t rosalind_search_naive(
        rosalind_dna_t const * haystack,
        rosalind_dna_t const * needle,
        size_t * occurrences,
        size_t max_occurences)
{
    size_t i = 0;
    size_t j = 0;
    size_t cnt_occurrences = 0;

    if(haystack->dna_len < needle->dna_len)
    {
        return(0);
    }

    for(i = 0; i < (haystack->dna_len - needle->dna_len); i++)
    {
        for(j = 0; j < needle->dna_len; j++)
        {
            if(haystack->dna[i + j] != needle->dna[j])
            {
                break;
            }
        }

        if(j == needle->dna_len)
        {
            occurrences[cnt_occurrences++] = i;
            if(cnt_occurrences >= max_occurences)
            {
                return(cnt_occurrences);
            }
        }
    }

    return(cnt_occurrences);
}


/*
 * The follwing function scans DNA string, counting it's nucleotides.
 * Assumes leading whitespace has already been skipped.
 * Returns number of characters consumed.
 */
static size_t parse_dna(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len,             /* dataset buffer size              */
        rosalind_dna_t *dnainfo,    /* output DNA info here             */
        char term)                  /* terminator                       */
{
    size_t pos;                     /* input buffer cursor              */
    binary_dna_t * dna;             /* output buffer cursor             */

    dnainfo->dna = (binary_dna_t *)buf;

    /*
     * Scan the DNA string looking for the terminator, counting symbols, eliminating
     * whitespace, and converting from character to binary representation.
     */
    for(pos = 0, dna = (binary_dna_t *)buf; pos < buf_len; pos++, buf++)
    {
        char c = *buf;

        if(c == term)
        {
            break;
        }

        if(isspace(c))
        {
            continue;
        }

        dnainfo->dna_len++;

        switch(c)
        {
            case 'A':
                dnainfo->a_cnt++;
                *dna++ = A;
                break;

            case 'C':
                dnainfo->c_cnt++;
                *dna++ = C;
                break;

            case 'G':
                dnainfo->g_cnt++;
                *dna++ = G;
                break;

            case 'T':
            case 'U':
                { compiler_assert(T == U); }
                dnainfo->t_cnt++;
                *dna++ = T;
                break;

            default:
                /*
                 * An invalid chacter.  Clean up and abort.
                 */
                printf("Error! Invalid DNA string: %s\n", dnainfo->dna);
                memset(dnainfo, 0, sizeof(rosalind_dna_t));
                return(buf_len);
        }
    }

    /*
     * Clear symbols that have been moved and trailing whitespace.
     */
    { compiler_assert(sizeof(char) == 1); }
    memset(dna, 0, buf - (char *)dna);

    pos += skip_whitespace(buf, buf_len - pos);

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
 * If the first character is '>', assume that this is a FAFSTA record.
 * Otherwise, assume that this is a list of (DNA) strings separated by newline.
 * Returns number of characters consumed
 */
static size_t parse_rec(
        char *buf,                  /* dataset buffer                   */
        size_t buf_len,             /* dataset buffer size              */
        rosalind_dna_t *dna)        /* output DNA info here             */
{
    size_t pos = skip_whitespace(buf, buf_len);

    if(pos < buf_len)
    {
        if(buf[pos] == '>')
        {
            pos += parse_id(buf + pos, buf_len - pos, dna);
            pos += parse_dna(buf + pos, buf_len - pos, dna, '>');
        }
        else
        {
            pos += parse_dna(buf + pos, buf_len - pos, dna, '\n');
        }
    }

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