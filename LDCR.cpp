#include "LDCR.h"
#include "LDCP.h"
#include "rdv.h"
#include "participant.h"
#include <iostream>
#include <sstream>
#include <fstream>

//CONSTRUCTEURS/DESTRUCTEURS
LDCR::LDCR():d_tete{nullptr}
{}
LDCR::LDCR(const LDCR&l):d_tete{nullptr}   //constructeur par recopie
{
    chainonRDV *crtLR= l.d_tete;
    chainonRDV *prec;

    while(crtLR!=nullptr)
    {
        chainonRDV *nouv=new chainonRDV{crtLR->d_rdv};
        if(d_tete==nullptr)
        {
            d_tete=nouv;
        }
        else
        {
            //chainage
            prec->d_suiv=nouv;
            nouv->d_prec=prec;
        }
        //passage au suivant
        prec=nouv;
        crtLR=crtLR->d_suiv;
    }

}
LDCR::~LDCR()
{
    chainonRDV *crt=d_tete;
    while(crt!=nullptr)
    {
        chainonRDV *tmp=crt->d_suiv;
        delete crt;
        crt=tmp;
    }
    d_tete=nullptr;
}

//SURCHARGES
bool LDCR::operator==(const LDCR &l)
{
    if(this==&l) return true;
    
    chainonRDV *crt=d_tete;
    chainonRDV *crtL=l.d_tete;

    while(crt!=nullptr && crtL!=nullptr && crt->d_rdv==crtL->d_rdv) //tant quon n est pas a la fin 
    {        
        //passage au suivant                                                         //et que le chainon courant de this est egal
        crt=crt->d_suiv;                                                              // au chainon courant de lp
        crtL=crtL->d_suiv;
    }

    if(crt==nullptr && crtL==nullptr) return true;
    return false;
}

bool LDCR::operator!=(const LDCR &l)
{
    return !((*this)==l);
}

//AUTRES METHODES
bool LDCR::chercheParNom(string &nom, RDV &r) //nom rdv=unique
{
    chainonRDV *crt=d_tete;
    while(crt!=nullptr && crt->d_rdv.getNom()!=nom)
    {
        crt=crt->d_suiv;
    }
    if(crt==nullptr) return false;
    else 
    {
        r=crt->d_rdv;
        return true;
    }
}




void LDCR::ajtRdv(RDV &r)
{
    chainonRDV *nouv=new chainonRDV{r};
    chainonRDV *crt=d_tete;
    chainonRDV *prec=nullptr;

    if(d_tete==nullptr) //CAS N 1 : LISTE VIDE => LE NOUVEL ELEMENT DEVIENT LA TETE
    {
        d_tete=nouv;
        return ;
    }
    if(d_tete->d_suiv==nullptr) //CAS N 2 : LISTE CONTENANT 1 ELEMENT (LA TETE)
    {
       if(nouv->d_rdv<d_tete->d_rdv) //inserer en tete
        {
            nouv->d_suiv=d_tete;
            d_tete->d_prec=nouv;
            d_tete=nouv;
            return ;
        }
        if(nouv->d_rdv>d_tete->d_rdv) //inserer après la tete
        {
            d_tete->d_suiv=nouv;
            nouv->d_prec=d_tete;
            return ;
        }
    }
    //POUR TOUS LES AUTRES CAS
    while(crt!=nullptr && nouv->d_rdv > crt->d_rdv)  //tant que nouv est superieur a lelement courant
    {
        prec=crt;
        crt=crt->d_suiv;
    }
    if(crt!=nullptr) //on nest pas  a la fin
    {
        crt->d_prec=nouv;
    }
    prec->d_suiv=nouv;
    nouv->d_prec=prec;
    nouv->d_suiv=crt;
}

void LDCR::modifRdv(string nom,int hd,int hf,int j,int m, int a)
{
    chainonRDV *crt=d_tete;
    while(crt!=nullptr && crt->d_rdv.getNom()!=nom)
    {
        crt=crt->d_suiv;
    }
    crt->d_rdv.setHoraireJour(hd,hf,j,m,a);
}


bool LDCR::suprRdv(RDV &r)
{
    if(d_tete!=nullptr)
    {
        chainonRDV *crt=d_tete;
        chainonRDV *prec=nullptr;

        while(crt!=nullptr && crt->d_rdv!=r)
        {
            prec=crt;
            crt=crt->d_suiv;
        }



        if(crt!=nullptr)
        {
            chainonRDV *suiv=crt->d_suiv;
            delete crt;
            
            if(prec!=nullptr)   //pas en tete
            {
                prec->d_suiv=suiv;
                
            }
            else // en tete
            {
                d_tete=suiv;
            }
            if(suiv!=nullptr) //pas a la fin
            {
                suiv->d_prec=prec;
            }
            return true;            


        }
        else{
            return false;
        }
    }
    else
    {
        return false;
    }
}
void LDCR::ajtParticipantRdv(string nom, participant &p) //ajt un participant p a un rdv nommé nom
{
    chainonRDV *crt=d_tete;
    while(crt!=nullptr && crt->d_rdv.getNom()!=nom)  //le nom est unique donc recherche par nom seulement
    {
        crt=crt->d_suiv;
    }
   
    crt->d_rdv.ajtParticipant(p);

}

void LDCR::retirerParticipantRdv(string nom,participant &p)
{
    chainonRDV *crt=d_tete;
    while(crt!=nullptr && crt->d_rdv.getNom()!=nom)  //le nom est unique donc recherche par nom seulement
    {
        crt=crt->d_suiv;
    }

    crt->d_rdv.retirerParticipant(p);

}



string LDCR::afficherRdvDate(int j,int m, int a)
{
    string contenuListe = "";
    int cpt=0;
    chainonRDV *crt=d_tete;
    string vide="";
    while(crt!=nullptr)
    {ostringstream oss;

        if(crt->d_rdv.getJour()==j && crt->d_rdv.getMois()==m && crt->d_rdv.getAn()==a)
        {


            oss<<crt->d_rdv;
            contenuListe += oss.str() + "\n";
            cpt++;
        }
        crt=crt->d_suiv;
    }
  
if(cpt==0) return vide;
else
return contenuListe;
}



//PR TEST

string LDCR::afficherListe()const
{
    string contenuListe = "";

    chainonRDV *crt=d_tete;
    while(crt!=nullptr)
    {
        ostringstream oss;
        oss<<crt->d_rdv;
        contenuListe += oss.str() + "\n";
        crt=crt->d_suiv;
    }
    if(contenuListe=="")
        contenuListe="Auncun résultat";

    return contenuListe;

}

void LDCR::EcrireListeFichier(string nomFichier)
{
    int i=0;
    chainonRDV *crt=d_tete;
    while(crt!=nullptr)
    {
        i++;
        crt=crt->d_suiv;
    }
         ofstream ost;
         ost.open(nomFichier);
         crt=d_tete;
         ost<<i<<endl;
            while(crt!=nullptr)
            {
               ost<<crt->d_rdv.getNom()<<" ";
               ost<<crt->d_rdv.getJour()<<"/"<<crt->d_rdv.getMois()<<"/"<<crt->d_rdv.getAn()<<" ";
               ost<<crt->d_rdv.getHeureDebut()<<" ";
               ost<<crt->d_rdv.getHeureFin()<<" ";
               ost<<endl;
               crt=crt->d_suiv;
            }
            ost.close();
}


string LDCR::afficherParticipantsRDV(string nom)
{
    string contenuListe = "";
    chainonRDV *crt=d_tete;
    while(crt!=nullptr && crt->d_rdv.getNom()!=nom) //cherche le rdv nommé nom
    { 

        crt=crt->d_suiv;
    }
    ostringstream oss;
    oss<<crt->d_rdv.afficherListeParticipants();
    contenuListe += oss.str() + "\n";


    return contenuListe;
}

bool LDCR::participantsDispo(RDV r,RDV nouvRdv,LDCP lp)  //true = tlm dispo
{
    chainonRDV *crt=d_tete;
    bool pasdisp=false;
    while(crt!=nullptr && crt->d_rdv!=r )
    {
        crt=crt->d_suiv;
    }

    return lp.chercheSiParticipantsDispo(crt->d_rdv,nouvRdv);
    
    


}

