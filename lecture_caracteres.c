
/* ------------------------------------------------------------------------
-- module letcure_caracteres
--
-- sequence de caracteres
--
-- P. Habraken : 12 novembre 2002
-- L. Mounier : Aout 2016 (version en C)
 ------------------------------------------------------------------------ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lecture_caracteres.h"

// Déclaration des variables locales au module
int CarCour;                         // Caractère courant
unsigned int LigneCour, ColonneCour; // Numéros de ligne et colonne
FILE *File;                          // Le fichier d'entrée

// Fonction pour démarrer la lecture des caractères à partir d'un fichier ou de l'entrée standard
void demarrer_car(char *nom_fichier)
{
   if (strlen(nom_fichier) == 0) // Vérifier si le nom du fichier est vide

   {
      File = stdin; // Utiliser l'entrée standard si aucun nom de fichier n'est fourni
   }
   else
   {
      File = fopen(nom_fichier, "r");
      if (File == NULL) // Vérifier si le fichier n'a pas pu être ouvert

      {
         fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", nom_fichier);
         exit(1);
      }
   }
   LigneCour = 1; // Initialiser les numéros de ligne et de colonne
   ColonneCour = 0;
   avancer_car(); // Avancer pour lire le premier caractère
}

// Fonction pour avancer à la prochaine position dans le fichier et mettre à jour les numéros de ligne et de colonne
void avancer_car()
{
   if (!feof(File)) // Vérifier si le fichier n'est pas à sa fin

   {
      CarCour = fgetc(File); // Lire le caractère suivant dans le fichier

      if (CarCour != '\n') // Vérifier si le caractère n'est pas une nouvelle ligne

      {
         ColonneCour = ColonneCour + 1; // Mettre à jour la colonne courante
      }
      else
      {
         ColonneCour = 1; // Réinitialiser la colonne courante et avancer à la ligne suivante

         LigneCour = LigneCour + 1;
      }
   }
   else
   {
      CarCour = EOF; // Si le fichier est à sa fin, définir le caractère courant comme la fin de fichier
   }
}

/* --------------------------------------------------------------------- */

char caractere_courant()
{
   return CarCour;
}

/* --------------------------------------------------------------------- */

int fin_de_sequence_car()
{
   return CarCour == EOF;
}

/* --------------------------------------------------------------------- */

unsigned int numero_ligne()
{
   return LigneCour;
}

/* --------------------------------------------------------------------- */

unsigned int numero_colonne()
{
   return ColonneCour;
}

/* --------------------------------------------------------------------- */

void arreter_car()
{
   fclose(File);
}

/* --------------------------------------------------------------------- */

// begin
// put("Analyseur lexical : Machine_Caracteres. ");
// put_line("Copyright UJF - UFR IMAG.");
// end lecture_caracteres;
