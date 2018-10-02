#include "utils.h"
#include "bonhomme.h"

#include <iostream>
using namespace std;
#include <cassert>


// Méthodes
IntPoint2 Bonhomme::get_coord(int i){
    return corps[i];
}
void Bonhomme::set_coord(int i, IntPoint2 P){
    corps[i]=P;
}
void Bonhomme::set_direc_v(int i){
    direc_v=i;
}
void Bonhomme::set_direc_h(int i){
    direc_h=i;
}

int Bonhomme::get_direc_h(){
    return direc_h;
}

void Bonhomme::set_dep_h(int i){
    dep_h=i;
}
int Bonhomme::get_dep_coup(){
    if ((dep_pied_d>0)||(dep_pied_g>0)||(dep_poing_d>0)||(dep_poing_g>0))
        return 1;
    return 0;
}
void Bonhomme::set_dep_v(int i){
    dep_v=i;
}


//Méthodes de déplacement
void Bonhomme::change_etat(int clavier, int a, int i){
    if (i==1)
        change_etat1(clavier,a);
    if (i==2)
        change_etat2(clavier,a);
}

void Bonhomme::change_etat1_h(int clavier, int a){
    if (clavier=='d'){  //DROITE
        dep_h=1;
        //Si on ne regarde pas déjà à droite, on doit tourner le corps
        if (direc_h!=0){
            traits(WHITE);
            cercles(WHITE);
            for (int i=3; i<12; i++)
                corps[i].x()=2*corps[12].x()-corps[i].x();
            direc_h=0;
        }
    }
    if (clavier=='q'){  //GAUCHE
        dep_h=-1;
        //Si on ne regarde pas déjà à gauche, on doit tourner le corps
        if (direc_h!=2){
            traits(WHITE);
            cercles(WHITE);
            for (int i=3; i<12; i++)
                corps[i].x()=2*corps[12].x()-corps[i].x();
            direc_h=2;
        }
    }
}
void Bonhomme::change_etat1_v(int clavier, int a){
    if ((clavier=='s')&&(corps[12].y()==H*a-2*a)&&(corps[0].y()==H*a-2*a-c-R)){ //BAS
        direc_v=1;
        dep_v=-1;
    }
    if ((clavier=='z')&&(corps[12].y()==H*a-2*a)&&(corps[0].y()==H*a-2*a-c-R)){ //HAUT
        direc_v=3;
        dep_v=1;
    }
}
void Bonhomme::change_etat1_coup(int clavier, int a){
    //COUP DE POING GAUCHE
    if ((clavier=='w')&&(corps[3].y()==corps[2].y()+3*t/6)){
        dep_poing_g=1;
    }
    //COUP DE POING DROIT
    if ((clavier=='x')&&(corps[4].y()==corps[2].y()+3*t/6)){
        dep_poing_d=1;
    }
    //COUP DE PIED GAUCHE
    if ((clavier=='c')&&(corps[10].y()==corps[12].y())&&(dep_pied_d==0)&&(dep_v>=0)){
        dep_pied_g=1;
    }
    //COUP DE PIED DROIT
    if ((clavier=='v')&&(corps[11].y()==corps[12].y())&&(dep_pied_g==0)&&(dep_v>=0)){
        dep_pied_d=1;
    }
}
void Bonhomme::change_etat1(int clavier, int a){
    change_etat1_h(clavier,a);
    change_etat1_v(clavier,a);
    change_etat1_coup(clavier,a);
}

void Bonhomme::change_etat2_h(int clavier, int a){
    if (clavier=='m'){  //DROITE
        dep_h=1;
        //Si on ne regarde pas déjà à droite, on doit tourner le corps
        if (direc_h!=0){
            traits(WHITE);
            cercles(WHITE);
            for (int i=3; i<12; i++)
                corps[i].x()=2*corps[12].x()-corps[i].x();
            direc_h=0;
        }
    }
    if (clavier=='k'){  //GAUCHE
        dep_h=-1;
        //Si on ne regarde pas déjà à gauche, on doit tourner le corps
        if (direc_h!=2){
            traits(WHITE);
            cercles(WHITE);
            for (int i=3; i<12; i++)
                corps[i].x()=2*corps[12].x()-corps[i].x();
            direc_h=2;
        }
    }
}
void Bonhomme::change_etat2_v(int clavier, int a){
    if ((clavier=='l')&&(corps[12].y()==H*a-2*a)&&(corps[0].y()==H*a-2*a-c-R)){ //BAS
        direc_v=1;
        dep_v=-1;
    }
    if ((clavier=='o')&&(corps[12].y()==H*a-2*a)&&(corps[0].y()==H*a-2*a-c-R)){ //HAUT
        direc_v=3;
        dep_v=1;
    }
}
void Bonhomme::change_etat2_coup(int clavier, int a){
    // COUP de POING GAUCHE
    if ((clavier==':')&&(corps[3].y()==corps[2].y()+3*t/6)){
        dep_poing_g=1;
    }
    // COUP de POING DROIT
    if (((clavier=='!') || (clavier == '=')) &&(corps[4].y()==corps[2].y()+3*t/6)){
        dep_poing_d=1;
    }
    //COUP de PIED GAUCHE
    if ((clavier==',')&&(corps[10].y()==corps[12].y())&&(dep_pied_d==0)){
        dep_pied_g=1;
    }
    //COUP de PIED DROIT
    if ((clavier==';')&&(corps[11].y()==corps[12].y())&&(dep_pied_g==0)){
        dep_pied_d=1;
    }
}
void Bonhomme::change_etat2(int clavier, int a){
    change_etat2_h(clavier,a);
    change_etat2_v(clavier, a);
    change_etat2_coup(clavier,a);
}

void Bonhomme::deplace_saut(){
    //SAUT
    int x=c-t;
    if ((1<=dep_v)&&(dep_v<=x)){
        dep_v+=2;
        for (int i=0; i<13; i++)
            corps[i]=corps[i]+4*dir[3];
    }
    if ((x+1<=dep_v)&&(dep_v<=2*x)){
        dep_v+=2;
        for (int i=0; i<13; i++)
            corps[i]=corps[i]+4*dir[1];
    }
    if (dep_v==2*x+1){
        dep_v=0;
    }
}
void Bonhomme::deplace_boule(int a){
    //BOULE
    if ((-1>=dep_v)&&(dep_v>=-97)){
        dep_v-=1;
        if (dep_v>=-13){
            for (int i=0; i<8; i++)
                corps[i]=corps[i]+(a/2)*dir[1];
        }
    }
    if ((-98>=dep_v)&&(dep_v>=-109)){
        dep_v-=2;
        for (int i=0; i<8; i++)
            corps[i]=corps[i]+a*dir[3];
    }
    if (dep_v==110){
        dep_v=0;
    }
}
void Bonhomme::deplace_droite(int a){
    //DEPLAC DROITE
    int x=2*a;
    if ((1<=dep_h)&&(dep_h<=x)){
        dep_h+=1;
        for (int i=0; i<13; i++)
            corps[i]=corps[i]+2*dir[0];
    }
    if (dep_h==x+1){
        dep_h=0;
    }
}
void Bonhomme::deplace_gauche(int a){
    //DEPLAC GAUCHE
    int x=2*a;
    if ((-1>=dep_h)&&(dep_h>=-x)){
        dep_h-=1;
        for (int i=0; i<13; i++)
            corps[i]=corps[i]+2*dir[2];
    }
    if (dep_h==-x-1){
        dep_h=0;
    }
}
void Bonhomme::deplace_pgd(){
    //COUP de POING DROITE
    if ((1<=dep_poing_d)&&(dep_poing_d<=t/2-3)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[4]=corps[4]+2*dir[0]+2*dir[3];
            corps[6]=corps[6]+4*dir[0];
        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[4]=corps[4]+2*dir[2]+2*dir[3];
            corps[6]=corps[6]+4*dir[2];
        }
        dep_poing_d+=2;
    }
    if ((t/2-2<=dep_poing_d)&&(dep_poing_d<=t-4)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[4]=corps[4]+2*dir[2]+2*dir[1];
            corps[6]=corps[6]+4*dir[2];

        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[4]=corps[4]+2*dir[0]+2*dir[1];
            corps[6]=corps[6]+4*dir[0];
        }
        dep_poing_d+=2;
    }
    if (dep_poing_d==t-3)
        dep_poing_d=0;
}
void Bonhomme::deplace_pgg(){
    //COUP de POING GAUCHE
    if ((1<=dep_poing_g)&&(dep_poing_g<=t/2-3)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[3]=corps[3]+2*dir[0]+2*dir[3];
            corps[5]=corps[5]+4*dir[0];
        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[3]=corps[3]+2*dir[2]+2*dir[3];
            corps[5]=corps[5]+4*dir[2];
        }
        dep_poing_g+=2;
    }
    if ((t/2-2<=dep_poing_g)&&(dep_poing_g<=t-4)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[3]=corps[3]+2*dir[2]+2*dir[1];
            corps[5]=corps[5]+4*dir[2];

        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[3]=corps[3]+2*dir[0]+2*dir[1];
            corps[5]=corps[5]+4*dir[0];
        }
        dep_poing_g+=2;
    }
    if (dep_poing_g==t-3)
        dep_poing_g=0;
}
void Bonhomme::deplace_pdg(){
    //COUP de PIED GAUCHE
    //Montée de jambe
    if ((1<=dep_pied_g)&&(dep_pied_g<=(c-t)/2)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[8]=corps[8]+2*dir[0]+2*dir[3];
            corps[10]=corps[10]+2*dir[0]+2*dir[3];
        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[8]=corps[8]+2*dir[2]+2*dir[3];
            corps[10]=corps[10]+2*dir[2]+2*dir[3];
        }
        dep_pied_g+=2;
    }
    if ((((c-t)/2+1)<=dep_pied_g)&&(dep_pied_g<=c-t)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[10]=corps[10]+4*dir[0]+2*dir[3];

        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[10]=corps[10]+4*dir[2]+2*dir[3];
        }
        dep_pied_g+=2;
    }
    //Descente
    if ((c-t+1<=dep_pied_g)&&(dep_pied_g<=3*(c-t)/2)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[10]=corps[10]+4*dir[2]+2*dir[1];

        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[10]=corps[10]+4*dir[0]+2*dir[1];
        }
        dep_pied_g+=2;
    }
    if ((3*(c-t)/2+1<=dep_pied_g)&&(dep_pied_g<=(c-t)*2)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[8]=corps[8]+2*dir[2]+2*dir[1];
            corps[10]=corps[10]+2*dir[2]+2*dir[1];
        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[8]=corps[8]+2*dir[0]+2*dir[1];
            corps[10]=corps[10]+2*dir[0]+2*dir[1];
        }
        dep_pied_g+=2;
    }
    if (dep_pied_g==2*(c-t)+1)
        dep_pied_g=0;
}
void Bonhomme::deplace_pdd(){
    //COUP de PIED DROIT
    //Montée de jambe
    if ((1<=dep_pied_d)&&(dep_pied_d<=(c-t)/2)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[9]=corps[9]+2*dir[0]+2*dir[3];
            corps[11]=corps[11]+2*dir[0]+2*dir[3];
        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[9]=corps[9]+2*dir[2]+2*dir[3];
            corps[11]=corps[11]+2*dir[2]+2*dir[3];
        }
        dep_pied_d+=2;
    }
    if ((((c-t)/2+1)<=dep_pied_d)&&(dep_pied_d<=c-t)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[11]=corps[11]+4*dir[0]+2*dir[3];

        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[11]=corps[11]+4*dir[2]+2*dir[3];
        }
        dep_pied_d+=2;
    }
    //Descente
    if ((c-t+1<=dep_pied_d)&&(dep_pied_d<=3*(c-t)/2)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[11]=corps[11]+4*dir[2]+2*dir[1];

        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[11]=corps[11]+4*dir[0]+2*dir[1];
        }
        dep_pied_d+=2;
    }
    if ((3*(c-t)/2+1<=dep_pied_d)&&(dep_pied_d<=(c-t)*2)){
        if (direc_h==0){
            //On regarde vers la droite
            corps[9]=corps[9]+2*dir[2]+2*dir[1];
            corps[11]=corps[11]+2*dir[2]+2*dir[1];
        }
        if (direc_h==2){
            //On regarde vers la gauche
            corps[9]=corps[9]+2*dir[0]+2*dir[1];
            corps[11]=corps[11]+2*dir[0]+2*dir[1];
        }
        dep_pied_d+=2;
    }
    if (dep_pied_d==2*(c-t)+1)
        dep_pied_d=0;
}
void Bonhomme::deplace_chute(int a){
    //CHUTE
    for (int i=0; i<13; i++)
        corps[i].y()+=a/5;
    dep_chute+=1;
    vie-=1;
}

void Bonhomme::deplace(Bonhomme &vieux, int a){
    for (int i=0; i<13; i++)
        vieux.set_coord(i,corps[i]);
    if(1<=dep_v)
        deplace_saut();
    if (-1>=dep_v)
        deplace_boule(a);
    if (1<=dep_h)
        deplace_droite(a);
    if (-1>=dep_h)
        deplace_gauche(a);
    if (1<=dep_poing_d)
        deplace_pgd();
    if (1<=dep_poing_g)
        deplace_pgg();
    if (1<=dep_pied_g)
        deplace_pdg();
    if (1<=dep_pied_d)
        deplace_pdd();
    if ((dep_chute!=0)&&(dep_chute<15*a))
        deplace_chute(a);
}


// Collisions coup de poing
void Bonhomme::collision_poing(Bonhomme &B2){
    collisionpg_corps(B2);
    collisionpg_jambe(B2);
    collisionpg_tete(B2);
}
void Bonhomme::collisionpg_tete(Bonhomme &B2){
    //B2 la victime de B1 : coup de poing gauche en pleine face
    if ((1<=dep_poing_g)&&(dep_poing_g<=t/2-3)){
        double dist=distance(corps[5],B2.get_coord(0));
        if (dist<R){
            B2.vie=B2.vie-10;
            if (direc_h==0){
                dep_h=-R;
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                dep_h=R;
                B2.set_dep_h(-1);
            }
            dep_poing_g=t-dep_poing_g-1;
        }
    }
    //B2 la victime de B1 : coup de poing droit en pleine face
    if ((1<=dep_poing_d)&&(dep_poing_d<=t/2-3)){
        double dist=distance(corps[6],B2.get_coord(0));
        if (dist<R){
            B2.vie=B2.vie-10;
            if (direc_h==0){
                dep_h=-R;
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                dep_h=R;
                B2.set_dep_h(-1);
            }
            dep_poing_d=t-dep_poing_d-1;
        }
    }
}
void Bonhomme::collisionpg_corps(Bonhomme &B2){
    //B2 la victime de B1 : coup de poing gauche en plein corps
    if ((1<=dep_poing_g)&&(dep_poing_g<=t/2-3)){
        double dist1=abs(corps[5].x()-B2.get_coord(0).x());
        if ((dist1<3) && (B2.get_coord(1).y()<=corps[5].y()) && (corps[5].y()<= B2.get_coord(7).y())){
            B2.vie=B2.vie-5;
            if (direc_h==0){
                dep_h=-R;
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                dep_h=R;
                B2.set_dep_h(-1);
            }
            dep_poing_g=t-dep_poing_g-1;
        }
    }
    //B2 la victime de B1 : coup de poing droit en plein corps
    if ((1<=dep_poing_d)&&(dep_poing_d<=t/2-3)){
        double dist1=abs(corps[6].x()-B2.get_coord(0).x());
        if ((dist1<3) && (B2.get_coord(1).y()<=corps[6].y()) && (corps[6].y()<= B2.get_coord(7).y())){
            B2.vie=B2.vie-5;
            if (direc_h==0){
                dep_h=-R;
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                dep_h=R;
                B2.set_dep_h(-1);
            }
            dep_poing_d=t-dep_poing_d-1;
        }
    }
}
void Bonhomme::collisionpg_jambe(Bonhomme &B2){
    //B2 la victime de B1 : coup de poing gauche en pleines jambes
    if ((1<=dep_poing_g)&&(dep_poing_g<=t/2-3)){
        double dist=min(dist_droite(B2.get_coord(7),B2.get_coord(8),corps[5]),dist_droite(B2.get_coord(7),B2.get_coord(8),corps[5]));
        if ((dist<2) && (B2.get_coord(7).y()<=corps[5].y()) && (corps[5].y()<= B2.get_coord(12).y())){
            B2.vie=B2.vie-5;
            if (direc_h==0){
                dep_h=-R;
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                dep_h=R;
                B2.set_dep_h(-1);
            }
            dep_poing_g=t-dep_poing_g-1;
        }
    }
    //B2 la victime de B1 : coup de poing droite en plein corps
    if ((1<=dep_poing_d)&&(dep_poing_d<=t/2-3)){
        double dist1=min(abs(corps[6].x()-B2.get_coord(9).x()),abs(corps[6].x()-B2.get_coord(8).x()));
        if ((dist1<2) && (B2.get_coord(7).y()<=corps[6].y()) && (corps[6].y()<= B2.get_coord(12).y())){
            B2.vie=B2.vie-5;
            if (direc_h==0){
                dep_h=-R;
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                dep_h=R;
                B2.set_dep_h(-1);
            }
            dep_poing_d=t-dep_poing_d-1;
        }
    }
}

//Collision coup de pied
void Bonhomme::collision_pied(Bonhomme &B2){
    collisionpd_corps(B2);
    collisionpd_jambe(B2);
    collisionpd_tete(B2);
}
void Bonhomme::collisionpd_tete(Bonhomme &B2){
    //B2 la victime de B1 : coup de pied gauche en pleine face
    if ((1<=dep_pied_g)&&(dep_pied_g<=c-t)){
        double dist=distance(corps[10],B2.get_coord(0));
        if (dist<R){
            B2.vie=B2.vie-10;
            if (direc_h==0){
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                B2.set_dep_h(-1);
            }
            dep_pied_g=2*(c-t)-dep_pied_g+2;
        }
    }
    //B2 la victime de B1 : coup de pied droit en pleine face
    if ((1<=dep_pied_d)&&(dep_pied_d<=c-t)){
        double dist=distance(corps[11],B2.get_coord(0));
        if (dist<R){
            B2.vie=B2.vie-10;
            if (direc_h==0){
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                B2.set_dep_h(-1);
            }
            dep_pied_d=2*(c-t)-dep_pied_d+2;
        }
    }
}
void Bonhomme::collisionpd_corps(Bonhomme &B2){
    //B2 la victime de B1 : coup de pied gauche en plein corps
    if ((1<=dep_pied_g)&&(dep_pied_g<=c-t)){
        double dist1=abs(corps[10].x()-B2.get_coord(0).x());
        if ((dist1<3) && (B2.get_coord(1).y()<=corps[10].y()) && (corps[10].y()<= B2.get_coord(7).y())){
            B2.vie=B2.vie-5;
            if (direc_h==0){
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                B2.set_dep_h(-1);
            }
            dep_pied_g=2*(c-t)-dep_pied_g+2;
        }
    }
    //B2 la victime de B1 : coup de pied droit en plein corps
    if ((1<=dep_pied_d)&&(dep_pied_d<=c-t)){
        double dist1=abs(corps[11].x()-B2.get_coord(0).x());
        if ((dist1<3) && (B2.get_coord(1).y()<=corps[11].y()) && (corps[11].y()<= B2.get_coord(7).y())){
            B2.vie=B2.vie-5;
            if (direc_h==0){
                dep_h=-R;
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                dep_h=R;
                B2.set_dep_h(-1);
            }
            dep_pied_d=2*(c-t)-dep_pied_d+2;
        }
    }
}
void Bonhomme::collisionpd_jambe(Bonhomme &B2){
    //B2 la victime de B1 : coup de pied gauche en pleines jambes
    if ((1<=dep_pied_g)&&(dep_pied_g<=c-t)){
        double dist_cuisses=min(dist_droite(B2.get_coord(7),B2.get_coord(8),corps[10]),dist_droite(B2.get_coord(7),B2.get_coord(9),corps[10]));
        double dist_tibia=min(dist_droite(B2.get_coord(8),B2.get_coord(10),corps[10]),dist_droite(B2.get_coord(9),B2.get_coord(11),corps[10]));
        double dist=min(dist_cuisses,dist_tibia);
        bool cuisse = ((B2.get_coord(7).y()<=corps[10].y()) && (corps[10].y()<= B2.get_coord(8).y()));
        bool tibia = ((B2.get_coord(8).y()<=corps[10].y()) && (corps[10].y()<= B2.get_coord(12).y()));
        bool zone ;
        if (dist==dist_cuisses) zone = cuisse;
        if (dist==dist_tibia) zone = tibia;
        if ((dist<1.1) && zone){
            B2.vie=B2.vie-5;
            if (direc_h==0){
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                B2.set_dep_h(-1);
            }
            dep_pied_g=2*(c-t)-dep_pied_g+2;
        }
    }
    //B2 la victime de B1 : coup de pied droit en pleines jambes
    if ((1<=dep_pied_d)&&(dep_pied_d<=c-t)){
        double dist_cuisses=min(dist_droite(B2.get_coord(7),B2.get_coord(8),corps[11]),dist_droite(B2.get_coord(7),B2.get_coord(9),corps[11]));
        double dist_tibia=min(dist_droite(B2.get_coord(8),B2.get_coord(10),corps[11]),dist_droite(B2.get_coord(9),B2.get_coord(11),corps[11]));
        double dist=min(dist_cuisses,dist_tibia);
        bool cuisse = ((B2.get_coord(7).y()<=corps[11].y()) && (corps[11].y()<= B2.get_coord(8).y()));
        bool tibia = ((B2.get_coord(8).y()<=corps[11].y()) && (corps[11].y()<= B2.get_coord(12).y()));
        bool zone ;
        if (dist==dist_cuisses) zone = cuisse;
        if (dist==dist_tibia) zone = tibia;
        if ((dist<1.1) && zone){
            B2.vie=B2.vie-5;
            if (direc_h==0){
                B2.set_dep_h(1);
            }
            if (direc_h==2){
                B2.set_dep_h(-1);
            }
            dep_pied_d=2*(c-t)-dep_pied_d+2;
        }
    }
}

//Méthodes d'affichages
void Bonhomme::traits(Color C)const{
    drawLine(corps[1],corps[7],C,2);
    drawLine(corps[7],corps[8],C,2);
    drawLine(corps[8],corps[10],C,2);
    drawLine(corps[7],corps[9],C,2);
    drawLine(corps[9],corps[11],C,2);
    drawLine(corps[2],corps[3],C,2);
    drawLine(corps[3],corps[5],C,2);
    drawLine(corps[2],corps[4],C,2);
    drawLine(corps[4],corps[6],C,2);
}
void Bonhomme::cercles(Color C)const{
    drawCircle(corps[0],R,C,4);
//    if (C==WHITE)
//        fillCircle(corps[0],R,C,2);
//    else
//        putNativeBitmap(corps[0].x()-R,corps[0].y()-R,Tete,false,2*R/215.);
    fillCircle(corps[5],2,C);
    fillCircle(corps[6],2,C);
    fillCircle(corps[10],2,C);
    fillCircle(corps[11],2,C);
}
void Bonhomme::affiche(int i)const{
    if (i==1){
        cercles(RED);
    }
    if (i==2){
        cercles(GREEN);
    }
    traits(BLACK);
}
void Bonhomme::affiche(int i, Bonhomme vieux)const{
    //On n'efface finalement pas le vieux bonhomme pour éviter des tâches blanches !
//    // On efface le vieux bonhomme
//    vieux.cercles(WHITE);
//    vieux.traits(WHITE);
    // On dessine le nouveau bonhomme
    if (i==1)
        cercles(RED);
    if (i==2)
        cercles(GREEN);
    traits(BLACK);
}

//Affichage de la vie
void Bonhomme::affiche_vie(int i){
    int x=R/1.5;
    if (i==1){
        fillRect(x,x,200,x,RED);
        drawRect(x,x,200,x,BLACK,4);
    }
    if (i==2){
        fillRect(W*x-9.5*x-200,x,200,x,GREEN);
        drawRect(W*x-9.5*x-200,x,200,x,BLACK,4);
    }
}
void Bonhomme::change_vie(int i){
    int x=R/1.5;
    if (vie>0){
        if (i==1){
            fillRect(x,x,vie*2,x,RED);
            fillRect(x+2*vie,x,200-vie*2,x,WHITE);
            drawRect(x,x,200,x,BLACK,4);
        }
        if (i==2){
            fillRect(W*x-9.5*x-200,x,vie*2,x,GREEN);
            fillRect(W*x-9.5*x-200+2*vie,x,200-vie*2,x,WHITE);
            drawRect(W*x-9.5*x-200,x,200,x,BLACK,4);
        }
    }
    if (vie==0){
        if (i==1){
            fillRect(x,x,200,x,WHITE);
            drawRect(x,x,200,x,BLACK,4);
        }
        if (i==2){
            fillRect(W*x-9.5*x-200,x,200,x,WHITE);
            drawRect(W*x-9.5*x-200,x,200,x,BLACK,4);
        }
    }
}

//Chutes
void Bonhomme::chute_plateforme(int a){
    int debut = 5*a;
    int fin = (W-5)*a;

    if (((corps[12].x()<=debut) || (corps[12].x()>=fin))){
        dep_chute=1;
    }
}

//Constructeur
Bonhomme::Bonhomme(int a, int i){

    R=1.8*a;
    t=6*a;
    c=12*a;
    b=2*a;
    j=3.5*a;
    eps=a/4;

    direc_v=0;   //ni vers le haut, ni vers le bas
    if (i==1)
        direc_h=0;    //regarde vers la droite initialement
    if (i==2)
        direc_h=2;    //regarde vers la gauche initialement
    dep_h=0;   //intialement on est immobile
    dep_v=0;
    dep_poing_d=0;
    dep_poing_g=0;
    dep_pied_d=0;
    dep_pied_g=0;
    dep_chute=0;

    vie=100;

    // ordre : tete, cou, epaules, coude_g, coude_d, main_g, main_d, cul, genou_g, genou_d, pied_g, pied_d, pos;
    corps[12]={W*a*i/3,H*a-2*a};   //pos
    IntPoint2 P{eps,0};
    corps[11]=corps[12]+P;  //pied_d
    P={-eps,0};
    corps[10]=corps[12]+P;  //pied_g
    P={0,-c+t};
    corps[7]=corps[12]+P;   //cul
    if (direc_h==0)
        P={int(eps+sqrt(pow(j,2)-pow((c-t)/2,2))),(-c+t)/2};
    if (direc_h==2)
        P={int(eps-sqrt(pow(j,2)-pow((c-t)/2,2))),(-c+t)/2};
    corps[9]=corps[12]+P;   //genou_d
    if (direc_h==0)
        P={int(-eps+sqrt(pow(j,2)-pow((c-t)/2,2))),(-c+t)/2};
    if (direc_h==2)
        P={int(-eps-sqrt(pow(j,2)-pow((c-t)/2,2))),(-c+t)/2};
    corps[8]=corps[12]+P;   //genou_g
    P={0,int(-c+t/3-0.5*a)};
    corps[2]=corps[12]+P;   //epaules
    P={0,-c};
    corps[1]=corps[12]+P;   //cou
    P={0,-c-R};
    corps[0]=corps[12]+P;   //tête
    if (direc_h==0)
        P={int(sqrt(pow(b,2)+pow(3*t/6,2))/2-eps),3*t/6};
    if (direc_h==2)
        P={int(-sqrt(pow(b,2)+pow(3*t/6,2))/2-eps),3*t/6};
    corps[3]=corps[2]+P;    //coude_g
    if (direc_h==0)
        P={int(sqrt(pow(b,2)+pow(3*t/6,2))/2+eps),3*t/6};
    if (direc_h==2)
        P={int(-sqrt(pow(b,2)+pow(3*t/6,2))/2+eps),3*t/6};
    corps[4]=corps[2]+P;    //coude_d
    if (direc_h==0)
        P={int(sqrt(pow(b,2)+pow(3*t/6,2))-eps),0};
    if (direc_h==2)
        P={int(-sqrt(pow(b,2)+pow(3*t/6,2))-eps),0};
    corps[5]=corps[2]+P;    //main_g
    if (direc_h==0)
        P={int(sqrt(pow(b,2)+pow(3*t/6,2))+eps),0};
    if (direc_h==2)
        P={int(-sqrt(pow(b,2)+pow(3*t/6,2))+eps),0};
    corps[6]=corps[2]+P;    //main_d


//    //Si on rajoute une photo au niveau de la tête
//    int b,c;
//    byte* rgb;
//    loadColorImage(srcPath("Baptiste.png"),rgb,b,c);
//    Tete = NativeBitmap(b,c);
//    Tete.setColorImage(0,0,rgb,b,c);

//    delete[] rgb;

}


