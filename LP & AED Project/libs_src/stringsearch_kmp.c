#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stringsearch_kmp.h"
#include "libs_src\lib_util.h"


/**
 *  KMP using http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
 *
 *  @param pat     <#pat description#>
 *  @param m       <#m description#>
 *  @param kmpNext <#kmpNext description#>
 */
void preKmp_LP(char *pat, int m, int * kmpNext) {
    int i, j;
    i = 0;
    j = kmpNext[0] = -1;
    while (i < m) {
        while (j > -1 && pat[i] != pat[j])
            j = kmpNext[j];
        i++;
        j++;
        if (pat[i] == pat[j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}

/**
 *  KMP using: http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
 *
 *  @param pat <#pat description#>
 *  @param m   <#m description#>
 *  @param str <#str description#>
 *  @param n   <#n description#>
 */
void KMP_LP(char *pat, int m, char *str, int n) {
    int i, j, *kmpNext;
    int sz_kmpNext = m+1;
    kmpNext = (int*)malloc(sz_kmpNext * sizeof(int));
    /* Preprocessing */
    preKmp_LP(pat, m, kmpNext);
    printf("Longest Prefix Array:  ");
    printArray(kmpNext, sz_kmpNext);
    /* Searching */
    i = j = 0;
    while (j < n) {
        while (i > -1 && pat[i] != str[j])
            i = kmpNext[i];
        i++;
        j++;
        if (i >= m) {
            printf("Matching at %d\n",(j - i));
            i = kmpNext[i];
        }
    }
    free(kmpNext);
}

void clientKMP_LP(){
    char pat[]="GCAGAGAG";
    int M=8;
    char txt[]="AAAGCAGAGAGAAA";
    int N=14;
    KMP_LP(pat, M, txt, N);
}



// create the DFA from a character array over R-character alphabet
void KMP(char pattern[M_KMP], int dfa[R_KMP][M_KMP]) {
    int X,c,j,i;
    // reset dfa[][] matrix to zeros
    for (i = 0; i < R_KMP; i++)
        for (j = 0; j < M_KMP; j++)
            dfa[i][j]=0;
    // build DFA from a pattern with length M
    dfa[pattern[0]-(int)'A'][0] = 1;
    for (X = 0, j = 1; j < M_KMP; j++) {
        for (c = 0; c < R_KMP; c++){
            dfa[c][j] = dfa[c][X];     // Copy mismatch cases.
        }
        dfa[pattern[j]-(int)'A'][j] = j+1;      // Set match case.
        X = dfa[pattern[j]-(int)'A'][X];        // Update restart state.
    }
}

// return offset of first match; -1 if no match
int KMPsearch(char * text, int dfa[R_KMP][M_KMP]) {
    // simulate operation of DFA on text
    int N = (int) strlen(text);
    int i, j;
    for (i = 0, j = 0; i < N && j < M_KMP; i++) {
        j = dfa[text[i]-(int)'A'][j];
    }
    if (j == M_KMP) return i - M_KMP;    // found
    return -1;                    // not found
}


void clientKMP() {
    char * txt="BCBAABACAABABACA";
    char * pat="ABABAC";
    int dfa[R_KMP][M_KMP];
    char * prox_pos;
    int pos=0;

    KMP(pat,dfa); // dfa create

    prox_pos=txt;
    while (pos >= 0) {
        pos = KMPsearch(prox_pos,dfa);
        if (pos >= 0) {
            printf("Correspondencia em i=%d\n",pos);
            prox_pos=&txt[pos+1];
        } else
            printf("Nao existem mais correspondencias!\n");
    }
}

void printKMP_DFA(int dfa[R_KMP][M_KMP]) {
    int i,j;
    printf("\nDFA:\n");
    for (j=0; j<R_KMP; j++) {
        for (i=0; i<M_KMP; i++) {
            printf("%d ",dfa[j][i]);
        }
        printf("\n");
    }
    //printf("\n\n");
}

void printKMPsearch(char * text, char * pat, int dfa[R_KMP][M_KMP]) {
    // simulate operation of DFA on text
    int N = (int) strlen(text);
    char * occor = (char *)malloc(N*sizeof(char));
    int i, j;
    //printf("\nKMP Search (non-overlapped occurrences):\n(text[i],pat[j],j)=");
    printf("\nKMP Search (non-overlapped occurrences):\n");
    //printf("(text[i],j)=");
    printf("P=%s,M=%d\nT=%s\nS=",pat,M_KMP,text);
    for (i = 0, j = 0; i < N; i++) {
        //printf("(%c,%c,%d)",text[i],pat[j],j);
        //printf("(%c,%d)",text[i],j);
        printf("%d",j);
        j = dfa[text[i]-(int)'A'][j];
        occor[i] = ' ';
        if (j == M_KMP) {
            //printf("*"); // found occorrence of pat
            occor[i]='*';
            //j=0;
            j = dfa[text[i]-(int)'A'][0];
        }
    }
    printf("\nO=");
    for (i = 0; i < N; i++)
        printf("%c",occor[i]);
    printf("(O-ocorrencias)\n\n");
}

void clientKMP_6nov2013() {
    char * txt="AABAABACAAABAAC";
    char * pat="AABAAC"; // length == M
    int dfa[R_KMP][M_KMP];
    KMP(pat,dfa); // KMP dfa create
    printKMP_DFA(dfa);
    printKMPsearch(txt,pat,dfa);
}


void clientKMP_19nov2015_aulatp() {
    char * pat="AAABBC"; // length == M == 6
    int dfa[R_KMP][M_KMP];
    KMP(pat,dfa); // KMP dfa create
    printKMP_DFA(dfa);
}

void clientKMP_14jan2016() {
    //char * txt="ABCAABABABCABCCAAAABC";
    //char * pat="ABCABCA"; // length == M
    char * txt="AACCCCBBAAACCBBABCABCCAABC";
    char * pat="CCBBAAA"; // length == M

    int dfa[R_KMP][M_KMP];
    KMP(pat,dfa); // KMP dfa create
    printKMP_DFA(dfa);
    printKMPsearch(txt,pat,dfa);
}


void clientKMP_3fev2016() {
    char * txt="ACAACCCAABCCBCAABCAABCCBC";
    //char * pat="CAABCCB"; // length == M_KMP
    //char * pat="CCCABC"; // length == M_KMP
    char * pat="AABBABC"; // length == M_KMP. oral jose nery e teresecampante (23/2)

    int dfa[R_KMP][M_KMP];
    KMP(pat,dfa); // KMP dfa create
    printKMP_DFA(dfa);
    printKMPsearch(txt,pat,dfa);
}


void clientKMP_6jul2016() {
    char * txt="AAAABBCAABBCCBCAABCAABCCBC";
    char * pat="AABBABC"; // length == M_KMP

    int dfa[R_KMP][M_KMP];
    KMP(pat,dfa); // KMP dfa create
    printKMP_DFA(dfa);
    printKMPsearch(txt,pat,dfa);
}

void client_strstr_bf() {
    char * txt="ABABRACADABRA";
    char * pat="ABRA";
    char * pos_match;
    pos_match=txt;
    while (pos_match != 0) {
        pos_match = strstr_bf(pos_match,pat);
        if (pos_match!=0) {
            printf("Correspondencia em i=%d\n", (int)(pos_match - txt));
            pos_match+=1;
        } else
            printf("Nao existem mais correspondencias!\n");
    }
}

/**
 * Implementação usando pesquisa exaustiva de strstr(txt,pat)
 */
char * strstr_bf(char * txt, char * pat) {
    int M1 = (int) strlen(pat);
    int N = (int) strlen(txt);
    int i,j;
    for (i = 0; i <= N - M1; i++) {
        for (j = 0; j < M1; j++)
            if (txt[i+j] != pat[j])
                break;
        if (j == M1) return &txt[i];
    }
    return 0;
}
