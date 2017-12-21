#ifndef CORPUS_H_INCLUDED
#define CORPUS_H_INCLUDED
#include "conversa.h"

typedef struct Corpus Corpus;

struct Corpus{
    Conversa* first;
};

Corpus * newcorpus();
#endif // CORPUS_H_INCLUDED
