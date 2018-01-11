#include <graphics.h>
#include <math.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <conio.h>

void pentool();
void brushtool();
void erasertool();
void texttool();
void paintbuckettool();
void lupatool();
int  choosecolor(int);
int  clearwoll();

void linetool();
void threeangle();
void fourangle();
void circule();

void save();

int choose(int, int);

int color = 0;
int x, y;

int main()
{
    initwindow(1500,800, "PAÝNT - ILYAS MAMMADOV");

    bar(2,29,1351,795);
    setfillstyle(1, LIGHTGRAY);
    bar(2,2,1496,25);
    bar(1355,29,1496,279);
    bar(1355,283,1496,510);
    bar(1355,514,1496,650);
    bar(1355,655,1496,795);
    outtextxy(1405,258,"Araclar");
    outtextxy(1405,490,"Sekiller");
    outtextxy(1405,630,"Renkler");
    outtextxy(1410,775,"Save");

    readimagefile("pentool.jpg", 1370,34,1420,84);
    readimagefile("brushtool.jpg", 1425,34,1475,84);
    readimagefile("erasertool.jpg", 1370,89,1420,139);
    readimagefile("texttool.jpg", 1425,89,1475,139);
    readimagefile("paintbuckettool.jpg", 1370,144,1420,194);
    readimagefile("lupatool.jpg", 1425,144,1475,194);
    readimagefile("colorchoosertool.jpg", 1425,199,1475,249);
    readimagefile("clear.jpg", 1370,199,1420,249);

    readimagefile("line.jpg", 1370,288,1420,338);
    readimagefile("threeangle.jpg", 1425,288,1475,338);
    readimagefile("fourangle.jpg", 1370,343,1420,393);
    readimagefile("circule.jpg", 1425,343,1475,393);

    readimagefile("colors.jpg", 1368,516,1478,625);

    readimagefile("save.jpg",1375,660,1480,770);

    /*for(int i = 1450; i < 1475; i++)
        for( int j = 519; j < 544; j++)
            putpixel(i,j,15);
    for(int i = 1424; i < 1449; i++)
        for( int j = 519; j < 544; j++)
            putpixel(i,j,14);
    for(int i = 1398; i < 1423; i++)
        for( int j = 519; j < 544; j++)
            putpixel(i,j,13);
    for(int i = 1371; i < 1397; i++)
        for( int j = 519; j < 544; j++)
            putpixel(i,j,12);
    for(int i = 1450; i < 1475; i++)
        for( int j = 545; j < 570; j++)
            putpixel(i,j,11);
    for(int i = 1424; i < 1449; i++)
        for( int j = 545; j < 570; j++)
            putpixel(i,j,10);
    for(int i = 1398; i < 1423; i++)
        for( int j = 545; j < 570; j++)
            putpixel(i,j,9);
    for(int i = 1371; i < 1397; i++)
        for( int j = 545; j < 570; j++)
            putpixel(i,j,8);
    for(int i = 1450; i < 1475; i++)
        for( int j = 571; j < 596; j++)
            putpixel(i,j,7);
    for(int i = 1424; i < 1449; i++)
        for( int j = 571; j < 596; j++)
            putpixel(i,j,6);
    for(int i = 1398; i < 1423; i++)
        for( int j = 571; j < 596; j++)
            putpixel(i,j,5);
    for(int i = 1371; i < 1397; i++)
        for( int j = 571; j < 596; j++)
            putpixel(i,j,4);
    for(int i = 1450; i < 1475; i++)
        for( int j = 597; j < 622; j++)
            putpixel(i,j,3);
    for(int i = 1424; i < 1449; i++)
        for( int j = 597; j < 622; j++)
            putpixel(i,j,2);
    for(int i = 1398; i < 1423; i++)
        for( int j = 597; j < 622; j++)
            putpixel(i,j,1);
    for(int i = 1371; i < 1397; i++)
        for( int j = 597; j < 622; j++)
            putpixel(i,j,0);*/

    bas:
    setcolor(0);

    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
        x = mousex();
        y = mousey();
    }
    if(choose(x, y) == 0)
        goto bas;
    goto bas;

    getch();
    closegraph();
    return 0;
}

void pentool()
{
    rectangle(1370,34,1420,84);
    int x1, x2, y1, y2;
    bas:
    x2 = NULL;
    y2 = NULL;
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){}
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
        if(choose(mousex(),mousey()) == 0)
            goto bas;
        else{
            if(mousex()>2 && mousey()>29 && mousex()< 1351 && mousey()< 795){
                x1 = mousex();
                y1 = mousey();
                line((x2==NULL) ? x1:x2, (y2==NULL) ? y1:y2, mousex(), mousey());
                x2 = x1;
                y2 = y1;

            }
        }
    }
    goto bas;
}

void brushtool()
{
    bas:
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){}
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
        if(choose(mousex(),mousey()) == 0)
            goto bas;
        else{
            if(mousex()>22 && mousey()>49 && mousex()< 1332 && mousey()< 775){
                /*for(int i = mousex()-20; i < mousex()+20; i++)
                    for( int j = mousey()-20; j < mousey()+20; j++)
                        putpixel(i,j,color);*/
                setfillstyle(1,color);
                pieslice(mousex(),mousey(),0,360,20);
            }
        }
    }
    goto bas;
}

void erasertool()
{
    bas:
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){}
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
        if(choose(mousex(),mousey()) == 0)
            goto bas;
        else{
            if(mousex()>52 && mousey()>79 && mousex()< 1302 && mousey()< 745)
                bar(mousex()-50, mousey()-50,mousex()+50,mousey()+50);
        }
    }
    goto bas;
}

void texttool()
{

}

void paintbuckettool()
{

}

void lupatool()
{

}

int clearwoll()
{
    setfillstyle(1,15);
    bar(2,29,1351,795);
    return 0;
}

void linetool()
{
    rectangle(1370,288,1420,338);
    int x1, x2, y1, y2;
    bas:
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
        x1 = mousex();
        y1 = mousey();
    }
    if(choose(x1, y1) == 0)
        goto bas;
    else{
        clearmouseclick(WM_LBUTTONDOWN);
        while(!ismouseclick(WM_LBUTTONDOWN)){
            x2 = mousex();
            y2 = mousey();
            setcolor(0);
            line(x1,y1, x2, y2);
            setcolor(15);
            delay(10);
            line(x1,y1,x2,y2);
        }
    if(choose(x2, y2) == 0)
        goto bas;
    else{
        setcolor(color);
        line(x1, y1, x2, y2);
    }
    }
    goto bas;
}

void threeangle()
{

}

void fourangle()
{
    int x1, x2, y1, y2;
    bas:
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
    x1 = mousex();
    y1 = mousey();
    }
    if(choose(x1, y1) == 0)
        goto bas;
    else{
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
    x2 = mousex();
    y2 = mousey();
    }
    if(choose(x2, y2) == 0)
        goto bas;
    else{
    rectangle(x1, y1, x2, y2);
    }
    }
    goto bas;
}

void circule()
{
    int x1, x2, y1, y2;
    bas:
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
    x1 = mousex();
    y1 = mousey();
    }
    if(choose(x1, y1) == 0)
        goto bas;
    else{
        clearmouseclick(WM_LBUTTONDOWN);
        while(!ismouseclick(WM_LBUTTONDOWN)){
            x2 = mousex();
            y2 = mousey();
        }
        if(choose(x2, y2) == 0)
            goto bas;
        else{
            circle(x1, y1,sqrt(pow((x2-x1),2)+pow((y2-y1),2)));
        }
    }
    goto bas;
}

int choosecolor()
{

    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN)){
    x = mousex();
    y = mousey();
    }

    if(1450 < x && x <1475 && y >519 && y < 544){
        setcolor(15);
        color = 15;
    }
    if(1424 < x && x <1449 && y >519 && y < 544){
        setcolor(14);
        color = 14;
    }
    if(1398 < x && x <1423 && y >519 && y < 544){
        setcolor(13);
        color = 13;
    }
    if(1371 < x && x <1397 && y >519 && y < 544){
        setcolor(12);
        color = 12;
    }
    if(1450 < x && x <1475 && y >545 && y < 570){
        setcolor(11);
        color = 11;
    }
    if(1424 < x && x <1449 && y >545 && y < 570){
        setcolor(10);
        color = 10;
    }
    if(1398 < x && x <1423 && y >545 && y < 570){
        setcolor(9);
        color = 9;
    }
    if(1371 < x && x <1397 && y >545 && y < 570){
        setcolor(8);
        color = 8;
    }
    if(1450 < x && x <1475 && y >571 && y < 596){
        setcolor(7);
        color = 7;
    }
    if(1424 < x && x <1449 && y >571 && y < 596){
        setcolor(6);
        color = 6;
    }
    if(1398 < x && x <1423 && y >571 && y < 596){
        setcolor(5);
        color = 5;
    }
    if(1371 < x && x <1397 && y >571 && y < 596){
        setcolor(4);
        color = 4;
    }
    if(1450 < x && x <1475 && y >597 && y < 622){
        setcolor(3);
        color = 3;
    }
    if(1424 < x && x <1449 && y >597 && y < 622){
        setcolor(2);
        color = 2;
    }
    if(1398 < x && x <1423 && y >597 && y < 622){
        setcolor(1);
        color = 1;
    }
    if(1371 < x && x <1397 && y >597 && y < 622){
        setcolor(0);
        color = 0;
    }
    return 0;
}

void save()
{

}

int choose(int cx, int cy)
{
    if(cx>1370 && cy>34 && cx<1420 && cy<84)
        pentool();
    else if(cx>1425 && cy>34 && cx<1475 && cy<84)
        brushtool();
    else if(cx>1370 && cy>89 && cx<1420 && cy<139)
        erasertool();
    else if(cx>1425 && cy>89 && cx<1475 && cy<139)
        texttool();
    else if(cx>1370 && cy>144 && cx<1420 && cy<194)
        paintbuckettool();
    else if(cx>1425 && cy>144 && cx<1475 && cy<194)
        lupatool();
    else if(cx>1425 && cy>199 && cx<1475 && cy<249)
        choosecolor();
    else if(cx>1370 && cy>199 && cx<1420 && cy<249)
        clearwoll();
    else if(cx>1370 && cy>288 && cx<1420 && cy<338)
        linetool();
    else if(cx>1425 && cy>288 && cx<1475 && cy<338)
        threeangle();
    else if(cx>1370 && cy>343 && cx<1420 && cy<393)
        fourangle();
    else if(cx>1425 && cy>343 && cx<1475 && cy<393)
        circule();
    else if(cx>1370 && cy>519 && cx<1475 && cy<622)
        choosecolor();
    else if(cx>1375 && xy>660 && cx<1480 && cy<770)
        save();
    else if(cx<2 && cy<29 && cx>1351 && cy>795)
        return 0;
    else
        return 1;
}
