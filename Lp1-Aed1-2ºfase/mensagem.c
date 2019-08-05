#include <stddef.h>
#include "mensagem.h"

Mensagem * newmensagem(){
    Mensagem * mensagem = (Mensagem*)malloc(sizeof(Mensagem));
    mensagem->first = NULL;
    mensagem->next = NULL;
    return mensagem;
}


Mensagem * newmensagem2(char* mensagem){
    int i=0,a=0;
    char *palavra=NULL;
    char **todasPalavras=(char**)malloc(sizeof(char *)*10);
    int numero_de_palavras_na_conversa=0;

    palavra = strtok(mensagem," ,.!?\n");

    int tamanho_palavra=strlen(palavra);

    while(palavra!=NULL)
    {
        int l=0;
        for(l=0; l<tamanho_palavra; l++)
        {
            palavra[l]=tolower(palavra[l]);
        }
        todasPalavras[numero_de_palavras_na_conversa]=(char*)malloc(sizeof(char)*(strlen(palavra)+1));
        strcpy(todasPalavras[numero_de_palavras_na_conversa],palavra);
        todasPalavras[numero_de_palavras_na_conversa][strlen(palavra)]='\0';
        numero_de_palavras_na_conversa++;

        if(numero_de_palavras_na_conversa%10==0)
        {
            todasPalavras = realloc(todasPalavras,((numero_de_palavras_na_conversa+10)*sizeof(char*)));
            int h=0;
            for(h=numero_de_palavras_na_conversa; h<numero_de_palavras_na_conversa+10; h++)
            {
                todasPalavras[h]=NULL;

            }
        }

        palavra = strtok(NULL, " ,.!?\n");
    }

    Mensagem * m = newmensagem();

    for(i = 0;i < numero_de_palavras_na_conversa;i++){
        novaPalavra(m,todasPalavras[i]);
    }

    return m;
}

Palavra * getPalavra(Mensagem* m,int index){
    if(index == 0){
        return m->first;
    }
    int count = index;
    Palavra* current = m->first;
    while(count != 0){
        if(current->next == NULL){
            return NULL;
        }
        current = current->next;
        count--;
    }
    return current;
}

void acrescentaMensagem(Mensagem * m, Mensagem * m2){
    m->next = m2;
}

void novaPalavra(Mensagem * mensagem,char* texto){
    if(mensagem->first == NULL){
        mensagem->first = newpalavra(texto);
    }else{
        Palavra* current = mensagem->first;
        while(current->next != NULL){
            current = current->next;
        }
        Palavra* p = newpalavra(texto);
        acrescentaPalavra(current,p);
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
