#include "type_ast.h"
/*
void analyser(char *fichier, int *resultat);//pour le tp1
void analyser_2(char *fichier, int *resultat); //pour le TP2
void analyser_3(char *nom_fichier);//pour le tp3


// e.i : indifferent
// e.f : une Expression Arithmetique a ete lue dans fichier
// si elle ne contient pas d’erreur de syntaxe un message est affiche
// sinon le pgm termine sur un message d’erreur
void rec_eaep(int* val);
*/
void Rec_pgm(Ast *A);
void analyser_calculatrice(char *nom_fichier, Ast *A);
void analyser_interpreteur(char* nom_fichier, Ast *A);

void rec_op(char* op);
float evaluer(Ast A);

void Rec_eag(Ast *A);
void Rec_terme(Ast *A);
void Rec_seq_terme(Ast *A);
void Rec_suite_seq_terme(Ast Ag, Ast *A);
void Rec_facteur(Ast *A);
void Rec_seq_facteur(Ast *A);
void Rec_suite_seq_facteur(Ast Ag, Ast *A);
void Rec_op1(TypeOperateur *Op);
void Rec_op2(TypeOperateur *Op);
void Rec_op_comp(TypeOperateur *Op);
void Rec_op_bool(TypeOperateur *Op);
void Rec_aff();
void Rec_seq_aff();
void Rec_seq_inst(Ast *A);
void Rec_suite_seq_inst(Ast A1, Ast *A);
void Rec_condition(Ast *Acond);
void Rec_bool_condition(Ast *Acond);
void Rec_inst(Ast *A);



