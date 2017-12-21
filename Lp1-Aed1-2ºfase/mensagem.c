#include <stddef.h>
#include "mensagem.h"
#include "palavra.h"

Mensagem * mensagem(){
    Mensagem * mensagem = (Mensagem*)malloc(sizeof(Mensagem));
    mensagem->first = null;
    return mensagem;
}

void novaPalavra(Mensagem * mensagem,char* texto){
    if(mensagem->first == NULL){
        mensagem->first = novaPalavra(texto);
    }else{
        Palavra* current = mensagem->first;
        while(current->next != NULL){
            current = current->next;
        }
        acrescentaPalavra(current,texto);
    }
}

int removePalavra(Mensagem * mensagem,int index){
    if(mensagem->first == NULL){
        return 1;
    }
    int count = index;
    Palavra* prev = NULL;
    Palavra* current = mensagem->first;
    while(count != 0){
        if(current->next == NULL){
            return 1;
        }
        prev = current;
        current = current->next;
        count--;
    }
    Palavra * next = current->next;
    apagaPalavra(current);
    prev->next = next;
    return 0;
}
