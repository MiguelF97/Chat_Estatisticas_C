//
//  quickunion.h
//  union_find
//
//  Created by José Manuel Torres on 17/10/14.
//  Copyright (c) 2014 ___JOSETORRES___. All rights reserved.
//

#ifndef __union_find__quickunion__
#define __union_find__quickunion__

void initQU(int * id, int n);
void initWQU(int * id, int * sz, int n);
int findQU(int * id, int i);
int distance2rootQU(int * id, int i);
void printDistances2rootQU(int * id, int i, int n);
int connectedQU(int * id, int p, int q);
void unionQU(int * id, int p, int q);
void unionWQU(int * id, int * sz, int p, int q);

#endif /* defined(__union_find__quickunion__) */