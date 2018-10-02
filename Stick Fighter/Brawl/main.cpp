// Imagine++ project
// Project:  Brawl
// Marius Fouquerand & Marie Heurtevent

#include "utils.h"
#include "bonhomme.h"
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <iostream>
using namespace std;

void affiche_vie(Bonhomme& B1, Bonhomme &B2){
    B1.affiche_vie(1);
    B2.affiche_vie(2);
}
void change_vie(Bonhomme& B1, Bonhomme& B2){
    B1.change_vie(1);
    B2.change_vie(2);
}
void change_etat_2j(Bonhomme& B1, Bonhomme& B2, int clavier, int a){
    int c=clavier;
    B1.change_etat(c,a,1);
    B2.change_etat(c,a,2);
}
void change_etat_auto(Bonhomme&B1, Bonhomme& B2, int a){
    srand(time(NULL));
    int p1 = B2.get_coord(12).x();
    int p2 = B1.get_coord(12).x();
    int d=abs(p1-p2);
    int clavier;
    int p;
//    if ((p1>=p2)&&(B2.get_direc_h()!=2)){
//            traits(WHITE);
//            cercles(WHITE);
//            for (int i=3; i<12; i++)
//                corps[i].x()=2*corps[12].x()-corps[i].x();
//            direc_h=0;
//            B2.set_direc_h(2);
//    }
//    if ((p2>p1)&&(B2.get_direc_h()!=0)){
//            for (int i=3; i<12; i++)
//                corps[i].x()=2*corps[12].x()-corps[i].x();
//            direc_h=0;
//            B2.affiche(2,B2_v);
//            B2.set_direc_h(0);
//    }
//    p = int(rand()%10);
//    //if ((p==0)&&(B1.get_dep_coup()==1))
//    if (p==0)
//        clavier = 'o';
//    if (((p==1)||(p==2))&&((p1>=p2+a) && (p1<=(W-6)*a) && (p1>=6*a)))
//        clavier = 'k';
//    //if ((p==3)&&(B1.get_dep_coup()==1))
//    if (p==3)
//        clavier = 'l';
//    if (((p==4)||(p==5))&&((p1<=p2-a) && (p1<=(W-6)*a) && (p1>=6*a)))
//        clavier = 'm';
//    if ((p==6)&&(d<5*a))
//        clavier = ',';
//    if ((p==7)&&(d<5*a))
//        clavier = ';';
//    if ((p==8)&&(d<5*a))
//        clavier = ':';
//    if ((p==9)&&(d<5*a))
//        clavier = '!';
    p=int(rand()%6);
    switch (p) {
    case 1 :
        clavier = '!';
        break;
    case 2 :
        clavier = ':';
        break;
    case 3 :
        clavier = ';';
        break;
    case 0 :
        clavier = ',';
        break;
    }
    int q = int(rand()%4);
    if (q==0)
        clavier='l';
    if ((q==1)&&(B1.get_dep_coup()==1))
        clavier='o';
    int r=int(rand()%3);
    if ((p1>=p2+a) && (p1<=(W-6)*a) && (p1>=6*a)){
        switch (r){
        case 0 :
            clavier='k';
            break;
        }
    }
    if ((p1<=p2-a) && (p1<=(W-6)*a) && (p1>=6*a) ){
        if (r==1)
            clavier='m';
    }

    B2.change_etat(clavier, a,2);

}
void change_etat_1j(Bonhomme& B1, Bonhomme& B2, int clavier, int a){
    int c=clavier;
    B1.change_etat(c,a,1);
    change_etat_auto(B1,B2,a);
}
void collision(Bonhomme& B1, Bonhomme& B2){
    B1.collision_poing(B2);
    B2.collision_poing(B1);
    B1.collision_pied(B2);
    B2.collision_pied(B1);
}
void deplace(Bonhomme& B1, Bonhomme&B2,Bonhomme& B1_v, Bonhomme&B2_v, int a){
    B1.deplace(B1_v,a);
    B2.deplace(B2_v,a);
}
void affiche(Bonhomme& B1, Bonhomme& B2,Bonhomme& B1_v, Bonhomme& B2_v){
    noRefreshBegin();
    B1.affiche(1,B1_v);
    B2.affiche(2,B2_v);
    noRefreshEnd();
}
void end(Bonhomme& B1, Bonhomme& B2, int a, int i){
    drawString((W-15)*a/2,H*a/2-40,"Game Over",BLACK,40,0,false,true);
    if (B1.vie<5){
        B1.vie=0;
        B1.change_vie(1);
        if (i==2)
            drawString((W-10)*a/2,H*a/2+10,"GREEN WINS",GREEN,20,0,false,true);
        if (i==1)
            drawString((W-10)*a/2,H*a/2+10,"YOU LOSE",GREEN,20,0,false,true);
    }
    if (B2.vie<5){
        B2.vie=0;
        B2.change_vie(2);
        if (i==2)
            drawString((W-8)*a/2,H*a/2,"RED WINS",RED,20,0,false,true);
        if (i==1)
            drawString((W-8)*a/2,H*a/2,"YOU WIN",RED,20,0,false,true);
    }
    milliSleep(1000);
}
void chute(Bonhomme &B1, Bonhomme &B2, int a){
    B1.chute_plateforme(a);
    B2.chute_plateforme(a);
}
NativeBitmap load_fond_4(){
    int b,c;
    byte* rgb;
    loadColorImage(srcPath("Fond-4.png"),rgb,b,c);
    NativeBitmap Fond(b,c);
    Fond.setColorImage(0,0,rgb,b,c);
    delete[] rgb;
    return Fond;
}
NativeBitmap load_fond_5(){
    int b,c;
    byte* rgb;
    loadColorImage(srcPath("Fond-5.png"),rgb,b,c);
    NativeBitmap Fond(b,c);
    Fond.setColorImage(0,0,rgb,b,c);
    delete[] rgb;
    return Fond;
}
NativeBitmap load_fond_6(){
    int b,c;
    byte* rgb;
    loadColorImage(srcPath("Fond-6.jpg"),rgb,b,c);
    NativeBitmap Fond(b,c);
    Fond.setColorImage(0,0,rgb,b,c);
    delete[] rgb;
    return Fond;
}
NativeBitmap load_fond_7(){
    int b,c;
    byte* rgb;
    loadColorImage(srcPath("Fond-7.png"),rgb,b,c);
    NativeBitmap Fond(b,c);
    Fond.setColorImage(0,0,rgb,b,c);
    delete[] rgb;
    return Fond;
}
NativeBitmap load_menu(){
    int b,c;
    byte* rgb;
    loadColorImage(srcPath("Menu.png"),rgb,b,c);
    NativeBitmap Fond(b,c);
    Fond.setColorImage(0,0,rgb,b,c);
    delete[] rgb;
    return Fond;
}
NativeBitmap load_how(){
    int b,c;
    byte* rgb;
    loadColorImage(srcPath("How-to-play.png"),rgb,b,c);
    NativeBitmap Fond(b,c);
    Fond.setColorImage(0,0,rgb,b,c);
    delete[] rgb;
    return Fond;
}
NativeBitmap load_players(){
    int b,c;
    byte* rgb;
    loadColorImage(srcPath("Nb-players.png"),rgb,b,c);
    NativeBitmap Fond(b,c);
    Fond.setColorImage(0,0,rgb,b,c);
    delete[] rgb;
    return Fond;
}
NativeBitmap load_world(){
    int b,c;
    byte* rgb;
    loadColorImage(srcPath("Select-menu.png"),rgb,b,c);
    NativeBitmap Fond(b,c);
    Fond.setColorImage(0,0,rgb,b,c);
    delete[] rgb;
    return Fond;
}
void affiche_image(NativeBitmap Image,int x, int y, double r){
    putNativeBitmap(x,y,Image,false,r);
}
void jeu_2j(int a, int i){
    NativeBitmap Fond;
    if (i==6)
        Fond = load_fond_6();
    if (i==4)
        Fond = load_fond_4();
    if (i==5)
        Fond = load_fond_5();
    if (i==7)
        Fond = load_fond_7();
    affiche_image(Fond,0,0,0.85*a/20.);

    //1er joueur
    Bonhomme B1(a,1);
    Bonhomme B1_v(a,1);
    B1.affiche(1);

    //2eme joueur
    Bonhomme B2(a,2);
    Bonhomme B2_v(a,2);
    B2.affiche(2);

    drawString((W/2-5*a/20.)*a,H*a/3,"FIGHT !",MAGENTA,40,false,false,true);
    milliSleep(2000);

    affiche_vie(B1,B2);
    while ((B1.vie>0)&&(B2.vie>0)){
        int c=Clavier();
        milliSleep(5);
        change_etat_2j(B1,B2,c,a);
        collision(B1,B2);
        deplace(B1,B2,B1_v,B2_v,a);
        chute(B1,B2,a);
        noRefreshBegin();
        affiche_image(Fond,0,0,0.85*a/20.);
        change_vie(B1,B2);
        affiche(B1,B2,B1_v,B2_v);
        noRefreshEnd();
    }
    milliSleep(10);
    end(B1,B2,a,2);
    affiche_image(Fond,0,0,0.85*a/20.);
}
void jeu_1j(int a, int i){
    NativeBitmap Fond;
    if (i==6)
        Fond = load_fond_6();
    if (i==4)
        Fond = load_fond_4();
    if (i==5)
        Fond = load_fond_5();
    if (i==7)
        Fond = load_fond_7();
    affiche_image(Fond,0,0,0.85*a/20.);

    //1er joueur
    Bonhomme B1(a,1);
    Bonhomme B1_v(a,1);
    B1.affiche(1);

    //2eme joueur
    Bonhomme B2(a,2);
    Bonhomme B2_v(a,2);
    B2.affiche(2);

    drawString((W/2-5*a/20.)*a,H*a/3,"FIGHT !",MAGENTA,40*a/20.,false,false,true);
    milliSleep(2000);

    affiche_vie(B1,B2);
    while ((B1.vie>0)&&(B2.vie>0)){
        int c=Clavier();
        milliSleep(5);
        change_etat_1j(B1,B2,c,a);
        collision(B1,B2);
        deplace(B1,B2,B1_v,B2_v,a);
        chute(B1,B2,a);
        noRefreshBegin();
        affiche_image(Fond,0,0,0.85*a/20.);
        change_vie(B1,B2);
        affiche(B1,B2,B1_v,B2_v);
        noRefreshEnd();
    }
    milliSleep(10);
    end(B1,B2,a,1);
    affiche_image(Fond,0,0,0.85*a/20.);
}


int Menuf(int a){
    int x, y;
    getMouse(x,y);
    int y1 = a*H/3;
    int dy = 2*a*H/9;
    if (y>y1 && y< y1+dy)
        return 1;
    if (y>y1+dy && y< y1+2*dy)
        return 2;
    if (y>y1+2*dy && y< y1+3*dy)
        return 3;
    return 0;
}
int combien_de_joueurs(int a, NativeBitmap im){
    affiche_image(im,0,-45*a/20.,0.49*a/20.);
    int x1=int(W*a/2);
    int x,y;
    bool choix1, choix2;
    int j=0;
    getMouse(x,y);
    choix2 = (x>x1);
    choix1 = (x<x1) ;
    if (choix2)
        j=2;
    if (choix1)
        j=1;
    milliSleep(10);
    return j ;
}
int world(int a, NativeBitmap im){
    affiche_image(im,0,-45*a/20.,0.49*a/20.);
    int x1=W*a/2;
    int y1=H*a/2;
    int x,y;
    bool choix1, choix2, choix3, choix4;
    int j=0;
    getMouse(x,y);
    choix1 = ((x<x1) && (y<y1)) ;
    choix2 = ((x<x1) && (y>y1)) ;
    choix3 = ((x>x1) && (y<y1)) ;
    choix4 = ((x>x1) && (y>y1)) ;

    if (choix3)
        j=4;
    if (choix1)
        j=7;
    if (choix2)
        j=5;
    if (choix4)
        j=6;
    milliSleep(10);
    return j ;
}
void regles(int a, int j){
    if (j==2){
        drawString(2*a,H*a/3,"Joueur 1 :",RED,20,0,false,true);
        drawString(2*a,(H*a/3)+50,"dÃ©placements avec ZQSD",BLACK,15,0,false,true);
        drawString(2*a,(H*a/3)+100,"coups de poing gauche/droit avec C/V",BLACK,15,0,false,true);
        drawString(2*a,(H*a/3)+150,"coups de pied gauche/droit avec W/X",BLACK,15,0,false,true);
        drawString((W/2+2)*a,H*a/3,"Joueur 2 :",GREEN,20,0,false,true);
        drawString((W/2+2)*a,(H*a/3)+50,"dÃ©placements avec OKLM",BLACK,15,0,false,true);
        drawString((W/2+2)*a,(H*a/3)+100,"coups de poing gauche/droit avec :/!",BLACK,15,0,false,true);
        drawString((W/2+2)*a,(H*a/3)+150,"coups de pied gauche/droit avec ,/;",BLACK,15,0,false,true);
    }
    if (j==1){
        drawString((W/2-10)*a,H*a/3,"Vous Ãªtes le rouge :",RED,20,0,false,true);
        drawString((W/2-10)*a,(H*a/3)+50,"dÃ©placements avec ZQSD",BLACK,15,0,false,true);
        drawString((W/2-10)*a,(H*a/3)+100,"coups de poing gauche/droit avec C/V",BLACK,15,0,false,true);
        drawString((W/2-10)*a,(H*a/3)+150,"coups de pied gauche/droit avec W/X",BLACK,15,0,false,true);
    }
}
bool rejouer(int a){
    drawString((W/2-11*a/20.)*a ,H*a/4,"Play  again ? ",BLACK,50*a/20.,0,false,true);
    int x1=int(W*a/3);
    int y1=H*a/2;
    int x2=int(2*W*a/3);
    int y2=(H/2)*a;
    int r=4*a;

    drawString(x2-(r/2),y2+(r/4),"No",MAGENTA,40*a/20.,0,false,true);
    drawString(x1-(r/2),y1+(r/4),"Yes",MAGENTA,40*a/20.,0,false,true);
    int x,y;
    bool choix1, choix2;
    bool test;
    getMouse(x,y);
    choix2 = ((x-x2)*(x-x2)+(y-y2)*(y-y2)<=r*r);
    choix1 = ((x-x1)*(x-x1)+(y-y1)*(y-y1)<=r*r) ;
    if (choix2)
        test=false;
    if (choix1)
        test=true;
    milliSleep(10);

    fillRect(0,0,W*a,H*a,WHITE);
    return test;
}
int main()
{
    int a=14;
    NativeBitmap Menu = load_menu();
    NativeBitmap How = load_how();
    NativeBitmap Players = load_players();
    NativeBitmap World = load_world();

    openWindow(W*a,H*a);
    bool test =true;
    while (test){
        affiche_image(Menu,0,-45*a/20.,0.49*a/20);
        int menu = Menuf(a);

        int j;

        if (menu==1){
            bool rejoue = true;
            j=combien_de_joueurs(a,Players);
            int w=world(a, World);
            while (rejoue){
                if (j==2){
                    jeu_2j(a,w);
                }
                if (j==1){
                    jeu_1j(a,w);
                }
                if (j==0){
                    drawString((W/2-7)*a,H*a/2,"Try Again",CYAN,50);
                    milliSleep(1000);
                    fillRect(0,0,W*a,H*a,WHITE);
                }
                rejoue=rejouer(a);
            }

        }
        if (menu==2){
            affiche_image(How, 0,-45*a/20.,0.49*a/20.);
            click();
            test = true;
        }
        if (menu==3)
            test=false;
    }
    endGraphics();



    return 0;
}

