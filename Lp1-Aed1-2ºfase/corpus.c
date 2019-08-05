#include <stddef.h>
#include "corpus.h"

Corpus * newcorpus(){
    Corpus * c = (Corpus*)malloc(sizeof(Corpus));
    c->first = NULL;
    return c;
}
