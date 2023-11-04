#include "onglets.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QTextEdit>
#include <fstream>
#include <QCalendarWidget>
#include "LDCP.h"
#include "LDCR.h"
#include "participant.h"
#include "rdv.h"

LDCP listeP;
LDCR listeRDV;

string prenom,nom,email, nomFichier,tel;
int jour,hdebut,hfin,choix,nb,mois,an;


onglets::onglets(QWidget *parent)
    : QWidget(parent)
{
    creeInterface();

}

onglets::~onglets()
{
}

void onglets::creeInterface()
{
    // Créer un widget QTabWidget
    QTabWidget* Grandonglets = new QTabWidget(this);

    QTabWidget* onglets = new QTabWidget(this);
    QTabWidget* ongletsFichiers = new QTabWidget(this);
    QTabWidget* ongletsAffichage = new QTabWidget(this);

    // Créer les onglets et ajouter des widgets à chaque onglet
    QWidget* ongletAjouter = new QWidget(onglets);
    QWidget* ongletModifier = new QWidget(onglets);
    QWidget* ongletSupprimer = new QWidget(onglets);
    QWidget* ongletAjouterPAR = new QWidget(onglets);
    QWidget* ongletAfficherRsP = new QWidget(onglets);
    QWidget* ongletExportP = new QWidget(onglets);
    QWidget* ongletImportP = new QWidget(onglets);
    QWidget* ongletRetirer = new QWidget(onglets);
    //QWidget* ongletsFichiers = new QWidget(onglets);

    //QWidget* ongletGestionParticipant = new QWidget(Grandonglets);

    // Ajouter des widgets aux onglets (vous pouvez remplacer les QLineEdit avec les widgets de votre choix)
    nomLabelA = new QLabel("Nom : ");
    prenomLabelA = new QLabel("Prénom : ");
    emailLabelA = new QLabel("Email : ");
    telephoneLabelA = new QLabel("Téléphone : ");
    nomLineEditA = new QLineEdit;
    prenomLineEditA = new QLineEdit;
    emailLineEditA = new QLineEdit;
    telephoneLineEditA = new QLineEdit;
    ajouterParticipantButtonA = new QPushButton("Ajouter");

    QVBoxLayout* layoutAjouter = new QVBoxLayout(ongletAjouter);
    layoutAjouter->addWidget(nomLabelA);
    layoutAjouter->addWidget(nomLineEditA);
    layoutAjouter->addWidget(prenomLabelA);
    layoutAjouter->addWidget(prenomLineEditA);
    layoutAjouter->addWidget(emailLabelA);
    layoutAjouter->addWidget(emailLineEditA);
    layoutAjouter->addWidget(telephoneLabelA);
    layoutAjouter->addWidget(telephoneLineEditA);
    layoutAjouter->addWidget(ajouterParticipantButtonA);
    ongletAjouter->setLayout(layoutAjouter);

    QVBoxLayout* layoutModifier = new QVBoxLayout(ongletModifier);
    nomLabelM = new QLabel("Nom : ");
    prenomLabelM = new QLabel("Prénom : ");
    emailLabelM  = new QLabel("Nouveau email");
    telephoneLabelM = new QLabel("Nouveau téléphone");
    nomLineEditM = new QLineEdit;
    prenomLineEditM = new QLineEdit;
    nouveauEmailLineEditM = new QLineEdit;
    nouveauTelephoneLineEditM = new QLineEdit;
    modifierParticipantButtonM = new QPushButton("Modifier");
    // Ajouter des widgets pour la modification d'une personne
    layoutModifier->addWidget(nomLabelM);
    layoutModifier->addWidget(nomLineEditM);
    layoutModifier->addWidget(prenomLabelM);
    layoutModifier->addWidget(prenomLineEditM);
    layoutModifier->addWidget(emailLabelM);
    layoutModifier->addWidget(nouveauEmailLineEditM);
    layoutModifier->addWidget(telephoneLabelM);
    layoutModifier->addWidget(nouveauTelephoneLineEditM);
    layoutModifier->addWidget(modifierParticipantButtonM);
    ongletModifier->setLayout(layoutModifier);

    QVBoxLayout* layoutSupprimer = new QVBoxLayout(ongletSupprimer);
    // Ajouter des widgets pour la suppression d'une personne
    nomLabelS = new QLabel("Nom : ");
    prenomLabelS = new QLabel("Prénom : ");
    nomLineEditS = new QLineEdit;
    prenomLineEditS = new QLineEdit;
    supprimerParticipantButtonS = new QPushButton("Supprimer");
    layoutSupprimer->addWidget(nomLabelS);
    layoutSupprimer->addWidget(nomLineEditS);
    layoutSupprimer->addWidget(prenomLabelS);
    layoutSupprimer->addWidget(prenomLineEditS);
    layoutSupprimer->addWidget(supprimerParticipantButtonS);
    ongletSupprimer->setLayout(layoutSupprimer);

    QVBoxLayout* layoutAjouterPAR = new QVBoxLayout(ongletAjouterPAR);
    // Ajouter des widgets pour l'ajout d'une personne à un rdv
    nomLabelAPR = new QLabel("Nom personne : ");
    prenomLabelAPR = new QLabel("Prenom personne : ");
    nomLineEditAPR = new QLineEdit;
    prenomLineEditAPR = new QLineEdit;
    objectifLabelAPR = new QLabel("Nom rendez-vous : ");
    objectifLineEditAPR = new QLineEdit;
    ajouterParticipantRDVButton = new QPushButton("Ajouter un participant à un rendez-vous");
    layoutAjouterPAR->addWidget(nomLabelAPR);
    layoutAjouterPAR->addWidget(nomLineEditAPR);
    layoutAjouterPAR->addWidget(prenomLabelAPR);
    layoutAjouterPAR->addWidget(prenomLineEditAPR);
    layoutAjouterPAR->addWidget(objectifLabelAPR);
    layoutAjouterPAR->addWidget(objectifLineEditAPR);
    layoutAjouterPAR->addWidget(ajouterParticipantRDVButton);
    ongletSupprimer->setLayout(layoutAjouterPAR);

    QVBoxLayout* layoutAfficherRsP = new QVBoxLayout(ongletAjouterPAR);
    // Ajouter des widgets pour l'affichage des rdv d'un participant
    nomLabelAffRsP = new QLabel("Nom personne : ");
    nomLineEditAffRsP = new QLineEdit;
    afficherTousRDVsPersonne = new QPushButton("Afficher tous les rendez-vous d'un participant");
    layoutAfficherRsP->addWidget(nomLabelAffRsP);
    layoutAfficherRsP->addWidget(nomLineEditAffRsP);
    layoutAfficherRsP->addWidget(afficherTousRDVsPersonne);
    ongletAfficherRsP->setLayout(layoutAfficherRsP);


    QVBoxLayout* layoutExportP = new QVBoxLayout(ongletExportP);
    // Ajouter des widgets pour l'exportation des participants dans un fichier texte
    nomLabelFichierExportParticipants = new QLabel ("Nom du fichier");
    nomLineEditFichierExportParticipants = new QLineEdit;
    exporterPButton = new QPushButton ("Exporter");
    layoutExportP->addWidget(nomLabelFichierExportParticipants);
    layoutExportP->addWidget(nomLineEditFichierExportParticipants);
    layoutExportP->addWidget(exporterPButton);
    ongletExportP->setLayout(layoutExportP);

    QVBoxLayout* layoutImportP = new QVBoxLayout(ongletImportP);
    // Ajouter des widgets pour l'importation des participants depuis un fichier texte
    nomLabelFichierImportParticipants = new QLabel ("Nom du fichier");
    nomLineEditFichierImportParticipants = new QLineEdit;
    importerPButton = new QPushButton ("Importer");
    layoutImportP->addWidget(nomLabelFichierImportParticipants);
    layoutImportP->addWidget(nomLineEditFichierImportParticipants);
    layoutImportP->addWidget(importerPButton);
    ongletImportP->setLayout(layoutImportP);

    QVBoxLayout* layoutRetirer = new QVBoxLayout(ongletRetirer);
    // Ajouter des widgets pour retirer un rdv d'un participant
    nomLabelRetirerP = new QLabel("Nom : ");
    prenomLabelRetirerP = new QLabel("Prenom : ");
    nomLineEditRetirerP = new QLineEdit;
    prenomLineEditRetirerP = new QLineEdit;
    nomRDVLabelRetirerParticipant = new QLabel("Nom rendez-vous : ");
    nomRDVLineEditRetirerParticipant = new QLineEdit;
    retirerButton = new QPushButton ("Retirer");
    layoutRetirer->addWidget(nomLabelRetirerP);
    layoutRetirer->addWidget(nomLineEditRetirerP);
    layoutRetirer->addWidget(prenomLabelRetirerP);
    layoutRetirer->addWidget(prenomLineEditRetirerP);
    layoutRetirer->addWidget(nomRDVLabelRetirerParticipant);
    layoutRetirer->addWidget(nomRDVLineEditRetirerParticipant);
    layoutRetirer->addWidget(retirerButton);
    ongletRetirer->setLayout(layoutRetirer);

    // Ajouter les onglets au QTabWidget
    onglets->addTab(ongletAjouter, "Ajouter");
    onglets->addTab(ongletModifier, "Modifier");
    onglets->addTab(ongletSupprimer, "Supprimer");
    onglets->addTab(ongletAjouterPAR, "Ajouter un participant à un rendez-vous");
    onglets->addTab(ongletRetirer, "Retirer un participant d'un rendez-vous");
    ongletsAffichage->addTab(ongletAfficherRsP,"Les rendez-vous d'un participant");
    ongletsFichiers->addTab(ongletExportP,"Exporter les participants dans un fichier");
    ongletsFichiers->addTab(ongletImportP,"Importer les participants depuis un fichier");

    afficherTousParticipantsButton = new QPushButton("Afficher tous les participants");


    // Ajouter le QTabWidget à la boîte principale
    QHBoxLayout* layoutPrincipal = new QHBoxLayout();
    Grandonglets->addTab(ongletsFichiers,"Fichier");
    Grandonglets->addTab(onglets,"Gestion des personnes");
    layoutPrincipal->addWidget(Grandonglets);


    // Créer un widget QTabWidget
    QTabWidget* ongletsR = new QTabWidget(this);

    // Créer les onglets et ajouter des widgets à chaque onglet
    QWidget* ongletAjouterR = new QWidget(ongletsR);
    QWidget* ongletModifierR = new QWidget(ongletsR);
    QWidget* ongletSupprimerR = new QWidget(ongletsR);
    QWidget* ongletAfficherRD = new QWidget(ongletsR);
    QWidget* ongletRechercher = new QWidget(ongletsR);
    QWidget* ongletAfficherPRD = new QWidget(ongletsR);
    QWidget* ongletExportR = new QWidget(ongletsR);
    QWidget* ongletImportR = new QWidget(ongletsR);



    // Ajouter des widgets aux onglets
    objectifLabelAR = new QLabel("Nom : ");
    dateLabelAR = new QLabel("Date : ");
    heureDebutLabelAR = new QLabel("Heure de début en heure : ");
    heureFinLabelAR = new QLabel("Heure de fin en heure : ");
    objectifLineEditAR = new QLineEdit;
    dateLineEditAR = new QLineEdit;
    heureDebutLineEditAR = new QLineEdit;
    heureFinLineEditAR = new QLineEdit;
    ajouterRDVButtonAR = new QPushButton("Ajouter");
    QCalendarWidget *calendar = new QCalendarWidget();
    QVBoxLayout* layoutAjouterR = new QVBoxLayout(ongletAjouterR);
    layoutAjouterR->addWidget(objectifLabelAR);
    layoutAjouterR->addWidget(objectifLineEditAR);
    layoutAjouterR->addWidget(dateLabelAR);
    layoutAjouterR->addWidget(calendar);
    QPushButton *button = new QPushButton("Sélectionner");
    layoutAjouterR->addWidget(button);
    layoutAjouterR->addWidget(dateLineEditAR);
    connect(button, &QPushButton::clicked, [=]() {
        QDate selectedDate = calendar->selectedDate();
        QString dateString = selectedDate.toString("dd/MM/yyyy");
        dateLineEditAR->setText(dateString);});
    layoutAjouterR->addWidget(heureDebutLabelAR);
    layoutAjouterR->addWidget(heureDebutLineEditAR);
    layoutAjouterR->addWidget(heureFinLabelAR);
    layoutAjouterR->addWidget(heureFinLineEditAR);
    layoutAjouterR->addWidget(ajouterRDVButtonAR);
    ongletAjouterR->setLayout(layoutAjouterR);

    QVBoxLayout* layoutModifierR = new QVBoxLayout(ongletModifierR);
    objectifLabelMR = new QLabel("Nom : ");
    dateLabelMR = new QLabel("Nouvelle date : ");
    heureDebutLabelMR  = new QLabel("Nouvelle heure de debut");
    heureFinLabelMR = new QLabel("Nouvelle heure de debut");
    objectifLineEditMR = new QLineEdit;
    dateLineEditMR = new QLineEdit;
    heureDebutLineEditMR = new QLineEdit;
    heureFinLineEditMR = new QLineEdit;
    modifierRDVButtonMR = new QPushButton("Modifier");
    QCalendarWidget *calendarM = new QCalendarWidget();
    // Ajouter des widgets pour la modification d'un RDV
    layoutModifierR->addWidget(objectifLabelMR);
    layoutModifierR->addWidget(objectifLineEditMR);
    layoutModifierR->addWidget(dateLabelMR);
    layoutModifierR->addWidget(calendarM);
    QPushButton *buttonM = new QPushButton("Sélectionner");
    layoutModifierR->addWidget(buttonM);
    layoutModifierR->addWidget(dateLineEditMR);
    connect(buttonM, &QPushButton::clicked, [=]() {
        QDate selectedDate = calendarM->selectedDate();
        QString dateStringM = selectedDate.toString("dd/MM/yyyy");
        dateLineEditMR->setText(dateStringM);});
    layoutModifierR->addWidget(heureDebutLabelMR);
    layoutModifierR->addWidget(heureDebutLineEditMR);
    layoutModifierR->addWidget(heureFinLabelMR);
    layoutModifierR->addWidget(heureFinLineEditMR);
    layoutModifierR->addWidget(modifierRDVButtonMR);
    ongletModifierR->setLayout(layoutModifierR);

    QVBoxLayout* layoutSupprimerR = new QVBoxLayout(ongletSupprimerR);
    // Ajouter des widgets pour la suppression d'un RDV
    nomLabelSR = new QLabel("Nom rendez-vous : ");
    objectifLineEditSR = new QLineEdit;
    supprimerRDVButtonSR = new QPushButton("Supprimer");
    layoutSupprimerR->addWidget(nomLabelSR);
    layoutSupprimerR->addWidget(objectifLineEditSR);
    layoutSupprimerR->addWidget(supprimerRDVButtonSR);
    ongletSupprimerR->setLayout(layoutSupprimerR);

    QVBoxLayout* layoutRechercher = new QVBoxLayout(ongletRechercher);
    // Ajouter des widgets pour la recherche d'un participant pour un rdv donné
    nomLabelRechercheP = new QLabel("Nom personne : ");
    objectifLineEditRechercheP = new QLineEdit;
    dateLabelRechercheP = new QLabel("Date : ");
    dateLineEditRechercheP = new QLineEdit;
    hDebutLabelRechercheP = new QLabel("Heure de début en heure : ");
    hDebutLineEditRechercheP = new QLineEdit;
    hFinLabelRechercheP = new QLabel("Heure de fin en heure : ");
    hFinLineEditRechercheP = new QLineEdit;
    rehcercherRDVPButtonRR = new QPushButton("Rechercher");
    layoutRechercher->addWidget(nomLabelRechercheP);
    layoutRechercher->addWidget(objectifLineEditRechercheP);
    layoutRechercher->addWidget(dateLabelRechercheP);

    QCalendarWidget *calendarRecherche = new QCalendarWidget();
    layoutRechercher->addWidget(calendarRecherche);
    QPushButton *buttonRecherche = new QPushButton("Sélectionner");
    layoutRechercher->addWidget(buttonRecherche);
    layoutRechercher->addWidget(dateLineEditRechercheP);
    connect(buttonRecherche, &QPushButton::clicked, [=]() {
        QDate selectedDate = calendarRecherche->selectedDate();
        QString dateStringM = selectedDate.toString("dd/MM/yyyy");
        dateLineEditRechercheP->setText(dateStringM);});

    layoutRechercher->addWidget(dateLineEditRechercheP);
    layoutRechercher->addWidget(hDebutLabelRechercheP);
    layoutRechercher->addWidget(hDebutLineEditRechercheP);
    layoutRechercher->addWidget(hFinLabelRechercheP);
    layoutRechercher->addWidget(hFinLineEditRechercheP);
    layoutRechercher->addWidget(rehcercherRDVPButtonRR);
    ongletSupprimerR->setLayout(layoutSupprimerR);

    QVBoxLayout* layoutAfficherRD = new QVBoxLayout(ongletAfficherRD);
    // Ajouter des widgets pour l'affichage des rdv pour une date donnée
    nomLabelAffRD = new QLabel("Date : ");
    objectifLineEditAffRD = new QLineEdit;
    afficherRDVDateButton = new QPushButton("Afficher les rendez-vous");
    layoutAfficherRD->addWidget(nomLabelAffRD);

    QCalendarWidget *calendarAfficheRDVs = new QCalendarWidget();
    layoutAfficherRD->addWidget(calendarAfficheRDVs);
    QPushButton *buttonAfficheRDVs = new QPushButton("Sélectionner");
    layoutAfficherRD->addWidget(buttonAfficheRDVs);
    layoutAfficherRD->addWidget(objectifLineEditAffRD);
    connect(buttonAfficheRDVs, &QPushButton::clicked, [=]() {
        QDate selectedDate = calendarAfficheRDVs->selectedDate();
        QString dateStringM = selectedDate.toString("dd/MM/yyyy");
        objectifLineEditAffRD->setText(dateStringM);});

    layoutAfficherRD->addWidget(objectifLineEditAffRD);
    layoutAfficherRD->addWidget(afficherRDVDateButton);
    ongletAfficherRD->setLayout(layoutAfficherRD);

    QVBoxLayout* layoutAfficherPRD = new QVBoxLayout(ongletAfficherPRD);
    // Ajouter des widgets pour l'affichage des participants d'un rdv
    nomLabelAffPR = new QLabel("Nom rendez-vous : ");
    nomLineEditAffPR= new QLineEdit ;
    afficherParticipantsRDVButton = new QPushButton("Afficher les participants d'un rendez-vous");
    layoutAfficherPRD->addWidget(nomLabelAffPR);
    layoutAfficherPRD->addWidget(nomLineEditAffPR);
    layoutAfficherPRD->addWidget(afficherParticipantsRDVButton);
    ongletAfficherPRD->setLayout(layoutAfficherPRD);

    QVBoxLayout* layoutExportR = new QVBoxLayout(ongletExportR);
    // Ajouter des widgets pour l'exportation des rdv dans fichier texte
    nomLabelFichierExportRDV = new QLabel ("Nom du fichier");
    nomLineEditFichierExportRDV = new QLineEdit;
    exporterRButton = new QPushButton ("Exporter");
    layoutExportR->addWidget(nomLabelFichierExportRDV);
    layoutExportR->addWidget(nomLineEditFichierExportRDV);
    layoutExportR->addWidget(exporterRButton);
    ongletExportR->setLayout(layoutExportR);

    QVBoxLayout* layoutImportR = new QVBoxLayout(ongletImportR);
    // Ajouter des widgets pour l'exportation des rdv dans fichier texte
    nomLabelFichierImportRDV = new QLabel ("Nom du fichier");
    nomLineEditFichierImportRDV = new QLineEdit;
    importerRButton = new QPushButton ("Importer");
    layoutImportR->addWidget(nomLabelFichierImportRDV);
    layoutImportR->addWidget(nomLineEditFichierImportRDV);
    layoutImportR->addWidget(importerRButton);
    ongletImportR->setLayout(layoutImportR);

    // Ajouter les onglets au QTabWidget
    ongletsR->addTab(ongletAjouterR, "Ajouter");
    ongletsR->addTab(ongletModifierR, "Modifier");
    ongletsR->addTab(ongletSupprimerR, "Supprimer");
    ongletsAffichage->addTab(ongletAfficherRD, "Les rendez-vous pour une date");
    ongletsAffichage->addTab(ongletRechercher, "Rechercher si une personne à un rendez-vous");
    ongletsAffichage->addTab(ongletAfficherPRD, "Les participants d'un rendez-vous");
    ongletsFichiers->addTab(ongletExportR,"Exporter les rendez-vous dans un fichier");
    ongletsFichiers->addTab(ongletImportR,"Importer les rendez-vous depuis un fichier");

    afficherTousRDVsButton = new QPushButton("Afficher tous les rendez-vous");

    exporterCarnetButton = new QPushButton("Exporter le carnet");
    quitterButton = new QPushButton("Quitter");

    Grandonglets->addTab(ongletsR,"Gestion des rendez-vous");
    Grandonglets->addTab(ongletsAffichage,"Affichage");
    QVBoxLayout* boiteBoutons = new QVBoxLayout();
    boiteBoutons->addWidget(afficherTousParticipantsButton);
    boiteBoutons->addWidget(afficherTousRDVsButton);
    boiteBoutons->addWidget(exporterCarnetButton);
    boiteBoutons->addWidget(quitterButton);
    layoutPrincipal->addLayout(boiteBoutons);
    setLayout(layoutPrincipal);

    connect(ajouterParticipantButtonA , &QPushButton::clicked, this, &onglets::ajouterPersonne);
    connect(modifierParticipantButtonM , &QPushButton::clicked, this, &onglets::modifierPersonne);
    connect(supprimerParticipantButtonS , &QPushButton::clicked, this, &onglets::supprimerPersonne);
    connect(afficherTousParticipantsButton , &QPushButton::clicked, this, &onglets::afficherPersonnes);

    connect(ajouterRDVButtonAR , &QPushButton::clicked, this, &onglets::ajouterRDV);
    connect(modifierRDVButtonMR , &QPushButton::clicked, this, &onglets::modifierRDV);
    connect(supprimerRDVButtonSR , &QPushButton::clicked, this, &onglets::supprimerRDV);
    connect(afficherTousRDVsButton , &QPushButton::clicked, this, &onglets::afficherRDVs);

    connect(ajouterParticipantRDVButton , &QPushButton::clicked, this, &onglets::ajouterParticipantAUnRDV);
    connect(afficherTousRDVsPersonne , &QPushButton::clicked, this, &onglets::afficherRDVsDUnParticipant);
    connect(afficherRDVDateButton , &QPushButton::clicked, this, &onglets::afficherRDVsDate);
    connect( rehcercherRDVPButtonRR, &QPushButton::clicked, this, &onglets::rechercher);

    connect( afficherParticipantsRDVButton, &QPushButton::clicked, this, &onglets::afficherParticipantsDUnRDV);
    connect( exporterPButton, &QPushButton::clicked, this, &onglets::exporterParticipant);
    connect( importerPButton, &QPushButton::clicked, this, &onglets::importerParticipant);

    connect( exporterRButton, &QPushButton::clicked, this, &onglets::exporterRDV);
    connect( importerRButton, &QPushButton::clicked, this, &onglets::importerRDV);
    connect( retirerButton, &QPushButton::clicked, this, &onglets::retirer);
    connect( quitterButton, &QPushButton::clicked, this, &onglets::quitter);
    connect( exporterCarnetButton, &QPushButton::clicked, this, &onglets::exporterCarnet);

}



void onglets::ajouterPersonne() {
    // Récupérez les informations de la personne saisies dans les champs de texte
    string nom = nomLineEditA->text().toStdString();
    string prenom = prenomLineEditA->text().toStdString();
    string email = emailLineEditA->text().toStdString();
    string tel = telephoneLineEditA->text().toStdString();
  participant pp;

    participant p{nom,prenom,tel,email};
    if(QString::fromStdString(p.getNom())=="" || QString::fromStdString(p.getPrenom())=="" || QString::fromStdString(p.getTel())=="" || QString::fromStdString(p.getMail())=="")
            {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
            }


    if(listeP.chercherParNom(nom,pp))
            {
        QMessageBox::critical(this, "Erreur", "La personne existe déjà dans la liste des participants.");
        return;
            }
            else
            {
                listeP.ajtParticipant(p);
                QMessageBox::information(this, "Ajout réussi",
                    QString("Nom : ") + QString::fromStdString(p.getNom()) + "\n" +
                    QString("Prénom : ") + QString::fromStdString(p.getPrenom()) + "\n" +
                    QString("Téléphone : ") + QString::fromStdString(p.getTel()) + "\n" +
                    QString("Email : ") + QString::fromStdString(p.getMail()));
            }
  // Effacez les champs de texte pour la saisie d'une nouvelle personne
    nomLineEditA->clear();
    prenomLineEditA->clear();
    emailLineEditA->clear();
    telephoneLineEditA->clear();
}


void onglets::modifierPersonne() {
    // Récupérez les informations de la personne saisies dans les champs de texte
    string nom = nomLineEditM->text().toStdString();
    string prenom = prenomLineEditM->text().toStdString();

    string nouveauEmail = nouveauEmailLineEditM->text().toStdString();
    string nouveauTel = nouveauTelephoneLineEditM->text().toStdString();

    if(QString::fromStdString(nom)=="" || QString::fromStdString(prenom)=="" || QString::fromStdString(nouveauTel)=="" || QString::fromStdString(nouveauEmail)=="")
            {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
            }
        // Afficher un message pour confirmer la modification

    participant pp;
            if(listeP.chercherParNom(nom,pp))
            {
                listeP.modifParticipant(nom,prenom,nouveauEmail,nouveauTel);
                QMessageBox::information(this, "Modification réussie", "La personne a été modifiée avec succès !");
            }
            else{
                QMessageBox::critical(this, "Erreur", "Le nom entré n'appartient à aucun participant");
            }

        // Effacer les champs de texte
        nomLineEditM->clear();
        prenomLineEditM->clear();
        nouveauEmailLineEditM->clear();
        nouveauTelephoneLineEditM->clear();

}


void onglets::supprimerPersonne(){
    string nom = nomLineEditS->text().toStdString();
    string prenom = prenomLineEditS->text().toStdString();
    if(QString::fromStdString(nom)=="" || QString::fromStdString(prenom)=="")
    {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
    }

    participant pp;
            if(listeP.chercherParNom(nom,pp))
            {
                if(listeP.NbRDVParticipant(pp)==0)
                {
                    listeP.suprParticipant(pp);

                    QMessageBox::information(this, "Suppression réussie", "Participant supprimé avec succès !");

                }
                else
                {
                    QMessageBox::critical(this, "Erreur","Suppression impossible car le participant est inscrit a "+QString::number(listeP.NbRDVParticipant(pp))+" rendez-vous\n");


                }

            }
            else
            {
                QMessageBox::critical(this, "Erreur", "Le nom entré n'appartient à aucun participant");

            }
    nomLineEditS->clear();
    prenomLineEditS->clear();
}

void onglets::afficherPersonnes(){
    //LDCP* listeParticipants;
    QString liste = QString::fromStdString(listeP.afficherContenuListe());
    // Créez une instance de la nouvelle fenêtre pour afficher la liste
        QDialog* fenetreListe = new QDialog(this);
        fenetreListe->setWindowTitle("Liste des participants");

        // Créez une zone de texte pour afficher la liste
        QTextEdit* texteListe = new QTextEdit(fenetreListe);
        texteListe->setReadOnly(true);
        texteListe->setText( liste);


        // Ajoutez la zone de texte à la fenêtre
        QVBoxLayout* layout = new QVBoxLayout(fenetreListe);
        layout->addWidget(texteListe);
        fenetreListe->setLayout(layout);

        // Affichez la fenêtre
        fenetreListe->exec();
}

void onglets::ajouterRDV()
{
    string objectif = objectifLineEditAR->text().toStdString();
    QString date = dateLineEditAR->text();
    int hdebut = heureDebutLineEditAR->text().toInt();
    int hfin = heureFinLineEditAR->text().toInt();

    QStringList dateList = date.split("/");
    int jour = dateList[0].toInt();
    int mois = dateList[1].toInt();
    int an = dateList[2].toInt();

    if(QString::fromStdString(objectif)=="" || date.isEmpty() || QString::number(hdebut)=="" || QString::number(hfin)=="")
            {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
    }

    RDV rr;
    RDV r{objectif,jour,mois,an,hdebut,hfin};

    if(QString::fromStdString(r.getNom())==""   || r.getHeureFin()<=r.getHeureDebut() || r.getJour()>30
            || r.getHeureDebut()<0 || r.getHeureDebut()>=24 || r.getHeureFin()<0 || r.getHeureFin()>=24)

    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir correctement tous les champs.");
        return;
            }

            if(listeRDV.chercheParNom(objectif,rr))
            {
                QMessageBox::critical(this, "Erreur","Un rendez-vous du même nom existe déjà");
            }
            else
            {
                listeRDV.ajtRdv(r);

                QMessageBox::information(this, "Ajout réussi",
                    QString("Nom : ") + QString::fromStdString(r.getNom()) + "\n" +
                    QString("Jour : ") + QString::number(r.getJour()) +"/" +QString::number(r.getMois())+"/"+QString::number(r.getAn())+ "\n" +
                    QString("Heure de début : ") + QString::number(r.getHeureDebut()) + "\n" +
                    QString("Heure de Fin : ") + QString::number(r.getHeureFin()));
            }
            objectifLineEditAR->clear();
            dateLineEditAR->clear();
            heureDebutLineEditAR->clear();
            heureFinLineEditAR->clear();

}
void onglets::modifierRDV()
{
    string nom = objectifLineEditMR->text().toStdString();
    QString date = dateLineEditMR->text();
    int hdebut = heureDebutLineEditMR->text().toInt();
    int hfin = heureFinLineEditMR->text().toInt();

    if(QString::fromStdString(nom)=="" || date.isEmpty() || QString::number(hdebut)=="" || QString::number(hfin)=="")
            {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
    }

    RDV rr;

    QStringList dateList = date.split("/");
    int jour = dateList[0].toInt();
    int mois = dateList[1].toInt();
    int an = dateList[2].toInt();

    RDV nouv{nom,jour,mois,an,hdebut,hfin};

    if(QString::fromStdString(nouv.getNom())==""   || nouv.getJour()<=0   || nouv.getJour()>30|| nouv.getHeureFin()==nouv.getHeureDebut()
            || nouv.getHeureDebut()<0 || nouv.getHeureDebut()>=24 || nouv.getHeureFin()<0 || nouv.getHeureFin()>=24)

    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir correctement tous les champs.");
        return;
            }


            if(listeRDV.chercheParNom(nom,rr))
            {

                if(listeRDV.participantsDispo(rr,nouv,listeP))//VERIF QUE TT LES PARTICIP DISPOS
                {
                    listeRDV.modifRdv(nom,hdebut,hfin,jour,mois,an);
                    QMessageBox::information(this, "Modification réussie","RDV modifié avec succès");

                }
                else
                {
                    QMessageBox::critical(this, "Erreur","Modification impossible car au moins un des participants du rendez-vous n'est pas disponible au nouvel horaire");

                }




            }
            else
            {
                QMessageBox::critical(this, "Erreur","Le nom entré ne correspond à aucun rendez-vous");


            }

            objectifLineEditMR->clear();
            dateLineEditMR->clear();
            heureDebutLineEditMR->clear();
            heureFinLineEditMR->clear();
}
void onglets::supprimerRDV()
{
    string nom = objectifLineEditSR->text().toStdString();
    if(QString::fromStdString(nom)=="")
            {
        QMessageBox::warning(this, "Attention", "Veuillez entrer un rendez-vous.");
        return;
    }

    RDV rd;
            if(listeRDV.chercheParNom(nom,rd))
            {
                listeRDV.suprRdv(rd);
                listeP.suprRDV(rd);
                QMessageBox::information(this,"Suppression réussie" ,"Rendez-vous supprimé avec succès");

            }
            else
            {
                QMessageBox::critical(this, "Erreur","Le nom entré ne correspond à aucun rendez-vous");

            }
        objectifLineEditSR->clear();
}
void onglets::afficherRDVs()
{
    QString liste = QString::fromStdString(listeRDV.afficherListe());
    // Créez une instance de la nouvelle fenêtre pour afficher la liste
        QDialog* fenetreListe = new QDialog(this);
        fenetreListe->setWindowTitle("Liste des rendez-vous");

        // Créez une zone de texte pour afficher la liste
        QTextEdit* texteListe = new QTextEdit(fenetreListe);
        texteListe->setReadOnly(true);
        texteListe->setText( liste);


        // Ajoutez la zone de texte à la fenêtre
        QVBoxLayout* layout = new QVBoxLayout(fenetreListe);
        layout->addWidget(texteListe);
        fenetreListe->setLayout(layout);

        // Affichez la fenêtre
        fenetreListe->exec();
}

void onglets::ajouterParticipantAUnRDV()
{
    string nomrdv;
    string prenom;


     nom = nomLineEditAPR->text().toStdString();
    prenom = prenomLineEditAPR->text().toStdString();


    participant pp;
    RDV rr;

    if(!listeP.chercherParNom(nom,pp))
    {
        QMessageBox::critical(this, "Erreur", "Le nom entré n'appartient à aucun participant");

    }
    else{
            nomrdv = objectifLineEditAPR->text().toStdString();
            if(QString::fromStdString(nom)=="" ||QString::fromStdString(prenom)==""||QString::fromStdString(nomrdv)=="")
                    {
                QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
                return;
            }
            if(!listeRDV.chercheParNom(nomrdv,rr))
            {
                QMessageBox::critical(this, "Erreur","Le nom entré ne correspond à aucun rendez-vous");
            }


            if(listeP.RDVChevauchement(pp,rr))
            {
                QMessageBox::critical(this, "Erreur","Impossible d'ajouter le participant au rendez-vous car il n'est pas disponible");

            }
            else
            {
                listeRDV.ajtParticipantRdv(nomrdv,pp);
                listeP.ajtRDVParticipant(nom,prenom,rr);
                QMessageBox::information(this,"Ajout réussi"," Participant ajouté avec succès au rendez-vous");

            }
    }
    nomLineEditAPR->clear();
    prenomLineEditAPR->clear();
    objectifLineEditAPR->clear();
}

void onglets::afficherRDVsDUnParticipant()
{
    string nom = nomLineEditAffRsP->text().toStdString();

    if(QString::fromStdString(nom)=="")
    {
        QMessageBox::warning(this, "Attention", "Veuillez entrer un nom d'une personne.");
        return;
    }

    participant pp;
            if(listeP.chercherParNom(nom,pp))
            {
                QString liste = QString::fromStdString(listeP.afficheParticipantRDV(nom));
                // Créez une instance de la nouvelle fenêtre pour afficher la liste
                    QDialog* fenetreListe = new QDialog(this);
                    fenetreListe->setWindowTitle("Liste des rendez-vous d'un participant");

                    // Créez une zone de texte pour afficher la liste
                    QTextEdit* texteListe = new QTextEdit(fenetreListe);
                    texteListe->setReadOnly(true);
                    texteListe->setText( liste);


                    // Ajoutez la zone de texte à la fenêtre
                    QVBoxLayout* layout = new QVBoxLayout(fenetreListe);
                    layout->addWidget(texteListe);
                    fenetreListe->setLayout(layout);

                    // Affichez la fenêtre
                    fenetreListe->exec();

            }
            else
            {
                QMessageBox::critical(this, "Erreur", "Le nom entré n'appartient à aucun participant");
            }

        nomLineEditAffRsP->clear();
}


void onglets::afficherRDVsDate()
{
    QString date = objectifLineEditAffRD->text();
    QStringList dateList = date.split("/");
    int jour = dateList[0].toInt();
    int mois = dateList[1].toInt();
    int an = dateList[2].toInt();

    if(date.isEmpty())
            {
        QMessageBox::warning(this, "Attention", "Veuillez entrer une date.");
        return;
    }

                QString liste = QString::fromStdString(listeRDV.afficherRdvDate(jour,mois,an));
                // Créez une instance de la nouvelle fenêtre pour afficher la liste
                    QDialog* fenetreListe = new QDialog(this);
                    fenetreListe->setWindowTitle("Liste des rendez-vous pour une date");

                    // Créez une zone de texte pour afficher la liste
                    QTextEdit* texteListe = new QTextEdit(fenetreListe);
                    texteListe->setReadOnly(true);
                    texteListe->setText( liste);


                    // Ajoutez la zone de texte à la fenêtre
                    QVBoxLayout* layout = new QVBoxLayout(fenetreListe);
                    layout->addWidget(texteListe);
                    fenetreListe->setLayout(layout);

                    // Affichez la fenêtre
                    fenetreListe->exec();



    objectifLineEditAffRD->clear();
}


void onglets::rechercher()
{

     string nom = objectifLineEditRechercheP->text().toStdString();
     QString date = dateLineEditRechercheP->text();
     int hdebut = hDebutLineEditRechercheP->text().toInt();
     int hfin = hFinLineEditRechercheP->text().toInt();

     QStringList dateList = date.split("/");
     int jour = dateList[0].toInt();
     int mois = dateList[1].toInt();
     int an = dateList[2].toInt();

     if(date.isEmpty() || QString::fromStdString(nom)=="" || QString::number(hdebut)=="" || QString::number(hfin)=="")
             {
         QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
         return;
             }
     participant pp;
             if(listeP.chercherParNom(nom,pp))
             {
                 if(listeP.aRDVMoment(pp,jour,hdebut,hfin,mois,an))
                 {
                     QMessageBox::information(this,"Personne trouvée","La personne selectionnée a un RDV a la date entree.");

                 }
                 else
                 {
                     QMessageBox::warning(this,"Personne non trouvée","La personne selectionnée n'a aucun RDV a la date entree.");

                 }

             }
             else
             {
                 QMessageBox::critical(this, "Erreur","Le nom entré n'appartient à aucun participant");

             }
    objectifLineEditRechercheP->clear();
    dateLineEditRechercheP->clear();
    hDebutLineEditRechercheP->clear();
    hFinLineEditRechercheP->clear();
}

void onglets::afficherParticipantsDUnRDV()
{
    string nom = nomLineEditAffPR->text().toStdString();

    if(QString::fromStdString(nom)=="")
    {
        QMessageBox::warning(this, "Attention", "Veuillez entrer un nom d'un rendez-vous.");
        return;
    }
    RDV rr;
            if(listeRDV.chercheParNom(nom,rr))
            {

                QString liste = QString::fromStdString(listeRDV.afficherParticipantsRDV(nom));
                // Créez une instance de la nouvelle fenêtre pour afficher la liste
                    QDialog* fenetreListe = new QDialog(this);
                    fenetreListe->setWindowTitle("Liste des participants d'un rendez-vous");

                    // Créez une zone de texte pour afficher la liste
                    QTextEdit* texteListe = new QTextEdit(fenetreListe);
                    texteListe->setReadOnly(true);
                    texteListe->setText( liste);


                    // Ajoutez la zone de texte à la fenêtre
                    QVBoxLayout* layout = new QVBoxLayout(fenetreListe);
                    layout->addWidget(texteListe);
                    fenetreListe->setLayout(layout);

                    // Affichez la fenêtre
                    fenetreListe->exec();

            }
            else{
                QMessageBox::critical(this, "Erreur","Le nom entré n'appartient à aucun rendez-vous");

            }
    nomLineEditAffPR->clear();
}

void onglets::on_calendarWidget_selectionChanged()
{

    int jour,mois, an;
    QCalendarWidget* calendar = qobject_cast<QCalendarWidget*>(sender());
        if (calendar)
        {
            QDate selectedDate = calendar->selectedDate();
            int jour = selectedDate.day();
            int  mois = selectedDate.month();
            int an = selectedDate.year();

}
}

void onglets::exporterParticipant()
{
     nomFichier = nomLineEditFichierExportParticipants->text().toStdString();

     if(QString::fromStdString(nomFichier)=="")
     {
         QMessageBox::warning(this, "Attention", "Veuillez entrer un nom d'un fichier.");
         return;
     }
               listeP.EcrireListeFichier(nomFichier);
               QMessageBox::information(this,"Exportation réussie","Exportation faites avec succes");
    nomLineEditFichierExportParticipants->clear();
}

void onglets::importerParticipant()
{
    nomFichier = nomLineEditFichierImportParticipants->text().toStdString();
    if(QString::fromStdString(nomFichier)=="")
    {
        QMessageBox::warning(this, "Attention", "Veuillez entrer un nom d'un fichier.");
        return;
    }
    bool ok=true;

             ifstream ifs;
             ifs.open(nomFichier);

             if(!ifs.is_open())
             {
                QMessageBox::critical(this, "Erreur","MAUVAIS FICHIER");

             }
             else
             {
                ifs>>nb;
                 for(int i=0; i<nb; i++)
                 {
                    ifs>>nom>>prenom>>email>>tel;
                    participant p{nom,prenom,tel,email};
                    participant pp;
                    if(!listeP.chercherParNom(nom,pp))
                    {
                        listeP.ajtParticipant(p);
                    }
                    else
                        ok=false;
                 }
                 if(ok)
                    QMessageBox::information(this,"Importation réussie","Importation faites avec succes");
                 else
                     QMessageBox::warning(this,"Importation faites partiellement","Echec de l'importation pour au moins un participants car le nom existe déjà dans la base de données");
                 ifs.close();
             }

    nomLineEditFichierImportParticipants->clear();
}

void onglets::exporterRDV()
{
     nomFichier = nomLineEditFichierExportRDV->text().toStdString();
     if(QString::fromStdString(nomFichier)=="")
     {
         QMessageBox::warning(this, "Attention", "Veuillez entrer un nom d'un fichier.");
         return;
     }

               listeRDV.EcrireListeFichier(nomFichier);
               QMessageBox::information(this,"Exportation réussie","Exportation faites avec succes");
    nomLineEditFichierExportRDV->clear();
}


void onglets::exporterCarnet()
{

    listeP.EcrireListePRDVFichier();
    QMessageBox::information(this,"Exportation réussie","Exportation faites avec succes");

}


void onglets::importerRDV()
{
    nomFichier = nomLineEditFichierImportRDV->text().toStdString();
    string ponctuation;
    if(QString::fromStdString(nomFichier)=="")
    {
        QMessageBox::warning(this, "Attention", "Veuillez entrer un nom d'un fichier.");
        return;
    }
    bool ok=true;

             ifstream ifs;
             ifs.open(nomFichier);

             if(!ifs.is_open())
             {
                QMessageBox::critical(this, "Erreur","MAUVAIS FICHIER");

             }
             else
             {
                ifs>>nb;
                 for(int i=0; i<nb; i++)
                 {
                    ifs>>nom>>jour>>mois>>an>>hdebut>>hfin;
                    RDV r{nom,jour,mois,an,hdebut,hfin};
                    RDV rr;
                    if(!listeRDV.chercheParNom(nom,rr))
                    {
                        listeRDV.ajtRdv(r);
                    }
                    else
                    {
                        ok=false;
                    }
                 }
                 if(ok)
                    QMessageBox::information(this,"Importation réussie","Importation faites avec succes");
                 else
                    QMessageBox::warning(this,"Importation faites partiellement","Echec de l'importation pour au moins 1 rdv car le nom existe déjà dans la base de données");
                 ifs.close();
             }

    nomLineEditFichierImportRDV->clear();
}

void onglets::retirer()
{
    string nom =  nomLineEditRetirerP->text().toStdString();
    string prenom = prenomLineEditRetirerP->text().toStdString();


            participant pp;
            RDV rr;


            if(!listeP.chercherParNom(nom,pp))
            {
                QMessageBox::critical(this, "Erreur","Le nom entré n'appartient à aucun participant");
            }

            string nomrdv = nomRDVLineEditRetirerParticipant->text().toStdString();
            if(QString::fromStdString(nom)=="" ||QString::fromStdString(nomrdv)=="" ||QString::fromStdString(prenom)=="")
            {
                QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
                return;
            }
            if(!listeRDV.chercheParNom(nomrdv,rr))
            {
                QMessageBox::critical(this, "Erreur","Le nom entré n'appartient à aucun rendez-vous");
            }



            listeP.retirerRDVParticipant(nom,prenom,rr);
            listeRDV.retirerParticipantRdv(nomrdv,pp);

            QMessageBox::information(this,"Opération réussie","Participant retiré du rendez-s avec succès");

            nomLineEditRetirerP->clear();
            prenomLineEditRetirerP->clear();
            nomRDVLineEditRetirerParticipant->clear();
}

void onglets::quitter()
{
    close();
}


