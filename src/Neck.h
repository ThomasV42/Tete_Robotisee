/**
 \mainpage Classe de gestion du cou de Josiane
 \author Kevin
 \date avril 2015
 
 
 \file Neck.h
 \class     Neck
 \brief     Classe de gestion du cou à partir de la classe ServoDyn.
 
  Déclaration de la classe Neck, permet de faire des mouvement simples de la tête tels que oui, non, gauche...
 */
#ifndef NECK_H
#define	NECK_H

#include "ServoDyn.h"
#include <cstdlib>
#include <time.h>

class Neck {
public:
    enum class servo {HAUT, BAS, GAUCHE, DROITE};
private:
    ///(Voie Série) objet serialib permetant la gestion de la voie série dans le programme
    serialib vs;

    ///Objet servomoteur disignant le servormoteur de droite, le 1
    ServoDyn *servd;    //servomoteur droite

    ///Objet servomoteur disignant le servormoteur du milieu, le 2
    ServoDyn *servm;    //servomoteur milieu

    ///Objet servomoteur disignant le servormoteur de gauche, le 2
    ServoDyn *servg;    //servomoteur gauche

    ///Entier constant idiquant la position maximale du servomoteur 1
    int angleDMax = 215;        //angle de butée maximal du servomoteur droite

    ///Entier constant idiquant la position maximale du servomoteur 2
    int angleMMax = 240;        //angle de butée maximal du servomoteur milieu

    ///Entier constant idiquant la position maximale du servomoteur 3
    int angleGMax = 145;        //angle de butée maximal du servomoteur gauche

    ///Entier constant idiquant la position minimale du servomoteur 1
    int angleDMin = 175;        //angle de butée minimal du servomoteur droite

    ///Entier constant idiquant la position minimale du servomoteur 2
    int angleMMin = 110;        //angle de butée minimal du servomoteur milieu

    ///Entier constant idiquant la position minimale du servomoteur 3
    int angleGMin = 185;        //angle de butée minimal du servomoteur gauche

public:
    /**
     *\brief Constructeur de la classe Neck
     */
    Neck();

    /**
     *\brief Destructeur de la classe Neck
     */
    ~Neck();
    
    /**
     *\brief
     * Positionne la tête dans sa position centrale
     * \return true Réussite
     * \return false Echec
     */
    bool init();

    /**
     *\brief
     * Mouvement oui de la tête (haut, bas,...)
     * \return true Réussite
     * \return false Echec
     */
    bool Yes();
    
    /**
     *\brief
     * Mouvement non de la tête (droite, gauche,...)
     * \return true Réussite
     * \return false Echec
     */
    bool No();
    
    /**
     *\brief
     * Tourne la tête jusqu'à la position droite maximale
     * \return true Réussite
     * \return false Echec
     */
    bool setRight();

    /**
     *\brief
     * Tourne la tête jusqu'à la position gauche maximale
     * \return true Réussite
     * \return false Echec
     */
    bool setLeft();

    /**
     *\brief
     * Monte la tête jusqu'à la position maximale
     * \return true Réussite
     * \return false Echec
     */
    bool setUp();

    /**
     *\brief
     * Incline la tête jusqu'à la posotion maximale
     * \return true Réussite
     * \return false Echec
     */
    bool setDown();

    /**
     *\brief
     * Positonne la tête droite pour regarder en face
     * \return true Réussite
     * \return false Echec
     */
    bool setCenter();

    /**
     *\brief
     * Place chacun des servomoteurs dans la position indiquer avec la position entière
     *\param valS1 Entier correspondant à l'angle voulu pour le servomoteur de droite, le 1
     *\param valS2 Entier correspondant à l'angle voulu pour le servomoteur du milieu, le 2
     *\param valS3 Entier correspondant à l'angle voulu pour le servomoteur de gauche, le 3
     * \return true Réussite
     * \return false Echec
     */
    bool setPos(int valS1, int valS2, int valS3);
    
    /**
     *\brief
     * Place le servomoteur, choisi parmi un énumérateur, dans la position indiquer grâce à un angle
     *\param énumérateur servo correspondant au servomoteur que l'on souhaite déplacer avec la fonction
     * \param degres Entier correspondant à l'angle voulu pour le servomoteur choisi (postion centrale = 0°)
     * \return true Réussite
     * \return false Echec
     */
    bool setServoPos(servo servomoteur, int degres);
        
    /**
     *\brief
     * La tête se déplace aléatoirement pour montrer son activité
     * \return true Réussite
     * \return false Echec
     */
    bool Random();


};

#endif	/* NECK_H */

