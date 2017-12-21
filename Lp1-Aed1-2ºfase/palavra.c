#include <stddef.h>
#include "palavra.h"

Palavra * newpalavra(char* texto){
    Palavra * palavra = (Palavra*)malloc(sizeof(Palavra));
    palavra->text = texto;
    palavra->next = NULL;
    return palavra;
}

void acrescentaPalavra(Palavra* antiga, Palavra* next){
    antiga->next = next;
}

void apagaPalavra(Palavra * palavra){
    free(palavra);
}
