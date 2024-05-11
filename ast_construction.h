
#ifndef __AST_CONSTRUCTION__
#define __AST_CONSTRUCTION__

#include "type_ast.h"

Ast creer_operation(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) ;
// renvoie un arbre abstrait de nature OPERATEUR,  d'operateur opr 
// et ayant opde_gauche et opde_droit pour fils gauche et droit

Ast creer_bool(TypeOperateur opr , Ast opde_gauche , Ast opde_droit);
Ast creer_noeud();
void liberer_arbre(Ast Arbre);

Ast creer_valeur(float val) ; 
// renvoie un arbre abstrait "feuille", de nature OPERATION  
// et de valeur val

Ast creer_idf(char *idf);
Ast creer_seqinst(Ast gauche, Ast droit);
Ast creer_aff(Ast gauche, Ast droite);
Ast creer_lire(Ast fils_gauche);
Ast creer_ecrire(Ast fils_gauche);
Ast creer_si(Ast Acond, Ast Athen, Ast Aelse); 
Ast creer_tantque(Ast Acond, Ast Afaire);


#endif
