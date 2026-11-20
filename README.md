# Application pour gérer les trajets d'une société de bus
## Description
  Ce projet à été fait en binôme en Janvier 2026.
  
  Codé en C il permet depuis la console du terminal et grâce à des fichiers .csv d'importer des données représenatnt de nombreux trajets de bus (numéro du bus, ville de départ, destination, date de départ, horaire de départ, horaire d'arrivée, liste des passagers (id, nom, prix de son billet)).
  
  Ce projet propose une application pour gérer ces différents trajets à partir de fichiers .csv pouvant aller de 10 lignes à 5000 lignes de données, chacune représentant un trajet.

## Fonctionnalités
 - Affichage de tous les trajets prévus (villes de départ et d’arrivée, dates et horaires de départ et 
d’arrivée)
 - À partir du numéro d’un bus, affichage de toutes les informations sur le trajet (villes de départ et 
d’arrivée, dates et horaires de départ et d’arrivée, liste des clients)
 - affichage de tous les trajets triés par ville de départ et par date de départ
 - À partir du numéro d’un bus, ajout et suppression de clients
 - À partir du numéro d’un bus et de numéro (id) d’un client, modification ou ajout du nom du client ou 
du prix de son billet
 - Sauvegarde des données dans un fichier (mise à jour du fichier ou création d’un nouveau fichier)
 - Filtre sur les trajets partant d’une ville, partant à une date, arrivant le lendemain
 - Filtre sur les trajets combinant ville de départ, ville d’arrivée et date de départ
 - Affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les 
passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires
 - Possibilité de supprimer tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers 
sur les trajets identiques, en priorisant les passagers ayant payé le plus sur les dates et horaires les plus 
proches du trajet initial. Il faudra indiquer le gain généré par cette opération

## Outils
NetBeans

## Langages
C
