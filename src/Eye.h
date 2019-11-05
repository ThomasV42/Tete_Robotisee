/**
\mainpage Classe de pilotage des yeux de la tête robotisée
\author Florent Chaumette
\date Janvier - Mai 2015

Cette classe Eye permet le contrôle du mouvement des yeux
mais aussi du flux vidéo que ces derniers proposent via la
bibliothèque OpenCv (http://opencv.org/documentation.html).
 
Les erreurs seront gérées grâce à des exceptions. Il est du devoir de
l'utilisateur de les gérer.
 
\file Eye.h
Déclaration de la classe Eye
\class Eye
\brief Cette classe permet de contrôler les yeux de la tête du robot 
*/

#ifndef __OEIL_H__
#define __OEIL_H__

#include <opencv2/opencv.hpp>
#include <vector>
#include <exception>

using namespace cv;
using namespace std;

///Variable constante pour la couleur des rectangles affichés (correspond au bleu).
const Scalar_<int> COLOR(255,100,0);

class Eye {
private :
    ///Variable OpenCv correspondant au flux vidéo
    VideoCapture camera;
    
    ///Fichier de détection des têtes sur une image
    CascadeClassifier classificateurHead;
    
    ///Fichier de détection des yeux sur une image (+ précis, - rapide)
    CascadeClassifier classificateurEye;
    
    ///Variable OpenCv contenant des images pouvant être récupérées via le flux vidéo
    Mat image;
    
    ///Vecteur contenant les rectangles encadrant les yeux détectés
    vector<Rect> tabYeux;
    
    ///Vecteur contenant les rectangles encadrant les visages détectés
    vector<Rect> tabVisages;
    
    ///Variable contenant le rectangle encadrant le premier visage detecté
    Rect visageSeul;
    
    ///Chaine contenant le chemin vers le fichier Cascade pour les têtes
    string cheminCascadeHead;
    
    ///Chaine contenant le chemin vers le fichier Cascade pour les yeux
    string cheminCascadeEye;
    
public :
    
    /**
     * \class Eyexception
     * \brief Classe d'exception pour la classe Eye
     */
    class Eyexception : public exception {
        private :
            ///Code d'erreur. Le premier chiffre correspond à la partie de la tête et les deux derniers correspondent au numéro de l'erreur.
            int codeErreur;
            ///Explicite la partie de la tête où l'erreur se situe.
            const string partie = "Eye";
            ///Explicite l'erreur rencontrée.
            string erreur;
            
        public :
            /**
             * \brief Constructeur de la classe Eyexception
             * 
             * \param nCodeErreur Entier correspondant au code d'erreur
             * \param nErreur String explicitant l'erreur rencontrée
             */
            Eyexception(int nCodeErreur, string nErreur) noexcept {
                codeErreur = nCodeErreur;
                erreur = nErreur;
            }
            
            /**
             * \brief Méthode what
             * 
             * Cette méthode retourne un tableau de charactères explicitant 
             * l'erreur rencontrée
             * 
             * \return const char* : Chaine de caractères explicitant l'erreur
             */
            virtual const char* what() const noexcept {
                string temp;
                temp = partie + " - " + erreur;
                return temp.c_str();
            }
            
            /**
             * \brief Méthode getCode
             * 
             * Retourne le code d'erreur
             * 
             * \return int : Entier représentant le code d'erreur
             */
            virtual const int getCode() const noexcept {
                return codeErreur;
            }
    };
    
    /**
    * \brief Constructeur par défaut de la classe Eye
    * 
    * Ce constructeur initialise par défaut les attributs privés de la classe.
    * Constructeur par défaut.
    * 
    * Les valeurs par défaut de camera et de classificateur seront
    * 0 pour camera (Premier flux vidéo trouvé) et 
    * "/home/iris/Bureau/Josiane_Flo/Ressources/haarcascade_frontalface_alt2.xml"
    * pour classificateur.
    */
    Eye();  //NE PAS METTRE DE PARENTHESES !! Eye oeil; <-- BON / Eye oeil(); <-- FAUX
    
    /**
    * \brief Constructeur avec 2 paramètres de la classe Eye
    * 
    * Ce constructeur initialise les attributs privés de la classe avec les 
    * paramètres passés.
    * 
    * \param[in] device Entier représentant le flux vidéo à utiliser 
    * \param[in] nomFichierCascade Chemin vers le fichier HaarCascade à utiliser
    */
    //Eye(int device, string nomFichierCascade);
    
    ~Eye();
    
    /**
     * \brief Méthode init
     * 
     * Doit être appelée immédiatement après le constructeur. Permet l'initialisation de l'oeil.
     * Lève des exceptions de type Eyexception.
     */
    void init(int device, string headCascadePath, string eyeCascadePath);
    /**
     * \brief Méthode fluxVideo
     * 
     * Cette méthode permet de renvoyer l'image capté par la caméra.
     *  
     * \return Mat : Type OpenCv contenant l'image capturée par le flux vidéo 
     */
    Mat fluxVideo();
    
    /**
    * \brief Méthode getImage
    * 
    * Cette méthode renvoie un type Mat (OpenCv) correspondant à l'image
    * contenue dans la variable privé image de la classe Eye.
    * 
    * \return Mat : Type OpenCv contenant l'image de la variable image
    *  de la classe Eye
    */
    Mat getImage();
    
    /**
    * \brief Méthode getVisages()
    * 
    * Cette méthode permet de récuperer un vecteur de rectangle à afficher autour
    * des visages détectés.
    * 
    * \return vector<Rect> se trouvant autour des visages détectés
    */
    vector<Rect> getVisages();
    
    /**
    * \brief Méthode getVisage()
    * 
    * Contrairement à la méthode getVisages (avec un s -> nom provisoire),
    * cette fonction retourne le rectangle se trouvant au premier indice (0)
    * du vecteur.
    * 
    * \return Rect se trouvant autour du premier visage détecté
    */
    Rect getVisage();
    
    /**
    * \brief Méthode getNbrVisagesDetect
    * 
    * Cette méthode permet de récupérer le nombre de visages détectés.
    * 
    * \return int : Correspond à visages.size()
    */
    int getNbrVisagesDetect();
    
    /**
    * \brief Méthode afficherVisagesDetect
    * 
    * Cette méthode permet d'ajouter les rectangles encadrant les différents
    * visages détectés sur la variable image de la classe Eye.
    */
    void afficherVisagesDetect(bool SeulVisage, bool precision);
    
    /**
    * \brief Méthode detectMultiScale
    * 
    * Cette méthode permet de détecter les visages et donc de remplir les
    * variables visageSeul et visages de la classe Eye.
    * 
    * \param bool : Si vrai, le cascade de la tête est utilisé, si faux celui des
    * yeux sera utilisé.
    */
    void detectMultiScale(bool headOrEye);
};
#endif