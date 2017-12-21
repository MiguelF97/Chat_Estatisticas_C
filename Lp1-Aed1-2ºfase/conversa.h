#ifndef CONVERSA_H_INCLUDED
#define CONVERSA_H_INCLUDED

typedef struct Conversa{
    Mensagem* first;
}Conversa;

void novaMensagem(Conversa * conversa,char* mensagem);

#endif // CONVERSA_H_INCLUDED
