#ifndef __AST_PARCOURS__
#define __AST_PARCOURS__

void afficher_arb(Ast expr) ;
// affiche l'arbre abstrait de l'expression arithmetique expr

int evaluation(Ast expr) ;
// calcule la valeur de l'expression arithmetique expr
// FONCTION A COMPLETER !

int valeur_booleene(Ast A);
// évalue l'arbre abstract d'une condition

int valeur_booleene_op_bool(Ast A);
// évalue l'arbre abstract d'une condition bool (et,ou,non)

void interpreter_aff(Ast A);
void interpreter_lire(Ast A);
void interpreter_ecrire(Ast A);
void interpreter_si_alors_sinon(Ast A);
void interpreter_tantque(Ast A);

void interpreter(Ast A);








#endif

