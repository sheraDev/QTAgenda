#include "rdv.h"
#include "participant.h"
#include <iostream>
#include <vector>
#include <sstream>


using namespace std;


//CONSTRUCTEURS
RDV::RDV(){}
RDV::RDV(const string &nom,const int &j,const int& m, const int& a,const int& hd,const int&hf):
    d_nom{nom},d_jour{j},d_hDebut{hd},d_hFin{hf},d_mois{m},d_an{a}{}


//SURCHARGES

std::ostream& operator<<(std::ostream& os, const RDV& r)
{
    os<<"Nom : "<<r.d_nom<<endl<<"Date : "<<r.d_jour<<"/"<<r.d_mois<<"/"<<r.d_an<<endl<<"De "<<r.d_hDebut<<"h jusqu a "<<r.d_hFin<<"h"<<endl;
    return os;
}
RDV& RDV::operator=(const RDV &r)
{
    if(*this!=r)
    {
        d_nom=r.d_nom;
        d_jour=r.d_jour;
        d_mois=r.d_mois;
        d_an=r.d_an;
        d_hDebut=r.d_hDebut;
        d_hFin=r.d_hFin;
    }
    return *this;
}
bool RDV::operator<(const RDV &r) //true si this <r
{
    return d_nom<r.d_nom; 
}
bool RDV::operator>(const RDV &r)
{
    return d_nom>r.d_nom;
}
bool RDV::operator==(const RDV &r)
{
    return (d_nom==r.d_nom && d_jour==r.d_jour&& d_mois==r.d_mois && d_an==r.d_an && d_hDebut==r.d_hDebut && d_hFin==r.d_hFin);
}
bool RDV::operator!=(const RDV &r)
{
    if(*this==r)
    {
        return false;
    }
    return true;
}

//GETTERS
string RDV::getNom() const
{
    return d_nom;
}
int RDV::getHeureDebut() const
{
    return d_hDebut;
}
int RDV::getHeureFin() const
{
    return d_hFin;
}
int RDV::getJour() const
{
    return d_jour;
}

int RDV::getMois() const
{
    return d_mois;
}

int RDV::getAn() const
{
    return d_an;
}

//AFFICHAGE
string RDV::afficherListeParticipants() const
{
    string contenuListe = "";

    if(d_listeParticipants.size()==0)
    {
        contenuListe="Aucun participant n'est inscrit à ce rdv.";
    }
    else{
        for(int i=0;i<d_listeParticipants.size();i++)
        {
            ostringstream oss;
            oss<<d_listeParticipants[i];
            contenuListe += oss.str() + "\n";
        }
    }
    return contenuListe;
}

//AUTRE METHODES

bool RDV::chevauchementRDV(const RDV &r)  //true si this et r se chevauchent
{

    if (d_jour == r.d_jour) {
           if (d_mois == r.d_mois && d_an == r.d_an) {
               bool A = d_hDebut == r.d_hDebut || d_hFin == r.d_hFin;
               bool B = d_hDebut < r.d_hDebut && d_hFin > r.d_hDebut;
               bool C = d_hDebut > r.d_hDebut && d_hDebut < r.d_hFin;

               if (A || B || C) {
                   return true;
               } else {
                   return false;
               }
           } else {
               return false;
           }
       }
       return false;
}
   
   


void RDV::ajtParticipant(const participant&p)  //ajt le rdv this au participant p
{
    d_listeParticipants.push_back(p);
}
void RDV::retirerParticipant(participant &p)  //supr le rdv this du participant p
{
    int i=0;

    //parcours de la liste de participants du rdv
    while(i<d_listeParticipants.size() && d_listeParticipants[i].getNom()!=p.getNom())
    {
        i++;
    }
    d_listeParticipants.erase(d_listeParticipants.begin()+i);
}

void RDV::setHoraireJour(int hd,int hf,int j,int m, int a)
{
    d_hDebut=hd;
    d_hFin=hf;
    d_jour=j;
    d_mois=m;
    d_an= a;
}


