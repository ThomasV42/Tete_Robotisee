/**
 \file    ServoMoteur.cpp
 * Implémentation de la classe ServoMoteur
 \class ServoMoteur
*/
#include "ServoMoteur.h"

ServoMoteur::ServoMoteur() {
    acceleration = 0;
    cible = 0;
    position = 0;
    vitesse = 0;
}

ServoMoteur::~ServoMoteur() {
}