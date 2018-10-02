#pragma once

#ifndef BONHOMME_H
#define BONHOMME_H

#endif // BONHOMME_H

#include "utils.h"
#include <Imagine/Graphics.h>
using namespace Imagine;



class Bonhomme{

    // LONGUEURS
    int R;  //rayon de la tête
    int t;  //longueur du tronc (sans les jambes)
    int c;  //longueur du corps (tronc+jambes)
    int b;  //longueur d'un demi-bras
    int j;  //longueur d'une demi-jambe
    int eps; //petit ecart entre deux pieds au repos

    // DIRECTION
    int direc_h;  //direction horizontale du regard (gauche/droite)
    int direc_v;  //direction verticale (haut/bas)

    // ETATS
    int dep_h;  //deplacements horizontaux
    int dep_v;  //deplacements verticaux
    int dep_poing_g;  //coups de poing gauche
    int dep_poing_d;  //coups de poing droit
    int dep_pied_g;    //coups de pied gauche
    int dep_pied_d;    //coups de pied droit
    int dep_chute;

    // ARTICULATIONS
    IntPoint2 corps[13]; //points des articulations dans l'ordre :
                    // tete, cou, epaule, coude_g, coude_d, main_g, main_d, cul, genou_g, genou_d, pied_g, pied_d, pos;

    //NativeBitmap Tete;   //si on veut rajouter une photo sur la tête - sait-on jamais

    // FONCTIONS PRIVEES
    // Fonctions d'état
    void change_etat1_h(int clavier, int a);    //horizontal
    void change_etat1_v(int clavier, int a);    //vertical
    void change_etat1_coup(int clavier, int a);  //coups de poing/pied
    void change_etat1(int clavier, int a);     //avec les touches q,s,d,z
    void change_etat2_h(int clavier, int a);    //horizontal
    void change_etat2_v(int clavier, int a);    //vertical
    void change_etat2_coup(int clavier, int a);  //coups de poing/pied
    void change_etat2(int clavier, int a);     //avec les touches k,l,m,o
    // Collisions coup de poing
    void collisionpg_tete(Bonhomme &B2);
    void collisionpg_corps(Bonhomme &B2);
    void collisionpg_jambe(Bonhomme &B2);
    // Collisions coup de pied
    void collisionpd_tete(Bonhomme &B2);
    void collisionpd_corps(Bonhomme &B2);
    void collisionpd_jambe(Bonhomme &B2);
    // Déplacements
    void deplace_saut();
    void deplace_boule(int a);
    void deplace_droite(int a);
    void deplace_gauche(int a);
    void deplace_pgd();
    void deplace_pgg();
    void deplace_pdg();
    void deplace_pdd();
    void deplace_chute(int a);
    // Affichage
    void traits(Color C) const;
    void cercles(Color C) const;

public :
    //Méthodes
    IntPoint2 get_coord(int i);     //on récupère les coordonnées du ième point
    void set_coord(int i, IntPoint2 P);
    void set_direc_v(int i);
    void set_direc_h(int i);
    int get_direc_h();
    void set_dep_h(int i);
    int get_dep_coup();
    void set_dep_v(int i);

    //Déplacements
    void change_etat(int clavier, int a, int i);
    void deplace(Bonhomme &vieux, int a);
    //Collisions coup de poing
    void collision_poing(Bonhomme& B2);
    //Collisions coup de pied
    void collision_pied(Bonhomme& B2);
    //Affichage
    void affiche(int i) const;
    void affiche(int i,Bonhomme vieux) const;
    // Points de vie
    int vie ;
    void affiche_vie(int i);
    void change_vie(int i);
    //Chutes
    void chute_plateforme(int a);

    Bonhomme(int a, int i);    //constructeur
};

