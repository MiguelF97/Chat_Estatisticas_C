//
//  quickunion.c
//  union_find
//
//  Created by José Manuel Torres on 17/10/14.
//  Copyright (c) 2014 ___JOSETORRES___. All rights reserved.
//

#include <stdio.h>

#include "quickunion.h"


void initQU(int * id, int n) {
    int i;
    for (i = 0; i < n; i++) {
        id[i] = i;
    }
}

int findQU(int * id, int i) {
    while (i != id[i]) {
        //id[i] = id[id[i]]; // Path compression improvement (Simpler one-pass variant or path halving)
        i = id[i];
    }
    return i;
}


int connectedQU(int * id, int p, int q) {
    return findQU(id, p) == findQU(id, q);
}

void unionQU(int * id, int p, int q) {
    int i = findQU(id, p);
    int j = findQU(id, q);
    id[i] = j;
}


/**
 *  Instrument function for quick-union
 *
 *  @param id <#id description#>
 *  @param i  <#i description#>
 *  @param n  <#n description#>
 */
void printDistances2rootQU(int * id, int i, int n) {
    printf("dist: ");
    for (i=0; i<n; i++) {
        printf("%d ", distance2rootQU(id, i));
    }
    printf("\n");
}

/**
 *  Instrument function for quick-union
 *
 *  @param id <#id description#>
 *  @param i  <#i description#>
 *
 *  @return <#return value description#>
 */
int distance2rootQU(int * id, int i) {
    int d=0;
    while (i != id[i]) {
        i = id[i];
        d++;
    }
    return d;
}


/** 
 * Weighted Quich-Union improvement
 **/
void initWQU(int * id, int * sz, int n) {
    int i;
    for (i = 0; i < n; i++) {
        id[i] = i;
        sz[i] = 1;
    }
}


/**
 * Weighted Quich-Union improvement
 */
void unionWQU(int * id, int * sz, int p, int q) {
    int i = findQU(id, p);
    int j = findQU(id, q);
    if  (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
    else                { id[j] = i; sz[i] += sz[j]; }
}