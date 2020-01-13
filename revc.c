/*
 * http://rosalind.info/problems/revc/
 * 
 * Given: A DNA string s of length at most 1000 bp.
 * 
 * Return: The reverse complement sc of s.
 * 
 * Assumes ASCII.
 */

#include <string.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    char s[1002];   /* a DNA string of length at most 1000 bp                       */
    char sc[1002];  /* reverse complement of s                                      */
    int len;        /* length of the DNA string                                     */
    char map[256];  /* maps complementary symbols to each other;                    */
                    /*  using only 4 of the elements, so trading memory for speed   */
    int sc_len;     /* length of the sc string                                      */
        
    /*
     * Read dataset
     */
    len = read_dataset(argc, argv, s, sizeof(s));
    if(len < 0)
    {
        return(0);
    }
    
    /*
     * Initialize map.
     * This really should be static const, but this way is less typing.
     */
    memset(map, ' ', sizeof(map));
    map['A'] = 'T';
    map['C'] = 'G';
    map['G'] = 'C';
    map['T'] = 'A';
    
    /*
     * Scan s backwards to find end of the DNA string.
     * In case there are any newlines or what-not.
     */
    for(len = len - 1; len >= 0; len--)
    {
        if((s[len] >= 'A') && (s[len] <= 'Z'))
        {
            break;
        }
    }
    
    /*
     * Compute reverse complement of s
     */
    for(sc_len = 0; (sc_len < cnt_of_array(sc)) && (len >= 0); sc_len++, len--)
    {
        sc[sc_len] = map[s[len]];
    }

    /*
     * Add NUL terminator becase we didn't memset the whole array before reading it
     */
    if(sc_len < cnt_of_array(sc))
    {
        sc[sc_len] = 0;
    }
    
    /*
     * Output result
     */
    printf("%s", sc);
    return(0);
}
