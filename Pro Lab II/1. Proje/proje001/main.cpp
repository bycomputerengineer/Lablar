#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

struct city{
    char name[15];
    int total_cost;
    int path[20];
    int status;
    int x;
    int y;
};

struct Dot{
    int x;
    int y;
};

int number_of_cities = 0;
struct city cities[50];
struct Dot dot;
int matrix[81][81];


void advanced_print(int);
void print(int, int);
void dijkstra(int);
int control();

int main()
{
    FILE *file1;
    FILE *file2;
    FILE *file3;

    file1 = fopen("city kod.txt", "r");
    if(file1 == NULL){
        printf("Dosya acilamadi!");
        exit(0);
    }

    char city[15];
    char pass[50];

    fgets(pass, 50, file1);
    int counter;
    for(counter = 0; !feof(file1); counter++){//city bilgilerini tutan listeye city namelerini atar ve city sayisini hesaplar
        fscanf(file1, "%[^-]", city);
        fseek(file1, 1, SEEK_CUR);
        fgets(pass, 50, file1);

        strcpy(cities[counter].name, city);
        number_of_cities++;
    }
    fclose(file1);

    file3 = fopen("city Koordinatlari.txt", "r");
    if(file3 == NULL){
        printf("Dosya Acilamadi!");
        exit(0);
    }

    int n;
    for(n = 0; n < number_of_cities; n++){
        fscanf(file3, "%d %d", &cities[n].x, &cities[n].y);
    }
    fclose(file3);


    int i, j;

    for(i = 0; i < number_of_cities; i++){//komsuluk matrixinin baslangicta butun elemanlarini -1 yapar
        for(j = 0; j < number_of_cities; j++){
            matrix[i][j] = -1;
            matrix[j][i] = -1;
        }
    }


    char city1[15];
    char city2[15];
    int distance;


    file2 = fopen("city distance.txt", "r");
    fgets(pass, 50, file2);
    while(!feof(file2)){//dosyadan komsu cities arasindaki distanceyi okuyarak matrixte karsilik gelen yerlere yerlestirir
        fscanf(file2, "%[^-]", city1);
        fseek(file2, 1, SEEK_CUR);
        fscanf(file2, "%[^-]", city2);
        fseek(file2, 1, SEEK_CUR);
        fgets(pass, 50, file2);

        distance = atoi(pass);
        //fscanf(file2, "%s %s %d", city1, city2, &distance);
        for(counter = 0; counter < number_of_cities; counter++){//city listesini tarayarak dosyadan okunan distancenin ait oldugu citiesin kodlarini i ve j degiskenlerine atar
            if(!strcmp(city1, cities[counter].name)){//birinci sehrin kodunu i ye atar
                i = counter;
            }
            if(!strcmp(city2, cities[counter].name)){//ikinci sehrin kodunu j ye atar
                j = counter;
            }
        }

        matrix[i][j] = distance;
        matrix[j][i] = distance;
    }
    fclose(file2);

    printf("\n");
    for(i = 0; i < number_of_cities; i++){//komsuluk matrixini ekrana yazar
        for(j = 0; j < number_of_cities; j++){
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }


    initwindow(1000, 800, "COST CALCULATE");

    bar(0,0,1000,800);
    readimagefile("button1.jpg", 810, 30+200, 990, 100+200);
    readimagefile("button2.jpg", 810, 110+200, 990, 180+200);
    readimagefile("map.jpg", 0,0,800,800);
    readimagefile("calculate.jpg", 850,200+200,950,274+200);
    int secim;
    int city_1;
    int city_2;


    while(1){
        clearmouseclick(WM_LBUTTONDOWN);
        while(!ismouseclick(WM_LBUTTONDOWN)){ delay(200); }
        dot.x = mousex();
        dot.y = mousey();

        if(dot.x > 810 && dot.x < 990 && dot.y > 30+200 && dot.y < 100+200){
            secim = 1;
            setfillstyle(1, 15);
            bar(810, 30+200, 990, 100+200);
            readimagefile("button1.jpg", 815, 35+200, 985, 95+200);
            break;
        }
        else if(dot.x > 810 && dot.x < 990 && dot.y > 110+200 && dot.y < 180+200){
            secim = 2;
            setfillstyle(1, 15);
            bar(810, 110+200, 990, 180+200);
            readimagefile("button2.jpg", 815, 115+200, 985, 175+200);
            break;
        }
    }

    switch(secim){
        case 1: {
            city_1 = control();
            break;
        }
        case 2:{
            city_1 = control();
            city_2 = control();
        break;
        }
    }

    while(1){
        clearmouseclick(WM_LBUTTONDOWN);
        while(!ismouseclick(WM_LBUTTONDOWN)){ delay(200); }
        dot.x = mousex();
        dot.y = mousey();

        if(dot.x > 850 && dot.x < 950 && dot.y > 200+200 && dot.y < 274+200){
            if(secim == 1){
                advanced_print(city_1);
                break;
            }
            else{
                print(city_1, city_2);
                break;
            }
        }

    }

    _getch();
    closegraph();

    return 0;
}

int control()
{
    int city;
    int color = -1;
    int status = 0;
    while(1){
        clearmouseclick(WM_LBUTTONDOWN);
        while(!ismouseclick(WM_LBUTTONDOWN)){ delay(200); }
        dot.x = mousex();
        dot.y = mousey();
        color = getpixel(dot.x, dot.y);

        switch(color){
            case 55536883: city = 0; status = 1; break;
            case 66039040: city = 1; status = 1; break;
            case 14: city = 2; status = 1; break;
            case 50462464: city = 3; status = 1; break;
            case 55748096: city = 4; status = 1; break;
            case 59713426: city = 5; status = 1; break;
            case 61501170: city = 6; status = 1; break;
            case 64203692: city = 7; status = 1; break;
            case 50393854: city = 8; status = 1; break;
            case 56426655: city = 9; status = 1; break;
            case 59295484: city = 10 ;status = 1; break;
            case 52763886: city = 11; status = 1; break;
            case 58818814: city = 12; status = 1; break;
            case 59506925: city = 13; status = 1; break;
            case 61166592: city = 14; status = 1; break;
            case 51252125: city = 15; status = 1; break;
            case 60356862: city = 16; status = 1; break;
            case 58612481: city = 17; status = 1; break;
            case 55737510: city = 18; status = 1; break;
            case 60978944: city = 19; status = 1; break;
            case 50372780: city = 20; status = 1; break;
            case 58308668: city = 21; status = 1; break;
        }
        if(status == 1){
            fillellipse(cities[city].x, cities[city].y, 5, 5);
            break;
        }
        else{
            outtextxy(850, 50, "Renkli citiesden");
            outtextxy(850, 50+15, "birini seciniz");
            delay(1500);
            bar(850,50,990,100);
        }
    }
    return city;
}


void advanced_print(int x)
{
    ////////////////////////EN KISA pathLARI printMA////////////////////////


    dijkstra(x);

    char buffer[10];
    int i, j, d;
    puts("\nShortest way to other cities from selected city: ");
    printf("\n%-15s:%-10s: Cities on path\n\n", "city", " T-Cost  ");

    for(i = 0; i < number_of_cities; i++){ // geçilen şehirleri ve maliyetleri yazdırır
        printf("%-15s:   %-7d:    ", cities[i].name, cities[i].total_cost);
        for(d = 0; cities[i].path[d] != -1; d++){} //kaç şehirden geçtiğini hesaplar
        for(j = 0; j < d; j++){ //geçilen şehirleri ve maliyeti ekrana yazdırır
            fillellipse(cities[cities[i].path[j]].x, cities[cities[i].path[j]].y, 5, 5);
            if(j > 0){
                line(cities[cities[i].path[j-1]].x, cities[cities[i].path[j-1]].y, cities[cities[i].path[j]].x, cities[cities[i].path[j]].y);
                printf("  -->>  ");
            }
            printf("%s",cities[cities[i].path[j]].name);
        }
        if(i != x){
            line(cities[cities[i].path[j-1]].x, cities[cities[i].path[j-1]].y, cities[i].x, cities[i].y);
            outtextxy(cities[i].x, cities[i].y, itoa(cities[i].total_cost, buffer, 10));
        }
        fillellipse(cities[i].x, cities[i].y, 5, 5);
        printf("\n");
    }

    printf("\n\n");
}

void print(int x, int y)
{

    dijkstra(x);

    char buffer[10];
    puts("\nShortest way to other city from selected city: ");
    printf("\n%-15s:%-10s: Cities on path\n\n", "city", " T-Cost  ");

    setcolor(15);
    int d, j;
    printf("%-15s:   %-7d:    ", cities[y].name, cities[y].total_cost);
    for(d = 0; cities[y].path[d] != -1; d++){} //kaç şehirden geçtiğini hesaplar
    for(j = 0; j < d; j++){ //geçilen şehirleri ve maliyeti ekrana yazdırır
        fillellipse(cities[cities[y].path[j]].x, cities[cities[y].path[j]].y, 5, 5);
        if(j > 0){
            line(cities[cities[y].path[j-1]].x, cities[cities[y].path[j-1]].y, cities[cities[y].path[j]].x, cities[cities[y].path[j]].y);
            printf("  -->>  ");
        }
        printf("%s",cities[cities[y].path[j]].name);

    }
    line(cities[cities[y].path[j-1]].x, cities[cities[y].path[j-1]].y, cities[y].x, cities[y].y);
    outtextxy(cities[y].x, cities[y].y, itoa(cities[y].total_cost, buffer, 10));
    fillellipse(cities[y].x, cities[y].y, 5, 5);
    printf("\n\n");




}

void dijkstra(int point)
{
    int a;
    int g;
    for(a = 0; a < number_of_cities; a++){ //ilk başt bütün maliyetleri sonsuz kabul ediyoruz.
        cities[a].total_cost = 1000000;
        for(g = 0; g < 20; g++){
            cities[a].path[g] = -1;
        }
    }

    cities[point].total_cost = 0; //baslaangic dotsından baslangic dotsina maliyet sifir olacağından başlangıç şehrine ulaşma maliyrtini sıfır olarak güncelliyoruz.

    int b;
    for(b = 0; b < number_of_cities; b++){
        cities[b].status = 0;
    }

    int c, d, e, f, h;
    int min_cost;
    int last_point = 0;

    for(d = 0; 1; d++){ //dijkstra Algoritması
        min_cost = 1000000;
        for(c = 0; c < number_of_cities; c++){ //Gidilecek bir sonraki şehri seçer
            if(cities[c].total_cost < min_cost && cities[c].status == 0){
                min_cost = cities[c].total_cost;
                point = c;
            }
        }
        //printf("\n%s", cities[point].name);
        cities[point].status = 1;
        for(e = 0; e < number_of_cities; e++){ //yeni maliyetin daha ucuz olması statusunda maliyeti ve pathu günceller
            if(matrix[point][e] != -1 && cities[point].total_cost + matrix[point][e] < cities[e].total_cost){
                //printf("\n%s -> %s -->>", cities[point].name, cities[e].name);
                //printf(" %d->", cities[e].total_cost);
                cities[e].total_cost = cities[point].total_cost + matrix[point][e];
                //printf("%d", cities[e].total_cost);

                last_point = 0;
                for(h = 0; h < 20; h++){ //pathu günceller
                    cities[e].path[h] = cities[point].path[h];
                    if(cities[point].path[h] != -1 && cities[point].path[h+1] == -1){
                        last_point = h+1;
                    }
                }
                cities[e].path[last_point] = point;
            }
        }
        for(f = 0; f < number_of_cities; f++){ //bütün cities dolaşıldıysa algoritmayı sonlandırır
            if(cities[f].status == 0){
                break;
            }
        }
        if(f == number_of_cities){
            break;
        }
    }
}
