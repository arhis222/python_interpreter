
#ifndef __TYPE_AST__
#define __TYPE_AST__ 

typedef enum {OPERATION, VALEUR, INSTRUCTION} TypeAst ;
typedef enum {OPERATUER_NULL, N_PLUS, N_MUL, N_MOINS, N_DIV, N_EGAL, N_SUP, N_INF, N_SUPEGAL, N_INFEGAL, N_DIFF, N_ET, N_NON, N_OU } TypeOperateur ;

// Nouveaux types de nœuds pour l'arbre abstrait
typedef enum {N_INSTRUCTION_NULL, N_SEPINST, N_AFF, N_LIRE, N_ECRIRE, N_IDF, N_VALEUR, N_SI, N_TANTQUE} TypeInstruction ;

typedef struct noeud { 
	TypeAst nature ;
	TypeOperateur operateur ;
	TypeInstruction instruction; // Nouveau champ pour le type d'instruction
	struct noeud *gauche, *central, *droite ;
      	float valeur ;
		char *chaine ; //identificateur
} NoeudAst ;

typedef NoeudAst *Ast ;

#endif 

