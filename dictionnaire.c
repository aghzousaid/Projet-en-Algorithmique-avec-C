

# include<stdio.h>
# include<stdlib.h>

typedef struct noeud{
	char car;
	struct noeud *PFG,*PFD;
	}*Dictionnaire;
/*
Dictionnaire Creer_Dictionnaire(void){
	dictionnaire dic;
	dic=(char*)malloc(sizeof(dic));
	dic.car="";
	dic.PFG=dic.PFD=NULL;

	return dic;
}
*/

Dictionnaire Ajouter_Mot(Dictionnaire dic , char mot[]){
	if(mot!=""){
		
		printf("%c \n", mot[0]);
		printf("%s ", mot);
	}
	return dic;
}




int main(int argc, char *argv[])
{

Dictionnaire dic1;
   /* char chaine[] = "Salut"; // La taille du tableau chaine est automatiquement calculée

		printf("%s \n", chaine);
		printf("%c \n", chaine[0]);
		printf("%c \n", chaine[1]);*/
		
		dic1=Ajouter_Mot(dic1 , "SAID");


    return 0;
}
