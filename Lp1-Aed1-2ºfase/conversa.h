#ifndef CONVERSA_H_INCLUDED
#define CONVERSA_H_INCLUDED

#include "mensagem.h"

typedef struct Conversa Conversa;

struct Conversa{
    Conversa * next;
    Mensagem* first;
};

Conversa * newconversa();
void novaMensagem(Conversa * conversa,Mensagem* mensagem);

#endif // CONVERSA_H_INCLUDED
