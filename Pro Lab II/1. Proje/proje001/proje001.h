#define MESAFE_HESAPLA
#ifdef MESAFE_HESAPLA

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>


struct sehir{
    char isim[15];
    int toplam_maliyet;
    int yol[20];
    int durum;
    int x;
    int y;
};

struct Nokta{
    int x;
    int y;
};

int sehir_sayisi = 0;
struct sehir sehirler[50];
struct Nokta nokta;
int matris[81][81];


void gelismis_yazdir(int);
void yazdir(int, int);
void dijikstra(int);
int control();


#endif
