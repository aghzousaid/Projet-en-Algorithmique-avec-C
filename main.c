#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dico.h"
#include "main.h"

int main (int argc, char** argv) {
	
	char *string;
	int a;
	Dictionnaire dic = creerDic();

	do{
		afficher_menu();
		a = ChoixEntrer();
		switch(a){
			case 1:
				printf("Entrez le mot à ajouter: ");
				string = getString();
				if(appartientDic(dic, string)){
					printf("Le mot est déjà dans le dictionnaire\n");
				}
				else{
					dic = ajouterMot(dic, string);
					printf("Mot ajouté : %s\n", string);
				}
				break;
			case 2:
				printf("Entrez le mot à supprimer: ");
				string = getString();
				if(!appartientDic(dic, string)){
					printf("Le mot n'est pas dans le dictionnaire\n");
				}
				else{
					dic = supprimerMot(dic, string);
					printf("Mot supprimé\n");
				}
				break;
			case 3:
				printf("%s", afficherDic(dic));
				break;
			case 4:
				printf("Entrez le mot à tester: ");
				string = getString();
				if(appartientDic(dic, string)){
					printf("Le mot est bien dans le dictionnaire\n");
				}
				else{
					printf("Le mot n'est pas dans le dictionnaire\n");
				}
				break;
			case 5:
				dic =viderDic(dic);
				printf("Dictionnaire vidé\n");
				break;
			case 6:
				printf("Dans quel fichier? ");
				string = getString();
				enregistrerDic(dic, string);
				printf("Dictionnaire sauvé dans le fichier %s\n", string);
				break;
			case 7:
				printf("Quel fichier? ");
				string = getString();
				dic = chargerDic(dic, string);
				printf("Dictionnaire chargé depuis le fichier %s\n", string);
				break;
			case 8:
				break;
			default:
				printf("Commande non connue\n");
		}

		if (8 != a) {
			a = -1;
		}

	}while(a != 8);
}


void afficher_menu(){
	printf("1) Ajouter un mot\n");
	printf("2) Supprimer un mot\n");
	printf("3) Afficher le contenu du dictionnaire\n");
	printf("4) Tester si un mot appartient au dictionnaire\n");
	printf("5) Vider le dictionnaire\n");
	printf("6) Sauvegarder le contenu du dictionnaire dans un fichier\n");
	printf("7) Charger un dictionnaire à partir d'un fichier\n");
	printf("8) Quitter\n");
}

void clean(const char *buffer, FILE *fp)
{
	char *p = strchr(buffer,'\n');
	if (p != NULL) {
		*p = 0;
	} else {
		int c;
		while ((c = fgetc(fp)) != '\n' && c != EOF);
	}
}

int ChoixEntrer(){
	return getInt(2);
}

int getInt(int size){
	char* string = calloc(size+1, sizeof(char));
	fgets(string, size+1, stdin);
	clean(string, stdin);
	return strtoul(string, NULL, 10);
}

char* getString(){
	char* string = calloc(100, sizeof(char));
	fgets(string, 100, stdin);
	clean(string, stdin);
	return string;
}
