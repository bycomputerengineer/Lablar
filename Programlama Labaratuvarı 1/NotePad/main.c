#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <conio/myconio.h>

char c;

int i=1;
int j=1;
int k;
char dosya_adi[100];

    FILE *dosya;

//girilen karakterlerden liste olusturmak icin kendi veri tipimizi tanýmlýyoruz
struct text {
    struct text *onceki;
    char ch;
    struct text *sonraki;
};

//bagýllisteyi kaybetmemek için basýný ve sonunu tutuyoruz;
struct text *bas = NULL;
struct text *son = NULL;
struct text *temp;
struct text *keeper;
struct text *ctrl;
struct text *ctrlbas;
struct text *ctrlson;

void add(char);
void del();
void print();
void up();
void down();
int left();
int right();
void open();
void save();
void freetext();
void editor();
void ctrlleft();
void ctrlright();
void ctrlv();

int main()
{
    textbackground(WHITE);
    clrscr();
    editor();
    return 0;
}

void add(char ch)
{
    struct text *yeni = (struct text*)malloc(sizeof(struct text));
    yeni->ch = ch;

    if(bas == NULL){ //listede eleman yoksa listeye ekleme
        bas = yeni;
        son = yeni;
        bas->onceki = NULL;
        son->sonraki = NULL;
        temp = bas;
    }
    /*else if((j == 1 && i == 1) || temp->sonraki != NULL){//basa ekleme
        yeni->onceki = NULL;
        yeni->sonraki = temp;
        temp->onceki = yeni;
        bas = yeni;
    }*/
    else if(temp->sonraki != NULL){//listede eleman varsa ve araya eklenmeye çalisiliyorsa
        yeni->onceki = temp;
        yeni->sonraki = temp->sonraki;
        temp->sonraki->onceki = yeni;
        temp->sonraki = yeni;
    }
    else{//listenin sonuna eklenme
        temp->sonraki = yeni;
        yeni->onceki = temp;
        son = yeni;
        son->sonraki = NULL;
    }
    temp = yeni;
}

void del()
{
    if(ctrlbas == NULL){
        if(bas ==  NULL){
            //liste bossa hic bir islem yapmasın.
        }
        else if(temp->sonraki != NULL && temp == bas ){ //bastan silme
            bas = temp->sonraki;
            bas->onceki = NULL;
            free(temp);
            temp = bas;
            print();
        }
        else if(temp == bas){ //listede tek eleman varsa silme islemi
            bas = NULL;
            son = NULL;
            free(temp);
        }
        else if(temp->sonraki != NULL){//aradan silme
            keeper = temp;
            temp = temp->onceki;
            temp->sonraki = keeper->sonraki;
            keeper->sonraki->onceki = temp;
            free(keeper);
            print();
        }
        else if(temp->sonraki == NULL){//sondan silme
            son = temp->onceki;
            son->sonraki = NULL;
            free(temp);
            temp = son;
        }
    }
    else{
        if(bas ==  NULL){
            //liste bossa hic bir islem yapmasın.
        }
        else if(temp->sonraki != NULL && temp == bas ){ //bastan silme
            bas = keeper->sonraki;
            bas->onceki = NULL;
            freetext();
            temp = bas;
            print();
        }
        else if(keeper->sonraki != NULL){//aradan silme
            temp->onceki->sonraki = keeper->sonraki;
            keeper->sonraki->onceki = temp->onceki;
            freetext();
            print();
        }
        else if(keeper->sonraki == NULL){//sondan silme
            son = temp->onceki;
            son->sonraki = NULL;
            freetext();
            temp = son;
        }
    }
}

void print()
{
    clrscr();
    for(keeper = bas; keeper != NULL; /*dongunun icinde kontrol edilmistir*/ ){
        printf("%c", keeper->ch);
        if(keeper->sonraki != NULL){
            keeper = keeper->sonraki;
        }
        else{
            break;
        }
    }
}

void up()
{
    k = 1;

    if(j == 1){//satir basindaysa
        if(i != 1){//birinci satirda degilse
            if((temp->onceki != NULL) ? temp->onceki->onceki != NULL : FALSE){//ustteki satir bos veya yarimsa veya doluysa
                if(temp->onceki->onceki->ch == '\n'){//ustteki satir bossa
                    i--;
                    if(temp->sonraki != NULL){//son satirda degilse
                        temp = temp->onceki;
                    }
                }
                else{//ustteki satir yarimsa veya doluysa (oluyor)
                    i--;
                    temp = temp->onceki->onceki;
                    for(;(temp->onceki != NULL) ? temp->onceki->ch != '\n' : FALSE; temp = temp->onceki){//ustteki satirin basina gelmedikce tempi bir oncekine tasi
                        //bos dongu
                    }
                }
            }
        }
    }

    else if((temp->sonraki != NULL) ? temp->sonraki->ch == '\n' : TRUE){//satirin sonundaysak
        if(i != 1){//ilk satirda degilse
            for(keeper = temp; (keeper->onceki != NULL) ? keeper->onceki->ch != '\n' : FALSE; keeper = keeper->onceki){//keeper'i bulundugu satirin ilk karakterine tasir
                //bos dongu
            }
            if((keeper->onceki != NULL) ? (keeper->onceki->onceki != NULL) ? keeper->onceki->onceki->ch != '\n' : keeper->onceki->ch != '\n': FALSE){//diger durumlar(ustteki satir doluysa veya yarimsa)
                if((keeper->onceki != NULL) ? keeper->onceki->onceki != NULL : FALSE){//ustteki satir bos degilse
                    for(keeper = keeper->onceki->onceki; (keeper->onceki != NULL) ? keeper->onceki->ch != '\n' : FALSE; keeper = keeper->onceki){//ustteki satirin basini keepere tuttur ve satirin uzunlugunu k'ya ata.
                        k++;
                    }
                }
                i--;
                if(k < j){
                    j = k;
                }
                for(k = 1 ; k < j; keeper = keeper->sonraki){//ustteki satirin karakterini sayar.
                    k++;
                }
                temp = keeper;
            }
            else{//ustteki satir bossa
                i--;
                j = 1;
                if(keeper->ch == '\n'){//bulundugu satir ve ustteki satir bossa:
                    temp = keeper;
                    if((keeper->onceki != NULL) ? keeper->onceki->ch == '\n' : FALSE){//ustteki satirin ustteki de bossa
                        temp = keeper->onceki;
                    }
                }
                else{//bulundugu satir bos degilse
                    temp = keeper->onceki;
                }
            }
        }
    }
    else{//satirin ortasindaysak
        for(keeper = temp; (keeper->onceki != NULL) ? keeper->onceki->ch != '\n' : FALSE; keeper = keeper->onceki){//keeper'a bulundugumuz satirin basini tutturuyoruz
            //bos dongu
        }
        temp = keeper;
        if((keeper->onceki != NULL) ? keeper->onceki->onceki != NULL : FALSE){//ustteki satir bos degilse
            for(keeper = keeper->onceki->onceki; (keeper->onceki != NULL) ? keeper->onceki->ch != '\n' : FALSE; keeper = keeper->onceki){//ustteki satirin basini keepere tuttur ve satirin uzunlugunu k'ya ata.
                k++;
            }
        }
        if(i != 1){//ilk satirda degilse
            if(k == 1){//ustteki satir bossa
                i--;
                j = 1;
                temp = temp->onceki->onceki;
            }
            else if(k < j){//diger durumlar (ustteki satir imlecin j'sinden once, sonra bitiyorsa veya satir doluysa.
                i--;
                j = k;
                temp = temp->onceki->onceki;;
            }
            else{
                i--;
                for(k = 1 ; k < j; keeper = keeper->sonraki){//ustteki satirin karakterini sayar.
                    k++;
                }
                temp = keeper;
            }
        }
    }
}

void down()
{
    for(keeper = temp; (keeper->sonraki != NULL) ? keeper->sonraki->ch != '\n' : FALSE; keeper = keeper->sonraki){//imlecin bulunduğu satirin sonunu bul
        //bos dongu
    }
    if(j == 1 && keeper->sonraki != NULL){//satirin basindaysa ve alttaki satir null degilse
        if(keeper->sonraki->ch == '\n' || (keeper->sonraki->sonraki != NULL) ? keeper->sonraki->sonraki->ch == '\n' : TRUE){//alttaki satir bossa
            i++;
            temp = keeper->sonraki;
        }
        else{//alttaki satir bos degilse
            i++;
            temp = keeper->sonraki->sonraki;
        }
    }
    else if((temp->sonraki != NULL) ? temp->sonraki->ch =='\n' : TRUE){//satirin sonudaysa ve alttjaki sati null degilse
        if((temp->sonraki != NULL) ? temp->sonraki->ch =='\n' || (temp->sonraki->sonraki != NULL) ? temp->sonraki->sonraki->ch == '\n' : TRUE : FALSE){//alttaki satir bossa
            i++;
            j = 1;
            temp = temp->sonraki;
        }
        else if((temp->sonraki != NULL) ? (keeper->sonraki->sonraki != NULL) ? keeper->sonraki->sonraki->ch != '\n' : FALSE : FALSE){//alttaki satir yarim veya doluysa
            k = 1;
            for(keeper = keeper->sonraki->sonraki; (keeper->sonraki != NULL) ? keeper->sonraki->ch != '\n' : FALSE; keeper = keeper->sonraki){//alttaki satirin nerede bittigini kontrol ediyor
                k++;
            }
            i++;
            if(k <= j){
                j = k+1;
                temp = keeper;
            }
            else{
                temp = temp->sonraki->sonraki;
                for(k = 1; k < j; k++){
                    temp = temp->sonraki;
                }
            }
        }
    }
    else if(keeper->sonraki != NULL){//diger durumlar satirin ortasindaysak ve alttaki satir null degilse
        if(keeper->sonraki->ch == '\n' && (keeper->sonraki->sonraki == NULL) ? TRUE : (keeper->sonraki->sonraki->ch == '\n') ){//alttaki satir bossa
            i++;
            j = 1;
            temp = keeper->sonraki;
        }
        else{//alttaki satir yarim veya doluysa
            k = 1;
            temp = keeper;
            for(keeper = keeper->sonraki->sonraki; (keeper->sonraki != NULL) ? keeper->sonraki->ch != '\n' : FALSE; keeper = keeper->sonraki){//alttaki satirin karakterini sayar
                k++;
            }
            i++;
            if(k <= j){//imlecin j'si alttaki satirin karakter sayisindan fazla ise
                j = k+1;
                temp = keeper;
            }
            else{//imlecin j'si alttaki satirin bitiminden ondeyse

                temp = temp->sonraki->sonraki;
                for(k = 1; k <j; k++){
                    temp = temp->sonraki;
                }
            }
        }
    }
}

int left()
{
    if(j > 1){//satirin basinda degilse
        j--;
        temp = temp->onceki;
        return 1;
    }
    else{//satirin basindaysa
        if((temp != NULL) ? temp->onceki == NULL : TRUE){//ustteki satir null'sa.
            //listenin basindaysa hicbirsey yapmasin(yani birinci satirin basindaysa)
        }
        else if(j == 1 && i > 1){//ustteki satir bossa veya karakter varsa
            if((temp->onceki->onceki == NULL) ? TRUE : temp->onceki->onceki->ch == '\n'){//ustteki satir bossa
                i--;
                temp = temp->onceki;
                return 1;
            }
            else{//ustteki satirda karakter varsa durumu(oluyor).
                i--;
                temp = temp->onceki;
                keeper = temp;
                for(j = 2; (keeper->onceki != NULL) ? keeper->onceki->ch != '\n' : FALSE; j++){//ustteki satirin kacinci karakterde bittigini bulmak icin
                    keeper = keeper->onceki;
                }
                return 1;
            }
        }
    }
}

int right()
{
    if(temp->sonraki != NULL){//imlec text'in sonunda degilse
        if((temp->sonraki != NULL) ? temp->sonraki->ch != '\n' : FALSE){//satir sonu degilse
            j++;
            temp = temp->sonraki;
            return 1;
        }
        else if((temp->sonraki != NULL) ? temp->sonraki->ch == '\n' : TRUE){//satir sonuysa
            if((temp->sonraki != NULL) ? (temp->sonraki->sonraki != NULL) ? temp->sonraki->sonraki->ch != '\n': FALSE : FALSE){//alttaki satir bos degilse
                i++;
                j=1;
                temp = temp->sonraki->sonraki;
                return 1;
            }
            else{//alttaki satir bossa
                i++;
                j=1;
                temp = temp->sonraki;
                return 1;
            }
        }
    }
}

void ctrlleft()
{
    struct text *yeni = (struct text*)malloc(sizeof(struct text));
    yeni->ch = temp->ch;

    if(left() == 1){//listeye arkadan ekleme
        textbackground(BLACK);
        gotoxy(j, i);
        putchar(temp->sonraki->ch);
        textbackground(WHITE);
        if(ctrlbas == NULL){ //listede eleman yoksa listeye ekleme
            ctrlbas = yeni;
            ctrlson = yeni;
            ctrlbas->onceki = NULL;
            ctrlson->sonraki = NULL;
            keeper = temp;
        }
        else{//listede eleman varsa
            ctrlbas->onceki = yeni;
            yeni->sonraki = ctrlbas;
            ctrlbas = yeni;
            ctrlbas->onceki = NULL;
        }
    }
}

void ctrlright()
{
    struct text *yeni = (struct text*)malloc(sizeof(struct text));

    if(right() == 1){//listeye bastan ekleme
        yeni->ch = temp->ch;
        textbackground(BLACK);
        gotoxy(--j, i);
        putchar(temp->ch);
        textbackground(WHITE);
        j++;
        if(ctrlbas == NULL){ //listede eleman yoksa listeye ekleme
            ctrlbas = yeni;
            ctrlson = yeni;
            ctrlbas->onceki = NULL;
            ctrlson->sonraki = NULL;
        }
        else{//listede eleman varsa
            ctrlson->sonraki = yeni;
            yeni->onceki = ctrlson;
            ctrlson = yeni;
            ctrlson->sonraki = NULL;

        }
    }
}

void ctrlv()
{
    if(bas == NULL){ //listede eleman yoksa listeye ekleme
        bas = ctrlbas;
        son = ctrlson;
        bas->onceki = NULL;
        son->sonraki = NULL;
    }
    /*else if((j == 1 && i == 1) || temp->sonraki != NULL){//basa ekleme
        yeni->onceki = NULL;
        yeni->sonraki = temp;
        temp->onceki = yeni;
        bas = yeni;
    }*/
    else if(temp->sonraki != NULL){//listede eleman varsa ve araya eklenmeye çalisiliyorsa
        temp->sonraki->onceki = ctrlson;
        ctrlson->sonraki = temp->sonraki;
        temp->sonraki = ctrlbas;
        ctrlbas->onceki = temp;
    }
    else{//listenin sonuna eklenme
        temp->sonraki = ctrlbas;
        ctrlbas->onceki = temp;
        son = ctrlson;
        son->sonraki = NULL;
    }
    print();
}

/*void save(){
    char dosya_adi[100];
    clrscr();
    printf("Dosya ismini giriniz: ");
    scanf("%s", dosya_adi);
    FILE * dosya;
    dosya = fopen(dosya_adi,"w+");
    free(dosya_adi);
    if(dosya == NULL){
        printf("Dosya acilamadi\n");
        _getch();
    }
    else {
        keeper = bas;
        while(keeper != NULL){
            fprintf(dosya,"%c",keeper->ch);
            if(keeper->sonraki != NULL){
                keeper = keeper->sonraki;
            }
            else{
                printf("Dosyaya kaydedildi...");
                fclose(dosya);
                break;
            }
        }
    }
}

void open(){
    char dosya_adi[100];
    clrscr();
    printf("Dosya ismini giriniz: ");
    scanf("%s", dosya_adi);

    FILE * dosya;
    dosya = fopen(dosya_adi,"r+");
    free(dosya_adi);
    freetext();
    if(dosya == NULL){
        printf("Dosya acilamadi\n");
        _getch();
    }
    else{
        while(!feof(dosya)){
            fscanf(dosya,"%c",&c);
            add(c);
        }

        print();
        fclose(dosya);
    }
}*/

void save()
{
    clrscr();
    if(dosya == NULL){
        printf("Dosya adini giriniz: ");
        gets(dosya_adi);
        dosya = fopen(dosya_adi, "w+");
        if(dosya == NULL){
            printf("\n Dosya acilamadi!");
        }
    }
    if(dosya != NULL){
        dosya = fopen(dosya_adi, "w+");
        if(dosya == NULL){
            printf("\n Dosya acilamadi!");
        }
        else{
            for(keeper = bas; keeper != NULL; ){
                //fprintf(dosya, "%c", keeper->ch);
                fputc(keeper->ch, dosya);
                if(keeper->sonraki == NULL){
                    break;
                }
                keeper = keeper->sonraki;
            }
            fclose(dosya);
            dosya = NULL;
            free(dosya_adi);
            printf("\nDosya Kaydedildi.");
            _getch();
        }
    }
    print();
    editor();
}

void open()
{
    clrscr();
    if(dosya == NULL){
        printf("Dosya adini giriniz: ");
        gets(dosya_adi);
        dosya = fopen(dosya_adi, "r+");
        if(dosya == NULL){
            printf("\n Dosya acilamadi!");
        }
    }
    else{
        printf("Acik dosya mevcut!\nMevcut dosyayi kaydetmeden yeni bir dosya acamazsiniz.");
        _getch();
        print();
        editor();
    }

    if(dosya != NULL){
        freetext();
        while(!feof(dosya)){
            c = fgetc(dosya);
            add(c);
        }
        print();
        editor();
    }
}

void freetext()
{
    if(temp != NULL){
        for(keeper = bas; keeper != NULL;){//listeyi bosalt
            free(keeper);
            if(keeper->sonraki != NULL){
                keeper = keeper->sonraki;
            }
            else{
                break;
            }
        }
    }
}

void editor()
{
    do{//klavyeden karakter oku ve bagil listeye ekle

        c = _getch();

        if(c == -32){//yon tuslarý kontrolu
            if(temp != NULL)
            switch(_getch()){
                case 72: up(); break;
                case 80: down(); break;
                case 75: left(); break;
                case 77: right(); break;
                case 115: ctrlleft(); break;
                case 116: ctrlright(); break;
            }
        }
        else if(c == 27){
            exit(1);
        }
        else if(c == 22){
            ctrlv();
        }
        else if(c == 16){
            print();
        }
        else if(c == 19){
            save();
        }
        else if(c == 15){
            open();
        }
        else if(c == 8){
            if(j>1){
                j--;
                gotoxy(j,i);
                printf(" ");
                del();
            }
            else if((temp->onceki != NULL) ? temp->onceki->ch != '\n' : FALSE){//satirin basindaysak ve ustteki satir bos degilse
                if((keeper->onceki != NULL) ? keeper->onceki->onceki != NULL : FALSE){//ustteki satir bos degilse
                    for(keeper = keeper->onceki->onceki; (keeper->onceki != NULL) ? keeper->onceki->ch != '\n' : FALSE; keeper = keeper->onceki){//ustteki satirin basini keepere tuttur ve satirin uzunlugunu k'ya ata.
                    k++;
                    }
                }
                j = k;
                i--;
                gotoxy(j,i);
                del();
            }
        }

        else if(c == 13){
            i++;
            j=1;
            gotoxy(j, i);
            add('\n');
            if(temp->sonraki != NULL){
                print();
            }
        }

        else{
            if(j>79){//Satir sonuysa
                i++;
                j=1;
                gotoxy(j,i);

                printf("%c", c);
                add('\n');
                add(c);
            }

            if(temp != NULL){
                if(temp->sonraki != NULL){//imlecin bulundugu yerden sonra listede eleman varsa, yani araya yazma.
                    add(c);
                    print();
                    j++;
                    gotoxy(j,i);
                }
            }
            if(temp != NULL || j == 1){//imlecin bulundugu yerden sonra listede eleman yoksa, yani sona yazma.
                if(j == 1 && i == 1){//temp null sa - ilk eleman ekleniyorsa
                    printf("%c", c);
                    j++;
                    add(c);
                }
                else if(temp->sonraki == NULL){//ilk eleman haric sona ekleniyorsa
                    printf("%c", c);
                    j++;
                    add(c);
                }
            }
        }

        //i ve j koordinatlarýný sað alt köþede bize gösterir.
        gotoxy(80, 30);
        printf("j: %3d", j);
        gotoxy(80, 31);
        printf("i: %3d", i);
        gotoxy(j, i);

    }while(1);
}


















