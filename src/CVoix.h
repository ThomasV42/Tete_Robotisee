/**
\file CVoix.h
\class CVoix
\brief Classe permettant le TextToSpeech
\version 1.00
*/

#ifndef _CVOIX_H_
#define	_CVOIX_H_

#include <string>
#include <iostream>
#include <unistd.h>


using namespace std;

class CVoix {
public:
    //Deux voix française sont disponibles avec espeak : Masculine et Feminine
    //Afin de choisir entre les deux, je crée donc un enum (permet d'éviter les
    //erreurs de saisie)


    /** \enum Sexe
    * Enumeration du type de voix
    */
    enum class Sexe 
    {
        HOMME, ///< Voix Masculine
        FEMME ///< Voix Feminine
    };
private:
    /// Définit le type de la voix 
    Sexe sex;
    /// Définit la vitesse de lecture
    int vitesse;
    
public:
    /** \brief Constructeur par défaut de la classe CVoix
    *
    * Ce constructeur initialise les attributs de l'objet CVoix
    */
    CVoix();


    /** \brief Constructeur de la classe CVoix avec la vitesse
    *
    * Ce constructeur initialise les attributs de l'objet CVoix
    *
    *\param[in] New_Speed Vitesse de lecture du texte
    */
    CVoix(int New_Speed);


    /** \brief Recuperation du Sexe
    *
    * Cette fonction récupère la valeur de l'attribut sex
    *
    * \return Sexe Indiquant si la voix est HOMME ou FEMME
    */
    Sexe getSexe();     //Permet de recuperer le "sexe" du robot.


    /** \brief Choix du Sexe
    *
    * Cette fonction permet de choisir le type de voix
    *
    * \param[in] New_Sexe Ce paramètre est un string, FEMME pour une voix de femme, ou Homme pour une voix d'homme (voix par défaut)
    */
    void setSexe(string New_Sexe);     //Permet de choisir le sexe de notre  robot.


    /** \brief Recuperation de la Vitesse de lecture.
    *
    * Cette fonction renvoie la vitesse de lecture de l'objet CVoix
    *
    * \return int Vitesse de lecture de la voix
    */
    int getVitesse();   //Permet de récuperer la vitesse de parole.


    /** \brief Choix de la Vitesse.
    *
    * Cette fonction permet de choisir la vitesse de lecture par défaut 110
    *
    * \param[in] New_Speed Nouvelle vitesse de lecture, par défaut: 110
    */
    void setVitesse(int New_Speed);  //Permet de choisir la vitesse de parole.


    /** \brief Fait parler 
    *
    * Cette fonction est un TextToSpeech, elle utilise des appels system.
    * Envoi d'un string puis elle le transforme en son.
    *
    * \param[in] phrase Phrase qui doit etre lue par l'objet
    */
    void parler(string phrase);      //Fonction permettant de faire parler le robot.
};

#endif	
/* _CVOIX_H_ */

