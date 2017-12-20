#include <stdio.h>
#include <stdlib.h>



int main()
{

    menu();

    return 0;
}



void menu()
{
    // printf("\n\n %c %c",'a',tolower('A'));
    int i = 0, j = 0, n = 4, numero_frases=0, pi=0,auxint1=0,auxint2=0;
    char auxpalavra[30],auxpalavra2[30];

    char *texto = NULL;

    int  numero_de_palavras= 0;
    int todas_as_palavras_int=0;

    char *path = "data\\message_1.txt";
    char **array_frases=NULL;
    char **bag_of_words=NULL;


    char ***todas_palavras=NULL;
    todas_palavras=(char***)malloc(sizeof(char**)*1);

    int ***array_posicao_palavras=NULL;
    array_posicao_palavras=(int***)malloc(sizeof(int**)*1);



    texto= read_message(path);
    // printf("%s",texto);


    array_frases=create_array_strings(texto,&numero_frases);
    bag_of_words=separar_palavras(array_frases,numero_frases,&numero_de_palavras,array_posicao_palavras,todas_palavras,&todas_as_palavras_int);


  //  search_word(*array_posicao_palavras,38,*todas_palavras);
    system("cls");
    int escolha=0,escolha1=0;
    do
    {
        printf("\n\nMenu Principal\n\n");
        printf("1. Palavras extraidas\n");
        printf("2. Pesquisa no texto\n");
        printf("3. Estatisticas\n");
        printf("4. Exit\n");
        printf("=>");
        scanf("%d",&escolha);

        switch (escolha)
        {
        case  1:
            do
            {
                system("cls");
                printf("\n\n(1)Menu=>Palavras extraidas\n\n");
                printf("1. Bag-of-Words\n");
                printf("2. Todas as Palavras\n");
                printf("3. Todas as Palavras e respetivas posicoes\n");
                printf("4. Voltar\n");
                scanf("%d",&escolha1);

                switch(escolha1)
                {
                case  1:system("cls");
                        printf("\n\t\t\tBAG-OF-WORDS(%d)\n\n",numero_de_palavras);
                        printf_words(bag_of_words,numero_de_palavras);
                        break;

                case  2:system("cls");
                        printf("\n\t\t\tTODAS AS PALAVRAS(%d)\n\n",todas_as_palavras_int);
                        printf_words(*todas_palavras,todas_as_palavras_int);
                        break;

                case  3:system("cls");
                        printf("\n\t\t\t\t\tTODAS AS PALAVRAS(%d)\n",todas_as_palavras_int);
                        printf("\n\t\t(Num da frase/Num da palavra na frase/Num total da palavra no texto/Num Paragrafo)\n\n");
                        printf_words_positions(*todas_palavras,*array_posicao_palavras,todas_as_palavras_int);
                        break;

                case  4:system("cls");
                        break;

                default:printf("Escolha Errada\n");
                        system("cls");
                        break;

                }
            break;
            }
            while (escolha != 4);
            break;

        case  2:
            do
            {   system("cls");
                printf("\n\n(2)Menu=>Pesquisa no texto\n\n");
                printf("1. Procurar uma Palavra\n");
                printf("2. Primeira palavras entre a primeira ocorrencia entre duas Palavras\n");
                printf("3. Ocorrencia entre duas Palavras(Palavras Repetidas)\n");
                printf("4. Pesquisa de sequencia de caracteres\n");
                printf("5. Voltar\n");
                printf("=>");
                scanf("%d",&escolha1);

                switch(escolha1)
                {
                case  1:system("cls");
                        printf("\nIntroduza a Palavra que deseja Procurar=>");
                        scanf("%s",auxpalavra);
                        printf("\n\nProcurar Palavra(%s)\n\n",auxpalavra);
                        search_word(*array_posicao_palavras,todas_as_palavras_int,*todas_palavras,&auxpalavra);
                        break;

                case  2:system("cls");
                        printf("\nIntroduza a primeira Palavra=>");
                        scanf("%s",auxpalavra);
                        printf("\nIntroduza a segunda Palavra=>");
                        scanf("%s",auxpalavra2);
                        frase_entre_palavras(*array_posicao_palavras,todas_as_palavras_int,*todas_palavras,&auxpalavra,&auxpalavra2);
                        break;

                case  3:system("cls");
                        printf("\nIntroduza a primeira Palavra e a sua repeticao(string int)=>");
                        scanf("%s %d",auxpalavra,&auxint1);
                        printf("\nIntroduza a segunda Palavra e a sua repeticao(string int)=>");
                        scanf("%s %d",auxpalavra2,&auxint2);
                        frase_entre_palavras_escolhidas(*array_posicao_palavras,todas_as_palavras_int,*todas_palavras,&auxpalavra,&auxpalavra2,auxint1,auxint2);
                        break;
                case  4:system("cls");
                        printf("\nIntroduza a sequencia de caracteres=>");
                        scanf("%s",auxpalavra);
                        procurar_raizes(*todas_palavras,todas_as_palavras_int,auxpalavra);
                        break;

                case  5:system("cls");
                        break;
                default:printf("Escolha Errada\n");
                        break;


                }
            break;
            }
            while (escolha != 5);
            break;
        case  3:do
            {
                system("cls");
                printf("\n\n(3)Menu=>Estatisticas\n\n");
                printf("1. %% De todas as letras \n");
                printf("2. Primeiras e Ultimas Letras\n");
                printf("3. %% Palavra Media\n");
                printf("4. Tamanho da Palavra Menor ou Maior\n");
                printf("5. TF de uma Palavra\n");
                printf("6. Digramas e Trigramas\n");
                printf("7. Voltar\n");
                printf("=>");
                scanf("%d",&escolha1);

                switch(escolha1)
                {
                case  1:system("cls");
                        printf("\n\t\t\tTODAS AS LETRAS\n\n",numero_de_palavras);
                        search_letras(*todas_palavras, todas_as_palavras_int);
                        break;

                case  2:system("cls");
                        printf("\n\t\t\tPrimeiras e Ultimas Letras\n\n");
                        primeira_ultima_letra(*todas_palavras,todas_as_palavras_int);
                        break;

                case  3:system("cls");
                        printf("\n\t\t\t\t\t%%Palavra Media\n");
                        palavra_media(*todas_palavras,todas_as_palavras_int);
                        break;

                case  4:system("cls");
                        int numero=0;
                        printf("Introduza o tamanho=>",numero);
                        scanf("%d",&numero);
                        printf("\n\t\t\tTamanho da Palavra Menor ou Maior que %d\n\n",numero);
                        maior_tamanho(*todas_palavras,todas_as_palavras_int,numero);
                        break;

                case  5:system("cls");
                        printf("Introduza a palavra==>");
                        scanf("%s",auxpalavra);
                        printf("\n\tTF da Bag-of-Words");
                        Tf_Idf(*todas_palavras,todas_as_palavras_int,&auxpalavra);
                        break;

                case  6:system("cls");
                        printf("\n\n\tDigramas e Trigramas\n\n ");
                        digramas_trigramas(*todas_palavras,todas_as_palavras_int);
                        break;

                case  7:system("cls");
                        break;

                default:printf("Escolha Errada\n");
                        system("cls");
                        break;

                }
            break;
            }
            while (escolha != 7);

            break;
        case  4:
            printf("Bye Bye :)\n");
            return;
        default:
            printf("Escolha Errada\n");
            break;
        }

    }
    while (escolha != 4);


return;

}

//search_letras(palavras_com_repeticao, numero_da_palavra_frases_total);
    //primeira_ultima_letra(palavras_com_repeticao,numero_da_palavra_frases_total);
    //palavra_media(palavras_com_repeticao,numero_da_palavra_frases_total);
    //maior_tamanho(palavras_com_repeticao,numero_da_palavra_frases_total);


