#ifndef RDV_H 
#define RDV_H 
 
 #include <iostream>
 #include "participant.h"
 #include <vector>
 using namespace std;

 class participant;

 class RDV
 {
    friend class participant;
    friend class LDCP;
    friend class LDCR;
public:

    //CONSTRUCTEUR
    RDV();
    RDV(const string &nom,const int &j,const int& m, const int& a,const int& hd,const int&hf);

    //SURCHARGES
    friend ostream& operator<<(ostream &os,const RDV& r);
    RDV &operator=(const RDV &r);
    bool operator<(const RDV &r);
    bool operator>(const RDV &r);
    bool operator==(const RDV &r);
    bool operator!=(const RDV &r);

    //GETTERS
    string getNom() const;
    int getHeureDebut() const;
    int getHeureFin() const;
    int getJour() const;
    int getMois() const;
    int getAn() const;

    //AFFICHAGE
    string afficherListeParticipants() const;

    //AUTRES METHODES
    bool chevauchementRDV(const RDV &r);  //true si this et r se chevauchent

    void ajtParticipant(const participant &p);
    void retirerParticipant(participant &p);

    void setHoraireJour(int hd,int hf,int j,int m, int a);


    

private:
    string d_nom;
    int d_hDebut,d_hFin;
    int d_jour,d_mois,d_an;
    vector<participant> d_listeParticipants;
 
 };

#endif 














 
