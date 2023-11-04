#ifndef LDCP_H
#define LDCP_H

#include "participant.h"
#include "rdv.h"
#include "LDCR.h"

class participant;
class LDCR;

class chainonParticipant
{   friend class menu;
    friend class LDCP;


    private:
    chainonParticipant(participant p):d_participant(p),d_prec(nullptr),d_suiv(nullptr){};

    participant d_participant;
    chainonParticipant *d_prec,*d_suiv;


};

class LDCP
{

public:
    //CONSTRUCTEURS/DESTRUCTEUR
    LDCP();
    LDCP(const LDCP& lp);
    ~LDCP();

    //SURCHARGES
    bool operator==(const LDCP& lp);
    bool operator!=(const LDCP& lp);

    //AUTRES
    bool chercherParNom(string nom,participant &p);

    void ajtParticipant( participant p); //par ordre alphabetique
    void modifParticipant(string nom,string prenom,string email,string tel); //saisie nom/prenom et modif email/tel
    bool suprParticipant(participant &p);
    void ajtRDVParticipant(string nom,string prenom, RDV r); //ajouter un RDV au participant
    void retirerRDVParticipant(string nom,string prenom,RDV r);

    //
    string afficherContenuListe()const;
    string afficheParticipantRDV(string nom);
    bool aRDVMoment(participant p,int j,int hd,int hf,int m, int a);
    int NbRDVParticipant(participant p);
    bool RDVChevauchement(participant p,RDV r);
    void suprRDV(RDV r);
    bool chercheSiParticipantsDispo(RDV rdv,RDV nouvrdv);
    void EcrireListeFichier(string nomFichier);
    void EcrireListePRDVFichier();

 
private:
    chainonParticipant *d_tete;
    friend class menu;

};

#endif
