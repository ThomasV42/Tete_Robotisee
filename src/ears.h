/**
\file ears.h
\class Ears
\brief Oreille pour la tête robotisée (SpeechToText)
\author Thomas Veitès
\version 3.20
*/

#ifndef _EARS_H_
#define _EARS_H_

#include <pocketsphinx.h>
#include <cstdlib>
#include <string>
#include <cstring>



#include <stdio.h>
#include <string.h>

#if !defined(_WIN32_WCE)
#include <signal.h>
#include <setjmp.h>
#endif
#if defined(WIN32) && !defined(GNUWINCE)
#include <time.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/cont_ad.h>


#include <iostream>


#define WNF "wnf" //word not found flag
#define MODELDIR "/usr/local/share/pocketsphinx/model";

class Ears
{
	public:
		/** \brief Constructeur par defaut de la classe Ears
		*
		* Ce constructeur initialise les attribut de SA classe.
		* Il déclare et crée mais n'initialise pas les Objets !
		*/
		Ears();

		/** \brief Constructeur de la classe Ears
		*
		* Ce constructeur initialise les attribut de SA classe avec la langue passer.
		* Il déclare et crée mais n'initialise pas les Objets !
		*/
		Ears(std::string lang);


		/** \brief Destructeur de la classe Ears
		*
		* Ce destructeur supprime les attribut de la classe.
		*/
		~Ears();


		/** \brief Initialise les Objets.
		*
		* Cette fonction initialise les objets ayant besoin d'une initialisation.
		*
		* \return booléen indiquant si init a reussi TRUE = reussi / FALSE = échoué
		*/
		int init();


		/** \brief Permet de modifier le chemin pour le model de langue
		*
		* Cette fonction permet de modifier le repertoire du fichier model de langue
		*
		* \param[in] _lmDir Nouveau nom de repertoire pour le model de langue
		*
		* \return int 0 est une reussite, 1 est un echec
		*/
		int setLMdir(std::string _lmDir);


		/** \brief Permet de modifier le chemin pour le Dictionnaire
		*
		* Cette fonction permet de modifier le repertoire du fichier Dictionnaire
		*
		* \param[in] _lmDir Nouveau nom de repertoire pour le Dictionnaire
		*
		* \return int 0 est une reussite, 1 est un echec
		*/
		int setDICdir(std::string _dicDir);

	
		/** \brief Ecoute du micro fonction bloquante
		*
		* Cette fonction permet d'écouter sur l'entrée micro par defaut, l'ecoute est intelligente.
		*
		* \return std::string La suite de mot qui a été compris compris.
 		*/
		std::string listenMicro();


		void close();


	private:
		
		/** \brief Met a jour les models de langue
		*
		* Cette fonction permet de mettre a jour les models de langue
		* une fois les chemins des fichiers nesséssire pour Ears rensignés 
		*
		* \return int Renvoi 0 si tout c'es-t bien passé
		*/
		int updateModel();
		
		/// Chemin du fichier lm (Lauguage Model)
		std::string lmDir;

		/// Chemin du Dictionnaire de Mot
		std::string dicDir;

		/// Chemin du fichier des models acoustiques
		std::string hmmDir;
		
		/// Pointeur sur objet de type ps_decoder_t permet la conversion Speech To Text
		ps_decoder_t *ps;
		/// Pointeur sur objet de type cmd_ln_t permet de stocker la config pour l'objet ps_decoder_t
		cmd_ln_t *config;
		/// Pointeur sur objet de type FILE, permet de stocker un flux vers un fichier.
		FILE *fh;

		/// Score de probabilité de cohérence entre Speech et Text
		int32 score;
		
		int16 buf[512];
		int rv;

		/// Variable contenant le fichier de enregistrement (out.raw par defaut)
		std::string locFile;


		/* ATTRIBUT SUPPLEMENTAIRE POUR RECONNASANCE*/
		ad_rec_t *ad;
	    int16 adbuf[4096];
	    int32 k, ts, rem;
	    char const *hyp;
	    char const *uttid;
	    cont_ad_t *cont;
	    char word[256];

	    



};

#endif
/* _EARS_H_ */
