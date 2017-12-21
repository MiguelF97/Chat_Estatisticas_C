#include <stddef.h>
#include "palavra.h"

Palavra * palavra(char* texto){
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
