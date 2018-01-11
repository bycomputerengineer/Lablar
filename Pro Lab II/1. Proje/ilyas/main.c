#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

void gelismis_yazdir();
void yazdir();
void dijikstra(int);

struct sehir{
    char isim[15];
    int toplam_maliyet;
    int yol[20];
    int durum;
};

int sehir_sayisi = 0;
struct sehir sehirler[50];

int main()
{

    FILE *dosya1;

    dosya1 = fopen("sehir kod.txt", "r");
    if(dosya1 == NULL){
        printf("Dosya acilamadi!");
        exit(1);
    }

    char sehir[15];
    char gec[50];
    int mesafe;

    fgets(gec, 50, dosya1);
    int sayac;
    for(sayac = 0; !feof(dosya1); sayac++){//sehir bilgilerini tutan listeye sehir isimlerini atar ve sehir sayisini hesaplar
        fscanf(dosya1, "%[^-]", sehir);
        fseek(dosya1, 1, SEEK_CUR);
        fgets(gec, 50, dosya1);

        strcpy(sehirler[sayac].isim, sehir);
        sehir_sayisi++;
    }

    fclose(dosya1);

    printf("[1] - Bir sehirden tum sehirlere en kisa yolu hesapla.\n");
    printf("[2] - Bir sehirden diger bir sehire en kisa yolu hesapla.\n");
    printf("Seciminizi giriniz: ");
    int secim;
    scanf("%d", &secim);

    switch(secim){
        case 1: gelismis_yazdir(); break;
        case 2: yazdir(); break;
    }

    return 0;
}

void gelismis_yazdir()
{
    ////////////////////////EN KISA YOLLARI YAZDIRMA////////////////////////
    char sehir[15];
    printf("Bulundugunuz sehirin ismini girniz: ");
    scanf("%s", sehir);
    int x, sayac;
    for(sayac = 0; sayac < sehir_sayisi; sayac++){//sehir listesini tarayarak dosyadan okunan mesafenin ait oldugu sehirlerin kodlarini i ve j degiskenlerine atar
        if(!strcmp(sehir, sehirler[sayac].isim)){//birinci sehrin kodunu i ye atar
            x = sayac;
            break;
        }
    }

    dijikstra(x);

    int i, j, d;
    puts("\nSecilen sehirden diger sehire en kisa yol: ");
    printf("\n%-15s:%-10s: Gecilen Sehirler\n\n", "Sehir", "T-Maliyet");

    for(i = 0; i < sehir_sayisi; i++){ // geçilen şehirleri ve maliyetleri yazdırır
        printf("%-15s:   %-7d:    ", sehirler[i].isim, sehirler[i].toplam_maliyet);
        for(d = 0; sehirler[i].yol[d] != -1; d++){} //kaç şehirden geçtiğini hesaplar
        for(j = 0; j < d; j++){ //geçilen şehirleri ve maliyeti ekrana yazdırır
            if(j > 0){
                printf("  -->>  ");
            }
            printf("%s",sehirler[sehirler[i].yol[j]].isim);
        }
        printf("\n");
    }

    printf("\n\n");
}

void yazdir()
{
    int x,y, sayac;
    char sehir1[15];
    char sehir2[15];

    printf("\nNereden: ");
    scanf("%s", sehir1);
    printf("Nereye: ");
    scanf("%s", sehir2);

    for(sayac = 0; sayac < sehir_sayisi; sayac++){//sehir listesini tarayarak dosyadan okunan mesafenin ait oldugu sehirlerin kodlarini x ve y degiskenlerine atar
        if(!strcmp(sehir1, sehirler[sayac].isim)){//birinci sehrin kodunu x ye atar
            x = sayac;
        }
        if(!strcmp(sehir2, sehirler[sayac].isim)){//ikinci sehrin kodunu y ye atar
            y = sayac;
        }
    }

    dijikstra(x);

    puts("\nSecilen sehirden diger sehire en kisa yol: ");
    printf("\n%-15s:%-10s: Gecilen Sehirler\n\n", "Sehir", "T-Maliyet");

    int d, j;
    printf("%-15s:   %-7d:    ", sehirler[y].isim, sehirler[y].toplam_maliyet);
    for(d = 0; sehirler[y].yol[d] != -1; d++){} //kaç şehirden geçtiğini hesaplar
    for(j = 0; j < d; j++){ //geçilen şehirleri ve maliyeti ekrana yazdırır
        if(j > 0){
            printf("  -->>  ");
        }
        printf("%s",sehirler[sehirler[y].yol[j]].isim);
    }

    printf("\n\n");


}

void dijikstra(int point)
{

    int i, j;
    int matris[sehir_sayisi][sehir_sayisi];

    for(i = 0; i < sehir_sayisi; i++){//komsuluk matrisinin baslangicta butun elemanlarini -1 yapar
        for(j = i; j < sehir_sayisi; j++){
            matris[i][j] = -1;
            matris[j][i] = -1;
        }
    }


    char sehir1[15];
    char sehir2[15];
    char gec[50];
    int mesafe;
    int sayac;


    FILE *dosya2;
    dosya2 = fopen("sehir mesafe.txt", "r");
    fgets(gec, 50, dosya2);
    while(!feof(dosya2)){//dosyadan komsu sehirler arasindaki mesafeyi okuyarak matriste karsilik gelen yerlere yerlestirir
        fscanf(dosya2, "%s %s %d", sehir1, sehir2, &mesafe);
        for(sayac = 0; sayac < sehir_sayisi; sayac++){//sehir listesini tarayarak dosyadan okunan mesafenin ait oldugu sehirlerin kodlarini i ve j degiskenlerine atar
            if(!strcmp(sehir1, sehirler[sayac].isim)){//birinci sehrin kodunu i ye atar
                i = sayac;
            }
            if(!strcmp(sehir2, sehirler[sayac].isim)){//ikinci sehrin kodunu j ye atar
                j = sayac;
            }
        }

        matris[i][j] = mesafe;
        matris[j][i] = mesafe;
    }
    fclose(dosya2);

    printf("\n");
    for(i = 0; i < sehir_sayisi; i++){//komsuluk matrisini ekrana yazar
        for(j = 0; j < sehir_sayisi; j++){
            printf("%5d ", matris[i][j]);
        }
        printf("\n");
    }



    int a;
    int g;
    for(a = 0; a < sehir_sayisi; a++){ //ilk başt bütün maliyetleri sonsuz kabul ediyoruz.
        sehirler[a].toplam_maliyet = 1000000;
        for(g = 0; g < 20; g++){
            sehirler[a].yol[g] = -1;
        }
    }

    sehirler[point].toplam_maliyet = 0; //baslaangic noktasından baslangic noktasina maliyet sifir olacağından başlangıç şehrine ulaşma maliyrtini sıfır olarak güncelliyoruz.

    int b;
    for(b = 0; b < sehir_sayisi; b++){
        sehirler[b].durum = 0;
    }

    int c, d, e, f, h;
    int en_kucuk_maliyet;
    int yolun_sonu = 0;

    for(d = 0; 1; d++){ //Dijikstra Algoritması
        en_kucuk_maliyet = 1000000;
        for(c = 0; c < sehir_sayisi; c++){ //Gidilecek bir sonraki şehri seçer
            if(sehirler[c].toplam_maliyet < en_kucuk_maliyet && sehirler[c].durum == 0){
                en_kucuk_maliyet = sehirler[c].toplam_maliyet;
                point = c;
            }
        }
        //printf("\n%s", sehirler[point].isim);
        sehirler[point].durum = 1;
        for(e = 0; e < sehir_sayisi; e++){ //yeni maliyetin daha ucuz olması durumunda maliyeti ve yolu günceller
            if(matris[point][e] != -1 && sehirler[point].toplam_maliyet + matris[point][e] < sehirler[e].toplam_maliyet){
                //printf("\n%s -> %s -->>", sehirler[point].isim, sehirler[e].isim);
                //printf(" %d->", sehirler[e].toplam_maliyet);
                sehirler[e].toplam_maliyet = sehirler[point].toplam_maliyet + matris[point][e];
                //printf("%d", sehirler[e].toplam_maliyet);

                yolun_sonu = 0;
                for(h = 0; h < 20; h++){ //yolu günceller
                    sehirler[e].yol[h] = sehirler[point].yol[h];
                    if(sehirler[point].yol[h] != -1 && sehirler[point].yol[h+1] == -1){
                        yolun_sonu = h+1;
                    }
                }
                sehirler[e].yol[yolun_sonu] = point;
            }
        }
        for(f = 0; f < sehir_sayisi; f++){ //bütün sehirler dolaşıldıysa algoritmayı sonlandırır
            if(sehirler[f].durum == 0){
                break;
            }
        }
        if(f == sehir_sayisi){
            break;
        }
    }

}
