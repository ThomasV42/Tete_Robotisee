 /**
 \class     ServoMoteur
 \brief     Classe mère virtuel de gestion des différents servomoteurs du projet
 \file ServoMoteur.h
  Déclaration de la classe ServoMoteur
 */
#ifndef SERVOMOTEUR_H
#define	SERVOMOTEUR_H

#include "serialib.h"

class ServoMoteur {
protected:
    ///Entier utilisé pour l'acceleration
    int acceleration;
    
    ///Entier utilisé pour la vitesse
    int vitesse;
    
    ///Entier utilisé pour la position
    int position;
    
    ///Entier utilisé pour la cible
    int cible;
    
    ///Entier d'identification des servomoteurs
    int ID;

public:
    /**
     *\brief Constructeur de la classe ServoMoteur
     */
    ServoMoteur();
    
    /**
     *\brief Destructeur de la classe ServoMoteur
     */
    ~ServoMoteur();
    
    /**
     *\brief Méthode setAccélération virtuelle pure
     */
    virtual bool setAcceleration(int m_acceleration) = 0;
    
    /**
     *\brief Méthode setVitesse virtuelle pure
     */
    virtual bool setVitesse(int m_vitesse) = 0;
    
    /**
     *\brief Méthode setPosition virtuelle pure
     */
    virtual bool setPosition(int m_cible) = 0;
    
    /**
     *\brief Méthode getAcceleration virtuelle pure
     */
    virtual const int getAcceleration() = 0;
    
    /**
     *\brief Méthode getVitesse virtuelle pure
     */
    virtual const int getVitesse() = 0;
    
    /**
     *\brief Méthode getPostion virtuelle pure 
     */
    virtual const int getPosition() = 0;
    
    /**
     *\brief Méthode init virtuelle pure 
     */
    virtual bool init() = 0;
    
    /**
     *\brief Méthode arret virtuelle pure 
     */
    virtual void arret() = 0;
};

#endif	/* SERVOMOTEUR_H */

