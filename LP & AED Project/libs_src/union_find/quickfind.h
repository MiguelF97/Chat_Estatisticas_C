//
//  quickfind.h
//  union_find
//
//  Created by José Manuel Torres on 17/10/14.
//  Copyright (c) 2014 ___JOSETORRES___. All rights reserved.
//

#ifndef __union_find__quickfind__
#define __union_find__quickfind__

void initQF(int * id, int n);
int findQF(int * id, int p);
int connectedQF(int * id, int p, int q);
void unionQF(int * id, int n, int p, int q);

#endif /* defined(__union_find__quickfind__) */