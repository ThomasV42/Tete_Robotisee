/**
 \file    Neck.cpp
 * Implémentation de la classe Neck
 \class Neck
 */
#include "Neck.h"

Neck::Neck() {
    servd = new ServoDyn(1);
    servm = new ServoDyn(2);
    servg = new ServoDyn(3);
}

Neck::~Neck() {

}

bool Neck::init() {

    if (!servd->init()) return false;
    if (!servm->init()) return false;
    if (!servg->init()) return false;
    /**/
    if (!servd->setVitesse(40)) return false;
    if (!servm->setVitesse(40)) return false;
    if (!servg->setVitesse(40)) return false;
    if (!servd->setAcceleration(20)) return false;
    if (!servm->setAcceleration(20)) return false;
    if (!servg->setAcceleration(20)) return false;
    if (!servd->setPosition(200)) return false;
    if (!servm->setPosition(180)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servg->action()) return false;
    /*
    int angled = 180, angleg = 180;
    cout << "angleDMin avant : " << angleDMin << endl;
    do {
        cout<<endl;
        if (!servd->setPosition(angled)) return false;
        if (!servg->setPosition(angleg)) return false;
        if (!servd->action()) return false;
        angled += 5;
        angleg -= 5;
        cout << "fin do, angle droite : " << dec << angled << " angle gauche : " << angleg << endl;
        cout<<endl;
        sleep(1);
    } while (!servd->getErreurForce());
    angleDMin = angled - 10;
    angleGMax = angleg +10;
    cout << "angleDMin : " << angleDMin << endl;
    cout<<endl;
    
    /**/
    return true;
}

bool Neck::Yes() {
    /**/
    if (!servd->setPosition(angleDMax)) return false;
    if (!servg->setPosition(angleGMax)) return false;
    if (!servg->action()) return false;

    if (!servd->setPosition(200)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servg->action()) return false;

    if (!servd->setPosition(180)) return false;
    if (!servg->setPosition(180)) return false;
    if (!servg->action()) return false;
    /**/
    if (!servd->setPosition(200)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servg->action()) return false;

    if (!servd->setPosition(angleDMax)) return false;
    if (!servg->setPosition(angleGMax)) return false;
    if (!servg->action()) return false;

    if (!servd->setPosition(200)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servg->action()) return false;

    /**/
    return true;
}

bool Neck::No() {
    /**/
    if (!servd->setPosition(200)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servm->setPosition(160)) return false;
    if (!servm->action()) return false;
    /**/
    if (!servd->setPosition(200)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servm->setPosition(200)) return false;
    if (!servm->action()) return false;
    /**/
    if (!servd->setPosition(200)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servm->setPosition(160)) return false;
    if (!servm->action()) return false;
    /**/
    if (!servd->setPosition(200)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servm->setPosition(180)) return false;
    if (!servm->action()) return false;
    /**/
    return true;
}

bool Neck::setUp() {
    /**/
    if (!servd->setPosition(angleDMax)) return false;
    if (!servg->setPosition(angleGMax)) return false;
    if (!servg->action()) return false;
    /**/
    return true;
}

bool Neck::setDown() {
    /**/
    if (!servd->setPosition(angleDMin)) return false;
    if (!servg->setPosition(angleGMin)) return false;
    if (!servg->action()) return false;
    /**/
    return true;
}

bool Neck::setLeft() {
    /**/
    if (!servm->setPosition(angleMMin)) return false;
    if (!servg->action()) return false;
    /**/
    return true;
}

bool Neck::setRight() {
    /**/
    if (!servm->setPosition(angleMMax)) return false;
    if (!servg->action()) return false;
    /**/
    return true;
}

bool Neck::setCenter() {
    /**/
    if (!servd->setPosition(200)) return false;
    if (!servm->setPosition(180)) return false;
    if (!servg->setPosition(160)) return false;
    if (!servg->action()) return false;
    /**/
    return true;
}

bool Neck::setPos(int valS1, int valS2, int valS3) {
    /**/
    if (valS1 > angleDMax) valS1 = angleDMax;
    if (valS1 < angleDMin) valS1 = angleDMin;
    if (!servd->setPosition(valS1)) return false;
    /**/
    if (valS2 > angleMMax) valS2 = angleMMax;
    if (valS2 < angleMMin) valS2 = angleMMin;
    if (!servm->setPosition(valS2)) return false;
    /**/
    if (valS3 < angleGMax) valS3 = angleGMax;
    if (valS3 > angleGMin) valS3 = angleGMin;
    if (!servg->setPosition(valS3)) return false;
    /**/
    if (!servd->action()) return false;

    return true;
    /**/
}

bool Neck::setServoPos(servo servomoteur, int degres) {
    int deg = degres;
    /**/
    switch (servomoteur) {
    /**/
        case servo::DROITE:
            degres += 180;
            if (degres > angleMMax) degres = angleMMax;
            if (degres < angleMMin) degres = angleMMin;
            if (!servm->setPosition(degres)) return false;
            if (!servm->action()) return false;
            break;
    /**/
        case servo::GAUCHE:
            degres = degres * (-1);
            degres += 180;
            if (degres > angleMMax) degres = angleMMax;
            if (degres < angleMMin) degres = angleMMin;
            if (!servm->setPosition(degres)) return false;
            if (!servm->action()) return false;
            break;
    /**/
        case servo::HAUT:
            degres += 200;
            if (degres > angleDMax) degres = angleDMax;
            if (!servd->setPosition(degres)) return false;
            deg -= 160;
            deg = deg * (-1);
            if (deg < angleGMax) deg = angleGMax;
            if (!servg->setPosition(deg)) return false;
            if (!servd->action()) return false;
            break;
    /**/
        case servo::BAS:
            degres -= 200;
            degres = degres * (-1);
            if (degres > angleDMax) degres = angleDMax;
            if (degres < angleDMin) degres = angleDMin;
            if (!servd->setPosition(degres)) return false;
            deg += 160;
            if (deg < angleGMax) deg = angleGMax;
            if (deg > angleGMin) deg = angleGMin;
            if (!servg->setPosition(deg)) return false;
            if (!servd->action()) return false;
            break;
    /**/
    }
    return true;
}

bool Neck::Random() {
    int nbale1, nbale3;// nbale2,
    srand(time(NULL));    
    //while (true) {
/**///nbale2 = rand() % 3 + 1;
/**///for (int i = 1; i < nbale2; i++) {

    nbale1 = rand() % 80 + 140;
    servm->setPosition(nbale1);
    servm->action();

       // sleep(rand() % 5 + 1);

 /**///}
    nbale3 = rand() % 30 + 180;
    servd->setPosition(nbale3);
    servg->setPosition(nbale3 - 30);
    servd->action();
    //}
    return true;
}
