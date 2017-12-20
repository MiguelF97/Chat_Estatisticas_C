#include <string.h>
#include "../lib_util.h"
#include "ThreeSum.h"

/**
 *  print distinct triples (i, j, k) such that a[i] + a[j] + a[k] = 0
 *
 *  @param a int array
 *  @param N size of array
 */
void printAll(int* a, int N) {
    int i,j,k;
    for (i = 0; i < N; i++) {
        for (j = i+1; j < N; j++) {
            for (k = j+1; k < N; k++) {
                if (a[i] + a[j] + a[k] == 0) {
                    printf("%d %d %d\n",a[i],a[j],a[k]);
                }
            }
        }
    }
}

// return number of distinct triples (i, j, k) such that a[i] + a[j] + a[k] = 0
int countTriples(int* a, int N, long unsigned * cost_model) {
    int i,j,k;
    int cnt = 0;
    for (i = 0; i < N; i++) {
        for (j = i+1; j < N; j++) {
            for (k = j+1; k < N; k++) {
                *cost_model += 3; // foram feitos mais 3 acessos ao vector
                if (a[i] + a[j] + a[k] == 0) {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}



// returns true if the sorted array a[] contains any duplicated integers
int containsDuplicates(int * a, int N) {
    int i;
    for (i = 1; i < N; i++)
        if (a[i] == a[i-1]) return 1;
    return 0;
}




