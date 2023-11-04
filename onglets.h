#ifndef ONGLETS_H
#define ONGLETS_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QMessageBox>
#include "LDCP.h"
#include "LDCR.h"
#include "participant.h"
#include "rdv.h"

class onglets : public QWidget
{
    Q_OBJECT

public:
    onglets(QWidget *parent = nullptr);
    ~onglets();
    void creeInterface();
    void ajouterPersonne();
    void modifierPersonne();
    void supprimerPersonne();
    void afficherPersonnes();

    void ajouterRDV();
    void modifierRDV();
    void supprimerRDV();
    void afficherRDVs();

    void ajouterParticipantAUnRDV();
    void afficherParticipantsDUnRDV();
    void afficherRDVsDate();
    void afficherRDVsDUnParticipant();
    void rechercher();

    void exporterParticipant();
    void importerParticipant();

    void exporterRDV();
    void importerRDV();

    void exporterCarnet();

    void retirer();

    void quitter();

    void on_calendarWidget_selectionChanged();

private:
    QTableWidget* participantsTableWidget;
    QLabel* nomLabelA;
    QLabel* prenomLabelA ;
    QLabel* emailLabelA ;
    QLabel* telephoneLabelA ;
    QLineEdit* nomLineEditA;
    QLineEdit* prenomLineEditA ;
    QLineEdit* emailLineEditA ;
    QLineEdit* telephoneLineEditA ;
    QPushButton* ajouterParticipantButtonA ;
    QPushButton* afficherTousParticipantsButton;

    QLabel* nomLabelM;
    QLabel* prenomLabelM ;
    QLabel* emailLabelM ;
    QLabel* telephoneLabelM ;
    QLineEdit* nomLineEditM;
    QLineEdit* prenomLineEditM ;
    QLineEdit* nouveauEmailLineEditM ;
    QLineEdit* nouveauTelephoneLineEditM ;
    QPushButton* modifierParticipantButtonM;

    QLabel* nomLabelS;
    QLabel* prenomLabelS ;
    QLineEdit* nomLineEditS;
    QLineEdit* prenomLineEditS;
    QPushButton* supprimerParticipantButtonS;
    QPushButton* afficherParticipantButton;
    QPushButton* ajouterParticipantRDVButton;


    QLabel* nomLabelR ;
    QLabel* dateLabel ;
    QLabel* heureDebutLabel ;
    QLabel* heureFinLabel ;
    QLineEdit* nomLineEditR ;
    QLineEdit* dateLineEdit ;
    QLineEdit* heureDebutLineEdit;
    QLineEdit* heureFinLineEdit ;
    QPushButton* ajouterRDVButton ;
    QPushButton* supprimerRDVButton;
    QPushButton* afficherRDVButton;
    QPushButton* modifierRdvButton;


    QLabel* nomLabelAPR;
    QLabel* prenomLabelAPR ;
    QLineEdit* nomLineEditAPR;
    QLineEdit* prenomLineEditAPR ;
    QLabel* objectifLabelAPR;
    QLineEdit* objectifLineEditAPR;

    QLabel* nomLabelAffRsP;
    QLineEdit* nomLineEditAffRsP;
    QPushButton* afficherTousRDVsPersonne;

    QLabel* nomLabelAffRD ;
    QLineEdit* objectifLineEditAffRD ;
    QPushButton* afficherRDVDateButton;

    /***********************************************************/
    QTableWidget* participantsTableWidgetR;
    QLabel* objectifLabelAR;
    QLabel* dateLabelAR ;
    QLabel* heureDebutLabelAR ;
    QLabel* heureFinLabelAR ;
    QLineEdit* objectifLineEditAR;
    QLineEdit* dateLineEditAR ;
    QLineEdit* heureDebutLineEditAR ;
    QLineEdit* heureFinLineEditAR ;
    QPushButton* ajouterRDVButtonAR ;

    QLabel* objectifLabelMR;
    QLabel* dateLabelMR ;
    QLabel* heureDebutLabelMR ;
    QLabel* heureFinLabelMR ;
    QLineEdit* objectifLineEditMR;
    QLineEdit* dateLineEditMR ;
    QLineEdit* heureDebutLineEditMR ;
    QLineEdit* heureFinLineEditMR ;
    QPushButton* modifierRDVButtonMR;

    QLabel* nomLabelSR ;
    QLineEdit* objectifLineEditSR;
    QPushButton* supprimerRDVButtonSR;
    QPushButton* afficherTousRDVsButton;

    QLabel* nomLabelRechercheP;
    QLineEdit* objectifLineEditRechercheP ;
    QLabel* dateLabelRechercheP ;
    QLineEdit* dateLineEditRechercheP ;
    QLabel* hDebutLabelRechercheP ;
    QLineEdit* hDebutLineEditRechercheP ;
    QLabel* hFinLabelRechercheP ;
    QLineEdit* hFinLineEditRechercheP ;
    QPushButton* rehcercherRDVPButtonRR ;

    QLabel* nomLabelAffPR ;
    QLineEdit* nomLineEditAffPR ;
    QPushButton* afficherParticipantsRDVButton ;

    QLabel* nomLabelFichierExportParticipants;
    QLineEdit* nomLineEditFichierExportParticipants ;
    QPushButton* exporterPButton;

    QLabel* nomLabelFichierImportParticipants;
    QLineEdit* nomLineEditFichierImportParticipants ;
    QPushButton* importerPButton;

    QLabel* nomLabelFichierExportRDV;
    QLineEdit* nomLineEditFichierExportRDV ;
    QPushButton* exporterRButton;

    QLabel* nomLabelFichierImportRDV;
    QLineEdit* nomLineEditFichierImportRDV ;
    QPushButton* importerRButton;

    QPushButton* quitterButton;

    QLabel* nomLabelRetirerP;
    QLabel* prenomLabelRetirerP ;
    QLineEdit* nomLineEditRetirerP;
    QLineEdit* prenomLineEditRetirerP;
    QPushButton* retirerButton;
    QLabel* nomRDVLabelRetirerParticipant;
    QLineEdit* nomRDVLineEditRetirerParticipant;

    QPushButton* exporterCarnetButton;

};
#endif // ONGLETS_H
