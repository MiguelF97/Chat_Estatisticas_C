#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ThreeSum.h"
#include "ThreeSumFast.h"
#include "clientThreeSum.h"
#include "../lib_util.h"

int mainClientThreeSum(int N, char * filename)
{
    int * v;
    unsigned long custo=0;
    long long time_usec_init;
    long long time_usec_end;
    long elapsed_time;
    v = newIntArray(N);
    N = readInts(filename, v, N);
    printf("\n\nLidos %d valores\n",N);
    gettimeuseconds(&time_usec_init); // init time
    int cnt = countTriples(v, N, &custo);
    gettimeuseconds(&time_usec_end); // end time
    //printAll(v, N); // imprime todos os triplos
    //printArray(v,N);
    elapsed_time = (long) (time_usec_end - time_usec_init);
    printf("Custo = %ld // Numero de acessos ao vector\n",custo);
    printf("elapsed time (usec) = %ld\nelapsed time (sec) = %lf\ntriples = %d\n", elapsed_time,(elapsed_time*pow(10,-6)),cnt);
    freeIntArray(v);
    return 0;
}
int mainClientThreeSumFast(int N, char * filename)
{
    int * v;
    long long time_usec_init;
    long long time_usec_end;
    long elapsed_time;
    v = newIntArray(N);
    N = readInts(filename, v, N);

    printf("\n\nLidos %d valores\n",N);
    gettimeuseconds(&time_usec_init); // init time
    int cnt = countTriplesFast(v, N);
    gettimeuseconds(&time_usec_end); // end time
    //printAll(v, N); // imprime todos os triplos
    //printArray(v,N);
    elapsed_time = (long) (time_usec_end - time_usec_init);
    //printf("Custo = %ld // Numero de acessos ao vector\n",custo);
    printf("elapsed time (usec) = %ld\nelapsed time (sec) = %lf\ntriples = %d\n", elapsed_time,(elapsed_time*pow(10,-6)),cnt);
    freeIntArray(v);

    return 0;
}





int mainThreeSum()
{
    char * path2datafolder = "C:/Universidade/AEDI_Classes/data/";
    char * datafiles[] = {"1Kints.txt","2Kints.txt","4Kints.txt","8Kints.txt","250ints.txt","500ints.txt"};
    int tam[] = {1000,2000,4000,8000,250,500};
    int i,k=6;
    char filename[300];
    srand((unsigned)time(0));
    for(i=0; i<k; i++)
    {
        strcpy(filename, path2datafolder);
        strcat(filename, datafiles[i]);
        //printf("%s",filename);
        mainClientThreeSum(tam[i], filename);
    }
    return 0;
}


int mainThreeSumFast()
{
    char * path2datafolder = "C:/Universidade/AEDI_Classes/data/";
    char * datafiles[] = {"1Kints.txt","2Kints.txt","4Kints.txt","8Kints.txt","250ints.txt","500ints.txt"};
    int tam[] = {1000,2000,4000,8000,250,500};
    int i,k=6;
    char filename[300];
    srand((unsigned)time(0));
    for(i=0; i<k; i++)
    {
        strcpy(filename, path2datafolder);
        strcat(filename, datafiles[i]);
        //printf("%s",filename);
        mainClientThreeSumFast(tam[i], filename);
    }
    return 0;
}

