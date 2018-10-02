#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

// Taille fenêtre
const int W=50;
const int H=30;


//======================================
// Structure point



const int droite = 0;
const int bas = 1;
const int gauche = 2;
const int haut = 3;
const IntPoint2 dir[4] = {{1,0},{0,1},{-1,0},{0,-1}};

struct Dir{
    int t[4];
};

double distance(IntPoint2 P, IntPoint2 Q);
double dist_droite(IntPoint2 P1, IntPoint2 P2, IntPoint2 P3);
//Distance entre P1 et (P2,P3)



//======================================
// Gestion du clavier

int Clavier();
