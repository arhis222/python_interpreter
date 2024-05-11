#include <stdio.h>
#include <string.h>
#include "table_symbole.h"

Couple TS[NBMAXSYMB]; // La variable Table des Symboles
int NbSymb;           // Le nombre courant de couples dans la table

// Initialise la table des symboles.
void initTS()
{
    NbSymb = 0;
}

// Affiche le contenu de la table des symboles.
void afficheTS()
{
    printf("Table des Symboles :\n");
    for (int i = 0; i < NbSymb; i++)
    {
        printf("%s : %d\n", TS[i].nom, TS[i].valeur);
    }
}

// Vérifie si un identifiant est présent dans la table des symboles.
// Si oui, retourne 1 et met à jour la valeur associée dans v ; sinon, retourne 0
int estPresentTS(char *idf, int *v)
{
    for (int i = 0; i < NbSymb; i++)
    {
        if (strcmp(TS[i].nom, idf) == 0)
        {
            *v = TS[i].valeur;
            return 1; // Vrai, l'identifiant est présent
        }
    }
    return 0; // Faux, l'identifiant n'est pas présent
}

// Insère un nouvel identifiant dans la table des symboles avec sa valeur associée.
// Si l'identifiant est déjà présent, met à jour sa valeur.
void insererTS(char *idf, int v)
{
    int present = 0;
    for (int i = 0; i < NbSymb; i++)
    {
        if (strcmp(TS[i].nom, idf) == 0)
        {
            TS[i].valeur = v;
            present = 1;
            break;
        }
    }
    if (!present)
    {
        if (NbSymb < NBMAXSYMB)
        { // Contrôle si la table est pleine ou non.
            strcpy(TS[NbSymb].nom, idf);
            TS[NbSymb].valeur = v;
            NbSymb++;
        }
        else
        {
            printf("Erreur : Table des symboles est pleine.\n");
        }
    }
}
