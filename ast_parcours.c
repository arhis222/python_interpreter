#include <stdlib.h>
#include <stdio.h>
#include "type_ast.h"
#include "table_symbole.h"


void aff_operateur(TypeOperateur op){
	switch (op) {
		case N_PLUS:
			printf("+") ;
			break;
		case N_MOINS:
			printf("-") ;
			break;
		case N_MUL:
			printf("*") ;
			break;
		case N_DIV:
			printf("/") ;
			break;
		default:
			break;
	} 
}

void afficher_arb(Ast expr) {
    if (expr == NULL)
        return;
    switch (expr->nature) {
        case OPERATION:
            switch (expr->operateur) {
                case N_PLUS:
                    printf("+");
                    break;
                case N_MOINS:
                    printf("-");
                    break;
                case N_MUL:
                    printf("*");
                    break;
                case N_DIV:
                    printf("/");
                    break;
				case N_SUP:
					printf(">");
					break;
				case N_INF:
					printf("<");
					break;
				case N_SUPEGAL:
					printf(">=");
					break;
				case N_INFEGAL:
					printf("<=");
					break;
				case N_DIFF:
					printf("!=");
					break;
				case N_ET:
					printf("et");
					break;
				case N_OU:
					printf("ou");
					break;
				case N_NON:
					printf("non");
					break;
                default:
                    break;
            }
            printf("(");
            afficher_arb(expr->gauche);
            if (expr->droite != NULL) {
                printf(", ");
                afficher_arb(expr->droite);
            }
            printf(")");
            break;
		
        case VALEUR:
			// si le résultat est un entier, on l'affiche sans les décimales
			if ((int)(expr->valeur * 10000) % 10000 == 0) {
			printf("%d", (int)expr->valeur);
			} 
			// sinon on l'affiche avec les décimales
			else {
			printf("%.4f", expr->valeur);
			}
            break;
			
        case INSTRUCTION:
            switch (expr->instruction) {
                case N_SEPINST:
					printf("(");
					if (expr->gauche) { afficher_arb(expr->gauche); }
					//aff_operateur(expr->type);
					if (expr->droite) { afficher_arb(expr->droite); }
					printf(")");
					break;
				case N_AFF:
					printf("aff(");
					afficher_arb(expr->gauche);
					printf(", ");
					afficher_arb(expr->droite);
					printf(")");
					break;
				case N_IDF:
					printf("%s", expr->chaine);
					break;
				case N_LIRE:
					printf("(");
					printf("lire(%s)", expr->gauche->chaine);
					break;
				case N_ECRIRE:
					printf("ecrire(");
					afficher_arb(expr->gauche);
					printf(")");
					break;
				case N_VALEUR:
           		 	printf("%f", expr->valeur);
           			break;
				case N_SI:
					printf(" si ");
					afficher_arb(expr->gauche);
					printf(" alors ");
					afficher_arb(expr->central);
					printf(" sinon ");
					afficher_arb(expr->droite);
					printf(" fsi");
					break;
				case N_TANTQUE:
					printf(" tantque ");
					afficher_arb(expr->gauche);
					printf(" faire ");
					afficher_arb(expr->droite);
					printf(" fait ");
					break;
				
				default:
					break;
			}
            break;
        
		default:
            break;
    }
}

int evaluation(Ast expr) {
      // A COMPLETER !
	  int Vg,Vd,valeur;
	  switch(expr->nature)
	  {
	  	case VALEUR : //feuille
			return expr->valeur;
		case INSTRUCTION:
			if (!estPresentTS(expr->chaine, &valeur)) {
            printf("Erreur : identificateur non déclaré\n");
            exit(EXIT_FAILURE);
        	}
        	return valeur;
		break;
		case OPERATION : //operateur
			Vg = evaluation(expr->gauche);
			Vd = evaluation(expr->droite);
			switch(expr->operateur){
				case N_PLUS:
					return Vg + Vd;
				case N_MOINS:
					return Vg - Vd;
				case N_MUL:
					return Vg * Vd;
				case N_DIV:
					if (Vd == 0) 
					{
						printf("Erreur division par ZERO\n");
						exit(1);
					}
					return Vg / Vd;
				default:
					break;
			}	
		break;
		default:
            break;
	  }
      return -1 ;
}

int valeur_booleene(Ast A)
{
	// évalue l'arbre abstract d'une condition
	int valeurg, valeurd ; //valeurs de fils gauche et droite
	valeurg = evaluation(A->gauche) ;
	valeurd = evaluation(A->droite) ;
	switch(A->operateur)
	{
		case N_SUP:
			return valeurg > valeurd;
		case N_INF:
			return valeurg < valeurd;
		case N_SUPEGAL:
			return valeurg >= valeurd;
		case N_INFEGAL:
			return valeurg <= valeurd;
		case N_DIFF:
			return valeurg != valeurd;
		case N_EGAL:
			return valeurg == valeurd;
		default:
			break;
	}
	return -1;

}

int valeur_booleene_op_bool(Ast A)
{
	if (A->operateur == N_NON)
	{
		return !valeur_booleene(A->gauche);
	}
	
	else {
		if(A->operateur == N_ET || A->operateur == N_OU)
		{
			int valeurg, valeurd ; //valeurs de fils gauche et droite
			valeurg = valeur_booleene_op_bool(A->gauche) ;
			valeurd = valeur_booleene_op_bool(A->droite) ;
			switch(A->operateur)
			{
				case N_ET:
					return valeurg && valeurd;
				case N_OU:
					return valeurg || valeurd;
				case N_NON:
					return !valeurg;
				default:
					break;
			}
		}
		else {
			return valeur_booleene(A);
		}
		
	}
	return -1;

}


void interpreter_aff(Ast A)
{
	char *idf; // nom de l’IDF
	int v; // valeur de l’IDF
	idf = A->gauche->chaine; // on recupere le nom de l’IDF a affecter
	v = evaluation(A->droite); // on recupere la valeur de l’expression
	insererTS(idf, v); // on insere/remplace ce couple dans la TS
}

void interpreter_lire(Ast A)
{
	int v; // valeur de l’IDF
	// lecture d’un entier au clavier
	printf("Saisir la valeur du %s : ", A->gauche->chaine);
	scanf("%d", &v);
	// insere/remplace dans la TS
	insererTS(A->gauche->chaine, v) ;
}

void interpreter_ecrire(Ast A)
{
	int v; // valeur de l’IDF
	// calcul de l’eag a afficher
	v = evaluation(A->gauche);
	// affichage de v a l’ecran
	printf ("Voici valeur de l'operation ecrire() : %d\n",v) ;
}

void interpreter(Ast A);

void interpreter_si_alors_sinon(Ast A)
{	
	int condition ; // valeur de la condition
	// evaluation de la condition
	condition = valeur_booleene_op_bool(A->gauche);
	if (condition){ 
		interpreter(A->central); 
	}
	else {
		interpreter(A->droite);
	}
	
}

void interpreter_tantque(Ast A){ // A est un noeud N_TANTQUE
	int condition ; // valeur de la condition
	// evaluation de la condition
	condition = valeur_booleene_op_bool(A->gauche);
	while (condition){
		interpreter(A->droite);
		condition = valeur_booleene_op_bool(A->gauche);
	}

}

void interpreter(Ast A)
{	
	switch(A->instruction)
	{
	  	case N_SEPINST : 
			interpreter(A->gauche) ;
			if (A->droite) { 
                interpreter(A->droite);
            }
			break;

		case N_AFF : //affectation
			interpreter_aff(A);
			break;

		case N_LIRE : //lire
			interpreter_lire(A);
			break;

		case N_ECRIRE : //ecrire
			interpreter_ecrire(A);
			break;
		
		case N_SI :
			interpreter_si_alors_sinon(A);
			break;
		
		case N_TANTQUE :
			interpreter_tantque(A);
			break;

		default:
			printf("Erreur de syntaxe");
			exit(1);
	}
}

