#include "utils.h"

//======================================
// Structure point




//======================================
// Gestion du clavier

int Clavier() {
        Event e;
        do {
                getEvent(0,e);
                if (e.type==EVT_KEY_ON)
                        return e.key;
        } while (e.type!=EVT_NONE);
        return 0;
}

double distance(IntPoint2 P, IntPoint2 Q){
    return sqrt(pow(P.x()-Q.x(),2)+pow(P.y()-Q.y(),2));
}

double dist_droite(IntPoint2 P1, IntPoint2 P2, IntPoint2 P3){
    //Distance entre la droite (P1 P2) et le point P3
    double denom=1+pow((P2.y()-P1.y())/(0.00001+P2.x()-P1.x()),2);
    denom=sqrt(denom);
    double num=std::abs(-( (P2.y()-P1.y())*P3.x()/(0.00001+P2.x()-P1.x()) )+ P3.y() - P2.y() + ( P2.x()*(P2.y()-P1.y())/(0.00001+P2.x()-P1.x()) ));
    return num/denom;
}
