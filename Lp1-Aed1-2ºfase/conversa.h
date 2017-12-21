#ifndef CONVERSA_H_INCLUDED
#define CONVERSA_H_INCLUDED

#include "mensagem.h"

typedef struct Conversa Conversa;

struct Conversa{
    Mensagem* first;
};

void novaMensagem(Conversa * conversa,char* mensagem);

#endif // CONVERSA_H_INCLUDED
