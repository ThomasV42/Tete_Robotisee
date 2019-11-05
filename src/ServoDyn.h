/**
\class ServoDyn
\brief Classe de gestion des servomoteur Dynamixel
\file ServoDyn.h 
 Classe héritée de la classe virtuel ServoMoteur
 Déclaration de la classe ServoDyn


 */
#ifndef SERVODYN_H
#define	SERVODYN_H

#include "ServoMoteur.h"
#include <string>
#include <vector>

#define DEVICE_PORT "/dev/ttyACM0"

using namespace std;

class ServoDyn : public ServoMoteur {
protected:
    ///(Voie Série) objet serialib permetant la gestion de la voie série dans le programme
    serialib vs;

    ///Vecteur de caractères cotenant la trame à envoyer
    vector<unsigned char> trame;
    
    ///Enum des possibilités d'instruction pour la trame d'envoie
    enum class INSTRUCTION : int{PING = 0x01, LECTURE = 0x02, ECRITURED = 0x03, ECRITURER = 0x04, ACTION = 0x05, RESET = 0x06, ECRITURESYNC = 0x83};

    ///Enum des possibilités de registre  ou écrire pour la trame d'envoie
    enum class REGISTRE : int{CIBLE = 0x1E, VITESSE = 0x20, POSITION = 0x24, ACCELERATION = 0x49};
    
    /**
     * \brief Fonction utilisée dans "init()" pour placer les servomoteur dans leurs position centrale
     */
    bool positioncentrale();
    
    /**
     * \brief Fonction de calcul du checksum des trames
     * \param trame où calculer le cheksum 
     */
    int calculChecksum(vector<unsigned char> tr);

    /**
     * \brief Fonction d'ecriture de trame aux servomoteurs
     * \param trame à écrire
     */
    int envoyerDonnees(vector <unsigned char> tr);

    /**
     * \brief Fonction d'initialisation de la trame : en-tête et id du servomoteur concerné
     */
    void sTrame();

public:
    /**
     *\brief Méthode ScanVoieSerie
     * Cette méthode permet de savoir quels identifiant sont disponible, connectés, sur la voie série
     * \param Voie Objet serialib : voie série à scanner
     * \return Vecteur d'entier contenant les identifiant concernés
     */
    static vector<int> ScanVoieSerie(serialib Voie);
    
    /**
     *\brief Constructeur de la classe ServoDyn
     * Ce constructeur initialise un objet ServoMoteur de la classe du même nom.
     * Cela définit la vitesse, l'accélération, la position et la cible à 0.
     * \param m_ID Fixe l'ID de l'objet servomoteur créé
     */
    ServoDyn(int m_ID);

    /**
     *\brief Destructeur de la classe ServoDyn
     */
    ~ServoDyn();
    
    /**
     *\brief Méthode getErreurForce
     * Méthode utilisée par l'initialisation pour détecter la buté du servomoteur
     * \return true Erreur force
     * \return false Aucune erreur
     */
    bool getErreurForce();
    
    /**
     *\brief Méthode init
     * 
     * Cette méthode doit être appelé en premier après la création d'un objet ServoDyn.
     * Elle ouvre la voie série et place la tête dans sa position centrale.
     * \return true Réussite
     * \return false Echec
     */
    bool init();
    
    /**
     * \brief Méthode action
     * 
     * Cette méhode est utilisée après la méthodes setPosition pour mettre en action les servomoteurs en simultané.
     * \return true Réussite
     * \return false Echec
     */
    bool action();


    /**
     *\brief Méthode arret
     * 
     * Cette méthode doit être à la fin pour fermer la voie série.
     * \return Booléen qui indique la réussite (true) ou non (false) de la méthode
     */
    void arret();

    /**
     *\brief Méthode setAcceleration
     * 
     * Cette méthode permet de fixer l'accélération des servomoteurs.
     * \param m_acceleration Entier à donnée pour fixer l'accélération
     * \return true Réussite
     * \return false Echec
     */
    bool setAcceleration(int m_acceleration);

    /**
     *\brief Méthode setVitesse
     * 
     * Cette méthode permet de fixer la vitesse de mouvement des servomoteurs.
     * \param m_vitesse Entier à donné pour fixer la vitesse.
     * \return true Réussite
     * \return false Echec
     */
    bool setVitesse(int m_vitesse);

    /**
     *\brief Méthode setPosition
     * 
     * Cette méthode permet de déplacer le servomoteur concerné à une position donnée.
     * \param m_cible Entier à donné pour la position choisi.
     * \return true Réussite
     * \return false Echec
     */
    bool setPosition(int m_cible);

    /**
     *\brief Méthode getAcceleration
     * 
     * Cette méthode permet de récupérer l'accélération active sur le servomoteur concerné.
     * \return Entier qui indique l'accélération actuelle
     */
    const int getAcceleration();

    /**
     *\brief Méthode getVitesse
     * 
     * Cette méthode permet de récupérer la vitesse courante sur le servomoteur.
     * \return Entier indiquant la vitesse de mouvement actuel
     */
    const int getVitesse();

    /**
     *\brief Méthode getPosition
     * 
     * Cette méthode permet de fixer l'accélération des servomoteurs.
     * \return Entier indiquant la position actuel
     */
    const int getPosition();
};

#endif	/* SERVODYN_H */
