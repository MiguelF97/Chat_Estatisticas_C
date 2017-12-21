#ifndef MENSAGEM_H_INCLUDED
#define MENSAGEM_H_INCLUDED

#include "palavra.h"

typedef struct Mensagem Mensagem;

struct Mensagem{
    Mensagem * next;
    Palavra * first;
    int npalavras;
};

Mensagem * newmensagem();
Mensagem * newmensagem2(char* mensagem);
Palavra * getPalavra(Mensagem* m,int index);
void acrescentaMensagem(Mensagem * m, Mensagem * m2);
void novaPalavra(Mensagem * mensagem,char* texto);
int removePalavra(Mensagem * mensagem,int index);
#endif // MENSAGEM_H_INCLUDED
