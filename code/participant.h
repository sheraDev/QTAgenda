#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include "rdv.h"
#include <string>
#include <vector>

using namespace std;


class RDV;

class participant{
    friend class rdv;
    friend class LDCR;
    friend class LDCP;

public:

    //CONSTRUCTEURS
    participant();
    participant(const string &nom,const string &prenom,const string &tel,const string &mail);

    //SURCHARGES
    friend ostream &operator<<(ostream &ost, const participant &p);
    participant &operator=(const participant &p);
    bool operator<(const participant &p);
    bool operator>(const participant &p);
    bool operator==(const participant &p);
    bool operator!=(const participant &p);

    //GETTERS
    string getNom() const;
    string getPrenom() const;
    string getTel() const;
    string getMail() const;
    int getNbRDV() const;

    //AFFICHAGE
    string afficherListeRDV() const;
    //AUTRES
    void supprimerRDV(const RDV &r);

    //AUTRES METHODES
    void ajouterRDV(const RDV&rdv);  
    bool chercheRDVDate(int hdebut,int hfin,int jour,int mois, int a);  //true si this a un rdv
    bool chercheRDVChevauchement(RDV r);
    void ecrireListeRdv(ostream &ost) ;

   
   //SETTERS
   participant setEmailTel(string nom,string prenom,string mail,string tel);

private:
   string d_nom,d_prenom,d_email;
    string d_tel;
    vector<RDV> d_listeRDV;
};

#endif
