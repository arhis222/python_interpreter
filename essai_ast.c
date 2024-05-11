#include <stdio.h>

#include "ast_construction.h"
#include "ast_parcours.h"

int main()
{

  Ast ast1, ast2, ast3, ast4, ast;

  ast1 = creer_valeur(12);
  ast2 = creer_valeur(3);
  ast3 = creer_operation(N_PLUS, ast1, ast2);
  ast4 = creer_valeur(2);
  ast = creer_operation(N_MUL, ast3, ast4);

  printf("Premiere exemple : \n");
  printf("Arbre abstrait de l'expression\n");
  afficher_arb(ast);
  printf("\nValeur de l'expression : %d\n\n", evaluation(ast));

  /*#################################################*/
  /*2eme exemple*/
  Ast ast1_1, ast2_1, ast3_1, ast4_1, ast5_1, ast_1;

  ast1_1 = creer_valeur(3);
  ast2_1 = creer_valeur(5);
  ast3_1 = creer_operation(N_MUL, ast1_1, ast2_1);
  ast4_1 = creer_valeur(2);
  ast5_1 = creer_operation(N_PLUS, ast4_1, ast3_1);
  ast_1 = creer_operation(N_MOINS, ast5_1, ast4_1);

  printf("Troisieme exemple : \n");
  printf("Arbre abstrait de l'expression\n");
  afficher_arb(ast_1);
  printf("\nValeur de l'expression : %d\n\n", evaluation(ast_1));

  /*#################################################*/
  /*3eme exemple*/
  Ast ast1_2, ast2_2, ast3_2, ast4_2, ast5_2, ast_2;

  ast1_2 = creer_valeur(2);
  ast2_2 = creer_valeur(3);
  ast3_2 = creer_operation(N_PLUS, ast1_2, ast2_2);
  ast4_2 = creer_valeur(5);
  ast5_2 = creer_operation(N_MOINS, ast4_2, ast1_2);
  ast_2 = creer_operation(N_MUL, ast3_2, ast5_2);

  printf("Troisieme exemple : \n");
  printf("Arbre abstrait de l'expression\n");
  afficher_arb(ast_2);
  printf("\nValeur de l'expression : %d\n\n", evaluation(ast_2));

  /*#################################################*/
  /*4eme exemple*/
  Ast ast1_3, ast2_3, ast3_3, ast4_3, ast5_3, ast_3;

  ast1_3 = creer_valeur(5);
  ast2_3 = creer_valeur(2);
  ast3_3 = creer_operation(N_MOINS, ast1_3, ast2_3);
  ast4_3 = creer_valeur(3);
  ast5_3 = creer_operation(N_DIV, ast4_3, ast3_3);
  ast_3 = creer_operation(N_PLUS, ast2_3, ast5_3);

  printf("Quatrieme exemple : \n");
  printf("Arbre abstrait de l'expression\n");
  afficher_arb(ast_3);
  printf("\nValeur de l'expression : %d\n\n", evaluation(ast_3));

  /*#################################################*/
  /*5eme exemple*/
  Ast ast1_5, ast2_5, ast3_5, ast4_5, ast5_5, ast_5;

  ast1_5 = creer_valeur(5);
  ast2_5 = creer_valeur(2);
  ast3_5 = creer_operation(N_MOINS, ast1_5, ast2_5);
  ast4_5 = creer_valeur(1);
  ast5_5 = creer_operation(N_MOINS, ast3_5, ast4_5);
  ast_5 = creer_operation(N_DIV, ast4_5, ast5_5);

  printf("Cinqueme exemple : \n");
  printf("Arbre abstrait de l'expression\n");
  afficher_arb(ast_5);
  printf("\nValeur de l'expression : %d\n\n", evaluation(ast_5));

  /*#################################################*/
  /*6eme exemple*/

  Ast ast1_6, ast2_6, ast3_6, ast4_6, ast5_6, ast6_6, ast_6;

  ast1_6 = creer_idf("x");
  ast2_6 = creer_lire(ast1_6);
  ast3_6 = creer_valeur(2);
  ast4_6 = creer_operation(N_DIV, ast2_6, ast3_6);
  ast5_6 = creer_valeur(3);
  ast6_6 = creer_operation(N_PLUS, ast4_6, ast5_6);
  ast_6 = creer_seqinst(ast6_6, NULL);

  printf("Sixieme exemple : \n");
  printf("Arbre abstrait de l'expression\n");
  afficher_arb(ast_6);
  printf("\n");
  // printf("\nValeur de l'expression : %d\n\n", evaluation(ast_6)) ;
  /*#################################################*/
}
