#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

char *read_message(char *filename);
void add_new_line(char **destino, char *frase, int i);
char ** create_array_strings(char *frases,int *nfrases);
char **separar_palavras(char **array, int n_frases, int *numero_de_palavras, int ***palavra_com_posi,char*** array_repetidas,int *todas_as_palavras_int);
void frase_entre_palavras(int**array_palavras_posi,int numero_palavras,char **array_com_palavras,char*,char*);
void frase_entre_palavras_escolhidas(int**array_palavras_posi,int numero_palavras,char **array_com_palavras,char*,char*,int,int);
void search_letras(char **array_com_palavras,int numero_palavras);
char* caracteres_especiais(char* palavra,int tamanho_palavra);
void primeira_ultima_letra(char** array_com_palavras,int numero_palavras);
float palavra_media(char** array_com_palavrras,int numero_palavras);
char **maior_tamanho(char** array_com_palavras,int numero_palavras,int);
void procurar_raizes(char**palavras_com_repeticao,int numero_da_palavra_frases_total,char*);
void printf_words(char**,int);
void printf_words_positions(char **todas_palavras,int **array_posicao_palavras,int todas_as_palavras_int);
void Tf_Idf(char** bag_of_words,int tamanho,char*);
void digramas_trigramas(char** todas_palavras,int int_todas_palavras);

void search_word(int **array_palavras_posi,int numero_palavras,char**array_com_palavras,char* palavra);
#endif // FUNCTIONS_H_INCLUDED
