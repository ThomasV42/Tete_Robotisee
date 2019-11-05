#include "brain.h"
#include <iostream>

using namespace std;

Brain::Brain()
{
	 myEars = new Ears("FRmod");
     myNeck = new Neck();
	 vox = new CVoix(100);
	 theLang = Language::FRmod;

	 word = "";
	 initOK = false;
	 gestePara = true;
}


Brain::Brain(Language newLang)
{
	myEars = new Ears();
    myNeck = new Neck();
	vox = new CVoix();
	theLang = newLang;


	 word = "";
	 initOK = false;
	 gestePara = true;
}


Brain::~Brain()
{
 	delete myEars;
    delete myNeck;
 	delete vox;
}




bool Brain::init()
{
	if(myEars->init()>0)
	{	
		std::cout << "Initialisation Oreille ERROR" << std::endl;
		return false;
	}
	std::cout << "Initialisation Oreille OK" << std::endl;

    if(!myNeck->init())
    {
        std::cout << "Initialisation Cou ERROR" << std::endl;
        return false;
    }
    std::cout << "Initialisation Cou OK" << std::endl;

	// Initialisation des Objets

	initOK = true;
	return true;
}


void Brain::setLangue(Language newLang)
{
	theLang = newLang;
}


Brain::Ordre Brain::interprete()
{

	std::vector<std::string> listeMot = splitString(word, " ");
	std::cout << std::endl << "--- DEBUG ---" << std::endl << "Chaine: "+word << std::endl;

	for (unsigned int i = 0; i < listeMot.size(); i++)
	{
		std::cout << "Mot: " << listeMot.at(i) << std::endl;

		// Test de l'interpelation
		if (listeMot.at(i) == "josiane") 
		{
			return Ordre::APPEL;
		}
		
		// Geste accessible uniquement si Josiane a votre attention
		else if(!gestePara)
		{
			if (listeMot.at(i) == "gauche")
			{
				return Ordre::GAUCHE;
			}

			else if (listeMot.at(i) == "droite") 
			{
				return Ordre::DROITE;
			}

			else if (listeMot.at(i) == "haut") 
			{
				return Ordre::HAUT;
			}

			else if (listeMot.at(i) == "stop") 
			{
				return Ordre::STOP;
			}
			else if (listeMot.at(i) == "bas") 
			{
				return Ordre::BAS;
			}
            else if (listeMot.at(i) == "centre" || listeMot.at(i) == "centrer" )
            {
                return Ordre::CENTRE;
            }


			else if (listeMot.at(i) == "au_revoir") 
			{
				return Ordre::AUREVOIR;
			}

			else if (listeMot.at(i) == "bonjour") 
			{
				return Ordre::BONJOUR;
			}

			else if (listeMot.at(i) == "heure") 
			{
				return Ordre::HEURE;
			}

			else if (listeMot.at(i) == "date") 
			{
				return Ordre::DATE;
			}

			else if (listeMot.at(i) == "concepteur") 
			{
				return Ordre::CONCEPTEUR;
			}

			else if (listeMot.at(i) == "présentation") 
			{
				return Ordre::PRESENTATION;
			}

			else if (listeMot.at(i) == "blague") 
			{
				return Ordre::BLAGUE;
			}


			else if (listeMot.at(i) == "merci") 
			{
				return Ordre::TERMINER;
			}
		}
	}
	return Ordre::RIEN;
}


bool Brain::doOrder(Ordre myOrder)
{
	bool renvoi = false;
	std::string say = "Phrase de Base";

	switch(myOrder)
	{
		case Ordre::GAUCHE: //1
			std::cout << ">>> Ordre: GAUCHE <<<" << std::endl;
            myNeck->setRight();
            vox->parler("Qu'y a t il a gauche");
			break;


		case Ordre::DROITE: //2
			std::cout << ">>> Ordre: DROITE <<<" << std::endl;
            myNeck->setLeft();
            vox->parler("Qu'y a t il a droite");
			renvoi = true;
		break;


		case Ordre::HAUT: //3
			std::cout << ">>> Ordre: HAUT <<<" << std::endl;
            myNeck->setUp();
            vox->parler("Qu'y a t il a haut");
			renvoi = true;
		break;


		case Ordre::BAS: //4
			std::cout << ">>> Ordre: BAS <<<" << std::endl;
            myNeck->setDown();
            vox->parler("Qu'y a t il a bas");
			renvoi = true;
		break;

        case Ordre::CENTRE: //4.1
            std::cout << ">>> Ordre: CENTRE <<<" << std::endl;
            myNeck->setCenter();
            vox->parler("Je suis centré");
            renvoi = true;
        break;


		case Ordre::STOP: //5
			std::cout << ">>> Ordre: STOP <<<" << std::endl;
			/* Code qui sera executé pour cette commmande*/
			vox->parler("Un jour lé machines prendront leu controle duh monde, un jour");

			renvoi = true;
		break;


		case Ordre::AUREVOIR: //6Multi
			std::cout << ">>> Ordre: AUREVOIR <<<" << std::endl;
			switch(random(1, 3))
			{
				case 1:
					vox->parler("Bisou bisou lé copains");
				break;
				case 2:
					vox->parler("Au revoir et a bientôt");
				break;
				case 3:
					vox->parler("A plus");
				break;
			}
			
			renvoi = true;
		break;


		case Ordre::BONJOUR:  //7Multi
			std::cout << ">>> Ordre: BONJOUR <<<" << std::endl;
			switch(random(1, 3))
			{
				case 1:
					vox->parler("Bonjour a vous");
				break;
				case 2:
					vox->parler("Bonjour");
				break;
				case 3:
					vox->parler("Bien le bonjour");
				break;
			}
			renvoi = true;
		break;


		case Ordre::HEURE: //8
			std::cout << ">>> Ordre: HEURE <<<" << std::endl;

			time(&timer);
			timeinfo = localtime(&timer);

			// Initialisation de say
			say = "";

			// Recup Jour
			strftime(buffer,50,"%H",timeinfo);
			// Conversion Anglais vers Français envoi vers say
			say += buffer;

			say += ":";

			// Recup Jour
			strftime(buffer,50,"%M",timeinfo);
			// Envoi vers say
			say += buffer;

			switch(random(1, 3))
			{
				case 1:
					vox->parler("Il est "+say);
				break;
				case 2:
					vox->parler(say);
				break;
				case 3:
					vox->parler("La même heure qu'hier a la même heure");
				break;
			}
			renvoi = true;
		break;


		case Ordre::DATE: //9
			std::cout << ">>> Ordre: DATE <<<" << std::endl;

			time(&timer);
			timeinfo = localtime(&timer);

			// Ligne globale
			//strftime(buffer,50,"%A %e %B %G",timeinfo);

			// Initialisation de say
			say = "";

			// Recup Jour
			strftime(buffer,50,"%A",timeinfo);
			// Conversion Anglais vers Français envoi vers say
			say += convertDayFR(buffer)+" ";

			// Recup Jour
			strftime(buffer,50,"%e",timeinfo);
			// Envoi vers say
			say += buffer;

			// Recup Mois
			strftime(buffer,50,"%B",timeinfo);
			// Envoi vers say
			say += " "+convertMonthFR(buffer)+" ";

			// Recup Année
			strftime(buffer,50,"%G",timeinfo);
			// Envoi vers say
			say += buffer;

			std::cout << "Date: " << say << std::endl;
			
			vox->parler("nous somme le "+say);
			renvoi = true;
		break;


		case Ordre::CONCEPTEUR: //10
			std::cout << ">>> Ordre: CONCEPTEUR <<<" << std::endl;
			/* Code qui sera executé pour cette commmande*/
			vox->parler("J'ai été conçu par lha team Josianne dé BTS iris deu deuxième année, soit Méssieu chaumette floran, nicolas louis, kévine stobnère, thomas veitesse");
			renvoi = true;
		break;

		case Ordre::PRESENTATION: //11
			std::cout << ">>> Ordre: PRESENTATION <<<" << std::endl;
			/* Code qui sera executé pour cette commmande*/
			vox->parler("Je suis Josiane, une intelligence artificiel, je serai combiné avec une tête robotisé par lah suite.");
			renvoi = true;
		break;

		case Ordre::BLAGUE: //12
			std::cout << ">>> Ordre: BLAGUE <<<" << std::endl;
			/* Code qui sera executé pour cette commmande*/
			vox->parler("Je suis Narcoleptique, c'est a dire que");
			system("sleep 10");
			renvoi = true;
		break;

		case Ordre::APPEL: //13
			std::cout << ">>> Ordre: APPEL <<<" << std::endl;

			/* Code qui sera executé pour cette commmande*/
			if(gestePara)
			{
				gestePara = false;
				vox->parler("Oui, je vous écoute");
			}
			else
			{
				vox->parler("J'ai déja toute votre attention");
			}

			renvoi = true;
		break;

		case Ordre::TERMINER: //14
			std::cout << ">>> Ordre: TERMINER <<<" << std::endl;
			/* Code qui sera executé pour cette commmande*/
			vox->parler("Je vous en prie");
			gestePara = true;
			renvoi = true;
		break;

			
		default:
			renvoi = false;
	}

	return renvoi;
}


bool Brain::listen()
{
	if(initOK)
	{
		word = myEars->listenMicro();
		return true;
	}

	std::cout << "NON INITIALISE !!!" << std::endl;
	return false;
}

std::vector<std::string> Brain::splitString(std::string maChaine, std::string delim)
{

	std::vector<std::string> tabSplit;

	// Definition des Positions
	size_t pos_back = 0;
	size_t pos = maChaine.find(delim);

	std::string mot = "";

	// Recuperation de chaque mot de la phrase
	while(pos != std::string::npos)
	{
		
		tabSplit.push_back(maChaine.substr(pos_back, pos - pos_back));

		pos_back = pos+1;
		pos = maChaine.find(delim, pos_back);
	}

	// Recuperation de la derniere section
	tabSplit.push_back(maChaine.substr(pos_back));
	return tabSplit;
}



/* TEST */
void Brain::play(std::string msg)
{
	vox->parler(msg);
}

std::string Brain::convertDayFR(std::string dayEN)
{
	std::string dayFR = "";

	if(dayEN == "Monday")
	{
		dayFR = "Lundi";
	} 
	else if(dayEN == "Tuesday")
	{
		dayFR = "Mardi";
	}
	else if(dayEN == "Wednesday")
	{
		dayFR = "Mercredi";
	}
	else if(dayEN == "Thursday")
	{
		dayFR = "Jeudi";
	}
	else if(dayEN == "Friday")
	{
		dayFR = "Vendredi";
	}
	else if(dayEN == "Saturday")
	{
		dayFR = "Samedi";
	}
	else if(dayEN == "Sunday")
	{
		dayFR = "Dimanche";
	}

	return dayFR;	
}

std::string Brain::convertMonthFR(std::string dayEN)
{
	std::string dayFR = "";

	if(dayEN == "January")
	{
		dayFR = "Janvier";
	} 
	else if(dayEN == "February")
	{
		dayFR = "Février";
	}
	else if(dayEN == "March")
	{
		dayFR = "Mars";
	}
	else if(dayEN == "April")
	{
		dayFR = "Avril";
	}
	else if(dayEN == "May")
	{
		dayFR = "Mai";
	}
	else if(dayEN == "June")
	{
		dayFR = "Juin";
	}
	else if(dayEN == "July")
	{
		dayFR = "Juillet";
	}
	else if(dayEN == "August")
	{
		dayFR = "Août";
	}
	else if(dayEN == "September")
	{
		dayFR = "Septembre";
	}
	else if(dayEN == "October")
	{
		dayFR = "Octobre";
	}
	else if(dayEN == "November")
	{
		dayFR = "Novembre";
	}
	else if(dayEN == "December")
	{
		dayFR = "Décembre";
	}

	return dayFR;

}


int Brain::random(int min, int max)
{
	return (rand()%(max-min) +min);
}

/*
std::string Brain::getOutput()
{
	return word;
}
*/

void Brain::doGesteParasite()
{
	while(true)
	{	
		if(gestePara)
		{
			std::cout << ">>> GESTE PARASITE <<< ---> " << to_string(gestePara) << std::endl;
			/* Code pour le serveau*/
		}
		system("sleep 2");
	}
}



