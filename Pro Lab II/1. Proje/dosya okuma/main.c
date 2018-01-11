#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*typedef struct{
    char isim[20];
    int yol[20];
    int toplam_maliyet;
}sehir;*/

int main()
{
    FILE *dosya;
    //sehir sehirler[50];

    dosya = fopen("sehir mesafe.txt", "r");
    if(dosya == NULL){
        printf("Dosya Acilamadi");
        exit(0);
    }

    int i;
    char sehir1[20];
    char sehir2[20];
    char gec[50];
    char mes[4];
    int mesafe;
    fgets(gec, 50, dosya);
    for(i = 0; !feof(dosya); i++){
        fscanf(dosya, "%[^-]", sehir1);
        fseek(dosya, 1, SEEK_CUR);
        fscanf(dosya, "%[^-]", sehir2);
        fseek(dosya, 1, SEEK_CUR);
        fgets(gec, 50, dosya);

        mesafe = atoi(gec);
        //strcpy(sehirler[i].isim, sehir);

        printf("\n%s-", sehir1);
        printf("%s-", sehir2);
        printf("%d", mesafe);
    }
    fclose(dosya);

    /*printf("\n\n");
    for(i = 0; i<22; i++){
        printf("\n%s", sehirler[i].isim);
    }*/




    return 0;
}
