#include "CVoix.h"


CVoix::CVoix()
{
	vitesse = 110;
	sex = CVoix::Sexe::HOMME;
}


CVoix::CVoix(int New_Speed)
{
	vitesse = New_Speed;
	sex = CVoix::Sexe::HOMME;
}


CVoix::Sexe CVoix::getSexe()
{
    return sex;
}


void CVoix::setSexe(string New_Sexe)
{
	if(New_Sexe == "FEMME")
    	sex = CVoix::Sexe::FEMME;
    else
    	sex = CVoix::Sexe::HOMME;
}


int CVoix::getVitesse()
{
    return vitesse;
}


void CVoix::setVitesse(int New_Speed)
{
    vitesse = New_Speed;
}


void CVoix::parler(string phrase)
{
    string chaine = "espeak -s "+to_string(vitesse);
    
    switch(sex)
    {
    	case CVoix::Sexe::FEMME:
    		chaine += " -v mb/mb-fr4 \"";
    		break;

    	default:
    		    chaine += " -v mb/mb-fr1 \"";
    }

    chaine += phrase+"\"";

    system(chaine.c_str());
}