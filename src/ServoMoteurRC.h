/**
\file ServoMoteurRC.h
\class ServoMoteurRC
\brief Classe permettant le controle des servomoteurs fonctionnant en MLI Modulation par largeur d'impulsions)
\version 1.00
*/

#ifndef SERVOMOTEURRC_H
#define	SERVOMOTEURRC_H

#include <iostream>
#include <string>
#include <vector>


#include "serialib.h"
#include "ServoMoteur.h"


using namespace std;

class ServoMoteurRC : public ServoMoteur {

private:
    /* ATTRIBUTS */
    /// Chaîne permettant de connaître l'erreur retournée
    string erreur;
    
    /// Entier qui permet d'identifier un servomoteur
    int ID; // voie de 0 à 5 pour les moteurs 0 à 5
    
    /// Vecteur permettant de réaliser notre trame
    vector<unsigned char> trame;
    
    /// Création d'un objet serialib -> voie série
    serialib* VS;
    
    /// Définit le port utilisé pour la voie série
    char* device;
    
    /// Définit la vitesse de la voix série
    int speed;
    
	/**
     *\brief Méthode permettant de modifier la valeur dans la trame
     */   
    void valeurTrame(unsigned short newValeur);
	
	/**
     *\brief Méthode permettant d'envoyer la trame sur la voie série
     */   
    void envoyerTrame();

    
    
public:
    /* ENUM */
    /** \enum TacheRealisee
    * Enumeration des fonctions realisables
    */
    enum class TacheRealisee 
    {
        setPosition = 0x84,     ///< Modification de la position
        setVitesse = 0x87,      ///< Modification de la vitesse
        setAcceleration = 0x89, ///< Modification de l'accélération
        getPosition = 0x90,     ///< Récupération de la position
        getEtatMouvement = 0x93,///< Récupération de l'etat du servomoteur (actif ou inactif)
        getErrors = 0xA1        ///< Récupération des erreurs
    };
    
    /* CONSTRUCTEUR */

	/**
     *\brief Ce constructeur initialise les attributs de l'objet ServoMoteurRC
     */   
    ServoMoteurRC();
    
    /** \brief Constructeur de la classe ServoMoteurRC avec le numéro du servomoteur souhaité
    *
    * Ce constructeur initialise les attributs de l'objet ServoMoteurRC
    *
    *\param[in] ID Identifiant d'un servomoteur
    */
    ServoMoteurRC(int ID);
    
    /** \brief Destructeur de la classe ServoMoteurRC 
    *
    * Ce destructeur supprime un objet ServoMoteurRC
    *
    */
    ~ServoMoteurRC();

    /* FCT VIRTUELLES */
    /** \brief Fonction virtuelle d'initialisation
    *
    * Cette fonction permet l'initialisation des servomoteurs et l'ouverture de la voie série
    *
    * \param[in] New_Sexe Ce parametre est un std::string FEMME pour une voix de femme par defaut la voix est sur HOMME
    */
    virtual bool init(int fileDes);
    
    /** \brief Fonction virtuelle de fermeture
    *
    * Cette fonction permet la fermeture de la voie série
    *
    */
    virtual void arret();
    
    /** \brief Fonction virtuelle de modification de position
    *
    * Cette fonction permet de modifier la position d'un servomoteur
    *
    * \param[in] newPosition Ce parametre est la valeur souhaitée pour la position à atteindre
    */
    virtual int setPosition(unsigned short newPosition);
    
    /* FCT AJOUTEES */
    /** \brief Fonction virtuelle de modification de la vitesse
    *
    * Cette fonction permet de modifier la vitesse d'un servomoteur
    *
    * \param[in] newVitesse Ce parametre est la valeur souhaitée pour la vitesse de deplacement
    */
        
    void setDeviceVS(char* _device);
    
    /** \brief Fonction permettant de changer la vitesse de la voie série
    *
    * Cette fonction permet de modifier la vitesse de la voie série
    *
    * \param[in] _speed Ce parametre est la nouvelle vitesse à appliquer
    */
    void setSpeedVS(int _speed);
    
    
    /** \brief Fonction permettant de réaliser la trame de commande
    *
    * Cette fonction permet de réaliser la trame de commande des servomoteurs
    *
    * \param[in] newTache Ce parametre est la nouvelle tache à effectuer
    * \param[in] valeur Ce parametre est la nouvelle valeur à communiquer
    */
    void ecrireTrame(TacheRealisee newTache, unsigned short valeur);
    
    
    /** \brief Fonction permettant de lire la trame envoyée
    *
    * Cette fonction permet de debuger, et de vérifier l'exactitude de la trame envoyée au servomoteur
    *
    */    
    string AfficherTrame();
    
};

#endif	/* SERVOMOTEURRC_H */

