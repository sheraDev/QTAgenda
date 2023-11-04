#ifndef LDCR_H
#define LDCR_H

#include "rdv.h"
#include "participant.h"
#include "LDCP.h"

class RDV;
class LDCP;


class chainonRDV
{
    friend class LDCR;

    private:

    chainonRDV(RDV & r):d_rdv{r},d_prec{nullptr},d_suiv{nullptr}{};
    RDV d_rdv;
    chainonRDV *d_prec;
    chainonRDV *d_suiv;    
};

class LDCR
{

    friend class LDCP;
public:
    //CONSTRUCTEURS/DESTRUCTEURS
    LDCR();
    LDCR(const LDCR&l);
    ~LDCR();

    //SURCHARGES
    bool operator==(const LDCR &l);
    bool operator!=(const LDCR &l);


    //AUTRES METHODES
    bool chercheParNom(string &nom, RDV &r);
    void ajtRdv(RDV &r);
    void modifRdv(string nom,int hd,int hf,int j, int m, int a);
    bool suprRdv(RDV &r);
    void ajtParticipantRdv(string nom, participant &p);
    string afficherRdvDate(int j, int m, int a);
    void retirerParticipantRdv(string nom,participant &p);


    //PR TEST
    string afficherListe()const;
    void EcrireListeFichier(string nomFichier);
    string afficherParticipantsRDV(string nom);
    bool participantsDispo(RDV r,RDV nouvRdv,LDCP lp);
    



private:
    chainonRDV *d_tete;

};


#endif
