#include "Eye.h"

Eye::Eye() {
    cheminCascadeEye = "";
    cheminCascadeHead = "";
}

void Eye::init(int device, string headCascadePath, string eyeCascadePath) {
    if (camera.open(device) == false)
        throw Eyexception(301, "Aucune camera detecte / Probleme ouverture chemin vers camera");
    else if (classificateurHead.load(headCascadePath) == false)
        throw Eyexception(302, "Chemin vers Classificateur (tête) invalide");
    else {
        cheminCascadeHead = headCascadePath;
        if (classificateurEye.load(eyeCascadePath) == false)
            throw Eyexception(303, "Chemin vers Classificateur (yeux) invalide");
        else
            cheminCascadeEye = eyeCascadePath;
    }
}

Eye::~Eye() {

}

Mat Eye::fluxVideo() {
    camera >> image;
    return image;
}

Mat Eye::getImage() {
    return image;
}

vector<Rect> Eye::getVisages() {
    return tabVisages;
}

Rect Eye::getVisage() {
    return visageSeul;
}

int Eye::getNbrVisagesDetect() {
    return tabVisages.size();
}

void Eye::afficherVisagesDetect(bool SeulVisage, bool precision) {
    if (getNbrVisagesDetect() > 0) {
        Point_<int> hg;
        Point_<int> bd;
        if (!SeulVisage) {
            for (int i = 0; i < tabVisages.size(); i++) {
                hg = tabVisages.at(i).tl();
                bd = tabVisages.at(i).br();
                rectangle(image, tabVisages.at(i), COLOR, 2);
            }
        } else {
            hg = tabVisages.at(0).tl();
            bd = tabVisages.at(0).br();
            if(tabVisages.at(0).contains(tabYeux.at(0).tl()) && tabVisages.at(0).contains(tabYeux.at(1).tl())){
                rectangle(image, tabVisages.at(0), COLOR, 2);
                rectangle(image, tabYeux.at(0), COLOR, 2);
                rectangle(image, tabYeux.at(1), COLOR, 2);
            }
        }
    }
}

void Eye::detectMultiScale(bool headOrEye) {
    if(headOrEye)
        classificateurHead.detectMultiScale(image, tabVisages);
    else
        classificateurEye.detectMultiScale(image, tabYeux);
}