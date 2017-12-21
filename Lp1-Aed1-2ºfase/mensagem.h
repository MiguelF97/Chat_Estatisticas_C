#ifndef MENSAGEM_H_INCLUDED
#define MENSAGEM_H_INCLUDED

typedef struct Mensagem{
    Palavra * first;
    int npalavras;
}Mensagem;

Mensagem * novaMensagem();
void novaPalavra(Mensagem * mensagem,char* texto);
int removePalavra(Mensagem * mensagem,int index);
#endif // MENSAGEM_H_INCLUDED
