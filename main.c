#include <stdio.h>
#include <stdlib.h>
#include "Declarations.h"
#include "Structures.h"
#define chemin "trajets_10.csv"

int main(){
/** Importation des données  */
    int nb_trajets = nombre_Trajets(chemin);
    Trajet tab_trajets[nb_trajets];
    recuperer_donnees(chemin,tab_trajets);

/** choix / sous choix  */

    int choix;
    char char_choix;

/** case 1-3 et 9 initialisation et remplissages tableaux */
    int ordre_de_depart[nb_trajets];
    int tab_trie_ville[nb_trajets];
    int tab_trie_date[nb_trajets];
    int tab_trie_CA[nb_trajets];
    for(int i=0; i<nb_trajets; i++){
        ordre_de_depart[i]=i;
        tab_trie_ville[i]=i;
        tab_trie_date[i]=i;
        tab_trie_CA[i]=i;
    }

/** case 2 4 5 */

    int numerobus;

/** case 4 */

    int id_sup;
    char nv_nom[100];
    double nv_prix;

/** case 5 */

    int numerclient;

/** case 7 */

    int filtre_2[nb_trajets];
    int taille_filtre = 0;

/** case 8 */

    char vD[100], vA[100];
    int j, m, a;

/** case 9 */
    int tab_chiffre_affaire[nb_trajets];

/** case 10 */
    int somme1;
    Trajet nv_trajets[nb_trajets];
    int somme2;

/** MENU */

    int fin=0;
    while(fin==0){

        printf("Menu\n");
        printf("1 : Tous les trajets\n");
        printf("2 : Trajet a partir d'un numero de bus\n");
        printf("3 : Tous les trajets tries par ville de depart ou date de depart\n");
        printf("4 : Pour un bus, ajout et suppression de clients\n");
        printf("5 : Modification ou ajout du nom d'un client ou du prix de son billet\n");
        printf("6 : Sauvegarde des données\n");
        printf("7 : Filtre sur la ville de depart/date de depart et arrivee le lendemain\n");
        printf("8 : Filtre sur ville de depart/ville d'arrivee/date de depart\n");
        printf("9 : Trie par chiffre d'affaires\n");
        printf("10 : Supression des bus a chiffre d'affaire negatif avec repartition des passagers\n");
        printf("11 : Sortir de l'application\n");

        printf("Choisir le numero d'une option dans le menu : ");
        scanf("%d", &choix);
        enlever_retour_apres_int();
        printf("\n");

        switch(choix){
        case 1 :
            afficher_trajets(tab_trajets, ordre_de_depart, nb_trajets);
            break;
        case 2 :
            printf("Saisissez le numéro du Bus que vous souhaitez : ");
            scanf("%d", &numerobus);
            afficher_numBus(numerobus, tab_trajets, nb_trajets);
            break;
        case 3 :
             printf("Veux tu trier par ville de depart (A), ou par date de depart (B) : ");
             scanf("%s", &char_choix);
                 if(char_choix == 'A'){
                    printf("Les trajets tries par Ville de depart : \n\n");
                    ordre_trie_ville(tab_trajets, tab_trie_ville, 0, nb_trajets-1);
                    afficher_trajets(tab_trajets, tab_trie_ville, nb_trajets);
                 }
                 else if(char_choix == 'B'){
                    printf("Les trajets tries par Date de depart : \n\n");
                   ordre_trie_date(tab_trajets, tab_trie_date, 0, nb_trajets-1);
                   afficher_trajets(tab_trajets, tab_trie_date, nb_trajets);
                 }
                else{
                    printf("Vous n'avez pas saisi le bon choix !\n");
                }
             break;
        case 4 :
            printf("Donner le numBus sur lequel vous voulez ajouter ou supprimer un client : ");
            scanf("%d", &numerobus);
            enlever_retour_apres_int();
            if (verifier_numBus(numerobus,tab_trajets,nb_trajets)==-1){
                break;
            }
            printf("Ajouter un client (A) ou Supprimer un client (B) : ");
            scanf("%s", &char_choix);
            if (char_choix == 'A'){
                printf("Nom du nouveau client : ");
                enlever_retour_apres_int();
                fgets(nv_nom,101,stdin);
                retirer_retour_chariot(nv_nom);
                printf("\n");
                printf("Prix du billet : ");
                scanf("%lf", &nv_prix);
                enlever_retour_apres_int();
                add_client(numerobus,nv_nom,nv_prix,tab_trajets,nb_trajets);
                afficher_numBus(numerobus,tab_trajets,nb_trajets);
            }
            else if (char_choix == 'B'){
                printf("Id du client que vous voulez supprimer : ");
                scanf("%d", &id_sup);
                sup_client(numerobus,id_sup,tab_trajets,nb_trajets);
                afficher_numBus(numerobus,tab_trajets,nb_trajets);
            }
            else{
                printf("Vous n'avez pas saisi le bon choix !\n");
            }
            break;
        case 5 :
            printf("Donnez le numero de bus puis l'id du client que vous voulez modifier \n(separez les par un espace) : ");
            scanf("%d %d", &numerobus, &numerclient);
            modif_nom_prixbillet(tab_trajets, numerobus, numerclient, nb_trajets);
            afficher_numBus(numerobus, tab_trajets, nb_trajets);
            break;
        case 6 :
            sauvegarder_donnees(tab_trajets,nb_trajets);
            printf("Fichier Sauvegarde !");
            break;
        case 7 :
            taille_filtre = filtre_ville_date_lendemain(tab_trajets, filtre_2, nb_trajets);
            afficher_trajets(tab_trajets, filtre_2, taille_filtre);
            break;
        case 8 :
            printf("Entrez la ville de depart : ");
            fgets(vD,101,stdin);
            retirer_retour_chariot(vD);
            printf("Entrez la ville d'arrivee : ");
            fgets(vA,101,stdin);
            retirer_retour_chariot(vA);
            printf("Entrez la date de depart : \n");
            printf("Jour : ");
            scanf("%d",&j);
            enlever_retour_apres_int();
            printf("Mois : ");
            scanf("%d",&m);
            enlever_retour_apres_int();
            printf("Année : ");
            scanf("%d",&a);
            enlever_retour_apres_int();
            printf("Résultat(s)\n");
            filtre_trajet_sur_3(vD,vA,j,m,a,tab_trajets,nb_trajets);
            break;
        case 9 : for(int i=0; i<nb_trajets; i++){
                     tab_chiffre_affaire[i] = chiffre_daffaire(tab_trajets[i]);
                 }
                 printf("Les trajets tries par chiffre d'affaire : \n\n");
                 ordre_trie_CA(nb_trajets, tab_chiffre_affaire, tab_trie_CA, 0, nb_trajets-1);
                 affiche_trie_CA(tab_trajets, nb_trajets, tab_trie_CA, tab_chiffre_affaire);
                 break;
        case 10 :
            somme1=somme_chiffre_affaire(tab_trajets, nb_trajets);
            operation_sur_chiffredAffaire(tab_trajets,nb_trajets,nv_trajets);
            somme2=somme_chiffre_affaire(nv_trajets, nb_trajets);
            printf("\nLe gain généré par cette opération est : %.2d euros.\n\n",somme2-somme1);
            break;
        case 11 : printf("Merci pour votre visite !");
                  fin=1;
                  break;
        default : printf("Votre choix : %d, n'est pas dans le menu\n", choix);
        }
    }
    return 0;
}

