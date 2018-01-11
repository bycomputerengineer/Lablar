#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *dosya1;
FILE *dosya2;

int sehirSayisi=0;///toplam sehir sayisi

struct sehir
{

    char isim[30];
    int yol[10]; ///ge�ilen yollar
    int toplam_maliyet ;
    int durum;
};

struct sehir sehirler[100];///sehir yap�s�nda sehirler dizisi olusturduk.

void dijkstra();
void gelismis_yazdir();

int main()
{
    dosya1=fopen("sehir kod.txt","r");///okuma
    if(dosya1==NULL)
    {
        printf("dosya1 okunamadi..");
        exit (0);///dosya kapama-a��lmazsa

    }
    char gereksiz[50];

    fgets(gereksiz, 50, dosya1);///ilk satiri atlamak i�in
    for(sehirSayisi=0; !feof(dosya1); sehirSayisi++) ///dosyadaki sehirler yap�ya atan�r-ayn� zamnada sehir say�s�n� sayd�r�yoruz.feof () dosyan�n sonun geldi�inde true de�eri d�nd�r�r
    {
        fscanf(dosya1,"%[^-]",sehirler[sehirSayisi].isim);///sat�r�n bas�ndan bu karaktere kadar oku.
        fgets(gereksiz, 50, dosya1);
    }
    int i;
    printf("%d\n",sehirSayisi);


    for(i=0; i<=sehirSayisi; i++)
    {

        printf("%s\n",sehirler[i].isim);

    }
    fclose(dosya1);


    printf("[1] - Bir sehirden tum sehirlere en kisa yolu hesapla.\n");
    printf("[2] - Bir sehirden diger bir sehire en kisa yolu hesapla.\n");
    printf("Seciminizi giriniz: ");
    int secim;
    scanf("%d", &secim);

    switch(secim){
        case 1: gelismis_yazdir(); break;
        //case 2: yazdir(); break;
    }


    return 0;
}

void dijkstra( int baslangicSehir )
{

    int komsuluk_Matrisi[sehirSayisi][sehirSayisi];
    dosya2=fopen("sehir mesafe.txt","r");///ikinci dosyadan mesafeyi matrise atamak i�in okuma;
    if(dosya2==NULL)
    {
        printf("dosya2 okunamadi..");
        exit (0);///dosya kapama-a��lmazsa
    }
    int j,k;
    for(j=0; j<sehirSayisi; j++)
    {
        for(k=0; k<sehirSayisi; k++)
        {
            komsuluk_Matrisi[j][k]=-1;
        }
    }
    int m,n;

    char sehir1[25];
    char sehir2[25];
    int mesafe;
    char mesafe_str[5];
    char gereksiz[50];
    fgets(gereksiz,50,dosya2);
    for(m=0; !feof(dosya2); m++)
    {
        fscanf(dosya2,"%[^-]",sehir1);
        fseek(dosya2,1,SEEK_CUR);///GECERL� KONUM 1 KARAKTER ATLAR..
        fscanf(dosya2,"%[^-]",sehir2);
        fseek(dosya2,1,SEEK_CUR);///GECERL� KONUM 1 KARAKTER ATLAR..
        fgets(mesafe_str,5,dosya2);
        mesafe=atoi(mesafe_str);///string de�eri int de�ere atar
        for(n=0; n<sehirSayisi; n++)
        {

            if(!strcmp(sehir1,sehirler[n].isim))
            {
                j=n;/// sehir1 kodu(n) j ye atad�k
            } //0 � 1 e d�nd�rmek i�in
            if(!strcmp(sehir2,sehirler[n].isim))
            {
                k=n;// sehir2 kodu(n) k ya atad�k
            } ///0 � 1 e d�nd�rmek i�in

        }
        komsuluk_Matrisi[j][k]=mesafe;
        komsuluk_Matrisi[k][j]=mesafe; ///iki �ehir aras� mesafeleri atad�k
    }
    fclose(dosya2);

    for(m=0; m<sehirSayisi; m++)
    {
        for(n=0; n<sehirSayisi; n++) ///matrisi ekrana yazd�rd�k
        {
            printf("%5d",komsuluk_Matrisi[m][n]);

        }
        printf("\n");
    }

    int sayac1, sayac2;
    for(sayac1 = 0; sayac1 < sehirSayisi; sayac1++){
        sehirler[sayac1].toplam_maliyet = 100000;
        for(sayac2 = 0; sayac2 < 10; sayac2++ ){
            sehirler[sayac1].yol[sayac2] = -1;
         }
    }

    for(m = 0; m <sehirSayisi; m++){
        sehirler[m].durum = 0;
    }

    m = baslangicSehir;
    sehirler[m].toplam_maliyet = 0;

    int l, c,son = 0, en_kucuk_maliyet;
    for(j=0; j<sehirSayisi; j++){///her sehir i�in komsuluk durumunu kontrol eder.ve yolu g�nceller.
        en_kucuk_maliyet=100000;
        for(c = 0; c < sehirSayisi; c++){
            if(sehirler[c].toplam_maliyet < en_kucuk_maliyet && sehirler[c].durum == 0 ){///sehirler aras�ndan toplam maliyeti en k�c�k olan ve daha once hic gidilmemis olan sehrin kodunu m e at�yoruz
                en_kucuk_maliyet = sehirler[c].toplam_maliyet;
                m = c;
            }
        }

    sehirler[m].durum = 1;

        for(n=0; n<sehirSayisi; n++) { ///komsuysa maliyeti de�i�tir
            if(komsuluk_Matrisi[m][n] != -1 && komsuluk_Matrisi[m][n] + sehirler[m].toplam_maliyet < sehirler[n].toplam_maliyet ){
                sehirler[n].toplam_maliyet= komsuluk_Matrisi[m][n] +sehirler[m].toplam_maliyet ;
                son = 0;
                for (l=0; l<10; l++){   ///yolu g�ncelledik
                    sehirler[n].yol[l]=sehirler[m].yol[l];
                    if(sehirler[m].yol[l] != -1 && sehirler[m].yol[l+1] == -1){
                        son = l+1;
                    }
                }
                sehirler[n].yol[son]=m;/// m sehrinin yolunu n sehrine kopyalad�ktan sonra bu sehirin �zerine bir de min  kendisini ekl�yoruzz
                    ///ALGOR�TMA..
            }

        }
    }

}


void gelismis_yazdir()
{

    char sehir[15];
    printf("Bulundugunuz sehirin ismini girniz: ");
    scanf("%s", sehir);
    int x, sayac;
    for(sayac = 0; sayac < sehirSayisi; sayac++){//sehir listesini tarayarak dosyadan okunan mesafenin ait oldugu sehirlerin kodlarini i ve j degiskenlerine atar
        if(!strcmp(sehir, sehirler[sayac].isim)){//birinci sehrin kodunu i ye atar
            x = sayac;
            break;
        }
    }

    dijkstra(x);

    int i, j;
    for(i = 0; i < sehirSayisi; i++){
        printf("\n%15s:%8d:", sehirler[i].isim, sehirler[i].toplam_maliyet);
        for(j = 0; j < 10; j++){
            if(sehirler[i].yol[j] != -1){
                printf(" %s->", sehirler[sehirler[i].yol[j]].isim);
            }
        }
    }
}
