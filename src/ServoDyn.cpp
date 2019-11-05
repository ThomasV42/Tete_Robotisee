/**
 \file    ServoDyn.cpp
 * Implémentation de la classe ServoDyn
 \class ServoDyn
 */
#include "ServoDyn.h" 

vector<int> ServoDyn::ScanVoieSerie(serialib Voie) {
    vector<int> id;
    vector<unsigned char> tr(6);
    int nb = 0;
    tr.at(0) = 0xFF;
    tr.at(1) = 0xFF;
    tr.at(3) = 0x02;
    tr.at(4) = 0x01;
    for (int i = 0; i < 252; i++) {
        tr.at(2) = i;
        for (int i = 2; i < tr.size(); i++)
            nb += static_cast<int> (tr.at(i));
        nb = nb ^ 0xFF;
        nb = nb & 0x0ff;
        tr.at(5) = nb;
        Voie.Write(tr.data(), tr.size());

        vector <unsigned char> ret;
        char car = 0;
        int retour = 0;
        do {
            retour = Voie.ReadChar(&car, 100);
            if (retour > 0) ret.push_back(car);
        } while (retour > 0);

        if (ret.at(2) == i) id.push_back(i);
    }
    return id;
}

ServoDyn::ServoDyn(int m_ID) : ServoMoteur() {
    acceleration = 0;
    vitesse = 0;
    position = 0;
    ID = m_ID;
}

ServoDyn::~ServoDyn() {
}

void ServoDyn::sTrame() {
    trame.push_back(0xFF);
    trame.push_back(0xFF);
    trame.push_back(ID);
}

bool ServoDyn::getErreurForce(){
    sTrame();
    trame.push_back(0x02);
    trame.push_back(0x01);
    trame.push_back(calculChecksum(trame));
    
    if (envoyerDonnees(trame) == -1) return false;
    
    vector <unsigned char> ret;
    char car = 0;
    int retour = 0;
    do {
        retour = vs.ReadChar(&car, 100);
        if (retour > 0) ret.push_back(car);
    } while (retour > 0);
    cout << "trame recu : ";
    for (int i = 0; i < ret.size(); i++) cout << hex << static_cast<int> (ret.at(i)) << " ";
    cout << endl;
    if(ret.size() > 4){
        if((ret.at(4) & 0x20) == 32) return true;       // Masque 0x20 pour isoler le bit d'erreur de force
    }   
    
    trame.clear();
    return false;
}

bool ServoDyn::init() {    
    if (vs.Open(DEVICE_PORT, 115200) != 1)
        return false;
    
    if (!positioncentrale()) return false;

    cout << endl;

    if (!action()) return false;

    return true;
}

bool ServoDyn::positioncentrale() {
    //cout << "\n---------poscent---------" << endl;

    sTrame();
    trame.push_back(0x05);
    trame.push_back(static_cast<int> (ServoDyn::INSTRUCTION::ECRITURER));
    trame.push_back(static_cast<int> (ServoDyn::REGISTRE::CIBLE));
    trame.push_back(0x00);
    trame.push_back(0x08);
    trame.push_back(calculChecksum(trame));

    if (envoyerDonnees(trame) == -1) return false;
    /**/
    vector <unsigned char> ret;
    char car = 0;
    int retour = 0;
    do {
        retour = vs.ReadChar(&car, 100);
        if (retour > 0) ret.push_back(car);
    } while (retour > 0);

    //for (int i = 0; i < ret.size(); i++) cout << hex << static_cast<int> (ret.at(i)) << " ";
    /**/
    // cout << "\n---------poscent---------" << endl;

    trame.clear();
    return true;
}

bool ServoDyn::action() {
    //cout << "\n--------action--------" << endl;
    trame.push_back(0xFF);
    trame.push_back(0xFF);
    trame.push_back(0xFE);
    trame.push_back(0x02);
    trame.push_back(static_cast<int> (ServoDyn::INSTRUCTION::ACTION));
    trame.push_back(calculChecksum(trame));

    if (envoyerDonnees(trame) == -1) return false;

    vector <unsigned char> ret1;
    char car1 = 0;
    int retour1 = 0;
    do {
        retour1 = vs.ReadChar(&car1, 100);
        if (retour1 > 0) ret1.push_back(car1);
    } while (retour1 > 0);

    //for (int i = 0; i < ret1.size(); i++) cout << hex << static_cast<int> (ret1.at(i)) << " ";

    //cout << "\n--------action--------" << endl;

    trame.clear();
    return true;
}

int ServoDyn::calculChecksum(vector<unsigned char> tr) {
    int nb = 0;
    for (int i = 2; i < tr.size(); i++)
        nb += static_cast<int> (tr.at(i));
    nb = nb ^ 0xFF;
    nb = nb & 0x0ff;
    return nb;
}

int ServoDyn::envoyerDonnees(vector <unsigned char> trame) {
    return vs.Write(trame.data(), trame.size());
}

void ServoDyn::arret() {
    vs.Close();
}

bool ServoDyn::setPosition(int m_cible) {
    sTrame();
    cible = 2048 * m_cible;
    cible = cible / 180;
    if (cible >= 4095) cible = 4095;
    trame.push_back(0x05);
    trame.push_back(static_cast<int> (ServoDyn::INSTRUCTION::ECRITURER));
    trame.push_back(static_cast<int> (ServoDyn::REGISTRE::CIBLE));
    trame.push_back(cible & 0xFF);
    trame.push_back(cible >> 8);
    trame.push_back(calculChecksum(trame));
    if (envoyerDonnees(trame) == -1) return false;

    vector <unsigned char> ret;
    char car = 0;
    int retour = 0;
    do {
        retour = vs.ReadChar(&car, 100);
        if (retour > 0) ret.push_back(car);
    } while (retour > 0);
    /* 
    cout << "Dans setPosition ";
    for (int i = 0; i < ret.size(); i++) cout << hex << static_cast<int> (ret.at(i)) << " ";
    cout << endl;
    /**/
    trame.clear();
    return true;
}

bool ServoDyn::setAcceleration(int m_acceleration) {
    acceleration = m_acceleration;
    if (acceleration > 254 || acceleration < 0) {
        return false;
    }
    sTrame();
    trame.push_back(0x04);
    trame.push_back(static_cast<int> (ServoDyn::INSTRUCTION::ECRITURED));
    trame.push_back(static_cast<int> (ServoDyn::REGISTRE::ACCELERATION));
    trame.push_back(acceleration);
    trame.push_back(calculChecksum(trame));

    if (envoyerDonnees(trame) == -1) return false;

    vector <unsigned char> ret;
    char car = 0;
    int retour = 0;
    do {
        retour = vs.ReadChar(&car, 100);
        if (retour > 0) ret.push_back(car);
    } while (retour > 0);

    trame.clear();
    return true;

}

bool ServoDyn::setVitesse(int m_vitesse) {
    vitesse = 489 * m_vitesse;
    vitesse = vitesse / 55;
    if (vitesse < 490 && vitesse > -1) {
        sTrame();
        trame.push_back(0x05);
        trame.push_back(static_cast<int> (ServoDyn::INSTRUCTION::ECRITURED));
        trame.push_back(static_cast<int> (ServoDyn::REGISTRE::VITESSE));
        trame.push_back(vitesse & 0xFF);
        trame.push_back(vitesse >> 8);
        trame.push_back(calculChecksum(trame));

        if (envoyerDonnees(trame) == -1) return false;

        vector <unsigned char> ret;
        char car = 0;
        int retour = 0;
        do {
            retour = vs.ReadChar(&car, 100);
            if (retour > 0) ret.push_back(car);
        } while (retour > 0);

        trame.clear();
        return true;
    } else cout << "--hors if--" << endl;
    return false;
}

const int ServoDyn::getPosition() {
    sTrame();
    trame.push_back(0x04);
    trame.push_back(static_cast<int> (ServoDyn::INSTRUCTION::LECTURE));
    trame.push_back(static_cast<int> (ServoDyn::REGISTRE::POSITION));
    trame.push_back(0x02);
    trame.push_back(calculChecksum(trame));

    if (envoyerDonnees(trame) == -1)
        return -1;

    vector <unsigned char> ret;
    char car = 0;
    int retour = 0;
    do {
        retour = vs.ReadChar(&car, 100);
        if (retour > 0) ret.push_back(car);
    } while (retour > 0);

    position = (ret.at(5) + (ret.at(6) << 8)) * 180 / 2048;
    trame.clear();
    return position;
}

const int ServoDyn::getVitesse() {
    return vitesse * 55 / 489;
}

const int ServoDyn::getAcceleration() {
    return acceleration;
}