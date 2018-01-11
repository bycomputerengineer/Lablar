#include <stdio.h>
#include <graphics.h>
#include <conio.h>

int main(){

    FILE *dosya;
    dosya = fopen("Sehir Koordinatlari.txt", "w");
    if(dosya == NULL){
        printf("Dosya Acilamadi!");
        exit(1);
    }

    initwindow(1000,800);

    int x;
    int y;

    readimagefile("harita.jpg", 0,0,800,800);

    int color=0;

    while(1){
        clearmouseclick(WM_LBUTTONDOWN);
        while(!ismouseclick(WM_LBUTTONDOWN)){ delay(200);}
        color = getpixel(mousex(), mousey());

        printf("\n%d", color);
    }

    fclose(dosya);

    _getch();
    closegraph();

    return 0;

}
