#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

#include "type_ast.h"

Ast creer_operation(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = opr;
      if (opde_gauche == NULL || opde_droit == NULL) {
         printf("ERREUR_EXPRESSION\n") ;
	 exit(1) ;
      } else {
         expr->gauche = opde_gauche;
         expr->droite = opde_droit;
      } ;
      return expr ;
}

Ast creer_bool(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = opr;
      if (opde_gauche == NULL ) {
         printf("ERREUR_EXPRESSION\n") ;
         exit(1) ;
      } else {
         expr->gauche = opde_gauche;
         expr->droite = opde_droit;
      } ;
      return expr ;
}

Ast creer_noeud() {
    Ast n = malloc(sizeof(NoeudAst));
    return n;
}

void liberer_arbre(Ast Arbre) {
    if (!Arbre) { return; }
    if (Arbre->gauche) { liberer_arbre(Arbre->gauche); }
    if (Arbre->central) { liberer_arbre(Arbre->central); }
    if (Arbre->droite) { liberer_arbre(Arbre->droite); }
    if (Arbre->chaine) { free(Arbre->chaine); }
    free(Arbre);
}

Ast creer_valeur(float val) { 
      Ast expr = creer_noeud();
      expr->nature = VALEUR;
      expr->instruction = N_VALEUR;
      expr->valeur = val;
      return expr ;
}


Ast creer_idf(char *idf) {
      Ast arbre = creer_noeud();
      arbre->operateur = OPERATUER_NULL;
      arbre->nature = INSTRUCTION;
      arbre->instruction = N_IDF;
      arbre->chaine = strdup(idf);
      return arbre;
}
Ast creer_seqinst(Ast gauche, Ast droit) { // cree un noeud N_SEPINST de fils gauche  et de fils droit
      Ast noeud = creer_noeud();
      noeud->nature = INSTRUCTION;
      noeud->instruction = N_SEPINST;
      if (gauche == NULL){
            printf("ERREUR_EXPRESSION\n");
            exit(1);
      }
      noeud->gauche = gauche;
      noeud->droite = droit;
      return noeud;
}

Ast creer_aff(Ast gauche, Ast droite) { // cree un noeud N_AFF de fils gauche et droite
      Ast noeud = creer_noeud();
      noeud->nature = INSTRUCTION;
      noeud->instruction = N_AFF;
      if (gauche == NULL || droite == NULL) {
        printf("ERREUR_EXPRESSION\n");
        exit(1);
      }
      noeud->gauche = gauche;
      noeud->droite = droite;
      return noeud;
     
}

Ast creer_lire(Ast gauche) { // cree un noeud N_LIRE de fils gauche 
      Ast noeud = creer_noeud();
      noeud->nature = INSTRUCTION;
      noeud->instruction = N_LIRE;
      noeud->gauche = gauche;
      return noeud;
}

Ast creer_ecrire(Ast gauche) { // cree un noeud N_ECRIRE de fils gauche 
      Ast noeud = creer_noeud();
      noeud->nature = INSTRUCTION;
      noeud->instruction = N_ECRIRE;
      noeud->gauche = gauche;
      return noeud;
}

Ast creer_si(Ast Acond, Ast Athen, Ast Aelse){ //creer un noeud N_SI de fils gauche Acond, de fils milieu Athen et de fils droit Aelse
      Ast noeud = creer_noeud();
      noeud->nature = INSTRUCTION;
      noeud->instruction = N_SI;
      noeud->gauche = Acond;
      noeud->central = Athen;
      noeud->droite = Aelse;
      return noeud;
}

Ast creer_tantque(Ast Acond, Ast Afaire){ //creer un noeud N_TANTQUE de fils gauche Acond et de fils droit Afaire
      Ast noeud = creer_noeud();
      noeud->nature = INSTRUCTION;
      noeud->instruction = N_TANTQUE;
      noeud->gauche = Acond;
      noeud->droite = Afaire;
      return noeud;
}