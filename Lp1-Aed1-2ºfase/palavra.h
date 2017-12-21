#ifndef PALAVRA_H_INCLUDED
#define PALAVRA_H_INCLUDED

typedef struct Palavra{
    Palavra * next;
    char* text;
    //importancia etc
}Palavra;

Palavra * novaPalavra(char* texto);
void acrescentaPalavra(Palavra* antiga, char* texto);
void apagaPalavra(Palavra * palavra);
#endif // PALAVRA_H_INCLUDED
