int **create_int_matrix(int nrows, int ncols)
{
    int **m = malloc(nrows * sizeof(int *));
    for (int i = 0; i < nrows; i++)
    {
        m[i] = malloc(ncols*sizeof(int));
    }
    return m;
}

void free_int_matrix(int **m, int nrows)
{
    for(int i = 0; i < nrows; i++)
    {
        free(m[i]);
    }
    free(m);
}

void print_int_matrix(int**m, int nrows, int ncols)
{
    for(int i = 0; i<nrows; i++)
    {
        for(int j = 0; j<ncols; j++)
        {
            print("%.2d",n[i][j]);
        }
        printf("\n");
    }
}

void example()
{
    char *strings_array[5] = {"Hello","my","name","is\n"};

    for(int i = 0; i<5; i++)
    {
        printf("%d: \"%s\"\n",i,strings_array[i]);
    }
}
int main()
{
    int nrows = 10;
    int ncols = 10;
    int **m = create_int_matrix(nrows,ncols);
    for(int i = 0; i < nrows; i++)
    {
        for(j = 0; j<ncols; j++)
        {
            m[i][j] = i*j;
        }
    }
    print_int_matrix(m,nrows,ncols);
    free_int_matrix(m,nrows);
}
