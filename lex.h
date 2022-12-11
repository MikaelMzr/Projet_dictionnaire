#ifndef __LEX__H__
#define __LEX__H__


/* Fichiers d'en-tête */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Structure d'un Arbre */
typedef struct tree
{
	char value;
	struct tree *freredroit;
	struct tree *freregauche;
	struct tree *fils;
   
}Tree;


/* Prototypes des fonctions */
Tree *new_tree(char x);
void clean_tree(Tree *tr);
int rechercher(Tree *tr, char mot[]);
int insertion(Tree **tr, char mot[]);
void afficher(Tree *tr);
Tree *alloueNoeud(char x);


#endif
