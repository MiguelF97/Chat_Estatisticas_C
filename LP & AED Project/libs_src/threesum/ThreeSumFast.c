//
//  ThreeSumFast.c
//  
//
//  Created by José Manuel Torres on 19/09/16.
//
//
#include <stdio.h>
#include "../lib_util.h"
#include "ThreeSum.h"
#include "ThreeSumFast.h"

int countTriplesFast(int * a, int N) {
    int k, cnt, i, j;
    sortIntArray(a, N);
    if (containsDuplicates(a,N))
        return -1;
    cnt = 0;
    for (i = 0; i < N; i++) {
        for (j = i+1; j < N; j++) {
            k = binarySearch(a, N, -(a[i] + a[j]));
            if (k > j) cnt++;
        }
    }
    return cnt;
}