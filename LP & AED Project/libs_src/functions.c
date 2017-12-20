#include "lib_stats.h"
#include "lib_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//#include "stringsearch_kmp.c"
//#include "stringsearch_kmp.h"

//Bugs->>falta dar free na memoria :< -- Crasha raramente no digramas_trigramas -- Crasha ao encerrar o programa(diagramas_trigramas);

char* read_message(char *filename)
{
    int i=0;
    char *file_contents;
    long input_file_size;
    FILE *input_file = fopen(filename, "r");
    if(input_file == NULL)                           //Caso n tenho aberto com sucesso o ficheiro7
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
    // fecha o ficheiro
    return file_contents;       //retorna uma string com todo o conteudo do ficheiro
}

char **create_array_strings(char *frases,int *n_frases)
{
    const char delimiter[4]=".!?";
    char * token= NULL;
    int nfrases = 0,size_frase=0;
    char **frases_parsed = (char**)malloc(10*sizeof(char*)); //realloc
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


        token = strtok(NULL, ".!?");
    }

    int pi=0;
    printf("\n");
    for(pi = 0; pi < nfrases; pi++)
        printf("%s\n",frases_parsed[pi]);

    *n_frases=nfrases;
    return frases_parsed;
}

char **separar_palavras(char **array, int n_frases, int *numero_de_palavras,int *** array_posicao, char*** array_repetidas, int *todas_as_palavras_int)
{

    printf("%d----------\n",n_frases);
    char *palavra=NULL;
    int numero_de_palavra = 0,numero_da_palavra_frases=0,numero_da_palavra_frases_total=0,npalavrasmax=10,i,c;
    char **todasPalavras=(char**)malloc(sizeof(char *)*10);

    char** palavras_com_repeticao=(char**)malloc(sizeof(char*)*10);
    int ** palavra_com_posi=(int**)malloc(sizeof(int *)*10);

    for(i=0; i<n_frases; i++)
    {
        palavra = strtok (array[i]," ,.!?\n");


        numero_da_palavra_frases=0;

        while(palavra!=NULL)
        {
            int flag=1;

            int l=0;
            for(l=0; l< palavra[i]; l++)
            {
                palavra[l]=tolower(palavra[l]);
            }
            printf("\n%s",palavra);

            //palavra=caracteres_especiais(palavra,strlen(palavra));

            palavras_com_repeticao[numero_da_palavra_frases_total]=(char*)malloc(1*(strlen(palavra)+2));
            strcpy(palavras_com_repeticao[numero_da_palavra_frases_total],palavra);
            palavras_com_repeticao[numero_da_palavra_frases_total][strlen(palavra)]='\0';

            //   printf("%s\n",palavras_com_repeticao[numero_da_palavra_frases_total]);


            palavra_com_posi[numero_da_palavra_frases_total] = malloc(4 * sizeof(int));
            palavra_com_posi[numero_da_palavra_frases_total][0]=i+1;
            palavra_com_posi[numero_da_palavra_frases_total][1]=numero_da_palavra_frases+1;
            palavra_com_posi[numero_da_palavra_frases_total][2]=numero_da_palavra_frases_total+1;
            palavra_com_posi[numero_da_palavra_frases_total][3]=0;


            numero_da_palavra_frases++;
            numero_da_palavra_frases_total++;


            if(numero_da_palavra_frases_total%10==0 && numero_da_palavra_frases_total!=0)
            {

                palavra_com_posi = realloc(palavra_com_posi,((numero_da_palavra_frases_total+10)*sizeof(int*)));
                palavras_com_repeticao = realloc(palavras_com_repeticao,((numero_da_palavra_frases_total+10)*sizeof(char*)));
                int o=0;
                for(o=numero_da_palavra_frases_total; o<numero_da_palavra_frases_total+10; o++)
                {
                    palavra_com_posi[o]=NULL;
                    palavras_com_repeticao[o]=NULL;

                }

                // *(todasPalavras+numero_de_palavra)=(char**)malloc(sizeof(char *)*10);//-----A dar mal-----
            }



            for(c=0; c<numero_de_palavra; c++)
            {
                if(strcmp(palavra,todasPalavras[c])==0)
                {
                    flag=0;
                    break;
                }
            }
            if(flag==1)
            {
                todasPalavras[numero_de_palavra]=(char*)malloc(sizeof(char)*(strlen(palavra)+1));

                strcpy(todasPalavras[numero_de_palavra],palavra);
                todasPalavras[numero_de_palavra][strlen(palavra)] = '\0';


                //printf("%d\n",strlen(palavra));
                numero_de_palavra++;
                if(numero_de_palavra==npalavrasmax)
                {
                    npalavrasmax += 10;
                    todasPalavras = realloc(todasPalavras,(npalavrasmax*sizeof(char*)));
                    int h=0;
                    for(h=numero_de_palavra; h<npalavrasmax; h++)
                    {
                        todasPalavras[h]=NULL;

                    }
                    // *(todasPalavras+numero_de_palavra)=(char**)malloc(sizeof(char *)*10);//-----A dar mal-----
                }
            }

            palavra = strtok(NULL, " ,.!?\n");
        }

    }

    *numero_de_palavras=numero_de_palavra;

    //    search_word(palavra_com_posi,numero_da_palavra_frases_total,palavras_com_repeticao);
    //frase_entre_palavras(palavra_com_posi,numero_da_palavra_frases_total,palavras_com_repeticao); //-bug
    //  frase_entre_palavras_escolhidas(palavra_com_posi,numero_da_palavra_frases_total,palavras_com_repeticao); //-bug
    //search_letras(palavras_com_repeticao, numero_da_palavra_frases_total);
    //primeira_ultima_letra(palavras_com_repeticao,numero_da_palavra_frases_total);
    //palavra_media(palavras_com_repeticao,numero_da_palavra_frases_total);
    //maior_tamanho(palavras_com_repeticao,numero_da_palavra_frases_total);
    //    procurar_raizes(palavras_com_repeticao,numero_da_palavra_frases_total);



    * array_posicao=palavra_com_posi;
    *array_repetidas=palavras_com_repeticao;
    *todas_as_palavras_int=numero_da_palavra_frases_total;

    return todasPalavras;

}




void search_word(int **array_palavras_posi,int numero_palavras,char**array_com_palavras,char *auxpalavra)
{

    int i,flag=0,vezes_repetidas=0;
    int tamanho_pala=strlen(auxpalavra);

    for(i=0;i<tamanho_pala;i++)
    {
        auxpalavra[i]=tolower(auxpalavra[i]);
    }

    if(tamanho_pala>20)
    {
        printf("\nERRO-Palavra tem que ter menos que 20 caracteres\n");
        return ;
    }

    for(i=0; i<numero_palavras; i++)
    {
        if(strcmp(array_com_palavras[i],auxpalavra)==0)
        {
            flag=1;
            printf("\nNumero da frase->%d\n",array_palavras_posi[i][0]);
            printf("Numero da palavra na frase->%d\n",array_palavras_posi[i][1]);
            printf("Numero da palavra no texto->%d\n",array_palavras_posi[i][2]);

            vezes_repetidas++;
        }

    }
    if(flag!=0)
    {
        printf("\nA palavra aparece %d vezes\n\n\n",vezes_repetidas);
    }

    if(flag==0)
    {
        printf("\n\nEssa palavra nao existe nas mensagens\n\n\n");
    }

}

void frase_entre_palavras(int**array_palavras_posi,int numero_palavras,char **array_com_palavras,char*palavra1,char*palavra2)
{
    int palavra1_int=0,palavra2_int=0,flag_pla1=0,flag_pla2=0;
    int i,flag=0;

    int tamanho_pala1=strlen(palavra1);
    int tamanho_pala2=strlen(palavra2);

    if(tamanho_pala1>20||tamanho_pala2>20)
    {
        printf("\nERRO-Palavra tem que ter menos que 20 caracteres\n");
        return ;
    }
    for(i=0; i<numero_palavras; i++)
    {
        if(strcmp(array_com_palavras[i],palavra1)==0)
        {
            if(flag_pla1!=1)
            {
                flag_pla1=1;
                palavra1_int=i+1;
                flag++;
            }
        }

        if(strcmp(array_com_palavras[i],palavra2)==0)
        {
            if(flag_pla2!=1)
            {
                palavra2_int=i+1;
                flag++;
                flag_pla2=1;
            }
        }

        if(flag==2)
        {
            break;
        }

    }
    if(palavra2_int<palavra1_int)
    {
        printf("\n--ERRO na ordem ou Palavra(s) nao encontrada(s) --\n");
        return ;
        printf("\n--OU--\n");
    }

    else
        printf("\n--Existem %d palavras entre as duas escolhidas--\n",palavra2_int-palavra1_int-1);
    for(i=1; i<palavra2_int-palavra1_int; i++)
    {

        printf("-%s-\n",array_com_palavras[palavra1_int+i-1]);

    }

    return ;

}
void frase_entre_palavras_escolhidas(int**array_palavras_posi,int numero_palavras,char **array_com_palavras,char*palavra1,char*palavra2,int posicao1, int posicao2)
{

    int palavra1_int=0,palavra2_int=0;
    int i,flag=0,flag1=0,flag2=0,flag_total=0;

    int tamanho_pala1=strlen(palavra1);
    int tamanho_pala2=strlen(palavra2);
    if(tamanho_pala1>20||tamanho_pala2>20)
    {
        printf("\nERRO-Palavra tem que ter menos que 20 caracteres\n");
        return ;
    }



    for(i=0; i<numero_palavras; i++)
    {

        if(strcmp(array_com_palavras[i],palavra1)==0)
        {

            flag1++;

            if(flag1==posicao1)
            {
                palavra1_int=i+1;
                flag_total++;
            }
        }

        if(strcmp(array_com_palavras[i],palavra2)==0)
        {

            flag2++;

            if(flag2==posicao2)
            {
                palavra2_int=i+1;
                flag_total++;

            }
        }
        if(flag==2)
        {

            break;
        }


    }
    if(palavra2_int<palavra1_int)
    {
        printf("\n--ERRO na ordem ou Palavra(s) nao encontrada(s) --\n");
        return ;
        printf("\n--OU--\n");
    }

    else
        printf("\n--Existem %d palavras entre as duas escolhidas--\n",palavra2_int-palavra1_int-1);
    for(i=1; i<palavra2_int-palavra1_int; i++)
    {

        printf("-%s-\n",array_com_palavras[palavra1_int+i-1]);

    }

    return ;

}
void search_letras(char **array_com_palavras,int numero_palavras)
{

    char* letras=(char*)calloc(1000,sizeof(char));
    int* posicao_letras=(int*)calloc(1000,sizeof(int));

    int i=0,b=0,c=0,tamanho_palavra=0,tamanho_abc=0,flag=0,tamanho_total=0;

    for(i=0; i<numero_palavras; i++)
    {
        tamanho_palavra=strlen(array_com_palavras[i]);

        for(b=0; b<tamanho_palavra; b++)
        {
            flag=0;

            for(c=0; c<=tamanho_abc; c++)
            {

                if(array_com_palavras[i][b]==letras[c])
                {

                    flag=1;
                    posicao_letras[c]++;
                    tamanho_total++;
                    break;

                }
            }
            if(flag==0)
            {

                letras[tamanho_abc]=array_com_palavras[i][b];
                posicao_letras[c]++;
                tamanho_total++;
                tamanho_abc++;


            }

        }
    }
    b=0;
    printf("TOTAL=%d\n\n",tamanho_total);
    for(b=0; b<tamanho_abc; b++)
    {

        printf("%c--%d--%f%%\n",letras[b],posicao_letras[b],((float)posicao_letras[b]/tamanho_total) * 100);
    }

}
void primeira_ultima_letra(char** array_com_palavras,int numero_palavras)
{

    printf("????????????????????????????????1");
    int i,tamanho_palavra=0,numero_letras_primeiro=0,b,numero_letras_ultimo=0,c=0,tamanho_tolta1=0,tamanho_tolta2=0;

    char *array_primeira_letra=NULL;
    array_primeira_letra=(char*)calloc(1000,sizeof(char));
    int *array_int_primeira_letra=NULL;
    array_int_primeira_letra=(int*)calloc(1000,sizeof(int));



    char *array_ultima_letra=NULL;
    array_ultima_letra=(char*)calloc(1000,sizeof(char));
    int *array_int_ultima_letra=NULL;
    array_int_ultima_letra=(int *)calloc(1000,sizeof(int));


    for(i=0; i<numero_palavras; i++)
    {
        tamanho_palavra=strlen(array_com_palavras[i])-1;
        int flag=0;
        int flag_ultima=0;

        for(b=0; b<numero_letras_primeiro; b++)
        {
            if(array_com_palavras[i][0]==array_primeira_letra[b])
            {
                array_int_primeira_letra[b]++;
                tamanho_tolta1++;
                flag=1;
            }

        }

        if(flag==0)
        {

            array_primeira_letra[numero_letras_primeiro]=array_com_palavras[i][0];


            array_int_primeira_letra[b]++;


            tamanho_tolta1++;

            numero_letras_primeiro++;

        }


        for(c=0; c<numero_letras_ultimo; c++)
        {
            if(array_com_palavras[i][tamanho_palavra]==array_ultima_letra[c])
            {
                array_int_ultima_letra[c]++;
                tamanho_tolta2++;
                flag_ultima=1;
            }

        }

        if(flag_ultima==0)
        {

            array_ultima_letra[numero_letras_ultimo]=array_com_palavras[i][tamanho_palavra];

            array_int_ultima_letra[c]++;

            tamanho_tolta2++;

            numero_letras_ultimo++;
        }

        // printf("%d",array_int_ultima_letra[c]);
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

float palavra_media(char** array_com_palavras,int numero_palavras)
{
    int i;
    float soma=0.0;
    printf("\n\nTamanho da Palavra \\ Numero da Palavra\n");
    for(i=0; i<numero_palavras; i++)
    {
        soma=soma+strlen(array_com_palavras[i]);
        printf("%d--%d---\n",strlen(array_com_palavras[i]),i);
    }

    soma=(float)(soma/numero_palavras);
    printf("--Media do comprimento das palavras===>%f--\n",soma);

    return soma;
}

char **maior_tamanho(char** array_com_palavras,int numero_palavras,int limite)
{

    int i=0,tamanho_palavra=0;


    int tamanho_array_menores=0;
    char**array_com_palavras_menores;
    array_com_palavras_menores=calloc(10,sizeof(char*));


    int tamanho_array_maiores=0;
    char**array_com_palavras_maiores;
    array_com_palavras_maiores=calloc(10,sizeof(char*));


    int j=0;

    for(i=0; i<numero_palavras; i++)
    {
        tamanho_palavra=strlen(array_com_palavras[i]);
        if(tamanho_palavra<=limite)
        {
            // array_com_palavras_menores[tamanho_array_menores]=malloc(sizeof(char)*(tamanho_palavra+1));
            array_com_palavras_menores[tamanho_array_menores]=array_com_palavras[i];
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
            array_com_palavras_maiores[tamanho_array_maiores]=array_com_palavras[i];
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


    return array_com_palavras_menores;
}

void procurar_raizes(char** palavras_com_repeticao,int numero_da_palavra_frases_total,char *palavra)
{
    int i=0;

    char *aux=NULL;
    int int_ocorrencias=0;
    char **array_palavras_com_ocorrencia=NULL;
    array_palavras_com_ocorrencia=calloc(1,sizeof(char*));

    int** int_palavras_posicao=calloc(1,sizeof(int*));


    for(i=0; i<numero_da_palavra_frases_total; i++)
    {
        aux=strstr(palavras_com_repeticao[i],palavra);

        if(aux!=NULL)
        {

            array_palavras_com_ocorrencia[int_ocorrencias]=palavras_com_repeticao[i];
            int_palavras_posicao[int_ocorrencias]=i+1;
            int_ocorrencias++;


            array_palavras_com_ocorrencia=realloc(array_palavras_com_ocorrencia,(int_ocorrencias+1)*sizeof(char*));
            int_palavras_posicao=realloc(int_palavras_posicao,(int_ocorrencias+1)*sizeof(int*));
            int j=0;
            for(j=int_ocorrencias; j<int_ocorrencias+1; j++)
            {
                array_palavras_com_ocorrencia[j]=NULL;
                int_palavras_posicao[j]=NULL;
            }


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

void Tf_Idf(char** bag_of_words,int tamanho,char* palavra)
{

    int i=0;
    float TF=0.0,soma=0.0;

    for(i=0; i<tamanho; i++)
    {
        if(strcmp(bag_of_words[i],palavra)==0)
        {
            soma++;
        }
    }

    TF=(float)(soma/tamanho);
    printf("\n\n O TF da palavra %s e %f",palavra,TF);

}

void digramas_trigramas(char** todas_palavras,int int_todas_palavras)
{
    int i=0,b=0,c=0;
    int tamanho_palavra=0;

    int flag=0;
    int tamanho_total=0;
    int tamanho_digramas=0;
    char**array_digramas=(char**)calloc(10,sizeof(char*));
    array_digramas[0]=(char*)calloc(3,sizeof(char));
    int *int_digramas=(int*)calloc(10,sizeof(int));
    char auxdigramas[3];

    int flag2=0;
    int tamanho_total2=0;
    int tamanho_digramas2=0;
    char**array_digramas2=(char**)calloc(500,sizeof(char*));
    array_digramas2[0]=(char*)calloc(4,sizeof(char));
    int *int_digramas2=(int*)calloc(500,sizeof(int));
    char auxdigramas2[4];


    for(i=0; i<int_todas_palavras; i++)
    {
        tamanho_palavra=strlen(todas_palavras[i]);

        for(b=0; b<tamanho_palavra-1; b++)
        {
            flag=0;
            if(tamanho_total==0)
            {
                auxdigramas[0]=todas_palavras[0][0];
                auxdigramas[1]=todas_palavras[0][1];
                auxdigramas[2]='\0';
            }

            for(c=0; c<tamanho_digramas; c++)
            {
                auxdigramas[0]=todas_palavras[i][b];
                auxdigramas[1]=todas_palavras[i][b+1];
                auxdigramas[2]='\0';



                if(strcmp(&auxdigramas,array_digramas[c])==0)  //strcmp(auxdigramas,array_digramas[c])==0
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
                auxdigramas2[0]=todas_palavras[0][0];
                auxdigramas2[1]=todas_palavras[0][1];
                auxdigramas2[2]=todas_palavras[0][2];
                auxdigramas2[3]='\0';
            }

            for(c=0; c<tamanho_digramas2; c++)
            {

                auxdigramas2[0]=todas_palavras[i][b];
                auxdigramas2[1]=todas_palavras[i][b+1];
                auxdigramas2[2]=todas_palavras[i][b+2];
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
                        int_digramas2[o]=NULL;

                    }
                }
            }

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





void printf_words(char** array,int tamanho)
{
    int i=0,b=0,count=0;
    int tamanho_word=0;

    for(i=0; i<tamanho; i++)
    {
        tamanho_word=strlen(array[i]);

        printf("--");
        printf("|%s|",array[i]);
        printf("--");

        count++;
        for(b=12; b>tamanho_word; tamanho_word++)
        {
            printf(" ");
        }
        if(count==4)
        {
            printf("\n");
            count=0;
        }
    }
    printf("\n\n\n");
}

void printf_words_positions(char** array,int **array_posicao,int quantidade)
{
    int i=0,b=0,count=0;
    int tamanho_word=0;

    for(i=0; i<quantidade; i++)
    {



        tamanho_word=strlen(array[i]);

        printf("--");
        printf("|%d-%d-%d-%d--%s|",array_posicao[i][0],array_posicao[i][1],array_posicao[i][2],array_posicao[i][3],array[i]);
        printf("--");

        count++;
        for(b=12; b>tamanho_word; tamanho_word++)
        {
            printf(" ");
        }
        if(count==4)
        {
            printf("\n");
            count=0;
        }

    }
    printf("\n\n\n");
}

/*

  int asdd=0;
       for(pi = 0; pi < numero_da_palavra_frases_total; pi++)
       {

           for(asdd=0;asdd<3;asdd++)
           {
                printf("-%d-",palavra_com_posi[pi][asdd]);
           }
           printf("\n");
       }



    for(pi = 0; pi < numero_da_palavra_frases_total; pi++)
        {
            printf("%s\n",palavras_com_repeticao[pi]);
        }

      */
/*  int pi=0,asdd=0;
      for(pi = 0; pi < numero_palavras; pi++)
      {

          for(asdd=0;asdd<3;asdd++)
          {
               printf("-%d-",array_palavras_posi[pi][asdd]);
          }
          printf("\n");
      }


    char *array_pos_palavras=(char*)malloc(sizeof(char)*(tamanho_palavra+25));
    strcpy(array_pos_palavras,palavra);
    array_pos_palavras[tamanho_palavra]='-';
    array_pos_palavras[(tamanho_palavra+1)] = NULL;

    char* str1 =array_pos_palavras;

    strcat(str1,n_frasechar);


    str1[tamanho_palavra+strlen(n_frasechar)+1]='-';
    str1[tamanho_palavra+strlen(n_frasechar)+2]='\0';
    strcat(str1,numero_da_palavra_fraseschar);
    str1[tamanho_palavra+strlen(n_frasechar)+strlen(numero_da_palavra_fraseschar)+2]='-';
    str1[tamanho_palavra+strlen(n_frasechar)+strlen(numero_da_palavra_fraseschar)+3]='\0';
    strcat(str1,n_total_palchar);


    array_pos_palavras=str1;




char* caracteres_especiais(char* palavra,int tamanho_palavra)
{

        int i=0;
        for(i=0;i<tamanho_palavra;i++)
        {
            if(palavra[i]=='Ó')
            {
                palavra[i]=241;
            }
            if(palavra[i]=='ß')
            {

            }
            if(palavra[i]=='Ô')
            {

            }
            if(palavra[i]=='Ò')
            {

            }
            if(palavra[i]=='└')
            {

            }
            if(palavra[i]=='┴')
            {

            }
            if(palavra[i]=='┬')
            {

            }
            if(palavra[i]=='├')
            {

            }
            if(palavra[i]=='Ú')
            {

            }if(palavra[i]=='Û')
            {

            }
            if(palavra[i]=='╔')
            {

            }
            if(palavra[i]=='╩')
            {

            }
            if(palavra[i]=='Ý')
            {

            }
            if(palavra[i]=='═')
            {

            }
            if(palavra[i]=='¾')
            {

            }
            if(palavra[i]=='¶')
            {

            }
            if(palavra[i]=='§')
            {

            }
            if(palavra[i]=='Ë')
            {

            }
            if(palavra[i]=='È')
            {

            }
            if(palavra[i]=='ı')
            {

            }
            if(palavra[i]=='·')
            {

            }
             if(palavra[i]=='┌')
            {

            }
             if(palavra[i]=='þ')
            {

            }

        }
   //     printf("--%s--\n",palavra);
    return palavra;
}


char *searchwordSTR(char palavra,char **array_palavras_posi, int tamanho)
{
    int i,tamanho_palavra=strlen(palavra);
    char auxpalavra[20];
    for(i=0;i<tamanho;i++)
    {
        strncpy(auxpalavra, array_palavras_posi[i], tamanho_palavra);
        auxpalavra[tamanho_pala] = '\0';
        if(strcmp(auxpalavra,palavra))
        {

        }
    }
}



                        count_pala=0;
                        frase_pal = strtok (array_palavras_posi[i],"- ");
                      //  printf("%s\n---",array_palavras_posi[i]);
                        while(frase_pal!=NULL)
                        {
                            if(count_pala==3)
                            {
                             // printf("Numero da palavra no texto->%s\n",frase_pal);
                                palavra1_int=atoi(frase_pal);
                            }
                            count_pala++;
                            frase_pal  = strtok(NULL, "- ");
                        }


  count_pala=0;
             frase_pal = strtok (array_palavras_posi[i],"- ");
             while(frase_pal!=NULL)
             {
                 if(count_pala==3)
                 {
                    // printf("Numero da palavra no texto->%s\n",frase_pal);
                     palavra2_int=atoi(frase_pal);
                 }
                 count_pala++;
                 frase_pal  = strtok(NULL, "- ");
             }


              char auxpalavra2[20];
             strcpy(auxpalavra2,array_palavras_posi[i]);
             flag=1;
             count_pala=0;
             frase_pal = strtok (auxpalavra2,"- ");
             while(frase_pal!=NULL)
             {
                 if(count_pala==1)
                 {
                     printf("\nNumero da frase->%s\n",frase_pal);
                 }
                 if(count_pala==2)
                 {
                     printf("Numero da palavra na frase->%s\n",frase_pal);
                 }
                 if(count_pala==3)
                 {
                     printf("Numero da palavra no texto->%s\n",frase_pal);
                 }
                 count_pala++;

                 frase_pal  = strtok(NULL, "- ");
             }*/   /*char auxpalavra2[20];
             strcpy(auxpalavra2,array_palavras_posi[i]);
             flag=1;
             count_pala=0;
             frase_pal = strtok (auxpalavra2,"- ");
             while(frase_pal!=NULL)
             {
                 if(count_pala==1)
                 {
                     printf("\nNumero da frase->%s\n",frase_pal);
                 }
                 if(count_pala==2)
                 {
                     printf("Numero da palavra na frase->%s\n",frase_pal);
                 }
                 if(count_pala==3)
                 {
                     printf("Numero da palavra no texto->%s\n",frase_pal);
                 }
                 count_pala++;

                 frase_pal  = strtok(NULL, "- ");
             }

               char auxpalavra2[20];
             strcpy(auxpalavra2,array_palavras_posi[i]);
             flag=1;
             count_pala=0;
             frase_pal = strtok (auxpalavra2,"- ");
             while(frase_pal!=NULL)
             {
                 if(count_pala==1)
                 {
                     printf("\nNumero da frase->%s\n",frase_pal);
                 }
                 if(count_pala==2)
                 {
                     printf("Numero da palavra na frase->%s\n",frase_pal);
                 }
                 if(count_pala==3)
                 {
                     printf("Numero da palavra no texto->%s\n",frase_pal);
                 }
                 count_pala++;

                 frase_pal  = strtok(NULL, "- ");
             }

             */
