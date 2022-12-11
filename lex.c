#include "lex.h"


/*fonction qui alloue un Noeud*/
Tree *alloueNoeud(char x){
	Tree *tmp = (Tree*)malloc(sizeof(Tree));
	if(NULL == tmp)
		return NULL;
	tmp->value = x;
	tmp->freredroit = NULL;
	tmp->freregauche = NULL;
	tmp->fils = NULL;
	return tmp;
}

/*-----------------------------------------------------------------------*/

/*Fonction qui nettoie l'arbre , le vide*/
void clean_tree(Tree *tr)
{
	if(tr == NULL)
		return;



	clean_tree(tr->freregauche);
	clean_tree(tr->freredroit);
    clean_tree(tr->fils);


	free(tr);
}

/*-----------------------------------------------------------------------*/

/*fonction qui recherche si le mot est dans l'arbre , si il y est la fonction return 1, sinon elle retournera 0*/

int rechercher(Tree *tr, char mot[]){
	if(tr == NULL){
		return 0;
	}
	if (mot[0] == tr->value){
		if(mot[0]=='\0'){
			return 1;
		}
		else{
			
			return rechercher(tr->fils,mot+1);
		}
	}
	else{
		if(mot[0] < tr->value){
			return rechercher(tr->freregauche, mot);
		}
		else{
			return rechercher(tr->freredroit, mot);
		}
	}
	
}

/*-----------------------------------------------------------------------*/

/*Fonction qui insere un mot dans un arbre*/
int insertion(Tree **tr, char mot[]){
	if(*tr == NULL){
		*tr = alloueNoeud(*mot);
		
	}
	if (*mot == (*tr)->value){
		if(*mot == '\0')
			return 1;

		else{
			return insertion(&((*tr)->fils), mot+1);
		}
	}
	else if((*tr)->value < *mot)
		return insertion(&((*tr)->freredroit),mot);

	else
		return insertion(&((*tr)->freregauche),mot);
}

/*-----------------------------------------------------------------------*/

/*les fonctions suivantes affichent l'abre*/

void afficher(Tree *lexique, char *mot, int i){
	if (lexique->value == '\0'){ 
		printf("%s\n", mot);
    }
    if (lexique->freregauche != NULL){
        afficher(lexique->freregauche, mot, i);
    }
    if (lexique->fils != NULL){
        mot[i] = lexique->value; 
        mot[i+1] = '\0';
        afficher(lexique->fils, mot, i+1);
    }
    if (lexique->freredroit != NULL){
        afficher(lexique->freredroit, mot, i);
    }
}
void affiche_arbre(Tree *lexique){
    char * mot = malloc(sizeof(char)*512);
    int i = 0;
    afficher(lexique, mot, i);
 
}

/*-----------------------------------------------------------------------*/

/*Fonction qui permette la sauvegarde de l'arbre dans l'ordre alphabétique*/

void sauvegarde(FILE* fichier, Tree *lexique, char *mot, int i){
    if (lexique->value == '\0'){ 
        strcat(mot, "\n");
        fputs(mot, fichier);
    }
    if (lexique->freregauche != NULL){
        sauvegarde(fichier, lexique->freregauche, mot, i);
    }
    if (lexique->fils != NULL){
        mot[i] = lexique->value; 
        mot[i+1] = '\0';
        sauvegarde(fichier, lexique->fils, mot, i+1);
    }
    if (lexique->freredroit != NULL){
        sauvegarde(fichier, lexique->freredroit, mot, i);
    }
}

void save(Tree *lexique, FILE* fichier ){
    char * mot = malloc(sizeof(char)*512);
    int i = 0;
    sauvegarde(fichier, lexique, mot, i);
 
}


/*-----------------------------------------------------------------------*/

/*fonction qui sauvegarde l'arbre sous forme (.DIC) */
void save_tree_in_file(Tree *lexique, FILE* fichier){
    if (lexique == NULL){
       fputc(' ', fichier);
       return ;
    }
    if (lexique->value != '\0'){
        fputc(lexique->value, fichier);
        save_tree_in_file(lexique->freregauche, fichier);
        save_tree_in_file(lexique->fils, fichier);
    }
    else{
        fputc('\n', fichier);
        
    }
    save_tree_in_file(lexique->freredroit, fichier);

}


/*-----------------------------------------------------------------------*/



*/
int main(int argc, char const *argv[])
{
	Tree *arbre;
	arbre = NULL;
	FILE *file = NULL;
	
	/*FILE *out=fopen(argv[3], "w+");
	FILE *fichier=fopen(argv[4], "w+");*/
	file = fopen(argv[2], "r");
	if(file == NULL) {
    	printf("Error opening file");
  	}
  	else{
  		char *mot = (char *) malloc( 60 );
		while(fscanf(file, "%s", mot) > 0){
			insertion(&arbre, mot);
		}
	}
	
	if(argv[1][1] == 'l'){

	affiche_arbre(arbre);	

	}

	if(argv[1][1] == 's'){
	FILE *out=fopen(argv[3], "w+");	
	save(arbre , out);
	fclose(out);		
	}

	if(argv[1][1] == 'r'){
		if (rechercher(arbre, argv[3]) == 1)
		{
			printf("Le mot est présent dans le fichier\n");
		}
		else{
			printf("Le mot n'est pas présent dans le fichier\n");
		}
	}
	if(argv[1][1] == 'S'){
		FILE *fichier=fopen(argv[3], "w+");
		save_tree_in_file(arbre, fichier);
		fclose(fichier);

	}


	
	
	fclose(file);

	
	
	return 0;
}
