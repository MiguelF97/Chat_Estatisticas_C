/**
 *  @file lib_util.c
 *  @brief Implementation of some util function prototypes for aed1.
 *
 *  This file contains the implementations for
 *  some util functions you will need for aed1.
 *
 *  @author José Torres (jtorres@ufp.edu.pt)
 *  @bug No known bugs.
 */

#include "lib_util.h"

int readInts(char * filename, int * intvec, int nmax) {
    FILE * fp;
    int n=0;
    fp = fopen(filename, "r");
    if (fp != NULL) {
        while (!feof(fp) && n < nmax)
            fscanf(fp,"%d\n", &intvec[n++]);
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return n;
}

int readIntsHeader(char * filename, int ** intvec) {
    FILE * fp;
    int n=0, nmax;
    fp = fopen(filename, "r");
    if (fp != NULL) {
        fscanf(fp,"%d\n", &nmax); // header - size of array
        *intvec = newIntArray(nmax);
        while (!feof(fp) && n < nmax)
            fscanf(fp,"%d\n", &((*intvec)[n++]));
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return nmax;
}

#ifdef WIN32
int gettimeuseconds(long long * time_usec) {
    union {
        long long ns100; //time since 1 Jan 1601 in 100ns units
        FILETIME ft;
    } now;
    
    GetSystemTimeAsFileTime( &(now.ft) ); // win32 function!
    *time_usec=(long long) (now.ns100 / 10LL);
    return 0;
}
#else
int gettimeuseconds(long long * time_usec) {
    struct timeval time;
    gettimeofday(&time,NULL);
    
    *time_usec=(long long) (time.tv_sec * 1000000 + time.tv_usec);
    return 0;
}
#endif


/** 
  @brief gera um inteiro aleatoriamente/uniformemente no intervalo: val_min...val_max 
 */
int uniform(int val_min, int val_max) {
    return val_min + rand() % (val_max - val_min + 1);
}

/** @brief gera um double aleatoriamente/uniformemente no intervalo 0..1 */
double uniform_double(void) {
    return rand() / (double)(RAND_MAX);
}


/** @brief gera um double aleatoriamente/uniformemente no intervalo 0..1 */
double uniform_double_interval(double val_min, double val_max) {
    return val_min + (val_max - val_min) * (rand() / (double)(RAND_MAX));
}

/**
 * Return a real number with a standard Gaussian distribution.
 */
double gaussian_normal(void) {
    // use the polar form of the Box-Muller transform
    double r, x, y;
    do {
        x = uniform_double_interval(-1.0, 1.0);
        y = uniform_double_interval(-1.0, 1.0);
        r = x*x + y*y;
    } while (r >= 1 || r == 0);
    return x * sqrt(-2 * log(r) / r);
    
    // Remark:  y * sqrt(-2 * log(r) / r)
    // is an independent random gaussian
}

/// @brief function to fill an array with integer random uniformly distributed values (returns -1 if error)
int uniformArray(int * a, int N, int val_min, int val_max){
    int i;
    for (i=0; i<N; i++) {
        a[i] = uniform(val_min, val_max);
    }
    return 0;
}

/// @brief function to fill an array with integer random uniformly distributed distinct values (returns -1 if error)
int uniformDistinctArray(int * a, int N, int val_min, int val_max){
    int i, value, range = val_max - val_min + 1;
    char * b = newCharArray(range);
    for (i=0; i<range; i++)
        b[i]=0;
    for (i=0; i<N; i++) {
        do {
            value = uniform(val_min, val_max);
        } while (b[value - val_min] != 0);
        b[value - val_min]=1;
        a[i] = value;
    }
    freeCharArray(b);
    return 0;
}

/**
 * Return a real number from a gaussian distribution with given mean and stddev
 */
double gaussian(double mean, double stddev) {
    return mean + stddev * gaussian_normal();
}

/**
 *  @brief char array dynamic managing
 *
 *  @param N size of char array to be created
 *
 *  @return new char array allocated in heap memory
 */
char * newCharArray(int N){
    return (char *) malloc(sizeof(char)*N);
}

void freeCharArray(char * v){
    free(v);
}

/**
 *  @brief int array dynamic managing
 *
 *  @param N size of int array to be created
 *
 *  @return new int array allocate in heap memory
 */
int * newIntArray(int N){
    return (int *) malloc(sizeof(int)*N);
}

void freeIntArray(int * v){
    free(v);
}

void printArray(int* a, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
}

int compareIntValues(const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

/**
 *  Sort int arrays using quick sort from the C library
 *
 *  @param v integer array to sort
 *  @param n size of the array
 */
void sortIntArray(int * v, int n) {
    qsort (v, n, sizeof(int), compareIntValues);
}

int binarySearch(int a[], int n, int key) {
    int lo = 0, hi = n-1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if      (key < a[mid]) hi = mid - 1;
        else if (key > a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}

int writeInts(char * filename, int * intvec, int n){
    FILE * fp;
    int i=0;
    fp = fopen(filename, "w");
    if (fp != NULL) {
        while (i < n)
            fprintf(fp,"%d\n", intvec[i++]);
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return 0;
}

int writeIntsHeader(char * filename, int * intvec, int n){
    FILE * fp;
    int i=0;
    fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp,"%d\n", n); // header - size of array
        while (i < n)
            fprintf(fp,"%d\n", intvec[i++]);
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return 0;
}


