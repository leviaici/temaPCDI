#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int cmp(const void *a, const void *b) {
    const int *A = *(const int **)a;
    const int *B = *(const int **)b;
    if(A[0] == B[0])
        return A[1] - B[1];
    else
        return A[0] - B[0];
}

void citireDate(FILE *fin, int ***a, int *numar) {
    fscanf(fin, "%d",numar);

    *a = (int**)malloc(*numar * sizeof(int*));
    for(int i = 0; i < *numar; i++)
        (*a)[i] = (int*)malloc(2 * sizeof(int));

    for(int i = 0; i < *numar; i++)
        fscanf(fin, "%d %d",&(*a)[i][0],&(*a)[i][1]);
}
void afisareDatePentruVerificare(FILE *fout, int **a, int numar) {
    fprintf(fout, "%d\n",numar);
    for(int i = 0; i < numar; i++, fprintf(fout,"\n"))
        fprintf(fout, "%d %d",a[i][0],a[i][1]);
}

float divideEtImpera(int **a, int sus, int jos, float *rezultat) {

    if(sus == jos)
        return *rezultat;

    float distanta = (a[sus][0] - a[jos][0]) * (a[sus][0] - a[jos][0]) + (a[sus][1] - a[jos][1]) * (a[sus][1] - a[jos][1]);
    distanta = sqrt(distanta);
//    printf("%d %d|||%.2f|||%d %d\n",a[sus][0],a[sus][1],distanta,a[jos][0],a[jos][1]);

    if(distanta < *rezultat && distanta != 0)
        *rezultat = distanta;

    int mijloc = (sus + jos) / 2;

    float sol1, sol2;
    sol1 = divideEtImpera(a, sus, mijloc, rezultat);
    sol2 = divideEtImpera(a, mijloc + 1, jos, rezultat);

    if(sol1 < sol2)
        return sol1;
    else return sol2;
}

int main()
{
    FILE *fin = fopen("in.txt","r");
    FILE *fout = fopen("out.txt","w");

    int numar, **a;

    citireDate(fin, &a, &numar);
    // afisareDatePentruVerificare(fout, a,numar);
    qsort(a,numar,sizeof(a[0]),cmp);
//    afisareDatePentruVerificare(fout, a, numar);
    float rezultat = 2147483647;
    rezultat = divideEtImpera(a, 0, numar - 1, &rezultat);
    fprintf(fout,"%.2f",rezultat);

    return 0;
}