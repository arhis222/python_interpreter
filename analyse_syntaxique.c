#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"

#include "ast_construction.h"
#include "ast_parcours.h"
#include "type_ast.h"

#include "table_symbole.h"

extern Lexeme lexeme_courant(); // var locale

void Rec_pgm(Ast *A)
{
    Rec_seq_inst(A);
}

void analyser_calculatrice(char *nom_fichier, Ast *A)
{
    // *resultat = 0;
    // rec_eaep(resultat); // & ou pas
    Rec_eag(A);

    if (lexeme_courant().nature != FIN_SEQUENCE)
    {
        printf("Erreur de syntaxe ! \n");
        exit(1);
    }

    printf("Il n'y a pas d'erreur de syntaxe.\n");
}

void analyser_interpreteur(char *nom_fichier, Ast *A)
{
    demarrer(nom_fichier);
    // initTS();
    Rec_pgm(A); // (fichier, A) ; // A contient l’Ast du programme lu
    // interpreter(*A);
    // afficheTS();
    arreter();
}

void rec_op(char *op)
{
    switch (lexeme_courant().nature)
    {
    case PLUS:
    case MOINS:
    case MUL:
    case DIV:
        *op = lexeme_courant().chaine[0];
        avancer();
        break;
    default:
        printf("Erreur de syntaxe\n");
        exit(1);
    }
}

// Fonction pour évaluer une expression arithmétique représentée par un arbre syntaxique abstrait (AST)
float evaluer(Ast A)
{
    float Vg, Vd;
    switch (A->nature) // Examiner la nature de l'AST
    {
    case VALEUR:
        return A->valeur; // Retourner la valeur contenue dans la feuille
    case OPERATION:
        Vg = evaluer(A->gauche); // Évaluer le sous-arbre gauche
        Vd = evaluer(A->droite); // Évaluer le sous-arbre droit
        // Examiner le type d'opération
        switch (A->operateur)
        {
        case N_PLUS:
            return Vg + Vd; // Retourner la somme des valeurs des sous-arbres
        case N_MOINS:
            return Vg - Vd; // Retourner la différence des valeurs des sous-arbres
        case N_DIV:
            if (Vd == 0) // Vérifier si la division par zéro est tentée

            {
                printf("\nDivision par zéro!\n"); // Afficher un message d'erreur
                exit(1);                          // Quitter le programme avec un code d'erreur
            }
            else
            {
                return Vg / Vd; // Retourner le résultat de la division
            }
        case N_MUL:
            return Vg * Vd; // Retourner le produit des valeurs des sous-arbres
        default:
            break;
        }
    default:
        // Si la nature de l'AST n'est pas reconnue
        printf("Opérateur inconnu\n"); // Afficher un message d'erreur
        exit(1);                       // Quitter le programme avec un code d'erreur
    }
}

void Rec_eag(Ast *A)
{
    Rec_seq_terme(A);
}
void Rec_terme(Ast *A)
{
    Rec_seq_facteur(A);
}
void Rec_seq_terme(Ast *A)
{
    Ast A1 = NULL;
    Rec_terme(&A1);
    Rec_suite_seq_terme(A1, A);
}
void Rec_suite_seq_terme(Ast Ag, Ast *A)
{
    Ast A1 = NULL;
    Ast Ad = NULL;
    TypeOperateur Op;
    switch (lexeme_courant().nature)
    {
    case PLUS:
    case MOINS:
        // avancer();
        Rec_op1(&Op);
        Rec_terme(&Ad);
        A1 = creer_operation(Op, Ag, Ad);
        Rec_suite_seq_terme(A1, A);
        break;

    default: // cas epsilon
        *A = Ag;
        break;
    }
}
// Fonction récursive pour reconnaître et construire le facteur d'une expression arithmétique
void Rec_facteur(Ast *A)
{
    switch (lexeme_courant().nature)
    {
    case IDF:
        // Créer une feuille représentant l'identificateur
        *A = creer_idf(lexeme_courant().chaine);       // Créer un nœud AST pour l'identificateur
        avancer();                                     // Avancer au lexème suivant
        break;
    
    case DECIMAL:
        // Créer une feuille représentant la valeur décimale
        *A = creer_valeur(lexeme_courant().valeur_float); // Créer un nœud AST pour la valeur décimale
        avancer();                                  // Avancer au lexème suivant
        break;

    case ENTIER:
        // Créer une feuille représentant la valeur entière
        *A = creer_valeur(lexeme_courant().valeur); // Créer un nœud AST pour la valeur entière
        avancer();                                  // Avancer au lexème suivant
        break;

    case PARO:
        avancer();  // Avancer au lexème suivant
        Rec_eag(A); // Appeler la fonction pour reconnaître et construire l'expression arithmétique
        // Vérifier si la parenthèse fermante correspondante est présente
        if (lexeme_courant().nature != PARF)
        {
            printf("Erreur de syntaxe\n"); // Afficher un message d'erreur de syntaxe
            exit(1);                       // Quitter le programme avec un code d'erreur
        }
        avancer(); // Avancer au lexème suivant après la parenthèse fermante
        break;

    // Cas par défaut en cas de lexème courant inattendu
    default:
        printf("Erreur de syntaxe\n"); // Afficher un message d'erreur de syntaxe
        exit(1);                       // Quitter le programme avec un code d'erreur
    }
}

void Rec_seq_facteur(Ast *A)
{
    Ast A1 = NULL;
    Rec_facteur(&A1);
    Rec_suite_seq_facteur(A1, A);
}

void Rec_suite_seq_facteur(Ast Ag, Ast *A)
{
    Ast A1 = NULL;
    Ast Ad = NULL;
    TypeOperateur Op;
    switch (lexeme_courant().nature)
    {
    case DIV:
    case MUL:
        // avancer();
        Rec_op2(&Op);
        Rec_facteur(&Ad);
        A1 = creer_operation(Op, Ag, Ad);
        Rec_suite_seq_facteur(A1, A);
        break;

    default: // cas epsilon
        *A = Ag;
        break;
    }
}

// Fonction pour reconnaître et récupérer le premier opérateur
void Rec_op1(TypeOperateur *Op)
{
    switch (lexeme_courant().nature)
    {
    case PLUS:
        *Op = N_PLUS;               // Attribuer l'opérateur correspondant
        avancer();                  // Avancer au lexème suivant
        break;

    case MOINS:
        *Op = N_MOINS; // Attribuer l'opérateur correspondant
        avancer();     // Avancer au lexème suivant
        break;

    case MUL:
        *Op = N_MUL; // Attribuer l'opérateur correspondant
        avancer();   // Avancer au lexème suivant
        break;

    case DIV:
        *Op = N_DIV; // Attribuer l'opérateur correspondant
        avancer();   // Avancer au lexème suivant
        break;

    default:
        printf("Erreur de syntaxe\n"); // Afficher un message d'erreur de syntaxe
        exit(1);                       // Quitter le programme avec un code d'erreur
    }
}

void Rec_op2(TypeOperateur *Op)
{
    switch (lexeme_courant().nature)
    {
    case MUL:
        *Op = N_MUL;
        avancer();
        break;
    case DIV:
        *Op = N_DIV;
        avancer();
        break;
    default:
        printf("Erreur de syntaxe\n");
        exit(1);
    }
}

// Fonction pour reconnaître et récupérer un opérateur de comparaison
void Rec_op_comp(TypeOperateur *Op)
{
    // Vérifier si le lexème courant est un opérateur de comparaison
    if (lexeme_courant().nature == OPCOMP)
    {
        // Comparer la chaîne du lexème courant avec différents opérateurs de comparaison
        if (strcmp(lexeme_courant().chaine, ">") == 0)
        {
            *Op = N_SUP;   // Attribuer l'opérateur "supérieur" (>)
        }
        else if (strcmp(lexeme_courant().chaine, "<") == 0)
        {
            *Op = N_INF;   // Attribuer l'opérateur "inférieur" (<)
        }
        else if (strcmp(lexeme_courant().chaine, "!=") == 0)
        {
            *Op = N_DIFF;   // Attribuer l'opérateur "différent de" (!=)
        }
        else if (strcmp(lexeme_courant().chaine, ">=") == 0)
        {
            *Op = N_SUPEGAL; // Attribuer l'opérateur "supérieur ou égal" (>=)
        }
        else if (strcmp(lexeme_courant().chaine, "<=") == 0)
        {
            *Op = N_INFEGAL; // Attribuer l'opérateur "inférieur ou égal" (<=)
        }
        else if (strcmp(lexeme_courant().chaine, "==") == 0)
        {
            *Op = N_EGAL;   // Attribuer l'opérateur "égal" (==)
        }
        else
        {
            printf("Erreur de syntaxe\n"); // Afficher un message d'erreur de syntaxe si l'opérateur n'est pas reconnu
            exit(1);                       // Quitter le programme avec un code d'erreur
        }
        avancer(); // Avancer au lexème suivant
    }
    else
    {
        printf("Erreur de syntaxe\n"); // Afficher un message d'erreur de syntaxe si le lexème courant n'est pas un opérateur de comparaison
        exit(1);                       // Quitter le programme avec un code d'erreur
    }
}

void Rec_op_bool(TypeOperateur *Op)
{
    if (lexeme_courant().nature == OPBOOL)
    {
        if (strcmp(lexeme_courant().chaine, "et") == 0)
        {
            *Op = N_ET;
        }
        else if (strcmp(lexeme_courant().chaine, "ou") == 0)
        {
            *Op = N_OU;
        }
        else if (strcmp(lexeme_courant().chaine, "non") == 0)
        {
            *Op = N_NON;
        }
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        avancer();
    }
    else
    {
        printf("Erreur de syntaxe\n");
        exit(1);
    }
    
}

void Rec_aff()
{
    Ast A = NULL;
    int v; // valeur de l'IDF
    // char idf[LIDF]; //nom de l'IDF
    char *idf; // nom de l'IDF
    if (lexeme_courant().nature == IDF)
    {
        idf = lexeme_courant().chaine;
        avancer();
    }
    else
    {
        printf("Erreur de syntaxe\n");
        exit(1);
    }

    if (lexeme_courant().nature == AFF)
    {
        avancer();
    }
    else
    {
        printf("Erreur de syntaxe\n");
        exit(1);
    }

    Rec_eag(&A);       // A contient l’AST de l’expression
    v = evaluer(A);    // v contient la valeur de l’expression
    insererTS(idf, v); // insere/remplace dans la TS

    if (lexeme_courant().nature == SEPINST)
    {
        avancer();
    }
    else
    {
        printf("Erreur de syntaxe\n");
        exit(1);
    }
}

void Rec_seq_aff()
{
    switch (lexeme_courant().nature)
    {
    case IDF:
        Rec_aff();
        Rec_seq_aff();
        break;

    case FIN_SEQUENCE:
        avancer();
        break;

    default: // cas epsilon
        printf("Erreur de syntaxe\n");
        exit(1);
        break;
    }
}

void Rec_seq_inst(Ast *A)
{
    Ast A1 = NULL;
    Rec_inst(&A1);             // produit l’Ast A1 de l’instruction lue
    Rec_suite_seq_inst(A1, A); // produit l’Ast A de la sequence d’instructions lues
}

void Rec_suite_seq_inst(Ast A1, Ast *A)
{
    Ast A2 = NULL;
    switch (lexeme_courant().nature)
    {
    case SEPINST:
        avancer(); // on lit le SEPINST
        // Si apres le ";" il a SI ou SINON ou FSI ou ALORS on ne cree pas de noeud N_SEPINST car ca veut dire cette instruction est seule
        if (lexeme_courant().nature != SI && lexeme_courant().nature != SINON && lexeme_courant().nature != FSI && lexeme_courant().nature != ALORS)
        {
            if (lexeme_courant().nature == FIN_SEQUENCE)
            {
                *A = creer_seqinst(A1, NULL);
                break;
            }
            Rec_seq_inst(&A2);
            *A = creer_seqinst(A1, A2); // cree un noeud N_SEPINST de fils gauche A1 et de fils droit A2
        }
        else
        {
            *A = A1;
            Rec_seq_inst(&A2);
            if (A2 != NULL)
                *A = creer_seqinst(A1, A2); // cree un noeud N_SEPINST de fils gauche A1 et de fils droit A2
        }
        break;

    case PARF:
    case IDF:
        printf("Erreur de syntaxe\n");
        exit(1);

    default: // cas epsilon
        *A = A1;
        break;
    }
}

void Rec_condition(Ast *Acond)
{
    Ast Ag = NULL;
    Ast Ad = NULL;
    TypeOperateur Op;
    Rec_eag(&Ag);
    Rec_op_comp(&Op);
    Rec_eag(&Ad);
    *Acond = creer_operation(Op, Ag, Ad);
}

void Rec_bool_condition(Ast *Acond)
{
    Ast Ag = NULL;
    Ast Ad = NULL;
    TypeOperateur Op;
    if(strcmp(lexeme_courant().chaine, "non") == 0)
    {   
        Rec_op_bool(&Op);
        Rec_bool_condition(&Ag);
        *Acond = creer_bool(Op, Ag, NULL);
        return;
    }
    else {

        Rec_condition(Acond);
        if(lexeme_courant().nature == OPBOOL){
            Rec_op_bool(&Op);
            Rec_bool_condition(&Ad);
            *Acond = creer_bool(Op, *Acond, Ad);
        }
        
    }
    
}

void Rec_inst(Ast *A)
{
    Ast Ag = NULL;
    Ast Ad = NULL;
    Ast Acond = NULL;
    Ast Athen = NULL;
    Ast Aelse = NULL;
    Ast Abody = NULL;

    // char *idf; //nom de l'IDF
    // int v; //valeur de l'IDF
    switch (lexeme_courant().nature)
    {

    case IDF: // affectation
        // idf = lexeme_courant().chaine;
        Ag = creer_idf(lexeme_courant().chaine); // cree un arbre gauche qui contient l’IDF
        avancer();
        if (lexeme_courant().nature == AFF)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        };
        Rec_eag(&Ad); // Ad contient l’AST de l’expression
        // v = evaluer(Ad); // v contient la valeur de l’expression
        // insererTS(idf,v); // insere/remplace dans la TS
        *A = creer_aff(Ag, Ad); // cree un noeud N_AFF de fils Ag et Ad
        break;

    case LIRE:
        avancer();
        if (lexeme_courant().nature == PARO)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        if (lexeme_courant().nature == IDF)
        {
            Ag = creer_idf(lexeme_courant().chaine);
            avancer();
        }
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        };
        *A = creer_lire(Ag); // cree un noeud N_LIRE de fils gauche Ag
        if (lexeme_courant().nature == PARF)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        break;

    case ECRIRE:
        avancer();
        if (lexeme_courant().nature == PARO)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        Rec_eag(&Ag);
        *A = creer_ecrire(Ag); // cree un noeud N_ECRIRE de fils gauche Ag
        if (lexeme_courant().nature == PARF)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        break;

    case SI:
        avancer();
        Rec_bool_condition(&Acond);
        if (lexeme_courant().nature == ALORS)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        Rec_seq_inst(&Athen);
        if (lexeme_courant().nature == SINON)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        Rec_seq_inst(&Aelse);
        if (lexeme_courant().nature == FSI)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        *A = creer_si(Acond, Athen, Aelse); // creer un noeud N_SI de fils gauche Acond, de fils milieu Athen et de fils droit Aelse
        break;

    case TANTQUE:
        avancer();
        Rec_bool_condition(&Acond);
        if (lexeme_courant().nature == FAIRE)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        Rec_seq_inst(&Abody);
        if (lexeme_courant().nature == FAIT)
            avancer();
        else
        {
            printf("Erreur de syntaxe\n");
            exit(1);
        }
        *A = creer_tantque(Acond, Abody); // cree le noeud N_TANTQUE de fils gauche Acond et de fils droit Abody
        break;

    case FAIRE:
    case FAIT:
    case ALORS:
    case SINON:
    case FSI:
        break;

    default:
        printf("Erreur de syntaxe\n");
        exit(1);
    }
}
