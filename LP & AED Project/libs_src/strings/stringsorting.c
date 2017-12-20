#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../libs_src/lib_util.h"
//#include "lib_util.h"
#include "stringsorting.h"

/*************************************************************************
 * Util functions for struct StringElements and struct StringKeyElements
 ************************************************************************/

void createStringKeyElementsArray(StringKeyElementsArray * si, int N) {
    si->N = N;
    si->str = (char **) malloc(sizeof(char *)*N);
    si->len = (int *) malloc(sizeof(int)*N);
    si->keys = (int *) malloc(sizeof(int)*N);
    return;
}

void createStringKeyElementsArrayAndFill(StringKeyElementsArray * a, int N, char ** strings, int * keys){
    int i;
    createStringKeyElementsArray(a, N);
    for (i = 0; i < N; i++) {
        a->str[i] = strings[i];
        a->len[i] = (int)strlen(strings[i]);
        a->keys[i] = keys[i];
    }
}

void freeStringKeyElementsArray(StringKeyElementsArray * si) {
    free(si->str);
    free(si->len);
    free(si->keys);
    return;
}

void createStringElementsArray(StringElementsArray * si, int N) {
    si->N = N;
    si->str = (char **) malloc(sizeof(char *)*N);
    si->len = (int *) malloc(sizeof(int)*N);
    return;
}

void createStringElementsArrayAndFill(StringElementsArray * si, int N, char ** strings){
    int i;
    createStringElementsArray(si, N);
    for (i = 0; i < N; i++) {
        si->str[i] = strings[i];
        si->len[i] = (int)strlen(strings[i]);
    }
    return;
}

void freeStringElementsArray(StringElementsArray * si) {
    free(si->str);
    free(si->len);
    return;
}

void printStringElementsArray(StringElementsArray * a) {
    int i;
    printf("\n-------------\nStringElementsArray (N=%d):\n",a->N);
    for (i = 0; i < a->N; i++)
        printf("\t%s\t(%d)\n",a->str[i],a->len[i]);
    printf("-------------\n");
}

int charAt(StringElementsArray * a, int i, int d) {
    return (d < a->len[i]) ? (a->str[i][d]) : STRING_END_CHAR;
}

/**
 *  exchange a[i] and a[j] in collection StringElementsArray *a
 *
 *  @param a strin elements array
 *  @param i
 *  @param j
 */
void exchStringElementsArray(StringElementsArray *a, int i, int j) {
    char * temp_str = a->str[i];
    a->str[i] = a->str[j];
    a->str[j] = temp_str;
    int temp_len = a->len[i];
    a->len[i] = a->len[j];
    a->len[j] = temp_len;
}



/**
 *  String compare for strings
 *
 *  @param s1   <#s1 description#>
 *  @param s2   <#s2 description#>
 *  @param len1 <#len1 description#>
 *  @param len2 <#len2 description#>
 *
 *  @return -1 if s1<s2; +1 if s1>s2; 0 if s1==s2
 */
int strcmp4Strings(const char *s1, const char *s2, int len1, int len2) {
    int i=0;
    for ( ; *s1 == *s2; s1++, s2++, i++){
        if (i >= len1 && i >= len2)
            return 0;
        else if (i >= len1)
            return -1;
        else if (i >= len2)
            return +1;
    }
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}



/*************************************************************************
 * Key-indexed counting / radix sorting
 ************************************************************************/

void key_index_counting(StringKeyElementsArray * a, int N, int R) {
    int i,r,c;
    int * count = newIntArray(R + 1);
    // reset count[] array
    for (i = 0; i < R + 1; i++)
        count[i]=0;
    StringKeyElementsArray aux; // aux Array
    createStringKeyElementsArray(&aux,N); // create aux array

    // compute frequency counts
    for (i = 0; i < N; i++)
        count[a->keys[i]]++;

    // transform counts to indicies
    for (r = 0; r < R; r++)
        count[r+1] += count[r];

    // distribute
    for (i = 0; i < N; i++) {
        c = a->keys[i] - 1;
        aux.str[count[c]] = a->str[i];
        aux.len[count[c]] = a->len[i];
        aux.keys[count[c]] = a->keys[i];
        count[c]++;
    }

    // copy back
    for (i = 0; i < N; i++) {
        a->str[i] = aux.str[i];
        a->len[i] = aux.len[i];
        a->keys[i] = aux.keys[i];
    }

    freeStringKeyElementsArray(&aux);
}

void mainClienteKEYCOUNT() {
    // To Do

}

/*************************************************************************
 * LSD Radix Sort
 ************************************************************************/


void lsd_sort(StringElementsArray * a, int W, int R) {
    int i,r,d,c;
    int N = a->N;
    int * count = newIntArray(R + 1);
    StringElementsArray aux; // aux Array
    createStringElementsArray(&aux,N); // create aux array

    for (d = W-1; d >= 0; d--) {

        // reset count[] array
        for (i = 0; i < R+1; i++)
            count[i]=0;

        // compute frequency counts
        for (i = 0; i < N; i++)
            count[a->str[i][d] + 1]++;

        // transform counts to indicies
        for (r = 0; r < R; r++)
            count[r+1] += count[r];

        // distribute
        for (i = 0; i < N; i++) {
            c = a->str[i][d];
            aux.str[count[c]] = a->str[i];
            aux.len[count[c]] = a->len[i];
            count[c]++;
        }

        // copy back
        for (i = 0; i < N; i++) {
            a->str[i] = aux.str[i];
            a->len[i] = aux.len[i];
        }

        // Trace of iterations for LSD string sort
        printf("\nLSD Sorted List (right to left) after sorting key %d:\n",d);
        for (i = 0; i < N; i++)
            printf("\t%s\n",a->str[i]);
    }
    freeStringElementsArray(&aux);
}







void mainClienteLSDSORT() {
        // To Do
}



/*************************************************************************
 * MSD Radix Sort (without cutoff)
 ************************************************************************/

void msd_sort_whithout_cutoff(StringElementsArray *a, StringElementsArray *aux, int lo, int hi, int d, int R) {
    int i,r,c;
    int * count = newIntArray(R + 2);
    // reset count[] array
    for (i = 0; i < R+2; i++)
        count[i]=0;

    if (hi <= lo) return;


    //if (hi - lo <= cutoff_value) insertion_sort();

    // compute frequency counts
    for (i = lo; i <= hi; i++) {
        c = charAt(a, i, d);
        count[c + 2]++;
    }

    // transform counts to indicies
    for (r = 0; r < R + 1; r++)
        count[r+1] += count[r];

    // distribute
    for (i = lo; i <= hi; i++) {
        c = charAt(a, i, d);
        aux->str[count[c + 1]] = a->str[i];
        aux->len[count[c + 1]] = a->len[i];
        count[c + 1]++;
    }

    // copy back
    for (i = lo; i <= hi; i++) {
        a->str[i] = aux->str[i-lo];
        a->len[i] = aux->len[i-lo];
    }

    // Trace of recursive calls for MSD string sort (version with no cutoff for small subarrays used!)
    printf("\n-------------\nMSD Sorted List (left to right) after iteration (lo,hi,d)= %d,%d,%d:\n",lo,hi,d);
    for (i = lo; i <= hi; i++)
        printf("\t%s\n",a->str[i]);

    // recursively sort for each character
    for (r = 0; r < R; r++)
        msd_sort_whithout_cutoff(a, aux, lo + count[r], lo + count[r+1] - 1, d+1, R);
}







void mainClienteMSDSORT_WHITHOUT_CUTOFF() {
    // To Do
}



