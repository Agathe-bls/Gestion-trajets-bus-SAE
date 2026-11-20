#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct{         //Date
   int jour;
   int mois;
   int annee;
} Date;

typedef struct {        //Passager
    int id;
    char nom[100];
    double prixBillet;
} Passager;

typedef struct {        //Trajet
    int numBus;
    char villeDepart[100];
    char villeArrivee[100];
    Date dateDepart;
    int horaireDepart;
    int horaireArrivee;
    Passager passager[55]; // qui contient tous les passagers // et demander de e qu'il en est des cases non remplies (aleatoires ?)
} Trajet;

#endif // STRUCTURES_H_INCLUDED
