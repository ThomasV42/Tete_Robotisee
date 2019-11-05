#ifndef MACHOIRE_H
#define	MACHOIRE_H

#include "CVoix.h"
#include "ServoMoteurRC.h"
#include <thread>


using namespace std;

class Machoire {
private:
    /// Booléen permettant de savoir si la tête est entrain de parler
    bool parle;
    
    ///Création d'un objet de type ServoMoteurRC
    ServoMoteurRC* myServ;
    
    ///Création d'un objet de type CVoix
    CVoix vox;
    
    const int BUTEE_BO = 1200; // Valeur de la Butée Bouche Ouverte
    const int BUTEE_BF = 1100; // Valeur de la Butée Bouche Fermée
     
	/**
     *\brief Methode permettant de faire bouger la mâchoire en même temps que le son (thread)
     */    
    void bougerParole();

public:
    /**
     *\brief Constructeur de la classe ServoMoteur
     */
    Machoire();
    
    /**
     *\brief Destructeur de la classe ServoMoteur
     */
    ~Machoire();
    
    /**
     *\brief Méthode d'initialisation de la mâchoire
     */
    void init();
    
     /**
     *\brief Méthode d'arrêter la machoire
     */
    void arret();
    
    /**
     *\brief Méthode permettant d'ouvrir la bouche
     */    
    bool ouvrirBouche();
    
    /**
     *\brief Méthode permettant de fermer la bouche
     */    
    bool fermerBouche();
    

     /**
     *\brief Méthode permettant de parler tout en bougeant la mâchoire
     */     // .
    bool parler(string texte);
        
};




#endif	/* MACHOIRE_H */

