#include "palavra.h"

Palavra * novaPalavra(char* texto){
    Palavra * palavra = (Palavra*)malloc(sizeof(Palavra));
    palavra->text = texto;
    return palavra;
}

void acrescentaPalavra(Palavra* antiga, char* texto){
    antiga->next = novaPalavra(texto);
}

void apagaPalavra(Palavra * palavra){
    free(palavra);
}
