#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Boolean int
#define Mot char*

typedef struct noeud{
  char car;
  struct noeud *PFG, *PFD;
}* Dictionnaire;


void clean(const char*, FILE*);
char* ChaineSaisie();
int ChoixEntrer(int);

Boolean videDic(Dictionnaire);
Dictionnaire ajouterMot(Dictionnaire, Mot);
Boolean appartientDic(Dictionnaire, Mot);
Dictionnaire supprimerMot(Dictionnaire, Mot);
void afficherDic(Dictionnaire);
/* int enregistrerDic(Dictionnaire , char*);*/
//Dictionnaire chargerDic(Dictionnaire, char*);
Dictionnaire creerDic();
Dictionnaire viderDic(Dictionnaire);
Dictionnaire CheminMot(Mot mot);






char *tab[1000];
int i=0;
/*void initial(){
for(i=0;i<strlen(tab);i++){
	tab[i]='';
}
}*/

//creation d'un dictionnaire
Dictionnaire creerDic(){
	return NULL;
}

//creation d'un noeud
Dictionnaire creerNoeud(){
	return NULL;
}

//l'ajout d'un mot dans le dictionnaire
Dictionnaire ajouterMot(Dictionnaire dic, Mot mot){

	//initialisation de noeud a null
	Dictionnaire noeud = creerNoeud();

	if (videDic(dic)) {
		//le dictionnaire pointe sur le premier lettre du mot qui sont premier 
		//fils gauche après le reste des lettres seront ajoutées successivements de la même manière
		dic = CheminMot(mot);

	} else {
		if (dic->car == mot[0]) {
			// ajouter le caractere suivant dans le PFG 
			dic->PFG = ajouterMot(dic->PFG, mot+1);

		} else {
				if(dic->car >mot[0]){
					// si le caractère à inserer est inferieur au caractère de dic on cree un noeud après il sera le PFG de dic
					noeud = CheminMot(mot);
					noeud->PFD = dic;
					dic = noeud;
	
				} else  {
					// ajouter le caractere dans le PFD de dic
					dic->PFD = ajouterMot(dic->PFD, mot);
				}
			}
		}


	return dic;
}

//Suppression s'effectue apartient de le dernier caractère de mot saisie 
//après sa supprime jusqu'au premier caractère
Dictionnaire supprimerMot(Dictionnaire dic, Mot mot){


	Dictionnaire noeud = creerNoeud();

	if (videDic(dic)) {
		return dic;

	} else {
		if(appartientDic(dic,mot)){
			if (dic->car == mot[0]) {
	
				dic->PFG = supprimerMot(dic->PFG, mot+1);
				//suppression du caractère dont le PFG est null 
				if (dic->PFG == NULL) {
					noeud = dic;
					dic = dic->PFD;
					free(noeud);
				} 
		
			}else {
				if (dic->car < mot[0]) {
				dic->PFD = supprimerMot(dic->PFD, mot);
				}
			}
				
		}
	}
	return dic;
}


//tester si un mot appartient au dictionnaire
Boolean appartientDic(Dictionnaire dic, Mot mot){

	Boolean resultat;
	if (videDic(dic)) {
		
		return strlen(mot)==0;

	} else {
		//tester si le caractère de mot égale au premier carac de mot
		if (dic->car == mot[0]) {
			//comparer le caratere suivant de mot avec le caractere de PFG de car
			resultat = appartientDic(dic->PFG, mot+1);
		} else  {
			if (dic->car < mot[0]) {
				//comparer le caractere suivant de mot avec le caractere de PFD de dic
				resultat = appartientDic(dic->PFD, mot);

			} else {
				resultat=0;
			}
		}
	}
	
	return resultat;
}

//Vider un dictionnaire
Dictionnaire viderDic(Dictionnaire dic){
	if(!videDic(dic)){
		viderDic(dic->PFG);
		viderDic(dic->PFD);
		free(dic);
	}
		
	return NULL;
}

//tester si le dictionnaire est vide
Boolean videDic(Dictionnaire dictionnaire){
	return dictionnaire == NULL;
}

//construction des lettres
Dictionnaire CheminMot(Mot mot){

	Dictionnaire noeud = malloc(sizeof(struct noeud));
	if (mot[0]!= '\0') {
		noeud->car = mot[0];
		noeud->PFG = CheminMot(mot+1);
		noeud->PFD = NULL;
	} else {
		noeud->car = '\0';
		noeud->PFG = NULL;
		noeud->PFD = NULL;

	}

	return noeud;
}

void afficherDic(Dictionnaire dic){

	//initial();
	if (videDic(dic)) {

	} else if(dic->car == '\0') {
	
		printf("\n");
		//strcpy(tab[i],'\n');
		//i=i+1;
		afficherDic(dic->PFD);
		
	} else {
		printf("%c",dic->car);
		//strcpy(tab[i],dic->car);
		//i=i+1;
		afficherDic(dic->PFG);
		afficherDic(dic->PFD);
		
		}
	//return tab;

}




/*Alors cette fonction prend en paramètre la chaîne que vous avez récupérée avec fgets() et le flux qui est comme précédemment stdin. Cette fonction ne retourne rien.

D'abord, on cherche le caractère \n dans la chaîne à l'aide de la fonction strchr() (donc il faudra penser à inclure string.h). Si on trouve le \n, on le supprime de la chaîne et si on ne le trouve pas on vide le buffer avec une boucle while. Cette boucle ne s'arrête pas tant qu'elle lit un caractère différent de et que celui ci n'est pas le caractère de fin de flux ("Ctrl" + "Z" sur Windows ou "Ctrl" + "D" sur GNU/Linux).*/
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


//pour determiner le choix entrer par l'utilisateur
int ChoixEntrer(int size){
	char* string = calloc(size+1, sizeof(char));//Allocation mémoire d'un tableau de taille (size+1) ou string est un pointeur sur ce tableau

	//string:un pointeur vers un tableau alloué en mémoire où la fonction va pouvoir écrire le texte entré par l'utilisateur.
	//size+1:la taille du tableau string envoyé en premier paramètre.
	//si vous avez alloué un tableau de 10 char, fgets lira 9 caractères au maximum (il réserve toujours un caractère d'espace pour pouvoir écrire le \0 de fin de chaîne).
	//stdin:lire l'entrée standard par le clavier
	//fgets est equivalente scanf

	fgets(string, size+1, stdin); 

	clean(string, stdin);
	return strtoul(string, NULL, 10);
}

char* ChaineSaisie(){
	char* string = calloc(100, sizeof(char));
	fgets(string, 100, stdin);
	clean(string, stdin);
	return string;
}


int main (int argc, char* argv) {
	
	char *string;
	int choixEntrer=0;


	Dictionnaire dic = creerDic();

	while(choixEntrer!=8){
		printf("Attention!!! les caractères saisie doivent etre tous au même format, soit en minuscule, soit en majuscule\n");
		printf("1) Ajouter un mot\n");
		printf("2) Supprimer un mot\n");
		printf("3) Afficher le contenu du dictionnaire\n");
		printf("4) Tester si un mot appartient au dictionnaire\n");
		printf("5) Vider le dictionnaire\n");
		printf("6) Sauvegarder le contenu du dictionnaire dans un fichier\n");
		printf("7) Charger un dictionnaire à partir d'un fichier\n");
		printf("8) Quitter\n");

		choixEntrer = ChoixEntrer(2);
		switch(choixEntrer){
		
			case 1:
				printf("Saisir le mot à inserer dans le dictionnaire: ");
				string = ChaineSaisie();
				if(appartientDic(dic, string)){
					printf("Ce mot est déjà disponible dans le dictionnaire\n");
				}
				else{
					dic = ajouterMot(dic, string);
					printf("Le Mot %s a été ajouté avec succès dans le dictionnaire \n", string);
				}
				break;
			case 2:
				printf("Saisir le mot à supprimer dans le dictionnaire: ");
				string = ChaineSaisie();
				if(!appartientDic(dic, string)){
					printf("Le mot n'existe pas dans le dictionnaire\n");
				}
				else{
					dic = supprimerMot(dic, string);
					printf("Ce Mot a été supprimé avec succès:\n");
				}
				break;
			case 3:
				afficherDic(dic);
				break;
			case 4:
				printf("Saisir le mot à savoir s'il existe ou pas dans le dictionnaire: ");
				string = ChaineSaisie();
				if(appartientDic(dic, string)){
					printf("Le mot appartient au dictionnaire\n");
				}
				else{
					printf("Le mot n'appartient pas au dictionnaire\n");
				}
				break;
			case 5:
				dic =viderDic(dic);
				printf("le contenu du dictionnaire est totalement supprimé avec succès\n");
				break;
			case 6:
				printf("Entrer le nom du fichier a utiliser pour enregistrer le contenu du dictionnaire? ");
				string = ChaineSaisie();
				//enregistrerDic(dic, string);
				printf("le/les mot(s) du dictionnaire sont sauvegardé dans le fichier %s\n", string);
				break;
			case 7:
				printf("Saisir le nom du fichier pour charger le contenu du dictionnaire? ");
				string = ChaineSaisie();
				//dic = chargerDic(dic, string);
				printf(" le contenu du dictionnaire a été chargé depuis le fichier %s\n", string);
				break;
			case 8:
				break;
	
			default:
				printf("la commande saisie est incorrect, veuillez entrer la bonne commande parmis les choix ci desssous\n");
		}

		if ( choixEntrer!=8) {
			choixEntrer=0;
		}

	}
}




