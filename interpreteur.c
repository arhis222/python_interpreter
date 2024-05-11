#include <stdio.h>
#include "table_symbole.h"
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "ast_parcours.h"
#include "ast_construction.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
        Ast Arbre = NULL;
        char user_reponse1, user_reponse2 ;

        // Initialisation de la table des symboles
        initTS();

        switch (argc)
        {
        case 1:
                // Analyse du code de l'interpréteur depuis stdin
                analyser_interpreteur("", &Arbre);
                break;
        case 2:
                // Analyse du code de l'interpréteur depuis un fichier
                analyser_interpreteur(argv[1], &Arbre);
                break;
        default:
                printf("Nombre d'arguments incorrects !\n");
                exit(1);
        }

        // Interprétation de l'arbre syntaxique abstrait
        interpreter(Arbre);
        printf("\nL'execution est terminée avec succés\n");

        // Affichage de la table des symboles
        do {
        printf("\nVoulez-vous afficher la table des symboles ? (o/n) ");
        scanf(" %c", &user_reponse1);
        printf("\n");
        } 
        
        while (user_reponse1 != 'o' && user_reponse1 != 'O' && user_reponse1 != 'n' && user_reponse1 != 'N');
                if (user_reponse1 == 'o' || user_reponse1 == 'O') {
                afficheTS();
                }


        // Affichage de la formule formée
        do {
        printf("\nVoulez-vous afficher la formule formée ? (o/n) ");
        scanf(" %c", &user_reponse2);
        } 
        
        while (user_reponse2 != 'o' && user_reponse2 != 'O' && user_reponse2 != 'n' && user_reponse2 != 'N');
                if (user_reponse2 == 'o' || user_reponse2 == 'O') {
                printf("\nFormule formée: ");
                afficher_arb(Arbre);
                printf("\n");
                }

        return 0;
}
