/* ------------------------------------------------------------------------
-- paquetage analyse_lexicale
--
-- analyse lexicale d'une expression arithmetique
--
-- J-P. Peyrin, G. Serasset (version initiale) : janvier 1999
-- P.Habraken - 18/01/2010
--
-- 10 juin 2006 - PH :
-- remplacement record a champs variants par record "plat"
-- remplacement traitement iteratif par automate
--
-- Aout 2016 - LM : version C
------------------------------------------------------------------------ */
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

#define NB_MOTCLE 12
/* --------------------------------------------------------------------- */

/* Les variables et fonctions locales au module */

Lexeme lexeme_en_cours; /* le lexeme courant */

void ajouter_caractere(char *s, char c);
Nature_Caractere nature_caractere(char c);
int est_separateur(char c);
int est_chiffre(char c);
int est_symbole(char c);
void reconnaitre_lexeme();

/* --------------------------------------------------------------------- */

void demarrer(char *nom_fichier)
{
   demarrer_car(nom_fichier);
   avancer();
}

/* --------------------------------------------------------------------- */

void avancer()
{
   reconnaitre_lexeme();
}

/* --------------------------------------------------------------------- */

Lexeme lexeme_courant()
{
   return lexeme_en_cours;
}

/* --------------------------------------------------------------------- */

int fin_de_sequence()
{
   return lexeme_en_cours.nature == FIN_SEQUENCE;
}

/* --------------------------------------------------------------------- */

void arreter()
{
   arreter_car();
}

/* --------------------------------------------------------------------- */

// reconnaissance d'un nouveau lexeme
// etat initial : le caractere courant est soit separateur
//                soit le 1er caractere d'un lexeme
// etat final :
//       - un nouveau lexeme est reconnu dans lexeme_en_cours
//       - le caractere courant est soit la fin de fichier,
//		soit un separateur,  soit le 1er caractere d'un lexeme

void reconnaitre_lexeme()
{
   typedef enum
   {
      E_INIT,
      E_ENTIER,
      E_DECIMAL,
      E_FIN,
      E_IDF
   } Etat_Automate;                                                                                                               // Déclaration de l'énumération pour les états de l'automate
   Etat_Automate etat = E_INIT;                                                                                                   // Initialisation de l'état de l'automate
   float puissance = 10.0;
   char motCle[NB_MOTCLE][20] = {"lire", "ecrire", "si", "alors", "sinon", "fsi", "et", "ou", "non", "tantque", "faire", "fait"}; // Déclaration du tableau de mots-clés

   // on commence par lire et ignorer les separateurs
   while (est_separateur(caractere_courant()))
   {
      avancer_car();
   };

   lexeme_en_cours.chaine[0] = '\0'; // Initialiser le lexème courant

   // on utilise ensuite un automate pour reconnaitre et construire le prochain lexeme

   while (etat != E_FIN)
   {

      switch (etat)
      {

      case E_INIT: // etat initial

         switch (nature_caractere(caractere_courant()))
         {

         case LETTRE: // Reconnaissance d'un identificateur
            lexeme_en_cours.nature = IDF;
            lexeme_en_cours.ligne = numero_ligne();
            lexeme_en_cours.colonne = numero_colonne();
            ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
            etat = E_IDF;
            avancer_car();
            break;

         case C_FIN_SEQUENCE: // Fin de fichier
            lexeme_en_cours.nature = FIN_SEQUENCE;
            etat = E_FIN;
            break;

         case CHIFFRE: // Reconnaissance d'un entier
            lexeme_en_cours.nature = ENTIER;
            lexeme_en_cours.ligne = numero_ligne();
            lexeme_en_cours.colonne = numero_colonne();
            ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
            lexeme_en_cours.valeur = caractere_courant() - '0';
            etat = E_ENTIER;
            avancer_car();
            break;

         case SYMBOLE: // Reconnaissance d'un symbole
            lexeme_en_cours.ligne = numero_ligne();
            lexeme_en_cours.colonne = numero_colonne();
            ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
            switch (caractere_courant())
            { // Reconnaissance des différents symboles
            case '.':
               lexeme_en_cours.nature = DECIMAL; // je ne suis pas sûr si je dois ca faire vu que le point tout seul ne doit pas être un lexeme à part entière.
               etat = E_DECIMAL;
               break;
            case '(':
               lexeme_en_cours.nature = PARO;
               etat = E_FIN;
               break;
            case ')':
               lexeme_en_cours.nature = PARF;
               etat = E_FIN;
               break;
            case '+':
               lexeme_en_cours.nature = PLUS;
               etat = E_FIN;
               break;
            case '-':
               lexeme_en_cours.nature = MOINS;
               etat = E_FIN;
               break;
            case '*':
               lexeme_en_cours.nature = MUL;
               etat = E_FIN;
               break;
            case '/':
               lexeme_en_cours.nature = DIV;
               etat = E_FIN;
               break;
            case '=':
               // Reconnaissance de l'opérateur de comparaison ou d'affectation
               avancer_car();
               if (caractere_courant() == '=')
               {
                  ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                  lexeme_en_cours.nature = OPCOMP;
                  etat = E_FIN;
               }
               else if (caractere_courant() == ' ')
               {
                  lexeme_en_cours.nature = AFF;
                  etat = E_FIN;
               }
               else
               {
                  printf("Erreur_Lexicale : symbole '=%c' pas connu peut être tu veux dire '==' ?\n", caractere_courant());
                  exit(0);
               }
               break;
            case ';':
               lexeme_en_cours.nature = SEPINST;
               etat = E_FIN;
               break;
            case '!':
               avancer_car();
               if (caractere_courant() == '=')
               {
                  ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                  lexeme_en_cours.nature = OPCOMP;
                  etat = E_FIN;
               }
               else
               {
                  printf("Erreur_Lexicale : symbole '!' pas connu peut être tu veux dire '!=' ?\n");
                  exit(0);
               }
               break;
            case '<':
               avancer_car();
               if (caractere_courant() == '=')
               {
                  ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                  lexeme_en_cours.nature = OPCOMP;
                  etat = E_FIN;
               }
               else if (caractere_courant() == ' ')
               {
                  lexeme_en_cours.nature = OPCOMP;
                  etat = E_FIN;
               }
               else
               {
                  printf("Erreur_Lexicale : symbole '<%c' pas connu peut être tu veux dire '<=' ?\n", caractere_courant());
                  exit(0);
               }
               break;
            case '>':
               avancer_car();
               if (caractere_courant() == '=')
               {
                  ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                  lexeme_en_cours.nature = OPCOMP;
                  etat = E_FIN;
               }
               else if (caractere_courant() == ' ')
               {
                  lexeme_en_cours.nature = OPCOMP;
                  etat = E_FIN;
               }
               else
               {
                  printf("Erreur_Lexicale : symbole '>%c' pas connu peut être tu veux dire '>=' ?\n", caractere_courant());
                  exit(0);
               }
               break;
            default:
               printf("Erreur_Lexicale");
               exit(0);
            };
            avancer_car();
            break;

         default:
            printf("Erreur_Lexicale\n");
            exit(0);
         }
         break;

      case E_IDF:
         switch (nature_caractere(caractere_courant()))
         {
         case LETTRE:
         case CHIFFRE:

            ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
            etat = E_IDF;
            avancer_car();
            break;
         default:
            etat = E_FIN;
            break;
         }
         break;


      case E_DECIMAL:
         switch (nature_caractere(caractere_courant()))
         {
            case CHIFFRE:
               //float puissance = 10.0; //peut-être à décommenter, je ne suis pas sûr si son lieu de déclaration est correct.
               ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
               lexeme_en_cours.valeur_float += (float)(caractere_courant() - '0') / puissance;
               puissance *= 10.0; // Augmenter la puissance de 10 pour le prochain chiffre
               etat = E_DECIMAL;
               avancer_car();
               break;
            default:
               etat = E_FIN;
               break;
         }
         break;

      

      case E_ENTIER: // Reconnaissance d'un entier
         switch (nature_caractere(caractere_courant()))
         {
         case CHIFFRE:
            ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
            lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
            etat = E_ENTIER;
            avancer_car();
            break;

         case SYMBOLE:
                  if (caractere_courant() == '.') {
                  lexeme_en_cours.nature = DECIMAL;
                  ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                  lexeme_en_cours.valeur_float = (float)lexeme_en_cours.valeur;
                  lexeme_en_cours.valeur = 0; // Réinitialiser la valeur entière
                  etat = E_DECIMAL;
                  avancer_car();
                  break;
                  }


         default:
            etat = E_FIN;
         };


      case E_FIN: // etat final
         break;

      }; // fin du switch(etat)
   };    // fin du while (etat != fin)

   // Vérifier si l'identificateur est un mot-clé
   for (int i = 0; i < NB_MOTCLE; i++)
   {
      if (strcmp(lexeme_en_cours.chaine, motCle[i]) == 0)
      {
         // Mettre à jour la nature du lexème en fonction du mot-clé identifié
         switch (i)
         {
         case 0:
            lexeme_en_cours.nature = LIRE;
            etat = E_FIN;
            break;
         case 1:
            lexeme_en_cours.nature = ECRIRE;
            etat = E_FIN;
            break;
         case 2:
            lexeme_en_cours.nature = SI;
            etat = E_FIN;
            break;
         case 3:
            lexeme_en_cours.nature = ALORS;
            etat = E_FIN;
            break;
         case 4:
            lexeme_en_cours.nature = SINON;
            etat = E_FIN;
            break;
         case 5:
            lexeme_en_cours.nature = FSI;
            etat = E_FIN;
            break;
         case 6:
         case 7:
         case 8:
            lexeme_en_cours.nature = OPBOOL;
            etat = E_FIN;
            break;
         case 9:
            lexeme_en_cours.nature = TANTQUE;
            etat = E_FIN;
            break;
         case 10:
            lexeme_en_cours.nature = FAIRE;
            etat = E_FIN;
            break;
         case 11:
            lexeme_en_cours.nature = FAIT;
            etat = E_FIN;
            break;
         default:
            break;
         }
      }
   }
}

/* --------------------------------------------------------------------- */

// cette fonction ajoute le caractere c a la fin de la chaine s
// (la chaine s est donc modifiee)

void ajouter_caractere(char *s, char c)
{
   int l;

   l = strlen(s);
   s[l] = c;
   s[l + 1] = '\0';
};

/* --------------------------------------------------------------------- */

Nature_Caractere nature_caractere(char c)
{ // Pour déterminer la nature d'un caractère
   if (fin_de_sequence_car())
      // printf("FIN_DE_SEQ_CAR\n");
      return C_FIN_SEQUENCE;
   if (est_chiffre(c))
      // printf("EST_CHIFFRE\n");
      return CHIFFRE;
   if (est_lettre(c))
      // printf("EST_LETTRE\n");
      return LETTRE;
   if (est_symbole(c))
      // printf("SYMBOLE\n");
      return SYMBOLE;
   return ERREUR_CAR; // Retourner une erreur si le caractère n'appartient à aucune catégorie reconnue
}
/* --------------------------------------------------------------------- */

// Ca vaut vrai ssi c designe un caractère séparateur
int est_separateur(char c)
{
   return c == ' ' || c == '\t' || c == '\n';
}

/* --------------------------------------------------------------------- */

// Ca vaut vrai ssi c designe un caractère chiffre
int est_chiffre(char c)
{
   return c >= '0' && c <= '9';
}

/* --------------------------------------------------------------------- */

// Ca vaut vrai ssi c designe un caractère correspondant a un symbole
int est_symbole(char c)
{
   switch (c)
   {
   case '+':
   case '-':
   case '*':
   case '(':
   case ')':
   case '/':
   case ':':
   case ';':
   case '=':
   case '<':
   case '>':
   case '!':
   case '.':
      return 1;

   default:
      return 0;
   }
}
int est_lettre(char c)
{ // verifie si c'est une lettre
   if (isalpha((c)))
   {
      return 1;
   }
   return 0;
}

/* --------------------------------------------------------------------- */

// Renvoie la chaine des caractères correspondant à la nature du lexeme
char *Nature_vers_Chaine(Nature_Lexeme nature)
{
   switch (nature)
   {
   case ENTIER:
      return "ENTIER";
   case DECIMAL:
      return "DECIMAL";
   case PLUS:
      return "PLUS";
   case PARO:
      return "PARO";
   case PARF:
      return "PARF";
   case MOINS:
      return "MOINS";
   case MUL:
      return "MUL";
   case FIN_SEQUENCE:
      return "FIN_SEQUENCE";
   case AFF:
      return "AFFECTATION";
   case SEPINST:
      return "SEPARATEUR";
   case IDF:
      return "IDENTIFICATEUR";
   case LIRE:
      return "LIRE";
   case ECRIRE:
      return "ECRIRE";
   case SI:
      return "SI";
   case ALORS:
      return "ALORS";
   case SINON:
      return "SINON";
   case FSI:
      return "FSI";
   case OPCOMP:
      return "OPCOMP";
   case OPBOOL:
      return "OPBOOL";
   case TANTQUE:
      return "TANTQUE";
   case FAIRE:
      return "FAIRE";
   case FAIT:
      return "FAIT";
   default:
      return "ERREUR";
   };
}

/* --------------------------------------------------------------------- */

// Affiche à l'écran le lexeme l
void afficher(Lexeme l)
{

   switch (l.nature)
   {
   case FIN_SEQUENCE:
      break;
   default:
      printf("(ligne %d, ", l.ligne);
      printf("colonne %d) : ", l.colonne);
      printf("[");
      printf("nature = %s", Nature_vers_Chaine(l.nature));
      printf(", chaine = %s, ", l.chaine);
      switch (l.nature)
      {
      case ENTIER:
         printf("valeur = %d", l.valeur);
      default:
         break;

      case DECIMAL:
         printf("valeur =  %.4f", l.valeur_float);
         break;
      };
      printf("]");
   };
}

/* --------------------------------------------------------------------- */
