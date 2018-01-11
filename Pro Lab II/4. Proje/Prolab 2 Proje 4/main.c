#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int boyut;

double determinant(double matris[][boyut], int );

int main()
{
    double det;

    printf("Matrisin boyutunu giriniz: ");
    scanf("%d", &boyut);

    int i, j;
    double matris[boyut][boyut];

    for(i = 0; i < boyut; i++){
        for(j = 0; j < boyut; j++){
            printf("Matrisin %d satir %d sutun elemanini giriniz: ", i, j);
            scanf("%lf", &matris[i][j]);
        }
        printf("\n");
    }

    printf("\nDeterminant hesaplaniyor...\n");

    det = determinant(matris, boyut);

    printf("\nGirilen matrisin determinanti: %lf\n", det);

    return 0;
}

double determinant(double matris[][boyut],int n)
{
    double det;
    double temp[n-1][n-1];
    int i, j, k;
    int a, b;

    if(n == 1){
        det = matris[0][0];
    }
    else if(n == 2){
        det = (((matris[0][0])*(matris[1][1])) - ((matris[0][1])*(matris[1][0])));
        printf("\n%lf", det);
    }
    else{
        det = 0;
        for(k = 0; k < n; k++){
            for(i = 1; i < n; i++){
                for(j = 0; j < n; j++){
                    if(j < k){
                        temp[i-1][j] = matris[i][j];
                    }
                    else if(j > k){
                        temp[i-1][j-1] = matris[i][j];
                    }
                }
            }
            for(a = 0; a < n-1; a++){
                for(b = 0; b < n-1; b++){
                    printf("%lf", temp[a][b]);
                }
                printf("\n");
            }
            boyut--;
            det += (matris[0][k] * (pow((-1), (k+2))) * determinant(temp, n-1));
            boyut++;
            printf("\n%lf\n", det);
        }
    }
    return det;
}




























