#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int Add(int *n, char **loc, char *spot, int *cost)
{
    int i;
    for (i=0; i<strlen(spot); i++)
    {
        if (spot[i] == ',')
        {
            spot[i] = '\0';
            *cost = atoi(spot+i+1);
        }
    }
    for (i=0; i<*n; i++)
    {
        if(strcmp(spot, loc[i]) == 0)
        {
            return i;
        }
    }

    strcpy(loc[*n], spot);
    *n = *n + 1;
    return *n-1;
}

int *drum_minim(int **a,int s,int **t, int N)
{
 int *f,*d,INF=INT_MAX/2;
    f=calloc(N,sizeof(int));
    *t=calloc(N,sizeof(int));
    d=calloc(N,sizeof(int));
    int i,j;
    for (i = 0; i < N; i++)
    {
        f[i] = 0;
        d[i] = a[s][i];
    }

    f[s] = 1;
    d[s] = 0;
    d[0] = INF;
    for (int k = 0; k < N-1; ++k)
    {
        int pmax = 0;
        for (i = 0; i < N; ++i)
            if (f[i] == 0 && d[i] < d[pmax])
                pmax = i;

        if (pmax > -1)
        {
            f[pmax] = 1;
            for (i = 0; i < N; ++i)
                if (f[i] == 0 && d[pmax]!=INF && d[i] > d[pmax] + a[pmax][i])
                    {
                        d[i] = d[pmax] + a[pmax][i];
                        (*t)[i]=pmax;
                    }
        }
    }
    return d;
}


