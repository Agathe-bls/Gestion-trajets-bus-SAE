#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Declarations.h"
#include "Structures.h"
//#define chemin "trajets_bus.csv"
#define VMAX 2000
#define nbchamp 61

void retirer_retour_chariot(char chaine[]){ // I
    int i=0;
      while ((chaine[i]!='\0')&&(chaine[i]!='\n')){i++;}
    chaine[i]='\0';
}

void enlever_retour_apres_int() { // I
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int nombre_Trajets(char chemin[]){ // I
    int nT=0;
    char poubelle[VMAX];
    FILE *fic = fopen(chemin, "r");
    if (fic == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    while (fgets(poubelle,VMAX,fic)!=NULL){
        nT++;
    }
    return nT;
}

int verifier_numBus(int numBus, Trajet tab[], int nT){ // I
    int i_bus = -1,i = 0;
    while (tab[i].numBus != numBus && i<nT){i++;}
    if (tab[i].numBus == numBus) {
        i_bus=i;

    }
    else {
        printf("Bus %d non trouve.\n", numBus);
    }
    return i_bus;
}

void fusionner_dec(Passager tab[], int i_debut, int i_mil, int i_fin){ // I
    Passager temp[i_fin-i_debut+1] ;
    int i = i_debut ;
    int j = i_mil+1 ;
    int k = 0 ; // indice de parcours de temp
    while (i <= i_mil && j <= i_fin) {
        if (tab[i].prixBillet >= tab[j].prixBillet) {
            strcpy(temp[k].nom, tab[i].nom);
            temp[k].prixBillet = tab[i].prixBillet ;
            i = i+1 ;
        }
        else {
            strcpy(temp[k].nom, tab[j].nom);
            temp[k].prixBillet = tab[j].prixBillet ;
            j = j+1 ;
        }
        k = k+1 ;
    }
    while (i <= i_mil) {
        strcpy(temp[k].nom, tab[i].nom);
        temp[k].prixBillet = tab[i].prixBillet ;
        i = i+1 ;
        k = k+1 ;
    }
    while (j <= i_fin) {
        strcpy(temp[k].nom, tab[j].nom);
        temp[k].prixBillet = tab[j].prixBillet ;
        j = j+1 ;
        k = k+1 ;
    }
    for (k = 0 ; k < i_fin-i_debut+1 ; k++){
        strcpy(tab[k].nom, temp[i_debut+k].nom);
        tab[i_debut+k].prixBillet = temp[k].prixBillet ;
    }
}

void triprix(Passager passager[], int i_debut, int i_fin){ // I
    int i_mil;
    if (i_fin > i_debut) {
        i_mil = (i_debut + i_fin)/2 ;
        triprix(passager, i_debut, i_mil) ;
        triprix(passager, i_mil+1, i_fin) ;
        fusionner_dec(passager, i_debut, i_mil, i_fin) ;
    }
}

int comparer_dates(Date date1, Date date2){ // A 3.0
    if(date1.annee>date2.annee)
        return 1;
    if(date1.annee==date2.annee && date1.mois>date2.mois)
        return 1;
    if(date1.annee==date2.annee && date1.mois==date2.mois && date1.jour>date2.jour)
        return 1;
    return 0;
}

int comparer_horaires(int horaire1, int horaire2){ // A 7.0
    if(horaire1/100 > horaire2/100)
        return 1;
    if(horaire1/100 >= horaire2/100 && horaire1%100 > horaire2%100)
        return 1;
    return 0;
}

int chiffre_daffaire(Trajet trajet){ // A 9.0 & 10.0
    int ca= -100;
    int nb_heures;
    int nb_minutes;
    int min_dep = trajet.horaireDepart/100 * 60 + trajet.horaireDepart%100;
    int min_arr = trajet.horaireArrivee/100 * 60 + trajet.horaireArrivee%100;
    nb_minutes = min_arr - min_dep;

    if(nb_minutes < 0){
        nb_minutes += 24*60;
    }
    if(nb_minutes%60 == 0){
        nb_heures = nb_minutes/60;
    }
    else{
        nb_heures = nb_minutes/60 +1;
    }
    for(int i=0; i<55; i++){
    ca += trajet.passager[i].prixBillet;
    }
    ca -= nb_heures*50;
    return ca;
}

void affiche_trie_CA(Trajet tab_trajets[], int nb_trajets, int tab_trie_CA[], int tab_chiffre_affaire[]){
    int tab_ordre[1];
    for(int i=0; i<nb_trajets; i++){
        tab_ordre[0] = tab_trie_CA[i];
        printf("Chiffre d'affaire du trajet : %d\n",tab_chiffre_affaire[tab_ordre[0]]);
        afficher_trajets(tab_trajets, tab_ordre, 1);
    }
}

int difference_temps(Trajet bus1, Trajet bus2){
    int diff_annee = bus1.dateDepart.annee - bus2.dateDepart.annee,
    diff_mois = bus1.dateDepart.mois - bus2.dateDepart.mois,
    diff_jour = bus1.dateDepart.jour - bus2.dateDepart.jour,
    diff_h = bus1.horaireArrivee/100 - bus2.horaireArrivee/100,
    diff_minutes = bus1.horaireArrivee%100 - bus2.horaireArrivee%100
    ;
    diff_minutes += abs(diff_h)*60 + abs(diff_jour)*24*60 + abs(diff_mois)*24*60*30 + abs(diff_annee)*525600;
    return diff_minutes;
}

int somme_chiffre_affaire(Trajet tab_trajets[], int nb_trajets){
    int somme_ca = 0;
    for(int i=0; i<nb_trajets; i++){
        somme_ca += chiffre_daffaire(tab_trajets[i]);
    }
    return somme_ca;
}
