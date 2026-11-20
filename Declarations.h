#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED
#define VMAX 2000
#include "Structures.h"

/** IMPORTATION ET TRAITEMENT DE FICHIERS */

/**
* Auteur : Ensemble
* entrée/sortie tab: [Trajet]
* entrée chemin: [char]
* pré-cond : X
* post-cond : remplit le tableau tab avec tous les trajets du fichier chemin
*/
void recuperer_donnees(char chemin[],Trajet tab[]);

/**
* Auteur : Ensemble
* entrée ligne: [char]
* pré-cond : X
* sortie trajet: Trajet
* post-cond : renvoie les informations d'une chaine
              de caractères ligne sous la forme
              d'une structure Trajet
*/
Trajet ligne_to_Trajet(char ligne[]);

/**
* Auteur : Ensemble
* entrée char_date: [char]
* pré-cond : X
* sortie date : Date
* post-cond : renvoie les informations d'une chaine
              de caractères char_date sous la forme
              d'une structure Date
*/
Date char_to_Date(char char_date[]);

/**
* Auteur : Ensemble
* entrée char_passager: [char]
* pré-cond : X
* sortie passager: Passager
* post-cond : renvoie les informations d'une chaine
              de caractères char_passager sous la forme
              d'une structure Passager
*/
Passager char_to_Passager(char char_passager[]);



/** FONCTIONS PRINCIPALES */


/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajet]
* pré-cond : X
* post-cond : affiche tous les trajets prévus
              (numéro du trajet, numéro du bus, villes de départ et d’arrivée,
              dates et horaires de départ et d’arrivée)
*/
void afficher_trajets(Trajet tab_trajets[], int ordre[], int taille_tab_ordre); // 1

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée/sortie tab : [Trajet]
* entrée numBus: int
* entrée nT: int
* pré-cond : X
* post-cond : Affiche toutes les informations concernant
                le trajet du numéro de bus numBus entré en arguement de la fonction.
*/
void afficher_numBus(int numBus, Trajet tab[],int nT); // 2

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* entrée i_debut, i_fin: int
* entrée/sortie tab_trie_ville: [int]
* pré-cond : tableau bien initialisé avec les valeurs en partant de 0
             avec autant de valeurs que de nombres de trajets
* post-cond : modifie le tableau tab_trie_ville
              avec un tri rapide recursif indirect
              pour donner les indices des trajets
              triés par ville de départ
*/
void ordre_trie_ville(Trajet tab_trajets[], int tab_trie_ville[], int i_debut, int i_fin);// 3.1

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* entrée i_debut, i_fin: int
* entrée/sortie tab_trie_ville: [int]
* pré-cond : tab_trie_ville à nb_trajets elements, avec 0 <= i_debut <= i_fin <= nb_trajets
* sortie i: int
* post-cont : les éléments tab_trajets[tab_trie_ville[i_debut]] à tab_trajets[tab_trie_ville[i-1]]
              sont inférieurs ou égaux à tab_trajets[tab_trie_ville[i]],
              les éléments tab_trajets[tab_trie_ville[i+1]] à tab_trajets[tab_trie_ville[i_fin]]
              sont supérieurs à tab_trajets[tab_trie_ville[i]]
*/
int repartition_ville(Trajet tab_trajets[], int tab_trie_ville[], int i_debut, int i_fin); // 3.2


/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* entrée i_debut, i_fin: int
* entrée/sortie tab_trie_date: [int]
* pré-cond : tableau bien initialisé avec les valeurs en partant de 0
             avec autant de valeurs que de nombres de trajets
* post-cond : modifie le tableau tab_trie_date
              avec un tri rapide recursif indirect
              pour donner les indices des trajets
              triés par date de départ
*/
void ordre_trie_date(Trajet tab_trajets[], int tab_trie_date[], int i_debut, int i_fin);// 3.3

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* entrée i_debut, i_fin: int
* entrée/sortie tab_trie_date: [int]
* pré-cond : tab_trie_date à nb_trajets elements, avec 0 <= i_debut <= i_fin <= nb_trajets
* sortie i: int
* post-cont : les éléments tab_trajets[tab_trie_date[i_debut]] à tab_trajets[tab_trie_date[i-1]]
              sont inférieurs ou égaux à tab_trajets[tab_trie_date[i]],
              les éléments tab_trajets[tab_trie_date[i+1]] à tab_trajets[tab_trie_date[i_fin]]
              sont supérieurs à tab_trajets[tab_trie_date[i]]
*/
int repartition_date(Trajet tab_trajets[], int tab_trie_date[], int i_debut, int i_fin); // 3.4

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée/sortie tab : [Trajet]
* entrée numBus:
* entrée nv_nom: char
* entrée nv_prix: double
* entrée nT: int
* pré-cond : X

* post-cond : Dans le Trajet avec numBus entré,
                ajout d'un Passager avec pour nom et prixBillet
                respectivement nv_nom et nv_prix à la fin
                de la liste de Passager de ce Trajet
*/
void add_client(int numBus, char nv_nom[], double nv_prix, Trajet tab[],int nT); // 4.1

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée/sortie tab : [Trajet]
* entrée numBus: int
* entrée id: int
* entrée nT: int
* pré-cond : X
* post-cond : Dans le Trajet avec numBus entré,
                suppression d'un Passager avec l'id entré
*/
void sup_client(int numBus, int id, Trajet tab[],int nT); // 4.2

/**
* Auteur : Balsan Agathe
* entrée_sortie tab_trajets: [Trajets]
* entrée numerobus, numeroclient, nb_trajets: int
* pré-cond : X
* post-cond : modification ou ajout (si vide)
              du nom du client ou du prix du billet
              dans tab_trajets
*/
void modif_nom_prixbillet(Trajet tab_trajets[], int numerobus, int numeroclient, int nb_trajets); // 5

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée/sortie tab : [Trajet]
* entrée nT : int
* pré-cond : X
* post-cond : Sauvegarde les données qu'il y a dans tab en écrivant toutes les informations de chaque argument de tab dans une ligne du nouveau fichier sauvegarde.csv
*/
void sauvegarder_donnees(Trajet tab[], int nT); // 6

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* entrée nb_trajets: int
* entrée-sortie filtre_2 : [int]
* pré-cond : X
* sortie taille_filtre : int
* post-cond : n'affiche que les trajets
              partant d’une ville, partant
              à une date et arrivant le lendemain
              précisés en paramètres
*/
int filtre_ville_date_lendemain(Trajet tab_trajets[], int filtre_2[], int nb_trajets);// 7

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée/sortie tab : [Trajet]
* entrée vD: char
* entrée vA: char
* entrée j: int
* entrée m: int
* entrée a: int
* entrée nT: int
* pré-cond : X
* post-cond : Affiche les informations des trajets combinant la ville de départ vD,
                la ville d'arrivée vA, le jour, le mois, l'année entrés
*/
void filtre_trajet_sur_3(char vD[100], char vA[100], int j, int m, int a, Trajet tab[], int nT); // 8

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* entrée i_debut, i_fin: int
* entrée/sortie tab_trie_CA: [int]
* pré-cond : tableau bien initialisé avec les valeurs en partant de 0
             avec autant de valeurs que de nombres de trajets
* post-cond : modifie le tableau tab_trie_CA
              avec un tri rapide recursif indirect
              pour donner les indices des trajets
              triés par chiffre d'affaire
*/
void ordre_trie_CA(int nb_trajets, int tab_chiffre_affaire[], int tab_trie_CA[], int i_debut, int i_fin); //9.1

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* entrée i_debut, i_fin: int
* entrée/sortie tab_trie_CA: [int]
* pré-cond : tab_trie_CA à nb_trajets elements, avec 0 <= i_debut <= i_fin <= nb_trajets
* sortie i: int
* post-cont : les éléments tab_chiffre_affaire[tab_trie_CA[i_debut]] à tab_chiffre_affaire[tab_trie_CA[i-1]]
              sont inférieurs ou égaux à tab_chiffre_affaire[tab_trie_CA[i]],
              les éléments tab_chiffre_affaire[tab_trie_CA[i+1]] à tab_chiffre_affaire[tab_trie_CA[i_fin]]
              sont supérieurs à tab_chiffre_affaire[tab_trie_CA[i]]
*/
int repartition_CA(int tab_chiffre_affaire[], int tab_trie_CA[], int i_debut, int i_fin); //9.2

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée/sortie tab : [Trajet]
* entrée/sortie nv_tab : [Trajet]
* entrée nT : int
* pré-cond : X
* post-cond : supprime tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers
sur les trajets identiques, en priorisant les passagers ayant payé le plus sur les dates et horaires les plus
proches du trajet initial
*/
void operation_sur_chiffredAffaire(Trajet tab[], int nT, Trajet nv_tab[]); // 10




/** FONCTIONS AUXILIAIRES */

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée : char
* pré-cond : le nom du chemin existe
* sortie nT : int
* post-cond : renvoie le nombre nT de lignes qu'il y a ans le fichier chemin ce qui correspond au nombre de trajets disponibles dans le fichier
*/
int nombre_Trajets(char chemin[]); // main

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée/sortie tab: [Trajet]
* entrée numBus: int
* entrée nT: int
* pré-cond : X
* sortie i_bus: int
* post-cond : i_bus est l'indice du bus avec numBus entré s'il existe et i_bus vaut -1 s'il n'existe pas
*/
int verifier_numBus(int numBus, Trajet tab[], int nT); // 2.0 & 4.0

/**
* Auteur : Balsan Agathe
* entrée date1, date2 : Date
* pré-cond :
* sortie : int
* post-cond : retourne 0 si la date1 est
              plus petite ou égale à la date2
              et retourne 1 sinon
*/
int comparer_dates(Date date1, Date date2);// 3.0

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* pré-cond : X
* post-cond : lit tout ce qu'il y a dans le buffer (permet d'enlever ce qu'il y a apres un scanf)
*/
void enlever_retour_apres_int(); // 4.01

/**
* Auteur : Idrissi Ouadghiri Ibrahim
* entrée : char
* pré-cond : X
* post-cond : enlève le retour à la ligne à la fin de la chaine s'il y en a un
*/
void retirer_retour_chariot(char chaine[]); // 4.02

/**
* Auteur : Balsan Agathe
* entrée horaire1 horaire2: int
* pré-cond :
*post-cond : renvoie 1 si l'horaire1 est après l'horaire
             renvoie 0 sinon
*/
int comparer_horaires(int horaire1, int horaire2); // 7.0

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* pré-cond : X
* post-cond : retourne le chiffre d'affaire du trajet mis en entrée
*/
int chiffre_daffaire(Trajet trajet); // 9.0 & 10.0

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajets]
* entrée nb_trajets: int
* entrée tab_trie_CA, tab_chiffre_affaire : [int]
* pré-cond : tab_trie_CA de longueur nb_trajets-1               szerdtfbgnybybfhrgnzhdrgdnh"hucz (untkhréni,rhéunjfuk,nhs"a'zi
* post-cond : affiche chaque trajet avec son chiffre d'affaire
              triés d'après le trie de la fonction ordre_trie_CA
*/
void affiche_trie_CA(Trajet tab_trajets[], int nb_trajets, int tab_trie_CA[], int tab_chiffre_affaire[]);

/**
* entrée/sortie tab: [Passager]
* entrées i_debut, i_mil, i_fin: int
* pré-cond: 0 ≤ i_debut ≤ i_mil ≤ i_fin < 55 et tab[i_deb:i_mil] et tab[i_mil+1:i_fin] sont triés par ordre décroissant
* post-cond: tab[i_deb:i_fin] est trié par ordre décroissant
*/
void fusionner_dec(Passager tab[55], int i_debut, int i_mil, int i_fin); // 10.01

/**
* entrée/sortie passager: [Passager]
* entrées i_debut, i_fin: int
* pré-cond: 0 ≤ i_debut ≤ i_fin < 55
* post-cond: les éléments de passager sont triés par ordre décroissant en fonction du prixBillet
*/
void triprix(Passager passager[55], int i_debut, int i_fin); // 10.02

/**
* Auteur : Balsan Agathe
* entrée bus1, bus2: Trajets
* pré-cond : X
* sortie diff_minutes: int
* post-cond : retourne diff_minutes le temps de différence
              en minutes entre le départ des deux bus
*/
int difference_temps(Trajet bus1, Trajet bus2); //  10.02

/**
* Auteur : Balsan Agathe
* entrée tab_trajets: [Trajet]
* pré-cond : X
* sortie somme_ca: int
* post-cond : retourne somme_ca la somme des chiffres d'affaire
              des trajets de tab_trajets
*/
int somme_chiffre_affaire(Trajet tab_trajets[], int nb_trajets); // 10.03

#endif // DECLARATIONS_H_INCLUDED
