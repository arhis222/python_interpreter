#include <stdio.h>
#include <stdlib.h>

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "ast_parcours.h"

int main(int argc, char *argv[])
{
        char user_rep1, user_rep2;
        switch (argc)
        {
        case 1:
                // Démarre l'analyse lexicale sur stdin
                demarrer("");
                break;
        case 2:
                // Démarre l'analyse lexicale sur le fichier transmis en argument
                demarrer(argv[1]);
                break;
        default:
                printf("nombre d'arguments incorrects !\n");
                exit(1);
        };


        // Déclaration des variables pour stocker le résultat de l'évaluation
        float resultat ;
        Ast arbre = NULL;

        // Analyse syntaxique et construction de l'arbre syntaxique abstrait
        analyser_calculatrice(argv[1], &arbre);

        do
        {
        printf("\nVoulez-vous afficher l'arbre' ? (o/n) ");
        scanf(" %c", &user_rep1);
        printf("\n");
        }

        while (user_rep1 != 'o' && user_rep1 != 'O' && user_rep1 != 'n' && user_rep1 != 'N');
        if (user_rep1 == 'o' || user_rep1 == 'O')
        {
                afficher_arb(arbre);
        }

        // Affichage de l'arbre syntaxique abstrait

        // Évaluation de l'expression représentée par l'arbre syntaxique abstrait
        resultat = evaluer(arbre);
        // si le résultat est un entier, on l'affiche sans les décimales
        if ((int)(resultat * 10000) % 10000 == 0) {
        printf("\nVoici le résultat de l'évaluation : %d\n", (int)resultat);
        } 
        // sinon on l'affiche avec les décimales
        else {
        printf("\nVoici le résultat de l'évaluation : %.4f\n", resultat);
        }

        arreter(); // Termine l'analyse lexicale (ferme le fichier si nécessaire)
        return 0;
}
