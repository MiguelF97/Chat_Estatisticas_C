#include "lib_stats.h"
#include "lib_util.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"



char *ler_texto(char *path)
{
    int i=0;
    char *file_contents;
    long input_file_size;
    FILE *input_file = fopen(path, "r");
    if(input_file == NULL)                           //Caso n tenho aberto com sucesso o ficheiro
    {
        return NULL;
    }
    fseek(input_file, 0, SEEK_END);                 //Vai ate ao fim do ficheiro   --- fseek pos o pointer no fim do texto
    input_file_size = ftell(input_file);            //tamanho do ficheiro ---ftell diz onde e que esta o ponteiro do ficheiro(inputl_file aponta par ao fim);
    rewind(input_file);                         //volta a por o ponteiro no inicio
    file_contents = (char*)malloc((input_file_size+1) * (sizeof(char)));    //aloca a memoria para guardar o ficheiro todo
    for(i=0; i<input_file_size+1; i++)
    {
        *(file_contents+i)='\0';
    }
    fread(file_contents, input_file_size, 1, input_file);   //lê o ficheiro

    //  file_contents[input_file_size] = NULL;


    fclose(input_file);


    //printf("%s",file_contents);

    // fecha o ficheiro
    return file_contents;


}

int check_timestamp(char * frase, Mensagem *link_mensagem,Conversa*link_conversa )
{
    char*time_utilizador=NULL;

    char *frase_aux=calloc(100,1);
    strcpy(frase_aux,frase);

    char* Time_Stamp=calloc(100,1);
    char* Utilizador=calloc(100,1);
    int total=0;

    time_utilizador = strtok (frase_aux,">");

    int count=0;

    while (time_utilizador!=NULL)
    {
        if(count==0)
        {
            strcpy(Utilizador,time_utilizador);
            total=strlen(time_utilizador);
            link_mensagem->pessoa_correspondente=Utilizador;
            utilizadores_na_conversa(link_mensagem,link_conversa);
        }
        if(count==1)
        {

            strcpy(Time_Stamp,time_utilizador);
            total=total+strlen(time_utilizador);
            link_mensagem->time_stamp=Time_Stamp;
        }


        count++;
        time_utilizador = strtok (NULL,">");
    }

    free(time_utilizador);
    //free(Utilizador);
    free(frase_aux);

    return total+2;
}

void utilizadores_na_conversa(Mensagem* link_mensagem,Conversa* link_conversa)
{
    int current_uti=link_conversa->n_utilizadores,i,flag=0;
    char ** utilizadores=NULL;
    char *nome=link_mensagem->pessoa_correspondente;
    int tamanho_nome=strlen(nome);

    if(current_uti==0)
    {
        utilizadores=(char**)malloc(sizeof(char*)*10);  // ----------------SO DA ATE 10 UTILIZADORES POR CONVERSA
        utilizadores[0]=malloc(1*tamanho_nome+1);
        strcpy(utilizadores[0],nome);
        utilizadores[0][tamanho_nome]='\0';
        link_conversa->n_utilizadores=link_conversa->n_utilizadores+1;
        link_conversa->utilizadores_conversa=utilizadores;
    }
    else
    {
        utilizadores=link_conversa->utilizadores_conversa;
        for(i=0; i<current_uti; i++)
        {
            if(strcmp(utilizadores[i],nome)==0)
            {
                flag=1;
                break;
            }

        }
        if(flag==0)
        {
            utilizadores[current_uti]=malloc(1*tamanho_nome+1);
            strcpy(utilizadores[current_uti],nome);
            utilizadores[current_uti][tamanho_nome+1]='\0';
            link_conversa->n_utilizadores=link_conversa->n_utilizadores+1;
        }


    }

}

void search_word(Corpus* link_corpus,char * auxpalavra)
{

    int i,ias,asd,flag=0,vezes_repetidas=0;
    int tamanho_pala=strlen(auxpalavra);
    Conversa* current=link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;

    for(i=0; i<tamanho_pala; i++)
    {
        auxpalavra[i]=tolower(auxpalavra[i]);
    }

    if(tamanho_pala>20)
    {
        printf("\nERRO-Palavra tem que ter menos que 20 caracteres\n");
        return ;
    }


    for(i=0; i<link_corpus->n_conversas; i++)
    {

        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {

            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }


            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;
                }
                if(strcmp(current_pala->text,auxpalavra)==0)
                {
                    printf("\n\nPalavra->%s\n",current_pala->text);
                    printf("Numero da Palavra no Corpus->%d\n",current_pala->posicao_corpus);
                    printf("Numero da Palavra na Conversa->%d\n",current_pala->posicao_conversa);
                    printf("Numero da Palavra na Mensagem->%d\n",current_pala->posicao_mensagem);
                    vezes_repetidas++;
                    flag=1;
                }

                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }



    if(flag!=0)
    {
        printf("\n----------A Palavra Aparece no Total %d Vezes-----------\n\n\n",vezes_repetidas);
    }

    if(flag==0)
    {
        printf("\n\nEssa palavra nao existe nas mensagens\n\n\n");
    }

}

void frase_entre_palavras(Corpus* link_estruturas,char*palavra1,char*palavra2,int id_conversa)
{
    int i,flag=0,asd,count=0;
    id_conversa=id_conversa-1;

    int tamanho_pala1=strlen(palavra1);
    int tamanho_pala2=strlen(palavra2);

    Conversa*current=link_estruturas->first;

    if(id_conversa == 0)
    {
        current=link_estruturas->first;
    }
    current = link_estruturas->first;
    while(count < id_conversa)
    {
        if(current->next == NULL)
        {
            return ;
        }
        current = current->next;
        count++;
    }

    Mensagem* current_msg=current->first;
    Palavra*current_pala=current->first->first;



    if(tamanho_pala1>20||tamanho_pala2>20)
    {
        printf("\nERRO-Palavra tem que ter menos que 20 caracteres\n");
        return ;
    }


    int b=current->n_frases_total;
    for(i=0; i<b; i++)
    {


        if(current_msg!=NULL)
        {
            current_pala=current_msg->first;
        }


        int bb=current_msg->npalavras;
        for(asd=0; asd<bb; asd++)
        {
            if(current_pala==NULL)
            {
                break;
            }


            if(strcmp(current_pala->text,palavra1)==0&&flag==0)
            {
                flag++;
            }

            if(strcmp(current_pala->text,palavra2)==0)
            {
                flag++;
            }

            if(flag==2)
            {
                break;
            }

            current_pala=current_pala->next;
        }

        if(flag==2)
        {
            break;
        }
        current_msg=current_msg->next;

    }



    if(flag!=2)
    {
        printf("\n--ERRO na ordem ou Palavra(s) nao encontrada(s) --\n");
        return ;

    }

    count=0;
    current_msg=current->first;
    current_pala=current->first->first;

    printf("\n\n-----Palavras entre -%s- e -%s- na %d Conversa-----\n\n",palavra1,palavra2,id_conversa);

    b=current->n_frases_total;
    for(i=0; i<b; i++)
    {


        if(current_msg!=NULL)
        {
            current_pala=current_msg->first;
        }


        int bb=current_msg->npalavras;
        for(asd=0; asd<bb; asd++)
        {

            if(count==1&&strcmp(current_pala->text,palavra2)!=0)
            {
                printf("%s->",current_pala->text);
                printf("\t\t");
                printf("Na Mensagem %d- as %s horas\n",i+1,current_msg->time_stamp);
            }

            if(strcmp(current_pala->text,palavra1)==0&&count==0)
            {
                count++;
            }

            if(strcmp(current_pala->text,palavra2)==0)
            {
                count++;
            }

            if(count==2)
            {
                break;
            }


            current_pala=current_pala->next;
        }

        current_msg=current_msg->next;

        if(count==2)
        {
            break;
        }

    }




    return ;
}

void frase_entre_palavras_escolhidas(Corpus* link_estruturas,char*palavra1,char*palavra2,int id_conversa,int posicao1,int posicao2)
{

    int i,flag=0,asd;
    id_conversa--;

    int tamanho_pala1=strlen(palavra1);
    int tamanho_pala2=strlen(palavra2);

    int count=0;

    Conversa*current=link_estruturas->first;

    if(id_conversa == 0)
    {
        current=link_estruturas->first;
    }
    current = link_estruturas->first;
    while(count < id_conversa)
    {
        if(current->next == NULL)
        {
            return ;
        }
        current = current->next;
        count++;
    }




    Mensagem* current_msg=current->first;
    Palavra*current_pala=current->first->first;



    if(tamanho_pala1>20||tamanho_pala2>20)
    {
        printf("\nERRO-Palavra tem que ter menos que 20 caracteres\n");
        return ;
    }


    int b=current->n_frases_total;
    for(i=0; i<b; i++)
    {


        if(current_msg!=NULL)
        {
            current_pala=current_msg->first;
        }


        int bb=current_msg->npalavras;
        for(asd=0; asd<bb; asd++)
        {
            if(current_pala==NULL)
            {
                break;
            }

            if(strcmp(current_pala->text,palavra1)==0)
            {
                flag++;
            }

            if(strcmp(current_pala->text,palavra2)==0)
            {
                flag++;
            }

            if(flag==(posicao1+posicao2))
            {
                break;
            }

            current_pala=current_pala->next;
        }

        if(flag==(posicao1+posicao2))
        {
            break;
        }
        current_msg=current_msg->next;

    }



    if(flag!=(posicao1+posicao2))
    {
        printf("\n--ERRO na ordem ou Palavra(s) nao encontrada(s) --\n");
        return ;

    }


    count=0;
    current_msg=current->first;
    current_pala=current->first->first;

    printf("\n\n-----Palavras entre -%s- e -%s- na %d Conversa-----\n\n",palavra1,palavra2,id_conversa++);

    flag=0;
    b=current->n_frases_total;
    for(i=0; i<b; i++)
    {

        if(current_msg!=NULL)
        {
            current_pala=current_msg->first;
        }


        int bb=current_msg->npalavras;
        for(asd=0; asd<bb; asd++)
        {
            if(current_pala==NULL)
            {
                break;

            }

            if(count>=posicao1&&flag!=posicao2)
            {
                if((posicao2-flag)==1&&strcmp(palavra2,current_pala->text)==0)
                {
                    break;
                }
                printf("%s->",current_pala->text);
                printf("\t\t");
                printf("Na Mensagem %d- as %s horas\n",i+1,current_msg->time_stamp);
            }

            if(strcmp(current_pala->text,palavra1)==0)
            {
                count++;
            }

            if(strcmp(current_pala->text,palavra2)==0)
            {

                count++;
                flag++;
            }

            if(count==(posicao1+posicao2))
            {
                break;
            }


            current_pala=current_pala->next;
        }

        current_msg=current_msg->next;

        if(count==(posicao1+posicao2))
        {
            break;
        }

    }

    return ;
}

void search_letras(Corpus * link_corpus)
{
    char* letras=(char*)calloc(1000,sizeof(char));
    int* posicao_letras=(int*)calloc(1000,sizeof(int));

    Conversa* current=link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;

    int i=0,b=0,c=0,tamanho_palavra=0,tamanho_abc=0,flag=0,tamanho_total=0,ias,asd;

    for(i=0; i<link_corpus->n_conversas; i++)
  {

        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {

            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }

            if(current_msg==NULL)
            {
                break;
            }

            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;
                }
                tamanho_palavra=strlen(current_pala->text);

                for(b=0; b<tamanho_palavra; b++)
                {
                    flag=0;

                    for(c=0; c<=tamanho_abc; c++)
                    {
                        char *aux_palavra=current_pala->text;

                        if(aux_palavra[b]==letras[c])
                        {

                            flag=1;
                            posicao_letras[c]++;
                            tamanho_total++;
                            break;

                        }
                    }
                    if(flag==0)
                    {

                        letras[tamanho_abc]=current_pala->text[b];
                        posicao_letras[c]++;
                        tamanho_total++;
                        tamanho_abc++;


                    }

                }


                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }





    b=0;
    printf("TOTAL=%d\n\n",tamanho_total);
    for(b=0; b<tamanho_abc; b++)
    {

        printf("%c--%d--%f%%\n",letras[b],posicao_letras[b],((float)posicao_letras[b]/tamanho_total) * 100);
    }


}

void primeira_ultima_letra(Corpus* link_corpus)
{

    int i,tamanho_palavra=0,numero_letras_primeiro=0,numero_letras_ultimo=0,c=0,tamanho_tolta1=0,tamanho_tolta2=0,ias,asd,flag=0,flag_ultima=0;

    char *array_primeira_letra=NULL;
    array_primeira_letra=(char*)calloc(1000,sizeof(char));
    int *array_int_primeira_letra=NULL;
    array_int_primeira_letra=(int*)calloc(1000,sizeof(int));


    char *array_ultima_letra=NULL;
    array_ultima_letra=(char*)calloc(1000,sizeof(char));
    int *array_int_ultima_letra=NULL;
    array_int_ultima_letra=(int *)calloc(1000,sizeof(int));


    Conversa* current=link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;


    for(i=0; i<link_corpus->n_conversas; i++)
    {

        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {


            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }

            if(current_msg==NULL)
            {
                break;
            }

            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;
                }
                tamanho_palavra=strlen(current_pala->text);
             //   printf("%c",current_pala->text[tamanho_palavra-1]);
                flag_ultima=0;
                flag=0;

                for(b=0; b<numero_letras_primeiro; b++)
                {
                    if(current_pala->text[0]==array_primeira_letra[b])
                    {
                        array_int_primeira_letra[b]++;
                        tamanho_tolta1++;
                        flag=1;
                    }

                }

                if(flag==0)
                {

                    array_primeira_letra[numero_letras_primeiro]=current_pala->text[0];


                    array_int_primeira_letra[b]++;


                    tamanho_tolta1++;

                    numero_letras_primeiro++;

                }


                for(c=0; c<numero_letras_ultimo; c++)
                {
                    if(current_pala->text[tamanho_palavra-1]==array_ultima_letra[c])
                    {
                        array_int_ultima_letra[c]++;
                        tamanho_tolta2++;
                        flag_ultima=1;
                    }

                }

                if(flag_ultima==0)
                {

                    array_ultima_letra[numero_letras_ultimo]=current_pala->text[tamanho_palavra-1];

                    array_int_ultima_letra[c]++;

                    tamanho_tolta2++;

                    numero_letras_ultimo++;
                }


                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }



    printf("Primeiras letras das palavras(%d):\n\n",tamanho_tolta1);
    for(i=0; i<numero_letras_primeiro; i++)
    {
        printf("%c--%d--%f%%\n",array_primeira_letra[i],array_int_primeira_letra[i],((float)array_int_primeira_letra[i]/tamanho_tolta1) * 100);
    }
    printf("\n\n\n\n");
    printf("Ultimas letras das palavras(%d):\n\n",tamanho_tolta2);
    for(i=0; i<numero_letras_ultimo; i++)
    {
        printf("%c--%d--%f%%\n",array_ultima_letra[i],array_int_ultima_letra[i],((float)array_int_ultima_letra[i]/tamanho_tolta2) * 100);
    }

}

float palavra_media(Corpus * link_corpus)
{
    int i,ias,asd,numero_palavras=0;
    float soma=0.0;
    printf("\n\nTamanho da Palavra \\ Numero da Palavra\n");

    Conversa* current=link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;

    for(i=0; i<link_corpus->n_conversas; i++)
    {

        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {

            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }

            if(current_msg==NULL)
            {
                break;
            }

            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;
                }


                soma=soma+strlen(current_pala->text);
                printf("%d--%d---%s\n",strlen(current_pala->text),numero_palavras,current_pala->text);
                numero_palavras++;



                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }

    soma=(float)(soma/numero_palavras);
    printf("\n\n-->Media do comprimento das palavras===>%f<--\n\n",soma);

    return soma;
}

void maior_tamanho(Corpus* link_corpus,int limite)
{
    int i,ias,asd;

    int tamanho_palavra=0;

    int tamanho_array_menores=0;
    char**array_com_palavras_menores;
    array_com_palavras_menores=calloc(10,sizeof(char*));


    int tamanho_array_maiores=0;
    char**array_com_palavras_maiores;
    array_com_palavras_maiores=calloc(10,sizeof(char*));

    Conversa* current=link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;

    int j=0;

    for(i=0; i<link_corpus->n_conversas; i++)
    {


        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {


            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }

            if(current_msg==NULL)
            {
                break;
            }

            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {

                if(current_pala==NULL)
                {
                    break;
                }
                tamanho_palavra=strlen(current_pala->text);
                if(tamanho_palavra<=limite)
                {
                    array_com_palavras_menores[tamanho_array_menores]=current_pala->text;
                    tamanho_array_menores++;
                    if(tamanho_array_menores%10==0&&tamanho_array_menores!=0)
                    {
                        array_com_palavras_menores=realloc(array_com_palavras_menores,(tamanho_array_menores+10)*sizeof(char*));
                        for(j=tamanho_array_menores; j<tamanho_array_menores+10; j++)
                        {
                            array_com_palavras_menores[j]=NULL;
                        }
                    }
                }
                if(tamanho_palavra>=limite)
                {
                    array_com_palavras_maiores[tamanho_array_maiores]=current_pala->text;
                    tamanho_array_maiores++;
                    if(tamanho_array_maiores%10==0&&tamanho_array_maiores!=0)
                    {
                        array_com_palavras_maiores=realloc(array_com_palavras_maiores,(tamanho_array_maiores+10)*sizeof(char*));
                        for(j=tamanho_array_maiores; j<tamanho_array_maiores+10; j++)
                        {
                            array_com_palavras_maiores[j]=NULL;
                        }
                    }
                }


                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }

    printf("\n\nNumero de palavras menores %d\n\n",tamanho_array_menores);

    for(i=0; i<tamanho_array_menores; i++)
    {
        printf("--%s--\n",array_com_palavras_menores[i]);
    }


    printf("\n\nNumero de palavras maiores %d\n\n",tamanho_array_maiores);
    for(i=0; i<tamanho_array_maiores; i++)
    {
        printf("--%s--\n",array_com_palavras_maiores[i]);
    }


}

void procurar_raizes(Corpus* link_corpus, char* palavra)
{
    int i,asd,ias,count=0;

    char *aux=NULL;
    int int_ocorrencias=0;
    char **array_palavras_com_ocorrencia=NULL;
    array_palavras_com_ocorrencia=calloc(1,sizeof(char*));

    int* int_palavras_posicao=calloc(1,sizeof(int*));

    Conversa* current=link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;

    for(i=0; i<link_corpus->n_conversas; i++)
    {


        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {


            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }


            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;
                }
                count++;
                aux=strstr(current_pala->text,palavra);

                if(aux!=NULL)
                {

                    array_palavras_com_ocorrencia[int_ocorrencias]=current_pala->text;
                    int_palavras_posicao[int_ocorrencias]=count;
                    int_ocorrencias++;


                    array_palavras_com_ocorrencia=realloc(array_palavras_com_ocorrencia,(int_ocorrencias+1)*sizeof(char*));
                    int_palavras_posicao=realloc(int_palavras_posicao,(int_ocorrencias+1)*sizeof(int));
                    int j=0;
                    for(j=int_ocorrencias; j<int_ocorrencias+1; j++)
                    {
                        array_palavras_com_ocorrencia[j]=NULL;
                        int_palavras_posicao[j]=0;
                    }


                }

                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }
    printf("\n\n\n");
    printf("Palavra\\Localizacao no texto\n");
    for(i=0; i<int_ocorrencias; i++)
    {
        printf("|--%s--%d--|",array_palavras_com_ocorrencia[i],int_palavras_posicao[i]);
        printf("\n");

    }


}

void digramas_trigramas(Corpus * link_corpus)
{
    int i,ias,asd;

    int c=0;
    int tamanho_palavra=0;

    int flag=0;
    int tamanho_total=0;
    int tamanho_digramas=0;
    char**array_digramas=(char**)calloc(500,sizeof(char*));
    array_digramas[0]=(char*)calloc(3,sizeof(char));
    int *int_digramas=(int*)calloc(500,sizeof(int));
    char auxdigramas[3];

    int flag2=0;
    int tamanho_total2=0;
    int tamanho_digramas2=0;
    char**array_digramas2=(char**)calloc(500,sizeof(char*));
    array_digramas2[0]=(char*)calloc(4,sizeof(char));
    int *int_digramas2=(int*)calloc(500,sizeof(int));
    char auxdigramas2[4];

    Conversa* current=link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;



    for(i=0; i<link_corpus->n_conversas; i++)
    {

        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {


            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }

            if(current_msg==NULL)
            {
                break;
            }

            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;
                }
                tamanho_palavra=strlen(current_pala->text);

                for(b=0; b<tamanho_palavra-1; b++)
                {
                    flag=0;
                    if(tamanho_total==0)
                    {
                        auxdigramas[0]=current_pala->text[0];
                        auxdigramas[1]=current_pala->text[1];
                        auxdigramas[2]='\0';
                    }

                    for(c=0; c<tamanho_digramas; c++)
                    {
                        auxdigramas[0]=current_pala->text[b];
                        auxdigramas[1]=current_pala->text[b+1];
                        auxdigramas[2]='\0';



                        if(strcmp(auxdigramas,array_digramas[c])==0)  //strcmp(auxdigramas,array_digramas[c])==0
                        {

                            flag=1;
                            int_digramas[c]++;
                            tamanho_total++;
                            break;
                        }
                    }
                    if(flag==0)
                    {
                        array_digramas[tamanho_digramas]=(char*)calloc(3,sizeof(char));
                        array_digramas[tamanho_digramas][0]=auxdigramas[0];
                        array_digramas[tamanho_digramas][1]=auxdigramas[1];
                        array_digramas[tamanho_digramas][2]=auxdigramas[2];
                        int_digramas[c]++;
                        tamanho_total++;
                        tamanho_digramas++;
                        if(tamanho_digramas%10==0&&tamanho_digramas!=0)
                        {
                            array_digramas = realloc(array_digramas,((tamanho_digramas+10)*sizeof(char*)));
                            int_digramas = realloc(int_digramas,((tamanho_digramas+10)*sizeof(int)));
                            int o=0;
                            for(o=tamanho_digramas; o<tamanho_digramas+10; o++)
                            {
                                array_digramas[o]=NULL;
                                int_digramas[o]=0;

                            }
                        }
                    }

                }
                //---------------------------------

                for(b=0; b<tamanho_palavra-2; b++)
                {
                    flag2=0;
                    if(tamanho_total2==0)
                    {
                        auxdigramas2[0]=current_pala->text[0];
                        auxdigramas2[1]=current_pala->text[1];
                        auxdigramas2[2]=current_pala->text[2];
                        auxdigramas2[3]='\0';
                    }

                    for(c=0; c<tamanho_digramas2; c++)
                    {

                        auxdigramas2[0]=current_pala->text[b];
                        auxdigramas2[1]=current_pala->text[b+1];
                        auxdigramas2[2]=current_pala->text[b+2];
                        auxdigramas2[3]='\0';
                        //  printf("%s\n",&auxdigramas);


                        if(strcmp(auxdigramas2,array_digramas2[c])==0)  //strcmp(auxdigramas,array_digramas[c])==0
                        {

                            flag2=1;
                            int_digramas2[c]++;
                            tamanho_total2++;
                            break;
                        }
                    }
                    if(flag2==0)
                    {
                        array_digramas2[tamanho_digramas2]=(char*)calloc(4,sizeof(char));
                        array_digramas2[tamanho_digramas2][0]=auxdigramas2[0];
                        array_digramas2[tamanho_digramas2][1]=auxdigramas2[1];
                        array_digramas2[tamanho_digramas2][2]=auxdigramas2[2];
                        array_digramas2[tamanho_digramas2][3]=auxdigramas2[3];
                        int_digramas2[c]++;
                        tamanho_total2++;
                        tamanho_digramas2++;
                        if(tamanho_digramas2%10==0&&tamanho_digramas2!=0)
                        {
                            array_digramas2 = realloc(array_digramas2,((tamanho_digramas2+10)*sizeof(char*)));
                            int_digramas2 = realloc(int_digramas2,((tamanho_digramas2+10)*sizeof(int)));
                            int o=0;
                            for(o=tamanho_digramas2; o<tamanho_digramas2+10; o++)
                            {
                                array_digramas2[o]=NULL;
                                int_digramas2[o]=0;

                            }
                        }
                    }

                }


                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;
        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }

    printf("\n\nDIGRAMAS-FREQUENCIAS(%d)\n\n",tamanho_total);
    for(i=0; i<tamanho_digramas; i++)
    {
        printf("%s-%d--%f%%\n",array_digramas[i],int_digramas[i],((float)int_digramas[i]/tamanho_total) * 100);
    }

    printf("\n\nTRIGRAMAS-FREQUENCIAS(%d)\n\n",tamanho_total2);

    for(i=0; i<tamanho_digramas2; i++)
    {
        printf("%s-%d--%f%%\n",array_digramas2[i],int_digramas2[i],((float)int_digramas2[i]/tamanho_total2) * 100);
    }



}

int levenshtein(const char *s, int ls, const char *t, int lt)
{
    int a, b, c;

    if (!ls) return lt;
    if (!lt) return ls;

    if (s[ls] == t[ls])
        return levenshtein(s, ls - 1, t, lt - 1);

    a = levenshtein(s, ls - 1, t, lt - 1);
    b = levenshtein(s, ls,     t, lt - 1);
    c = levenshtein(s, ls - 1, t, lt    );

    if (a > b) a = b;
    if (a > c) a = c;

    return a + 1;

}



void MergeSort(Mensagem** headRef)
{
    Mensagem* head = *headRef;
    Mensagem* a;
    Mensagem* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}
Mensagem* SortedMerge(Mensagem* a, Mensagem* b)
{
    Mensagem* result = NULL;

    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    /* Pick either a or b, and recur */
    if (atoi(a->time_stamp) <= atoi(b->time_stamp))
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}
void FrontBackSplit(Mensagem* source,Mensagem** frontRef, Mensagem** backRef)
{
    Mensagem* fast;
    Mensagem* slow;
    if (source==NULL || source->next==NULL)
    {
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;

        /* Advance 'fast' two nodes, and advance 'slow' one node */
        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        /* 'slow' is before the midpoint in the list, so split it in two
          at that point. */
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}


void MergeSort2(Mensagem** headRef)
{
    Mensagem* head = *headRef;
    Mensagem* a;
    Mensagem* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit2(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort2(&a);
    MergeSort2(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge2(a, b);
}
Mensagem* SortedMerge2(Mensagem* a, Mensagem* b)
{
    Mensagem* result = NULL;

    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    /* Pick either a or b, and recur */
    if (a->importancia <= a->importancia)
    {
        result = a;
        result->next = SortedMerge2(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge2(a, b->next);
    }
    return(result);
}
void FrontBackSplit2(Mensagem* source,Mensagem** frontRef, Mensagem** backRef)
{
    Mensagem* fast;
    Mensagem* slow;
    if (source==NULL || source->next==NULL)
    {
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;

        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}


void MergeSort3(Mensagem** headRef)
{
    Mensagem* head = *headRef;
    Mensagem* a;
    Mensagem* b;

    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    FrontBackSplit3(head, &a, &b);

    MergeSort3(&a);
    MergeSort3(&b);

    *headRef = SortedMerge3(a, b);
}
Mensagem* SortedMerge3(Mensagem* a, Mensagem* b)
{
    Mensagem* result = NULL;

    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    if (a->tamanho_mensagem <= b->tamanho_mensagem)
    {
        result = a;
        result->next = SortedMerge3(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge3(a, b->next);
    }
    return(result);
}
void FrontBackSplit3(Mensagem* source,Mensagem** frontRef, Mensagem** backRef)
{
    Mensagem* fast;
    Mensagem* slow;
    if (source==NULL || source->next==NULL)
    {
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;

        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}



char**  add_conversa_struct(char* texto,Corpus *corpus,int* total_palavras,int *bag_total, char **bag_of_words_geral)
{
    int i=0,b=0,palavras_conv=0,palavras_todas_soma=*total_palavras;

    char ** bag_of_words_conversa=malloc(sizeof(char*)*10);
    int bag_of_words_conversa_num=0;


    Conversa* link_conversa=newconversa();
    novaConversa(corpus,link_conversa,texto);
    link_conversa->n_utilizadores=0;

    int n_frases=0;
    char **array_mensagens=texto_a_mensagem(texto,&n_frases);
    link_conversa->n_frases_total=n_frases;

    for(i=0; i<n_frases; i++)
    {

        int mensagem_current=NULL;
        Mensagem* link_mensagem=newmensagem();
        mensagem_current=  check_timestamp(*(array_mensagens+i),link_mensagem,link_conversa);
        int asdd=0;
        for(asdd=0; asdd<mensagem_current; asdd++)
        {
            *(*(array_mensagens+i)+asdd)=' ';
        }

        link_mensagem->tamanho_mensagem=0;
        novaMensagem(link_conversa,link_mensagem,*(array_mensagens+i));
        link_mensagem->tamanho_mensagem=strlen(*(array_mensagens+i));
        link_mensagem->importancia=50;

        int n_palavras=0;
        char **array_de_palavras=mensagem_a_palavra(*(array_mensagens+i),&n_palavras);

        link_mensagem->npalavras=n_palavras;

        for(b=0; b<n_palavras; b++)
        {
            Palavra* link_palavra= novaPalavra(link_mensagem,*(array_de_palavras+b));
            link_palavra->posicao_mensagem=b+1;
            link_palavra->posicao_conversa=palavras_conv+1;
            link_palavra->posicao_corpus=palavras_todas_soma+1;

            int c,flag=1;
            for(c=0; c<bag_of_words_conversa_num; c++)
            {
                if(strcmp(*(array_de_palavras+b),bag_of_words_conversa[c])==0)
                {
                    flag=0;
                    break;
                }
            }

            if(flag==1)
            {

                bag_of_words_conversa[bag_of_words_conversa_num]=(char*)malloc(sizeof(char)*(strlen(*(array_de_palavras+b))+1));

                strcpy(bag_of_words_conversa[bag_of_words_conversa_num],*(array_de_palavras+b));
                bag_of_words_conversa[bag_of_words_conversa_num][strlen(*(array_de_palavras+b))] = '\0';

                bag_of_words_conversa_num++;

                if(bag_of_words_conversa_num%10==0 && bag_of_words_conversa_num!=0)
                {

                    bag_of_words_conversa = realloc(bag_of_words_conversa,((bag_of_words_conversa_num+10)*sizeof(char*)));

                    int o=0;
                    for(o=bag_of_words_conversa_num; o<bag_of_words_conversa_num+10; o++)
                    {
                        bag_of_words_conversa[o]=NULL;
                    }


                }

            }

            //---------------------------Bag-of-words-GERAL---------------------

            flag=1;

            for(c=0; c<*bag_total; c++)
            {

                if(strcmp(*(array_de_palavras+b),bag_of_words_geral[c])==0)
                {
                    flag=0;
                    break;
                }
            }




            if(flag==1)
            {

                bag_of_words_geral[*bag_total]=(char*)malloc(sizeof(char)*(strlen(*(array_de_palavras+b))+1));

                strcpy(bag_of_words_geral[*bag_total],*(array_de_palavras+b));
                bag_of_words_geral[*bag_total][strlen(*(array_de_palavras+b))] = '\0';

                *bag_total=*bag_total+1;

                if(*bag_total%10==0 && *bag_total!=0)
                {

                    bag_of_words_geral = realloc(bag_of_words_geral,((*bag_total+10)*sizeof(char*)));

                    int o=0;
                    for(o=*bag_total; o<*bag_total+10; o++)
                    {
                        bag_of_words_geral[o]=NULL;
                    }


                }

            }


            palavras_conv++;
            palavras_todas_soma++;

        }

    }

    link_conversa->bag_of_words_conversa=bag_of_words_conversa;
    link_conversa->bag_of_words_num=bag_of_words_conversa_num;
    *total_palavras=palavras_todas_soma;

    return bag_of_words_geral;
}

char **mensagem_a_palavra(char * frase,int *n_palavras)
{

    char **array_palavras=(char**)malloc(sizeof(char *)*10);

    char * palavra= NULL;
    int numero_palavras = 0;

    palavra = strtok (frase," ,.!?\n");

    while(palavra!=NULL)
    {

        if(strcmp(palavra,"\n")==0||strcmp(palavra," ")==0)
        {
            break;
        }

        int l;
        for(l=0; l< strlen(palavra); l++)
        {
            palavra[l]=tolower(palavra[l]);
        }

        array_palavras[numero_palavras]=(char*)malloc(1*(strlen(palavra)+2));
        strcpy(array_palavras[numero_palavras],palavra);
        array_palavras[numero_palavras][strlen(palavra)]='\0';


        numero_palavras++;

        if(numero_palavras%10==0 && numero_palavras!=0)
        {

            array_palavras = realloc(array_palavras,((numero_palavras+10)*sizeof(char*)));
            int o=0;
            for(o=numero_palavras; o<numero_palavras+10; o++)
            {

                array_palavras[o]=NULL;

            }

        }

        palavra = strtok(NULL, " ,.!?\n");
    }

    *n_palavras=numero_palavras;
    return array_palavras;

}

char ** texto_a_mensagem(char * frases,int *n_frases)
{
    const char delimiter[4]="\n";
    char * token= NULL;
    int nfrases = 0,size_frase=0;
    char **frases_parsed = (char**)malloc(100*sizeof(char*)); //realloc
    token=strtok(frases,delimiter);
    while(token!=NULL)
    {

        if(strcmp(token,"\n")==0)
        {
            break;
        }
        size_frase=strlen(token);
        nfrases++;


        frases_parsed[nfrases-1]=(char*)malloc(sizeof(char)*(size_frase+2));
        strcpy(frases_parsed[nfrases-1],token);
        frases_parsed[nfrases-1][size_frase+1] = '\0';


        token = strtok(NULL, "\n");
    }

    *n_frases=nfrases;
    return frases_parsed;

}

float Tf_Idf(char* palavra,int id_conversa,Corpus * link_corpus)
{
    int ias,asd,b=0,bb=0,numero_termos_conversa=0;
    float TF=0.0,terms_count=0.0,IDF=0.0,TF_IDF=0.0;

    id_conversa--;

    Conversa*current=link_corpus->first;
    int count=0;

    if(id_conversa == 0)
    {
        current=link_corpus->first;
    }
    current = link_corpus->first;
    while(count < id_conversa)
    {
        if(current->next == NULL)
        {
            return 0.0;
        }
        current = current->next;
        count++;
    }

    Mensagem* current_msg=current->first;
    Palavra*   current_pala=current->first->first;

    b=current->n_frases_total;

    for(ias=0; ias<b; ias++)
    {
        if(current_msg!=NULL)
        {
            current_pala=current_msg->first;
        }
        bb=current_msg->npalavras;
        for(asd=0; asd<bb; asd++)
        {
            if(current_pala==NULL)
            {
                break;
            }
            if(strcmp(palavra,current_pala->text)==0)
            {
                terms_count++;
            }

            numero_termos_conversa++;
            current_pala=current_pala->next;
        }
        current_msg=current_msg->next;
    }



    TF=(float)(terms_count/numero_termos_conversa);


    int palavra_nos_ficheiros=0,i;

    Conversa*current_conversa=link_corpus->first;
    current_msg=link_corpus->first->first;
    current_pala=link_corpus->first->first->first;


    for(i=0; i<link_corpus->n_conversas; i++)
    {

        int  flag=0;

        b=current_conversa->n_frases_total;
        for(ias=0; ias<b; ias++)
        {


            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }


            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;

                }
                if(strcmp(palavra,current_pala->text)==0&&flag==0)
                {
                    palavra_nos_ficheiros++;
                    flag++;
                }
                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current_conversa=current_conversa->next;
        if (current_conversa!=NULL)
        {
            current_msg=current_conversa->first;
        }

    }

    IDF=log((float)(link_corpus->n_conversas/palavra_nos_ficheiros));
    TF_IDF=TF*IDF;
    printf("\n\n\t\t O TF_IDF da Palavra %s e %f",palavra,TF_IDF);

    return TF_IDF;

}

void novaConversa(Corpus * corpus, Conversa* conversa, char* texto)
{

    if(corpus->first == NULL)
    {
        corpus->first =conversa;
        corpus->first->toda_conversa=texto;

    }
    else
    {
        Conversa* current = corpus->first;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = conversa;
        current->next->toda_conversa= texto;

    }

}

Corpus * newcorpus()
{
    Corpus * c = (Corpus*)malloc(sizeof(Corpus));
    c->first = NULL;
    return c;
}
Conversa * newconversa()
{
    Conversa * link = (Conversa*)malloc(sizeof(Conversa));

    link->first = NULL;
    link->next= NULL;
    link->toda_conversa= NULL;
    return link;
}

void novaMensagem(Conversa * conversa,Mensagem* mensagem,char* mensagem_total)
{
    if(conversa->first == NULL)
    {
        conversa->first = mensagem;
        conversa->first->toda_mensagem= mensagem_total;
    }
    else
    {
        Mensagem* current = conversa->first;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = mensagem;
        current->next->toda_mensagem= mensagem_total;
    }
}

Mensagem * getMensagem(Conversa * c,int index)
{
    if(index == 0)
    {
        return c->first;
    }
    int count = index;
    Mensagem* current = c->first;
    while(count != 0)
    {
        if(current->next == NULL)
        {
            return NULL;
        }
        current = current->next;
        count--;
    }
    return current;
}

Mensagem * newmensagem()
{
    Mensagem * mensagem = (Mensagem*)malloc(sizeof(Mensagem));
    mensagem->first = NULL;
    mensagem->next = NULL;
    return mensagem;
}

Palavra * getPalavra(Mensagem* m,int index)
{
    if(index == 0)
    {
        return m->first;
    }
    int count = index;
    Palavra* current = m->first;
    while(count != 0)
    {
        if(current->next == NULL)
        {
            return NULL;
        }
        current = current->next;
        count--;
    }
    return current;
}

Palavra* novaPalavra(Mensagem * mensagem,char* texto)
{
    if(mensagem->first == NULL)
    {
        mensagem->first = newpalavra(texto);
        return  mensagem->first;
    }
    else
    {
        Palavra* current = mensagem->first;
        while(current->next != NULL)
        {
            current = current->next;
        }
        Palavra* p = newpalavra(texto);
        acrescentaPalavra(current,p);
        return p;
    }

}

int removePalavra(Corpus* link_estruturas,Mensagem * mensagem,int index)
{
    index--;
    Palavra* aux= mensagem->first->next;
    if(index==0)
    {
    apagaPalavra(mensagem->first);
    mensagem->first=aux;
    atualizar_index(link_estruturas);
    return 0;
    }
    if(mensagem->first == NULL)
    {
        return 1;
    }
    int count = index;
    Palavra* prev = NULL;
    Palavra* current = mensagem->first;
    while(count != 0)
    {
        if(current->next == NULL)
        {
            return 1;
        }
        prev = current;
        current = current->next;
        count--;
    }
    prev->next=current->next;
    apagaPalavra(current);
    mensagem->npalavras=mensagem->npalavras-1;

    return 0;
}

Palavra * newpalavra(char* texto)
{
    Palavra * palavra = (Palavra*)malloc(sizeof(Palavra));
    palavra->text = texto;
    palavra->next = NULL;
    return palavra;
}

void acrescentaPalavra(Palavra* antiga, Palavra* next)
{
    antiga->next = next;
}

void apagaPalavra(Palavra * palavra)
{
    free(palavra);
}

void atualizar_index(Corpus* link_corpus)
{
    int asd,ias,i;

    int t_conversa=0,t_corpus=0,t_mensagem=0;

    Conversa* current=link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;


    for(i=0; i<link_corpus->n_conversas; i++)
    {
        t_conversa=0;
        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {

            t_mensagem=0;
            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }


            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
    if(current_pala==NULL)
    {
        break;
    }

                t_corpus++;
                t_conversa++;
                t_mensagem++;
                current_pala->posicao_conversa=t_conversa;
                current_pala->posicao_corpus=t_corpus;
                current_pala->posicao_mensagem=t_mensagem;

                current_pala=current_pala->next;
            }


            current_msg=current_msg->next;

        }
        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }
return;
}

void printf_words(Corpus* link_estruturas,int index)
{
    Conversa* current=link_estruturas->first;
    int i=0,count=0;
    index--;
    int    flag=0;

    if(index==-2)
    {
        flag++;
        for(i=0; i<link_estruturas->bag_of_words_num; i++)
        {
            printf("%s\n",link_estruturas->bag_of_words_geral[i]);
        }

    }
    else
    {

        if(index == 0)
        {
            flag++;
            current=link_estruturas->first;
        }
        current = link_estruturas->first;
        while(count < index)
        {
            flag++;
            if(current->next == NULL)
            {
                printf("\n\n\t\t----NAO EXISTE ESSA MENSAGEM-----");
                return ;
            }
            current = current->next;
            count++;
        }

        for(i=0; i<current->bag_of_words_num; i++)
        {
            printf("%s\n",current->bag_of_words_conversa[i]);
        }
    }


}

void printf_words_all(Corpus* link_corpus)
{
    Conversa* current= link_corpus->first;
    Mensagem* current_msg=link_corpus->first->first;
    Palavra* current_pala=link_corpus->first->first->first;

    int i=0,asd,ias;

    printf("\n\n\t\tPALAVRA---->ID_CORPU|||ID_CONVERSA|||ID_MENSAGEM\n\n");

    for(i=0; i<3; i++)
    {

        if(current==NULL)
        {
            break;
        }


        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {


            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }
            if(current_msg==NULL)
            {
                break;
            }


            int bb=current_msg->npalavras;
            for(asd=0; asd<bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;
                }
                printf("%s->",current_pala->text);
                printf("%d-",current_pala->posicao_corpus);
                printf("%d-",current_pala->posicao_conversa);
                printf("%d\n",current_pala->posicao_mensagem);

                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }

   return;
}

void funcao_palavras_parecidas(char * palavra_aux,Corpus* link_corpus, int id_conversa, int id_mensagem, int id_palavra)
{
    int i,b,tamanho2=0;
    int tamanho1=strlen(palavra_aux);
    char** palavras_parecidas =malloc(sizeof(char*)*3);
    int * palavras_inteiras=malloc(sizeof(int)*3);

    int distancia=0;

    for(i=0; i<3; i++)
    {
        palavras_parecidas[i]=NULL;
        palavras_inteiras[i]=100;
    }
    for(i=0; i<link_corpus->bag_of_words_num; i++)
    {
        tamanho2=strlen(link_corpus->bag_of_words_geral[i]);
        distancia= levenshtein(palavra_aux, tamanho1, link_corpus->bag_of_words_geral[i], tamanho2);

        for(b=0; b<3; b++)
        {
            if(distancia<palavras_inteiras[b])
            {
                palavras_inteiras[b]=distancia;
                palavras_parecidas[b]=malloc(1*(tamanho2+1));
                strcpy(palavras_parecidas[b],link_corpus->bag_of_words_geral[i]);
                palavras_parecidas[b][tamanho2+1]='\0';
                break;
            }
        }

    }
    int numero=0;
    printf("\n\nPrentende Usar Alguma Das Palavras Seguintes?(Escolha o numero)\n");
    for(i=0; i<3; i++)
    {
        printf("\t%d----%s",i,palavras_parecidas[i]);
    }
    printf("\t3----%s\n",palavra_aux);
    printf("=>");
    scanf("%d",&numero);

    if(numero==0)
    {
        strcpy(palavra_aux,palavras_parecidas[0]);
    }
    if(numero==1)
    {
        strcpy(palavra_aux,palavras_parecidas[1]);
    }
    if(numero==2)
    {
        strcpy(palavra_aux,palavras_parecidas[2]);
    }

    procurar_local(link_corpus,palavra_aux,id_conversa,id_mensagem,id_palavra);
    //atualizar_index(link_corpus);

//free(palavras_inteiras);
return;

}

void procurar_local(Corpus* link_estruturas,char * aux_palavra,int id_conversa, int id_mensagem, int id_palavra)
{
    Conversa* current=link_estruturas->first;
    Mensagem* current_msg=link_estruturas->first->first;
    Palavra* current_pala=link_estruturas->first->first->first;
    Palavra* link_palavra= NULL;

    int i,ias,asd;

    for(i=0; i<id_conversa; i++)
    {

        for(ias=0; ias<id_mensagem; ias++)
    {

            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }

            for(asd=0; asd<=id_palavra; asd++)
            {
                if(i==id_conversa-1&&ias==id_mensagem-1&&asd==id_palavra-1)
                {
                    link_palavra= newpalavra(aux_palavra);

                    link_palavra->next=current_pala->next;
                    current_pala->next=link_palavra;
                    current_msg->npalavras=current_msg->npalavras+1;

                  //  inserir_bag_of_words(current,aux_palavra); crasha
                    atualizar_index(link_estruturas);
                    return;

                }
                if(i==id_conversa-1&&ias==id_mensagem-1&&asd==id_palavra)
                {
                    link_palavra= newpalavra(aux_palavra);
                    link_palavra->next=current_msg->first;
                    current_msg->first=link_palavra;
                    current_msg->npalavras=current_msg->npalavras+1;

               //     inserir_bag_of_words(current,aux_palavra);
                    atualizar_index(link_estruturas);
                    return;

                }

                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;


        }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }

}

void sava_structs(Corpus *link_estruturas,int flag)
{
    Conversa* current=link_estruturas->first;
    Mensagem* current_msg=link_estruturas->first->first;
    Palavra* current_pala=link_estruturas->first->first->first;
    int i,ias,asd;
    char espacos[]="\n\n----\n\n";
    char separar[]=">";


FILE *f = fopen("data\\Todas_as_conversas.txt", "w");
if(flag==2)
{
    fclose(f);
    FILE *f = fopen("data\\Todas_as_conversas_bin.bin", "wb");

     for(i=0; i<link_estruturas->n_conversas; i++)
    {

         fwrite(espacos,1,sizeof(espacos),f);

        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {


            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }

            fwrite(current_msg->pessoa_correspondente,1,sizeof(current_msg->pessoa_correspondente),f);
            fwrite(separar,1,sizeof(separar),f);
            fwrite(current_msg->time_stamp,1,sizeof(current_msg->time_stamp),f);
            fwrite(separar,1,sizeof(separar),f);

             int bb=current_msg->npalavras;
            for(asd=0; asd< bb; asd++)
            {
                if(current_pala==NULL)
                {
                    break;
                }
                fwrite(current_pala->text, 1, sizeof(current_pala->text), f);
                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;
       }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }
    return;
}

if (f == NULL)
{
    printf("Error opening file!\n");
    return ;
}

    for(i=0; i<link_estruturas->n_conversas; i++)
    {

         fprintf(f,"\n\n----\n\n");

        int b=current->n_frases_total;
        for(ias=0; ias<b; ias++)
        {


            if(current_msg!=NULL)
            {
                current_pala=current_msg->first;
            }
            fprintf(f,"\n%s>%s>",current_msg->pessoa_correspondente,current_msg->time_stamp);

             int bb=current_msg->npalavras;
            for(asd=0; asd< bb; asd++)
            {if(current_pala==NULL)
            {
                break;
            }

                fprintf(f,"%s ",current_pala->text);
                current_pala=current_pala->next;
            }

            current_msg=current_msg->next;
       }

        current=current->next;
        if (current!=NULL)
        {
            current_msg=current->first;
        }

    }

fclose(f);
system("cls");
printf("\n\n\tFICHEIRO GUARDADO\n\n");

return;
}

void inserir_bag_of_words(Conversa* link_conversa,char *palavra)
{
    int i,flag=0,tamanho=0;

    for(i=0;i<link_conversa->bag_of_words_num;i++)
    {
        if(strcmp(palavra,link_conversa->bag_of_words_conversa[i])==0)
        {
            flag=1;
        }
    }
    if(flag==0)
    {
        link_conversa->bag_of_words_conversa=realloc(link_conversa->bag_of_words_conversa,link_conversa->bag_of_words_num+1);
        tamanho=strlen(palavra);
        link_conversa->bag_of_words_conversa[link_conversa->bag_of_words_num+1]=malloc(1*(tamanho+1));
        strcpy(link_conversa->bag_of_words_conversa[link_conversa->bag_of_words_num+1],palavra);
        link_conversa->bag_of_words_conversa[link_conversa->bag_of_words_num+1][tamanho]='\0';
    }

}
