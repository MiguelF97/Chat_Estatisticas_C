#ifndef PALAVRA_H_INCLUDED
#define PALAVRA_H_INCLUDED

typedef struct Palavra Palavra;

struct Palavra{
    Palavra * next;
    char* text;
    //importancia etc
};

Palavra * newpalavra(char* texto);
void acrescentaPalavra(Palavra* antiga, Palavra * next);
void apagaPalavra(Palavra * palavra);
#endif // PALAVRA_H_INCLUDED
