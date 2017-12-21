#include <stddef.h>
#include "mensagem.h"
#include "palavra.h"
#include "conversa.h"

void novaMensagem(Conversa * conversa,char* mensagem)
{

    int i=0,a=0;
    char *palavra=NULL;
    char **todasPalavras=(char**)malloc(sizeof(char *)*10);
    int tamanho_palavra=strlen(palavra);
    int numero_de_palavras_na_conversa=0;

    palavra = strtok (mensagem," ,.!?\n");

    while(palavra!=NULL)
    {
        int l=0;
        for(l=0; l<tamanho_palavra; l++)
        {
            palavra[l]=tolower(palavra[l]);
        }


        todasPalavras[numero_de_palavra]=(char*)malloc(sizeof(char)*(strlen(palavra)+1));
        strcpy(todasPalavras[numero_de_palavra],palavra);
        todasPalavras[numero_de_palavra][strlen(palavra)]='\0';
        numero_de_palavras_na_conversa++;

        if(numero_de_palavras_na_conversa%10==0)
        {
            todasPalavras = realloc(todasPalavras,((numero_de_palavras_na_conversa+10)*sizeof(char*)));
            int h=0;
            for(h=numero_de_palavra; h<numero_de_palavras_na_conversa+10; h++)
            {
                todasPalavras[h]=NULL;

            }
        }

        palavra = strtok(NULL, " ,.!?\n");
    }
}
