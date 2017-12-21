#include <stddef.h>
#include "mensagem.h"
#include "palavra.h"
#include "conversa.h"

Conversa * newconversa(){
    Conversa * c = (Conversa*)malloc(sizeof(Conversa));
    c->first = NULL;
    return c;
}

void novaMensagem(Conversa * conversa,Mensagem* mensagem)
{
    if(conversa->first == NULL){
        conversa->first = mensagem;
    }else{
        Mensagem* current = conversa->first;
        while(current->next != NULL){
            current = current->next;
        }
        acrescentaMensagem(current,mensagem);
    }
}

Mensagem * getMensagem(Conversa * c,int index){
    if(index == 0){
        return c->first;
    }
    int count = index;
    Mensagem* current = c->first;
    while(count != 0){
        if(current->next == NULL){
            return NULL;
        }
        current = current->next;
        count--;
    }
    return current;
}
