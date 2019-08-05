//
//  quickfind.c
//  union_find
//
//  Created by José Manuel Torres on 17/10/14.
//  Copyright (c) 2014 ___JOSETORRES___. All rights reserved.
//


#include "quickfind.h"


void initQF(int * id, int n) {
    int i;
    for (i = 0; i < n; i++)
        id[i] = i;
}


int connectedQF(int * id, int p, int q) {
    int pid = findQF(id, p);
    int qid = findQF(id, q);
    return (pid == qid);
}

/**
 *  Devolve o id do conjunto q que pertence p
 *
 *  @param id array com informação sobre os conjuntos a que pertencem os elementos.
 *  @param p  <#p description#>
 *
 *  @return id do conjunto a que pertence elemento p.
 */
int findQF(int * id, int p) {
    return id[p];
}

/**
 Permite unir dois conjuntos: o conjunto a que pertence
 o elemento p com o conjunto a que pertence o elemento q.

 @param id
 @param n
 @param p
 @param q

 @return não retorna nada! (void)
 */
void unionQF(int * id, int n, int p, int q) {
    int pid = findQF(id, p);
    int qid = findQF(id, q);
    int i;
    for (i = 0; i < n; i++)
        if (id[i] == pid) id[i] = qid;
}