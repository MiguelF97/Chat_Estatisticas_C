#ifndef MENSAGEM_H_INCLUDED
#define MENSAGEM_H_INCLUDED

#include "palavra.h"

typedef struct Mensagem Mensagem;

struct Mensagem{
    Palavra * first;
    int npalavras;
};

Mensagem * mensagem();
void novaPalavra(Mensagem * mensagem,char* texto);
int removePalavra(Mensagem * mensagem,int index);
#endif // MENSAGEM_H_INCLUDED
