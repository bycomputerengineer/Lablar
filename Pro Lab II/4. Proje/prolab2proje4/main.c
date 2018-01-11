#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <mysql-connector-c-6.1.10-winx64\include\mysql.h>

MYSQL *mysql;
MYSQL_RES *sonuc;
MYSQL_ROW satir;
MYSQL *baglan;
int sorgu;

void yeni_sefer();
void bilet_sat();
void yolcu_sorgula();
void ucusu_iptal_et();
void bileti_iptal_et();
void sefer_sorgula();
void doluluk_orani();
void sorgu_yazdir();
void SQL_CMD();

/*void kayitekle(){
    char sorgu_cumlesi[1000];
    char giris[20];
    while(1){
        strcpy(sorgu_cumlesi, "insert into sehirler(s_adi) values('");
        scanf("%s", giris);
        strcat(sorgu_cumlesi, "');");
        sorgu = mysql_query(mysql, sorgu_cumlesi);
    }
}*/

int main()
{

    mysql = mysql_init(NULL);

    if (!(mysql_real_connect(mysql, "localhost", "by.engineer", "AZNp5415893", "prolab_yeni", 3306, NULL, 0)))
    {
        fprintf(stderr, "%s\n", mysql_error(mysql));
        mysql_close(mysql);
        exit(1);
    }

    int secim;
    while(1){
        system("cls");
    printf("***************************** ANA MENU **********************************");
        printf("\n[1] - Yeni Sefer Tanimlama");
        printf("\n[2] - Bilet Stisi");
        printf("\n[3] - Yolcu Sorgulama");
        printf("\n[4] - Ucus Iptali");
        printf("\n[5] - Bilet Iptali");
        printf("\n[6] - Sefer Sorgulama");
        printf("\n[7] - Doluluk Orani En Fazla Olan Ucuslar");
        printf("\n[8] - SQL CMD");
        printf("\n[0] - Ckis");

        printf("\nLutfen bir islem seciniz: ");
        scanf("%d", &secim);

        switch(secim){
            case 1:{yeni_sefer(); break;}
            case 2:{bilet_sat(); break;}
            case 3:{yolcu_sorgula(); break;}
            case 4:{ucusu_iptal_et(); break;}
            case 5:{bileti_iptal_et(); break;}
            case 6:{sefer_sorgula(); break;}
            case 7:{doluluk_orani(); break;}
            case 8:{SQL_CMD(); break;}
            case 0:{mysql_close(mysql); return 0;}
            default:{printf("\nHatali secim!\n"); _getch();}
        }
    }
    return 0;
}

void yeni_sefer()
{
    char sorgu_cumlesi[1000];
    char girisler[4][20];

    system("cls");
    printf("***************************** SEFER OLUSTURMA **********************************");
    while(1){
        flag:
        printf("\nYeni seferin bilgilerini giriniz: \n");
        printf("\nKuyruk Numarasi: ");
        scanf("%s", girisler[0]);
        printf("Baslangic Noktasi: ");
        scanf("%s", girisler[1]);
        printf("Bitis Noktasi: ");
        scanf("%s", girisler[2]);
        printf("Ucus Tarihini 'YYYY-MM-DD HH:MM:SS' : ");
        scanf("%s", girisler[3]);

        strcpy(sorgu_cumlesi, "insert into seferler(ukn, k_no, i_no, zaman) values('");
        strcat(sorgu_cumlesi, girisler[0]);
        strcat(sorgu_cumlesi, "',");
        strcat(sorgu_cumlesi, girisler[1]);
        strcat(sorgu_cumlesi, ",");
        strcat(sorgu_cumlesi, girisler[2]);
        strcat(sorgu_cumlesi, ",'");
        strcat(sorgu_cumlesi, girisler[3]);
        strcat(sorgu_cumlesi, "');");

        sorgu = mysql_query(mysql, sorgu_cumlesi);
        if(sorgu == 1){
            system("cls");
            printf(mysql_error(mysql));
            goto flag;
        }
        else{
            printf("\nSefer basariyla eklenmistir");
        }
        printf("\n[1] - Ana Menu");
        printf("\n[0] - Yeni Sefer");
        if(_getch() == '1'){
            break;
        }
    }
}

void bilet_sat()
{
    char sorgu_cumlesi[1000];
    char girisler[5][20];
    char girisler2[5][100];
    char s_no[10];
    int secim, sayac1;
    int bilet_sayisi;

    system("cls");
    printf("***************************** BILET SATISI **********************************");
    printf("\nBaslangic Noktasi: ");
    scanf("%s", girisler[0]);
    printf("\nBitis Noktasi: ");
    scanf("%s", girisler[1]);
    printf("\nTarihi 'YYYY-MM-DD' formatında giriniz: ");
    scanf("%s", girisler[2]);
    printf("\nBilet Sayisi: ");
    scanf("%d", &bilet_sayisi);

    strcpy(sorgu_cumlesi, "select * from seferler where k_no = ");
    strcat(sorgu_cumlesi, girisler[0]);
    strcat(sorgu_cumlesi, " and i_no = ");
    strcat(sorgu_cumlesi, girisler[1]);
    strcat(sorgu_cumlesi, " and zaman = '");
    strcat(sorgu_cumlesi, girisler[2]);
    strcat(sorgu_cumlesi, "';");

    sorgu = mysql_query(mysql, sorgu_cumlesi);
    printf(mysql_error(mysql));
    if(sorgu == 0){
        sonuc = mysql_store_result(mysql);
        sorgu_yazdir();
    }
    mysql_free_result(sonuc);

    strcpy(sorgu_cumlesi, "select s1.s_no , s1.k_no, s1.i_no, s2.s_no, s2.k_no, s2.i_no from seferler s1, seferler s2 where s1.zaman = '");
    strcat(sorgu_cumlesi, girisler[2]);
    strcat(sorgu_cumlesi, "' and s2.zaman = '");
    strcat(sorgu_cumlesi, girisler[2]);
    strcat(sorgu_cumlesi, "' and s1.k_no = ");
    strcat(sorgu_cumlesi, girisler[0]);
    strcat(sorgu_cumlesi, " and s2.i_no = ");
    strcat(sorgu_cumlesi, girisler[1]);
    strcat(sorgu_cumlesi, " and s1.i_no = s2.k_no;");

    sorgu = mysql_query(mysql, sorgu_cumlesi);
    printf(mysql_error(mysql));
    if(sorgu == 0){
        sonuc = mysql_store_result(mysql);
        sorgu_yazdir();
    }
    mysql_free_result(sonuc);

    strcpy(sorgu_cumlesi, "select s1.s_no, s1.k_no, s1.i_no, s2.s_no, s2.k_no, s2.i_no, s3.s_no, s3.k_no, s3.i_no from seferler s1, seferler s2, seferler s3 where s1.zaman = '");
    strcat(sorgu_cumlesi, girisler[2]);
    strcat(sorgu_cumlesi, "' and s2.zaman = '");
    strcat(sorgu_cumlesi, girisler[2]);
    strcat(sorgu_cumlesi, "' and s3.zaman = '");
    strcat(sorgu_cumlesi, girisler[2]);
    strcat(sorgu_cumlesi, "' and s1.k_no = ");
    strcat(sorgu_cumlesi, girisler[0]);
    strcat(sorgu_cumlesi, " and s1.i_no = s2.k_no and s2.i_no = s3.k_no and s3.i_no = ");
    strcat(sorgu_cumlesi, girisler[1]);
    strcat(sorgu_cumlesi, ";");

    sorgu = mysql_query(mysql, sorgu_cumlesi);
    printf(mysql_error(mysql));
    if(sorgu == 0){
        sonuc = mysql_store_result(mysql);
        sorgu_yazdir();
    }
    mysql_free_result(sonuc);

    char tckn[bilet_sayisi][15];
    int sayac;
    for(sayac = 0; sayac < bilet_sayisi; sayac++){
        printf("\n%d'ci Yolcunun TCKN'ni giriniz: ", sayac+1);
        scanf("%s", tckn[sayac]);
    }

    for(sayac = 0; sayac < bilet_sayisi; sayac++){
        strcpy(sorgu_cumlesi, "select * from musteriler where tckn = '");
        strcat(sorgu_cumlesi, tckn[sayac]);
        strcat(sorgu_cumlesi, "';");
        sorgu = mysql_query(mysql, sorgu_cumlesi);
        sonuc = mysql_store_result(mysql);
        if((satir = mysql_fetch_row(sonuc)) == NULL){
            flag:
            printf("\nGirilen TCKN'na ait bilgileri giriniz: ");
            printf("\nYolcu Adi: ");
            scanf("%s", girisler2[0]);
            printf("\nYolcu Soyadi: ");
            scanf("%s", girisler2[1]);
            printf("\nYolcu Yasadigi Sehir: ");
            scanf("%s", girisler2[2]);
            printf("\nYolcu E-postasi: ");
            scanf("%s", girisler2[3]);
            printf("\nYolcu Adresi: ");
            scanf("%s", girisler2[4]);

            strcpy(sorgu_cumlesi, "insert into musteriler values('");
            strcat(sorgu_cumlesi, tckn[sayac]);
            strcat(sorgu_cumlesi, "','");
            strcat(sorgu_cumlesi, girisler2[0]);
            strcat(sorgu_cumlesi, "','");
            strcat(sorgu_cumlesi, girisler2[1]);
            strcat(sorgu_cumlesi, "',");
            strcat(sorgu_cumlesi, girisler2[2]);
            strcat(sorgu_cumlesi, ",'");
            strcat(sorgu_cumlesi, girisler2[3]);
            strcat(sorgu_cumlesi, "','");
            strcat(sorgu_cumlesi, girisler2[4]);
            strcat(sorgu_cumlesi, "');");

            sorgu = mysql_query(mysql, sorgu_cumlesi);
            if(sorgu == 1){
                printf("\nMusteriler tablosuna ekleme hatali!");
                printf(mysql_error(mysql));
                goto flag;
            }
            else{
                printf("\nMusteriler tablosuna ekleme basarili!");
            }
        }
        printf("\nUcusunuz aktarmali mi?");
        printf("\n[1] - Direkt");
        printf("\n[2] - Bir Aktarmali");
        printf("\n[3] - Ikı Aktarmali\n");
        scanf("%d", &secim);

        for(sayac1 = 1; sayac1 <=secim; sayac1++){
            printf("\n%d'ci Ucus icin sefer numarasini giriniz: ", sayac1);
            scanf("%s", s_no);

            strcpy(sorgu_cumlesi, "insert into biletler(s_no, tckn) values(");
            strcat(sorgu_cumlesi, s_no);
            strcat(sorgu_cumlesi, ",'");
            strcat(sorgu_cumlesi, tckn[sayac]);
            strcat(sorgu_cumlesi, "');");

            sorgu = mysql_query(mysql, sorgu_cumlesi);
            if(sorgu == 1){
                printf("\nYolcular tablosuna ekleme hatali!");
                printf(mysql_error(mysql));
            }
            else{
                printf("\nYolcular tablosuna ekleme basarili!");
            }
        }
    _getch();
    }
}

void yolcu_sorgula()
{
    char tckn[11];
    flag:
    system("cls");
    printf("***************************** YOLCU SORGULAMA **********************************");
    printf("\nYolcunun TCKN'sini giriniz: ");
    scanf("%s", tckn);

    char sorgu_cumlesi[1000];
    strcpy(sorgu_cumlesi, "select tckn, s.s_no, s.k_no, s.i_no, s.zaman  from biletler b, seferler s where s.s_no = b.s_no and tckn = '");
    strcat(sorgu_cumlesi, tckn);
    strcat(sorgu_cumlesi, "';");


    sorgu = mysql_query(mysql, sorgu_cumlesi);
    printf(mysql_error(mysql));
    if(sorgu == 0){
        sonuc = mysql_store_result(mysql);
        sorgu_yazdir();
    }
    mysql_free_result(sonuc);

    printf("\n[1] - Ana Menu");
    printf("\n[0] - Yeni Sorgu");
    if(_getch() == '0'){
        goto flag;
    }
}

void ucusu_iptal_et()
{

    char s_no[10];

    flag:
    system("cls");
    printf("***************************** UCUS IPTALI **********************************");
    sorgu = mysql_query(mysql, "select * from seferler");
    printf(mysql_error(mysql));
    sonuc = mysql_store_result(mysql);
    sorgu_yazdir();

    printf("\nIptal edilecek ucusun sefer numarasini giriniz: ");
    printf("\nSefer No: ");
    scanf("%s", s_no);

    char sorgu_cumlesi[1000];
    strcpy(sorgu_cumlesi, "delete from seferler where s_no = ");
    strcat(sorgu_cumlesi, s_no);
    strcat(sorgu_cumlesi, ";");

    sorgu = mysql_query(mysql, sorgu_cumlesi);
    if(sorgu == 1){
        printf(mysql_error(mysql));
        printf("\nYanlis sefer numarasi gridiniz tekrar deneyiniz\n");
        _getch();
        goto flag;
    }
    else{
        printf("\nSefer basariyla silinmistir!\n");
        printf("\n[1] - Ana Menu");
        printf("\n[2] - Yeni Silme Islemi\n");
        if(_getch() == '2'){
            goto flag;
        }
    }
}

void bileti_iptal_et()
{
    char b_no[11];
    char tckn[20];
    char sorgu_cumlesi[1000];
    flag:
    system("cls");
    printf("****************************** BILET IPTALI ***************************\n");

    printf("\nIptal Edilecek Bilet TCKN: ");
    scanf("%s", tckn);

    strcpy(sorgu_cumlesi, "select b.bilet_no, s.s_no, s.k_no, s.i_no, s.zaman from seferler s, biletler b where b.s_no = s.s_no and b.tckn = '");
    strcat(sorgu_cumlesi, tckn);
    strcat(sorgu_cumlesi, "';");
    sorgu = mysql_query(mysql, sorgu_cumlesi);
    sonuc = mysql_store_result(mysql);
    sorgu_yazdir();

    printf("\nIptal Edilecek Bilet No: ");
    scanf("%s", b_no);

    strcpy(sorgu_cumlesi, "delete from biletler where b_no = '");
    strcat(sorgu_cumlesi, b_no);

    sorgu = mysql_query(mysql, sorgu_cumlesi);
    if(sorgu == 0){
        printf("\nBilet iptali gerceklestirilmistir.");
        printf("\n[1] - Ana Menu");
        printf("\n[2] - Yeni Iptal Islemi\n");
        if(_getch() == '2'){
            goto flag;
        }
    }
}

void sefer_sorgula()
{
    char ukn[15];
    char tarih[15];
    char sorgu_cumlesi[1000];

    flag:
    system("cls");
    printf("************************************** SEFER SORGULAMA ***********************************************\n");
    sorgu = mysql_query(mysql, "select * from seferler");
    sonuc = mysql_store_result(mysql);
    sorgu_yazdir();

    printf("\nUcakKuyruk Numarasi: ");
    scanf("%s", ukn);
    printf("Sefer Tarhi: ");
    scanf("%s", tarih);


    strcpy(sorgu_cumlesi, "select * from musteriler where TCKN IN(select TCKN from yolcular where ukn = '");
    strcat(sorgu_cumlesi, ukn);
    strcat(sorgu_cumlesi, "' and tarih = '");
    strcat(sorgu_cumlesi, tarih);
    strcat(sorgu_cumlesi, "');");

    sorgu = mysql_query(mysql, sorgu_cumlesi);
    if(sorgu == 1){
        printf(mysql_error(mysql));
        printf("\nYanlis bilgiler gridiniz tekrar deneyiniz");
        _getch();
        goto flag;
    }
    else{
        sonuc = mysql_store_result(mysql);
        sorgu_yazdir();
        printf("\n[1] - Ana Menu");
        printf("\n[2] - Yeni Sorgu Islemi\n");
        if(_getch() == '2'){
            goto flag;
        }
    }
}

void doluluk_orani()
{
    system("cls");
    printf("***************************** DOLULUK ORANI **********************************");
    sorgu = mysql_query(mysql, "select sonuc.ukn, sonuc.tarih, toplam, kapasite, (toplam/kapasite)*100 as oran from ucaklar u, (select ukn,tarih, count(*) as toplam from yolcular group by ukn,tarih)as sonuc where sonuc.ukn=u.ukn group by sonuc.tarih,sonuc.ukn,oran order by oran  desc");
    printf(mysql_error(mysql));
    sonuc = mysql_store_result(mysql);
    sorgu_yazdir();

    _getch();
}

void sorgu_yazdir()
{
    int kolon_sayisi;
    kolon_sayisi = mysql_field_count(mysql);
    int sayac, sayac1;
    int sonuc_sayisi = mysql_num_rows(sonuc);
    printf("\n");
    for(sayac = 0; sayac < kolon_sayisi; sayac++){
        printf("+---------------------");
    }
    printf("+\n");
    for(sayac = 0;(satir = mysql_fetch_row(sonuc)) != NULL && sayac < sonuc_sayisi; sayac++){
        for(sayac1 = 0; sayac1 < kolon_sayisi; sayac1++){
            printf("| %-20s", satir[sayac1]);
        }
        printf("|\n");
    }
    for(sayac = 0; sayac < kolon_sayisi; sayac++){
        printf("+---------------------");
    }
    mysql_free_result(sonuc);
    printf("+\n");
}

void SQL_CMD()
{
    system("cls");
    printf("***************************** SQL TERMINAL **********************************");
    char sorgu_cumlesi[1000];
    char giris[1000];
    while(0 != strcmp(sorgu_cumlesi, "exit")){
        printf("\nSQL_CAMD >> ");
        gets(giris);
        strcpy(sorgu_cumlesi, giris);
        if(strcmp(sorgu_cumlesi, "clear") == 0){
            system("cls");
            continue;
        }
        sorgu = mysql_query(mysql, sorgu_cumlesi);
        //printf(mysql_error(mysql));
        printf("%d", mysql_errno(mysql));
        if(sorgu == 0){
            sonuc = mysql_store_result(mysql);
            if(sonuc != NULL){
                sorgu_yazdir();
                mysql_free_result(sonuc);
            }
        }
    }
}
