#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Declarations.h"
#include "Structures.h"
#define VMAX 2000
#define nbchamp 61



/** IMPORTATION ET TRAITEMENT DE FICHIERS */

void recuperer_donnees(char chemin[], Trajet tab_trajets[]) { // E
    char ligne[VMAX];
    FILE *fic = fopen(chemin, "r");
    if(fic == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (fgets(ligne, VMAX, fic)) {
        tab_trajets[i] = ligne_to_Trajet(ligne);
        i++;
    }
    fclose(fic);
}

Trajet ligne_to_Trajet(char ligne[]){ // E
    Trajet trajet;
    char resultat[nbchamp][100]={0};
    int i=0, j=0, k=0;
    while (ligne[i] != '\0'&& ligne[i] != '\n'){
        if (ligne[i] == ','){
            resultat[j][k] = '\0';
            j++;
            k = 0;
        }
        else {
            resultat[j][k] = ligne[i];
            k++;
        }
        i++;
    }
    resultat[j][k] = '\0';
    int nbChamps=j+1;

    trajet.numBus=strtol(resultat[0], NULL, 10); // conversion char to int
    strcpy(trajet.villeDepart,resultat[1]);
    strcpy(trajet.villeArrivee,resultat[2]);
    trajet.dateDepart=char_to_Date(resultat[3]);
    trajet.horaireDepart=strtol(resultat[4], NULL, 10);
    trajet.horaireArrivee=strtol(resultat[5], NULL, 10);

    for (int p = 0; p < 55; p++) {
        trajet.passager[p].id = 0;
        trajet.passager[p].nom[0] = '\0';
        trajet.passager[p].prixBillet = 0.0;
    }
    for(int i=6;i<nbChamps;i++){
        trajet.passager[i-6]=char_to_Passager(resultat[i]);
    }
    return trajet;
}

Date char_to_Date(char char_date[]){ // E
    Date date;
    char resultat_date[3][5];
    int i=0, j=0, k=0;
    while(char_date[i]!= '\0'){
        if(char_date[i] == '/'){
            resultat_date[j][k] = '\0';
            j++;
            k = 0;
        }
        else{
            resultat_date[j][k] = char_date[i];
            k++;
        }
        i++;
    }
    resultat_date[j][k] = '\0';

    date.jour=strtol(resultat_date[0], NULL, 10);
    date.mois=strtol(resultat_date[1], NULL, 10);
    date.annee=strtol(resultat_date[2], NULL, 10);
    return date;
}

Passager char_to_Passager(char char_passager[]){ // E
    Passager passager;
    char resultat_passager[4][100];
    int i=0, j=0, k=0;
    while(char_passager[i]!= '\0'){
        if(char_passager[i] == ':'){
            resultat_passager[j][k] = '\0';
            j++;
            k = 0;
        }
        else{
            resultat_passager[j][k] = char_passager[i];
            k++;
        }
        i++;
    }
    resultat_passager[j][k] = '\0';

    passager.id=strtol(resultat_passager[0], NULL, 10);
    strcpy(passager.nom,resultat_passager[1]);
    passager.prixBillet=strtod(resultat_passager[2], NULL);
    return passager;
}


/** FONCTIONS PRINCIPALES */

void afficher_trajets(Trajet tab_trajets[], int ordre[], int taille_tab_ordre){ // A1
    for(int i=0; i<taille_tab_ordre; i++){
        int i_ordre = ordre[i];
        printf("Trajet numero %d\n", i+1);
        printf("Numero du bus : %d\n", tab_trajets[i_ordre].numBus);
        printf("Ville de depart : %s\n", tab_trajets[i_ordre].villeDepart);
        printf("Ville d'arrivee : %s\n", tab_trajets[i_ordre].villeArrivee);
        printf("Date de depart : %d/%d/%d\n",tab_trajets[i_ordre].dateDepart.jour,
                                             tab_trajets[i_ordre].dateDepart.mois,
                                             tab_trajets[i_ordre].dateDepart.annee);
        printf("Horaire de depart : %d h %d\n", tab_trajets[i_ordre].horaireDepart/100,
                                                tab_trajets[i_ordre].horaireDepart%100);
        printf("Horaire d'arrivee : %d h %d\n\n", tab_trajets[i_ordre].horaireArrivee/100,
                                                  tab_trajets[i_ordre].horaireArrivee%100);
    }
}

void afficher_numBus(int numBus, Trajet tab[],int nT){ // I2
    int i_bus=verifier_numBus(numBus, tab, nT);
    if (tab[i_bus].numBus==numBus){
        printf("Voici les informations sur le bus %d :\n",numBus);
        printf("Ville de depart : %s\n",tab[i_bus].villeDepart);
        printf("Ville d'arrivee : %s\n",tab[i_bus].villeArrivee);
        printf("Date : %d/%d/%d\n", tab[i_bus].dateDepart.jour,tab[i_bus].dateDepart.mois,tab[i_bus].dateDepart.annee);
        printf("Horaire de depart : %02d:%02d\n", tab[i_bus].horaireDepart/100,tab[i_bus].horaireDepart%100);
        printf("Horaire d'arrivee : %02d:%02d\n", tab[i_bus].horaireArrivee/100,tab[i_bus].horaireArrivee%100);
        printf("Liste des passagers :\n\n\tNumero passager | Prenom Nom | Prix billet\n\n");
        for(int k=0;tab[i_bus].passager[k].id!='\0';k++){
            printf("%d\t|\t%s\t|\t%.2lf\n", tab[i_bus].passager[k].id, tab[i_bus].passager[k].nom, tab[i_bus].passager[k].prixBillet);
        }
    }
}

void ordre_trie_ville(Trajet tab_trajets[], int tab_trie_ville[], int i_debut, int i_fin) { // A3.1
    int ind;
    if (i_debut<i_fin) {
        ind = repartition_ville(tab_trajets, tab_trie_ville, i_debut, i_fin);
        ordre_trie_ville(tab_trajets, tab_trie_ville, i_debut, ind-1);
        ordre_trie_ville(tab_trajets, tab_trie_ville, ind+1, i_fin);
    }
}

int repartition_ville(Trajet tab_trajets[], int tab_trie_ville[], int i_debut, int i_fin){ // A3.2
    char *pivot = tab_trajets[tab_trie_ville[i_debut]].villeDepart;
    int i= i_debut+1, j= i_fin;
    while(i<j){
        while(i<j && strcmp(tab_trajets[tab_trie_ville[i]].villeDepart, pivot)<0)
            i++;
        while(i<j && strcmp(tab_trajets[tab_trie_ville[j]].villeDepart, pivot)>=0)
            j--;
        if(i<j){
            int tmp = tab_trie_ville[i];
            tab_trie_ville[i] = tab_trie_ville[j];
            tab_trie_ville[j] = tmp;
            i++;
            j--;
        }
    }
    if(strcmp(tab_trajets[tab_trie_ville[i]].villeDepart, pivot)>=0)
        i--;
    int tmp = tab_trie_ville[i_debut];
    tab_trie_ville[i_debut] = tab_trie_ville[i];
    tab_trie_ville[i] = tmp;
    return i;
}

void ordre_trie_date(Trajet tab_trajets[], int tab_trie_date[], int i_debut, int i_fin) { // A3.3
    int ind;
    if (i_debut<i_fin) {
        ind = repartition_date(tab_trajets, tab_trie_date, i_debut, i_fin);
        ordre_trie_date(tab_trajets, tab_trie_date, i_debut, ind-1);
        ordre_trie_date(tab_trajets, tab_trie_date, ind+1, i_fin);
    }
}

int repartition_date(Trajet tab_trajets[], int tab_trie_date[], int i_debut, int i_fin) { // A3.4
    Date pivot = tab_trajets[tab_trie_date[i_debut]].dateDepart;
    int i= i_debut+1, j= i_fin;
    while(i<j){
        while(i<j && comparer_dates(tab_trajets[tab_trie_date[i]].dateDepart, pivot)==0)
            i++;
        while(i<j && comparer_dates(tab_trajets[tab_trie_date[j]].dateDepart, pivot)==1)
            j--;
        if(i<j){
            int tmp = tab_trie_date[i];
            tab_trie_date[i] = tab_trie_date[j];
            tab_trie_date[j] = tmp;
            i++;
            j--;
        }
    }
    if(comparer_dates(tab_trajets[tab_trie_date[i]].dateDepart, pivot)==1)
        i--;
    int tmp = tab_trie_date[i_debut];
    tab_trie_date[i_debut] = tab_trie_date[i];
    tab_trie_date[i] = tmp;
    return i;
}

void add_client(int numBus, char nv_nom[], double nv_prix, Trajet tab[],int nT){ // I4.1
    int i_bus=verifier_numBus(numBus, tab, nT);
    if (tab[i_bus].numBus==numBus){
        int i=0;
        while (tab[i_bus].passager[i].id!='\0'){i++;}
        if (i<55){
            tab[i_bus].passager[i].id=i+1;
            strcpy(tab[i_bus].passager[i].nom, nv_nom);
            tab[i_bus].passager[i].prixBillet=nv_prix;
        }
    }
}

void sup_client(int numBus, int id, Trajet tab[],int nT){ // I4.2
    int i_bus=verifier_numBus(numBus, tab, nT);
    if (tab[i_bus].numBus==numBus){
        int i=0;
        while (tab[i_bus].passager[i].id!=0){
            if (tab[i_bus].passager[i].id==id){
                for(int j=i;tab[i_bus].passager[j].id!=0;j++){
                    strcpy(tab[i_bus].passager[j].nom,tab[i_bus].passager[j+1].nom);
                    tab[i_bus].passager[j].prixBillet=tab[i_bus].passager[j+1].prixBillet;
                    if (tab[i_bus].passager[j+1].id==0){
                        tab[i_bus].passager[j].id=0;
                    }
                }
            }
            i++;
        }
    }
}

void modif_nom_prixbillet(Trajet tab_trajets[], int numerobus, int numeroclient, int nb_trajets){ // A5
    char choix;
    int i=0;
    int j=0;
    char nouvnom[100];
    double nouvprix;
    printf("Voulez vous modifier le nom du client %d (A) ou le prix de son billet (B)? : ", numeroclient);
    scanf("%s", &choix);
    if(choix==65){
        while(i<nb_trajets){
            if(tab_trajets[i].numBus == numerobus){
                printf("Quel nouveau nom voulez vous donner au client %d du bus %d? : ", numeroclient, numerobus);
                scanf("%s", nouvnom);
                strcpy(tab_trajets[i].passager[numeroclient-1].nom,nouvnom);
            }
            i++;
        }
    }
    else if(choix==66){
        while(j<nb_trajets){
            if(tab_trajets[j].numBus == numerobus){
                printf("Quel nouveau prix voulez vous donner au billet du client %d du bus %d? : ", numeroclient, numerobus);
                scanf("%lf", &nouvprix);
                tab_trajets[j].passager[numeroclient-1].prixBillet = nouvprix;
            }
            j++;
        }
    }
}

void sauvegarder_donnees(Trajet tab[], int nT){ // I6
    FILE * fic = fopen("sauvegarde.csv","w");
    if (fic == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<nT;i++){
        fprintf(fic, "%d,%s,%s,%d/%d/%d,%d,%d", tab[i].numBus, tab[i].villeDepart, tab[i].villeArrivee, tab[i].dateDepart.jour, tab[i].dateDepart.mois, tab[i].dateDepart.annee, tab[i].horaireDepart, tab[i].horaireArrivee);
        for(int j=0;tab[i].passager[j].id!=0;j++){
            fprintf(fic, ",%d:%s:%.2lf", tab[i].passager[j].id, tab[i].passager[j].nom, tab[i].passager[j].prixBillet);
        }
        fprintf(fic, "\n");
    }
    fclose(fic);
}

int filtre_ville_date_lendemain(Trajet tab_trajets[], int filtre_2[], int nb_trajets){ // A7
    int j=0;
    char ville_depart[100];
    int j_depart, m_depart, a_depart;
    printf("De quelle ville voulez vous partir et a quelle date(jour mois annee separes par des espaces) : ");
    scanf("%s %d %d %d", ville_depart, &j_depart, &m_depart, &a_depart);
    for(int i=0; i<nb_trajets; i++){
        if(strcmp(tab_trajets[i].villeDepart, ville_depart) == 0 && tab_trajets[i].dateDepart.jour==j_depart && tab_trajets[i].dateDepart.mois==m_depart && tab_trajets[i].dateDepart.annee==a_depart && comparer_horaires(tab_trajets[i].horaireDepart, tab_trajets[i].horaireArrivee) == 1){
            filtre_2[j]=i;
            j++;
        }
    }
    printf("\nLes trajets qui partent de %s le %d/%d/%d et arrivent le lendemain sont :\n",  ville_depart, j_depart, m_depart, a_depart);
    if(j==0){
        printf("Aucun\n");
    }
    return j;
}

void filtre_trajet_sur_3(char vD[100], char vA[100], int j, int m, int a, Trajet tab[], int nT){ // I8
    printf("Resultat :\n");
    for(int i=0;i<nT;i++){
        if((strcmp(tab[i].villeDepart,vD)==0)&&(strcmp(tab[i].villeArrivee,vA)==0)&&(tab[i].dateDepart.jour==j)&&(tab[i].dateDepart.jour==j)&&(tab[i].dateDepart.jour==j)){
            printf("Bus numero : %d\n",tab[i].numBus);
        }
    }
}

void ordre_trie_CA(int nb_trajets, int tab_chiffre_affaire[], int tab_trie_CA[], int i_debut, int i_fin) { //A9.1
    int ind;
    if (i_debut<i_fin) {
        ind = repartition_CA(tab_chiffre_affaire, tab_trie_CA, i_debut, i_fin);
        ordre_trie_CA(nb_trajets, tab_chiffre_affaire, tab_trie_CA, i_debut, ind-1);
        ordre_trie_CA(nb_trajets, tab_chiffre_affaire, tab_trie_CA, ind+1, i_fin);
    }
}

int repartition_CA(int tab_chiffre_affaire[], int tab_trie_CA[], int i_debut, int i_fin) { // A9.2
    int pivot = tab_chiffre_affaire[tab_trie_CA[i_debut]];
    int i= i_debut+1, j= i_fin;
    while(i<j){
        while(i<j && tab_chiffre_affaire[tab_trie_CA[i]] <= pivot)
            i++;
        while(i<j && tab_chiffre_affaire[tab_trie_CA[j]] > pivot)
            j--;
        if(i<j){
            int tmp = tab_trie_CA[i];
            tab_trie_CA[i] = tab_trie_CA[j];
            tab_trie_CA[j] = tmp;
            i++;
            j--;
        }
    }
    if(tab_chiffre_affaire[tab_trie_CA[i]] > pivot)
        i--;
    int tmp = tab_trie_CA[i_debut];
    tab_trie_CA[i_debut] = tab_trie_CA[i];
    tab_trie_CA[i] = tmp;
    return i;
}

void operation_sur_chiffredAffaire(Trajet tab[], int nT, Trajet nv_tab[]){ // I10
    Trajet tab_nega[nT];
    int i=0,idxN=0;
    while(i<nT){
        if(chiffre_daffaire(tab[i])<=0){
            tab_nega[idxN]=tab[i];
            idxN++;
        }
        i++;
    }
    int j=0, idxR=0;
    while (j<nT){
        if (chiffre_daffaire(tab[j])>0){
            nv_tab[idxR]=tab[j];
            triprix(nv_tab[idxR].passager, 0, 55);
            idxR++;
        }
        j++;
    }
    int z = 0;
    while (z < idxN) {
        int min = -1;
        for (int i = 0; i < idxR; i++) {
            if (strcmp(tab_nega[z].villeDepart, nv_tab[i].villeDepart) == 0 && strcmp(tab_nega[z].villeArrivee, nv_tab[i].villeArrivee) == 0) {
                if (min == -1 || difference_temps(tab_nega[z], nv_tab[i]) < difference_temps(tab_nega[z], nv_tab[min])){
                    min = i;
                }
            }
        }
        if (min != -1) {
            int p = 0;
            while (p < 55 && nv_tab[min].passager[p].id != 0) {p++;}
            while (p < 55 && tab_nega[z].passager[0].id != 0) {
                nv_tab[min].passager[p].id = p+1;
                strcpy(nv_tab[min].passager[p].nom, tab_nega[z].passager[0].nom);
                nv_tab[min].passager[p].prixBillet = tab_nega[z].passager[0].prixBillet;
                sup_client(tab_nega[z].numBus, 1, tab_nega,idxN);
                p++;
            }
        }
        z++;
    }
}

