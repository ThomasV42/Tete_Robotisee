/**
\mainpage Classe Cerveau (Brain) pour Pilotage de la tete Robotisée 
\author Florent Chaumette, Kévin Stoebner, Nicolas Louis, Thomas Veitès
\date Mars-Avril 2015

Cette classe cerveau permet de piloter la Tete Robotisée Josiane developper par la
socièté Cybedroid sur Limoges.

Elle comprend tout les objets permettant de piloter chaque partie de la tête.

\file brain.h
\class Brain
\brief Pilotage complet de la tête robotisée
\version 1.20
*/


#ifndef _BRAIN_
#define _BRAIN_

#include "ears.h"
#include "CVoix.h"
#include "Neck.h"
#include "Eye.h"

#include <vector>
#include <ctime>


class Brain
{
	public:
		/** \enum Ordre
		* Enumeration de chaque ordre disponible pour la tête.
		*/
		enum class Ordre 
		{
			GAUCHE, ///< Ordre tourner la tête a gauche
			DROITE, ///< Ordre tourner la tête a droite
			HAUT, ///< Ordre lever la tete
			BAS, ///< Ordre baisser la tête
            CENTRE, ///< Ordre recentrer la tête

			STOP, ///< Ordre d'Arret Brutal 
			AUREVOIR,
			BONJOUR, ///< L'utilisateur a dit bonjour

			HEURE, ///< Donne l'heure du systeme
			DATE, ///< Donne la date du systeme

			CONCEPTEUR, ///< Presente la Team
			PRESENTATION, ///< La Tete se presente
			BLAGUE, ///< Ordre de raconter une blague
			RIEN, ///< Ordre RIEN

			APPEL, ///< Ordre de demande d'attention
			TERMINER, ///< Demande d'attention Terminé
		};

		
		/** \enum Language
		* Langue qui sera utilisé par Brain.
		*/
		enum class Language 
		{
			FR, ///< Langue Française (lente)
			FRmod, ///< Langue Française Modifié (Plus rapide)
			EN ///< Langue Anglais
		};



	private:
		/// Objet representant la partie Oreille (Reconnaissance Vocale)
		Ears* myEars;

		/// Objet representatn la partie Voix (TextToSpeech)
		CVoix* vox;

		/// Objet representatn la partie Cou (Servomoteurs Dynamixels)
        Neck* myNeck;

        /// Objet representatn la partie des Yeux (Caméras HD)
        Eye* myEye;

		/**********************************/
		/* INSERER ICI LES AUTRES MODULES */
		/**********************************/

		/// Variable contenant la langue qui a été definit.
		Language theLang;

		/// Variable de la dernière chaine entendu par Ears
		std::string word;

		/// Variable de l'init
		bool initOK;

		/// Variable permettant de savoir si les gestes parasites doivent être executé
		bool gestePara;

		/// Variable pour calculer le temps
		time_t timer;
		/// Structure contenant la date d'aujourd'hui.
		struct tm * timeinfo;
		/// Buffer contenant la date.
		char buffer [50];




		/** \brief Decouper une chaine
		*
		* Cette fonction privé permet de decouper
		* une chaine (string) via un delimiteur
		* puis de l'inserer dans un vecteur
		* Attention, le delimieteur n'est pas ajouté au vecteur !
		*
		* \param[in] maChaine Chaine de caratere a découper
		* \param[in] delim Delimiteur, chaine qui servira a decouper la chaine
		*
		* \return vector<string> Vecteur de String contenant la chaine découpée
		*/
		std::vector<std::string> splitString(std::string maChaine, std::string delim);


		/** \brief Conversion d'un jour en Français
		*
		* Cette fonction privé permet de convertir
		* un jour de l'Anglais (Monday) vers le Français (Lundi)
		*
		* \param[in] dayEN Nom du jour en Anglais
		*
		* \return std::string Le jour en Français
		*/
		std::string convertDayFR(std::string dayEN);


		/** \brief Conversion d'un mois en Français
		*
		* Cette fonction privé permet de convertir
		* un mois de l'Anglais (Monday) vers le Français (Lundi)
		*
		* \param[in] dayEN Nom du mois en Anglais
		*
		* \return std::string Le mois en Français
		*/
		std::string convertMonthFR(std::string dayEN);


		/** \brief Générateur de chiffre aléatoires
		*
		* Cette fonction privé permet de renvoyer un
		* chiffre aléatoire compris entre 2 valeurs
		*
		* \param[in] min Valeur Minimum
		* \param[in] max Valeur Maximum
		*
		* \return int Nombre aléatoire compris entre min et max
		*/
		int random(int min, int max);

		
	



	public:
		/** \brief Constructeur par defaut de la classe Brain
		*
		* Ce constructeur initialise les attribut de SA classe.
		* Il déclare et crée mais n'initialise pas les Objets !
		*/
		Brain();


		/** \brief Constructeur de la classe Brain
		*
		* Ce constructeur initialise les attribut de SA classe avec la langue passer.
		* Il déclare et crée mais n'initialise pas les Objets !
		*/
		Brain(Language theLang);


		/** \brief Destructeur de la classe Brain
		*
		* Ce destructeur supprime les attribut de la classe.
		*/
		~Brain();


		/** \brief Initialise les Objets.
		*
		* Cette fonction initialise les objets ayant besoin d'une initialisation.
		* Comme la classe Oreille par exemple.
		*
		* \return booléen indiquant si init a reussi TRUE = reussi / FALSE = échoué
		*/
		bool init();


		/** \brief Permet de modifier la langue
		*
		* Cette fonction permet de modifier la langue de l'objet Brain
		*
		* \param[in] myLang Type Language Choix entre FR FRmod EN (Français, Français Modifé, English)
		*/
		void setLangue(Language myLang);


		/** \brief Interprete une phrase pour retourner un geste
		*
		* Cette fonction analyse une phrase afin de retourner un Ordre
		* reconnu par la tête
		*
		*
		* \return Ordre qui sera interpreté par la fonction do(Ordre myOrder).
		*/
		Ordre interprete();


		/** \brief Execute l'ordre passé en parametre
		*
		* Cette fonction execute l'ordre qui lui est demandé par rapport
		*
		* \param[in] myOrder Ordre renvoyer par l'interpretation
		*
		* \return booléen qui indique si l'ordre a bien été executé TRUE = ok / FALSE = échoué.
		*/
		bool doOrder(Ordre myOrder);


		/** \brief Fait une ecoute du millieu
		*
		* Cette fonction enregistre le pendant un temps defini 
		* le son exterieur.
		*
 		*
		* \return booléen qui indique si l'ecoute a réussi TRUE = ok / FALSE = échoué.
		*/
 		bool listen();

 		/** \brief Lit le texte qui lui ai passé
		*
		* Cette fonction lit le texte qui lui ai passé
		* en paramètre.
		*
		* \param[in] msg Message texte a lire
 		*/
 		void play(std::string msg);

 		/*std::string getOutput();*/

 		/** \brief Fait les gestes parasites
		*
		* Cette fonction fait les gestes parasites, 
		* il faut donc la mettre dans un thread afin de pouvoir ecouter 
		*
		* \param[in] msg Message texte a lire
 		*/
 		void doGesteParasite();


};


#endif 
/* _BRAIN_ */
