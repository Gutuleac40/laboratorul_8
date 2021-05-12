#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "header.h"

int main()
{
    FILE *f, *g;
    f = fopen("_all_files.txt", "rt");
    char file[20], spot[40], **loc;
    int **p, i, n=0, s = 0, j,  **v, *d, *father, indepartat;
    int costx, costy, x, y, P, U;
    int min = INT_MAX, max = INT_MIN, mx, my, Mx, My;
    FILE *K, *H, *T, *R, *D, *L;
    T = fopen("total.txt", "wt");
    K = fopen("min.txt", "wt");
    H = fopen("max.txt", "wt");
    R = fopen("ruta.txt", "wt");
    D = fopen("departe.txt", "wt");
    L = fopen("drum_lung.txt", "wt");
    father = malloc(1000* sizeof(int));
    p=calloc(1000, sizeof(int*));
    for (i=0; i<1000; i++)
        p[i]=calloc(1000, sizeof(int));
    loc = calloc(1000, sizeof(char*));
    for (i=0; i<1000; i++)
        loc[i]=calloc(40, sizeof(char));
        v=calloc(1000, sizeof(int*));
    for (i=0; i<1000; i++)
        v[i]=calloc(1000, sizeof(int));
    while(fgets(file, 20, f))
    {
        file[strlen(file) - 1] = '\0';
        g = fopen(file, "rt");
        x = -1;
        y = -1;
        while(fgets(spot, 40, g))
        {
           x = Add(&n, loc, spot, &costx);
            if (x != -1 && y!= -1)
            {
                p[x][y] = costx-costy;
                p[y][x] = costx-costy;
                v[x][y] = 1;
                v[y][x] = 1;
                if (costx - costy > max)
                {max = costx - costy;
                 Mx = x;
                 My = y;
                }
                if (costx - costy < min)
                {
                    min = costx - costy;
                    mx = x;
                    my = y;
                }
            }
        y = x;
        costy = costx;
        }
        fclose(g);
    }
    printf("\nNumarul de statii: %d\n", n);
    fclose(f);
    fprintf(K, "%s-%s %d\n", loc[mx], loc[my], min);
    fprintf(H, "%s-%s %d\n", loc[Mx], loc[My], max);

    for(i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            s = s+p[i][j];
            if (p[i][j] == 0)
            {
                p[i][j] = INT_MAX / 2;
            }
        }
    }
fprintf(T, "%d", s/2);

d = drum_minim(p, Add(&n, loc, "Bucuresti Nord", 0), &father, n);
fprintf(R, "Distanta de la orasul meu la Bucuresti Nord:%d\n", d[Add(&n, loc, "Cluj Napoca", 0)]);

  j = Add(&n, loc, "Cluj Napoca", 0);
fprintf(R, "%s ", loc[j]);
   do
    {
        j = father[j];
        fprintf(R, "<-%s ", loc[j]);
    } while (j != 0);


max=0;
    for (i = 0; i < n; i++)
        if (d[i] != INT_MAX / 2 && d[i] > max)
        {
            max = d[i];
            indepartat = i;
        }
fprintf(D, " Cea mai indepartata de bucuresti este %s\n", loc[indepartat]);

//cele mai indepartate 2 statii
max=0;
for(i=0;i<n;i++)
    {
        d=drum_minim(p,i,&father,n);
        for(j=0;j<n;j++)
        {
            if(d[j]!=INT_MAX/2 && d[j]>max)
            {
                max=d[j];
                P=i;
                U=j;
            }
        }
    }
fprintf(L, "Cele mai indepartate 2 statii sunt: %s - %s %d", loc[P],loc[U], max);

    return 0;
}
