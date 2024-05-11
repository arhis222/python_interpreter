/* ------------------------------------------------------------------------
-- paquetage machine_lexemes
--
-- analyse lexicale d'une expression arithmetique
--
-- P.Habraken - 18/01/2010
--
-- 2 aout 2006 - PH :
-- remplacement record a champs variants par record "plat"
------------------------------------------------------------------------ */

   typedef enum {
	  ERREUR_CAR,   // caractere incorrect
	  CHIFFRE,			// chiffre 
	  SYMBOLE,			// symbole,
     C_FIN_SEQUENCE,   // caractere de fin de sequence  
     LETTRE
   } Nature_Caractere ;

   typedef enum { 
      ENTIER,           // sequence de chiffres
      DECIMAL,          // nombres décimaux
      PLUS,             // +
      MOINS,            // -
      MUL,              // *
      DIV,              // '/'
      PARO,             // '('
      PARF,             // ')'
      FIN_SEQUENCE,     // pseudo lexeme ajoute en fin de sequence
      AFF,              // '=' operateur d'affectation 
      SEPINST,          // ';' (fin_de_ligne devient separateur)
      IDF,              // seq. non vide de lettre/chiffre (debutant par lettre)
      LIRE,             //mots-cles lire
      ECRIRE,           //mots cles ecrire
      SI,               //mots_cles si
      ALORS,            //mots cles alors
      SINON,            //mots cles sinon
      FSI,              //mots cles fsi
      OPCOMP,           //operateur de comparaison {>,<,!=,>=,<=,==}
      OPBOOL,           //operateur logique {et,ou,non}
      TANTQUE,          //mots cles tantque
      FAIRE,            //mots cles faire
      FAIT,             //mots cles fait
    } Nature_Lexeme ;


   typedef struct { 
      Nature_Lexeme nature;    // nature du lexeme
      unsigned int ligne;           // numero de ligne
      unsigned int colonne;         // numero de colonne
      char chaine[256];           // chaine de caracteres
      int valeur;          // valeur d'un entier
      float valeur_float; // la valeur après les virgules.
   } Lexeme ; 

   void afficher(Lexeme l);

   void demarrer(char *nom_fichier);
   // e.i. : indifferent
   // e.f. : la sequence de lexemes est lue dans le fichier designe par
   //        nom_fichier
   //        fin_de_sequence <=> lexeme_courant.nature = FIN_SEQUENCE
   //        (non fin_de_sequence) => lexeme courant est le premier
   //        lexeme de la sequence
   //        l'exception Erreur_Lexicale est levee en cas d'erreur

   void avancer();
   // pre-condition : la machine sequentielle est demarree
   // e.i. : on pose i = rang du lexeme_courant :
   //        (non fin_de_sequence)
   //        et (non lexeme_courant.nature = FIN_SEQUENCE)
   // e.f. : fin_de_sequence <=> lexeme_courant.nature = FIN_SEQUENCE
   //        (non fin_de_sequence) => lexeme_courant est le lexeme i+1
   //        l'exception Erreur_Lexicale est levee en cas d'erreur

   Lexeme lexeme_courant();
   // pre-condition : la machine sequentielle est demarree
   // lexeme_courant est :
   // . le pseudo lexeme FIN_SEQUENCE si fin_de_sequence
   // . le pseudo lexeme ERREUR si une erreur a ete detectee
   // . le lexeme de rang i sinon

   int fin_de_sequence();
   // pre-condition : la machine sequentielle est demarree
   // fin_de_sequence vaut :
   // . vrai si tous les lexemes de la sequence ont ete reconnus
   // . faux sinon

   void arreter();
   // e.i. : la machine sequentielle est demarree
   // e.f. : la machine sequentielle est arretee
   
   // vaut vrai ssi c designe un caractere separateur
   int est_separateur(char c);

   // renvoie la chaine de caracteres correspondant a la nature du lexeme
   char *Nature_vers_Chaine (Nature_Lexeme nature);

   // cette fonction ajoute le caractere c a la fin de la chaine s 
   // (la chaine s est donc modifiee)
 
   void ajouter_caractere (char *s, char c);
   int est_symbole(char c);
   int est_lettre(char c); // verifie si c'est une lettre
   Nature_Caractere nature_caractere (char c);
