#include "participant.h"
#include "rdv.h"
#include "LDCP.h"
#include <sstream>
#include <fstream>


//CONSTRUCTEURS/DESTRUCTEUR
LDCP::LDCP():d_tete{nullptr}{}

LDCP::LDCP(const LDCP& lp):d_tete{nullptr}  //CONSTRCTEUR PAR RECOPIE
{
    chainonParticipant *crtLP= lp.d_tete;
    chainonParticipant *prec;

    while(crtLP!=nullptr)
    {
        chainonParticipant *nouv=new chainonParticipant{crtLP->d_participant};
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
        crtLP=crtLP->d_suiv;
    }

}
LDCP::~LDCP()
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr)
    {
        chainonParticipant *tmp=crt->d_suiv;
        delete crt;
        crt=tmp;
    }
    d_tete=nullptr;
}


//SURCHARGES
bool LDCP::operator==(const LDCP& lp)
{
    if(this==&lp) return true;
    
    chainonParticipant *crt=d_tete;
    chainonParticipant *crtLP=lp.d_tete;

    while(crt!=nullptr && crtLP!=nullptr && crt->d_participant==crtLP->d_participant) //tant quon n est pas a la fin 
    {        
        //passage au suivant                                                         //et que le chainon courant de this est egal
        crt=crt->d_suiv;                                                              // au chainon courant de lp
        crtLP=crtLP->d_suiv;
    }

    if(crt==nullptr && crtLP==nullptr) return true;
    return false;
}
bool LDCP::operator!=(const LDCP& lp)
{
    return !((*this)==lp);
}

//AUTRES

bool LDCP::chercherParNom(string nom,participant &p)
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr && crt->d_participant.getNom()!=nom)
    {
        crt=crt->d_suiv;
    }
    if(crt==nullptr) return false;
    else 
    {
        p=crt->d_participant;
        return true;
    }
        
}

void LDCP::ajtParticipant(participant p) //par ordre alphabetique
{
    
    chainonParticipant *nouv=new chainonParticipant{p};
    chainonParticipant *crt=d_tete;
    chainonParticipant *prec=nullptr;

    if(d_tete==nullptr) //CAS N 1 : LISTE VIDE => LE NOUVEL ELEMENT DEVIENT LA TETE
    {
        nouv->d_suiv=d_tete;
        d_tete=nouv;
        return ;
    }
    if(d_tete->d_suiv==nullptr) //CAS N 2 : LISTE CONTENANT 1 ELEMENT (LA TETE)
    {
       if(nouv->d_participant<d_tete->d_participant) //inserer en tete
        {
            nouv->d_suiv=d_tete;
            d_tete->d_prec=nouv;
            d_tete=nouv;
            return ;
        }
        if(nouv->d_participant>d_tete->d_participant) //inserer après la tete
        {
            d_tete->d_suiv=nouv;
            nouv->d_prec=d_tete;
            return ;
        }
    }
    //POUR TOUS LES AUTRES CAS
    while(crt!=nullptr && nouv->d_participant > crt->d_participant)  //tant que nouv est superieur a lelement courant
    {
        prec=crt;
        crt=crt->d_suiv;
    }
    if(prec!=nullptr)
    {
        prec->d_suiv=nouv;
   }
    else{
        d_tete=nouv;
    }

    nouv->d_suiv=crt;
    if(crt!=nullptr)
    {
        crt->d_prec=nouv;
    }

}

void LDCP::modifParticipant(string nom,string prenom,string email,string tel)
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr && crt->d_participant.getNom()!=nom)
    {
        crt=crt->d_suiv;
    }
    crt->d_participant=crt->d_participant.setEmailTel(nom,prenom,email,tel);


}

bool LDCP::suprParticipant(participant &p)
{
    if(d_tete!=nullptr)
    {
        chainonParticipant *crt=d_tete;
        chainonParticipant *prec=nullptr;

        //ON CHERCHE P
        while(crt!=nullptr && p!=crt->d_participant)
        {
            prec=crt;
            crt=crt->d_suiv;
        }

            chainonParticipant *suiv=crt->d_suiv;
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
    else
    {
        return false;
    }
}

void LDCP::ajtRDVParticipant(string nom,string prenom, RDV r) //ajouter un RDV au participant
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr && crt->d_participant.getNom()!=nom)  //le nom est unique donc recherche par nom seulement
    {
        crt=crt->d_suiv;
    }

    crt->d_participant.ajouterRDV(r);
}

void LDCP::retirerRDVParticipant(string nom,string prenom,RDV r)
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr && crt->d_participant.getNom()!=nom)  //le nom est unique donc recherche par nom seulement
    {
        crt=crt->d_suiv;
    }

    crt->d_participant.supprimerRDV(r);
}




string LDCP::afficherContenuListe() const
{
    string contenuListe = "";

    chainonParticipant *crt=d_tete;
    while(crt!=nullptr)
    {
        ostringstream oss;
        oss << crt->d_participant;
        contenuListe += oss.str() + "\n";

        crt=crt->d_suiv;
    }
    if(contenuListe=="")
        contenuListe="Auncun résultat";

    return contenuListe;
}

void LDCP::EcrireListeFichier(string nomFichier)
{
    int i=0;
    chainonParticipant *crt=d_tete;
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
               ost<<crt->d_participant.getNom()<<" ";
               ost<<crt->d_participant.getPrenom()<<" ";
               ost<<crt->d_participant.getMail()<<" ";
               ost<<crt->d_participant.getTel()<<" ";
               ost<<endl;
               crt=crt->d_suiv;
            }
            ost.close();
}

void LDCP::EcrireListePRDVFichier()
{

    string nomFichier="CARNET EXPORT";
    chainonParticipant *crt=d_tete;
        ofstream ost;
        ost.open(nomFichier);

           while(crt!=nullptr)
           {
            ost<<"Participant : \n";
              ost<<crt->d_participant.getNom()<<" ";
              ost<<crt->d_participant.getPrenom()<<" ";
              ost<<crt->d_participant.getMail()<<" ";
              ost<<crt->d_participant.getTel()<<" ";
              ost<<endl;

              ost<<"Liste de rendez-vous :\n";


             crt->d_participant.ecrireListeRdv(ost);


              ost<<endl;


              crt=crt->d_suiv;
           }
           ost.close();

}


string LDCP::afficheParticipantRDV(string nom)
{
    string contenuListe = "";
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr && crt->d_participant.getNom()!=nom)
    {
        crt=crt->d_suiv;
    }
    
    ostringstream oss;
    oss << crt->d_participant.afficherListeRDV();
    contenuListe += oss.str() + "\n";


    return contenuListe;
}

bool LDCP::aRDVMoment(participant p,int j,int hd,int hf, int m, int a)
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr && crt->d_participant!=p)
    {
        crt=crt->d_suiv;
    }
    if(crt->d_participant.chercheRDVDate(hd,hf,j,m,a)) return true;
    return false;

}

bool LDCP::RDVChevauchement(participant p,RDV r)
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr && crt->d_participant !=p)   //on cherche le participant
    {
        crt=crt->d_suiv;
    }
    if(crt->d_participant.chercheRDVChevauchement(r)) return true;
    return false;
}

int LDCP::NbRDVParticipant(participant p)
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr && crt->d_participant!=p)
    {
        crt=crt->d_suiv;
    }
    return crt->d_participant.getNbRDV();
}

void LDCP::suprRDV(RDV r)
{
    chainonParticipant *crt=d_tete;
    while(crt!=nullptr )  //parcourt les participants de LDCP
    {
        for(int i=0;i<crt->d_participant.d_listeRDV.size();i++)  //parcourt de la liste de RDV de chaque participant crt
        {
            if(crt->d_participant.d_listeRDV[i]==r) //si on trouve le rdv dans la liste de rdv de crt
            {
                crt->d_participant.supprimerRDV(r);
            }
        }
        crt=crt->d_suiv;
    }
}

bool LDCP::chercheSiParticipantsDispo(RDV rdv,RDV nouvrdv) //true si tlm dispo
{
    chainonParticipant *crt=d_tete;
    participant p;
    bool dsp=true;
    
    for(int i=0;i<rdv.d_listeParticipants.size();i++) //on parcourt les participants du rdv
    {
        chainonParticipant *crt=d_tete;
        while(crt!=nullptr && crt->d_participant!=rdv.d_listeParticipants[i])
        {
            crt=crt->d_suiv;
        }
        if(crt->d_participant.chercheRDVChevauchement(nouvrdv))
        {
            dsp=false;
        }
        

    }
    return dsp;
}

