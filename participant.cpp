#include "participant.h"
#include "rdv.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

//CONSTRUCTEUR
participant::participant(){}
participant::participant(const string &nom,const string &prenom,const string &tel,const string &mail):
    d_nom{nom},d_prenom{prenom},d_tel{tel},d_email{mail}{}

//SURCHARGES
ostream &operator<<(ostream &ost, const participant &p)
{
    ost<<endl<<"Nom : "<<p.d_nom<<endl<<"Prenom : "<<p.d_prenom<<endl<<"Numero de tel : "<<p.d_tel<<endl<<"Adresse email : "<<p.d_email<<endl;
    return ost;
}


participant& participant::operator=(const participant &p)
{
    
        d_nom=p.d_nom;
        d_prenom=p.d_prenom;
        d_tel=p.d_tel;
        d_email=p.d_email;
    
    return *this;
}

bool participant::operator<(const participant &p)  //true si this < p
{
    if(this==&p) return false;
    return d_nom<p.d_nom;
}

bool participant::operator>(const participant &p)
{
    if(this==&p) return false;
    return d_nom>p.d_nom;
}

bool participant::operator==(const participant &p)
{
    return (d_nom==p.d_nom && d_prenom==p.d_prenom && d_email==p.d_email&& d_tel==p.d_tel);
}

bool participant::operator!=(const participant &p)
{
    if(*this==p)
    {
        return false;
    }
    return true;
}


//GETTERS
string participant::getNom() const
{
    return d_nom;
}
string participant::getPrenom() const
{
    return d_prenom;
}
string participant::getTel() const
{
    return d_tel;
}
string participant::getMail() const
{
    return d_email;
}
int participant::getNbRDV() const
{
    return d_listeRDV.size();
}

//AFFICHAGE
string participant::afficherListeRDV() const
{    string contenuListe = "";
    if(d_listeRDV.size()==0)
    {
        contenuListe="La personne selectionnée n'est inscrite à aucun rendez vous.";
    }
    else{

        for(int i=0;i<d_listeRDV.size();i++)
        {
            ostringstream oss;
            oss<<d_listeRDV[i];
            contenuListe += oss.str() + "\n";




        }
    }
    return contenuListe;
}

//AUTRE METHODES

void participant::supprimerRDV(const RDV &r)  //suppr le rdv r de la personne this
{
    
    int i=0;
    bool present=false;
    while(i<d_listeRDV.size()&& !present)
    {
        
        if(d_listeRDV[i]==r) 
        {
            present=true;
        }
        else 
        {
            i++;
        }
    }
    if(present)
    {
        
        for(int j=i; j < d_listeRDV.size() - 1; j++)
            d_listeRDV[j] = d_listeRDV[j + 1];

        d_listeRDV.pop_back();
    }
    
}

bool participant::chercheRDVDate(int hdebut,int hfin,int jour,int mois, int an)
{
    int i=0;
   
    while(i<d_listeRDV.size() && jour!=d_listeRDV[i].getJour() && mois!=d_listeRDV[i].getMois() && an!=d_listeRDV[i].getAn() && hdebut!=d_listeRDV[i].getHeureDebut() && hfin!=d_listeRDV[i].getHeureFin())
    {
        
        i++;
    }
    if(i>=d_listeRDV.size()) return false;
    if(jour==d_listeRDV[i].getJour() && mois==d_listeRDV[i].getMois() && an ==d_listeRDV[i].getAn() && hdebut==d_listeRDV[i].getHeureDebut() && hfin==d_listeRDV[i].getHeureFin() )
    {
        return true;
    }
    return false;
    
}

bool participant::chercheRDVChevauchement(RDV r)  //true si chevauchement
{
    int i=0;

    while(i<d_listeRDV.size() && !d_listeRDV[i].chevauchementRDV(r))

    {
        i++;
    }
    if(i>=d_listeRDV.size()) return false;
    if(d_listeRDV[i].chevauchementRDV(r)) return true;
    return false;
}



//SETTERS
participant participant::setEmailTel(string nom,string prenom,string mail,string tel)
{
    d_email=mail;
    d_tel=tel;
    return *this;
}

void participant::ajouterRDV(const RDV &r)
{
    d_listeRDV.push_back(r);
}



void participant::ecrireListeRdv(ostream &ost)
{
    if(d_listeRDV.size()==0)
    {
        ost<<"aucun rendez vous.\n";
    }
    else{

        for(int i=0;i<d_listeRDV.size();i++)
        {
            ost<<d_listeRDV[i].getNom()<<" le "<<d_listeRDV[i].getJour()<<"/"<<d_listeRDV[i].getMois()<<"/"<<d_listeRDV[i].getAn()<<" de "<<d_listeRDV[i].getHeureDebut()<<"h à "<<
                 d_listeRDV[i].getHeureFin()<<"h \n";



        }
    }
}


    
