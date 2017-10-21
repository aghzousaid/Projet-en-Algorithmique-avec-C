#include "dico.h"


Dictionary createDictionary(){
	return NULL;
}

Dictionary addWord(Dictionary dictionary, Word word){
	en_minus(word);
	Dictionary node = NULL;

	if (emptyDictionary(dictionary)) {
		// add letters left
		dictionary = makeLetters(word);
	} else if (dictionary->car == word[0]) {
		#ifdef DEBUG
		printf("Lettre déjà existante: %c\n", word[0]);
		#endif
		// add the next letters
		dictionary->leftChild = addWord(dictionary->leftChild, word+1);
	} else if (dictionary->car < word[0]) {
		// find the next caracters
		dictionary->rightBrother = addWord(dictionary->rightBrother, word);
	} else {
		// create and add letters
		node = makeLetters(word);
		node->rightBrother = dictionary;
		dictionary = node;
	}

	return dictionary;
}

Dictionary deleteWord(Dictionary dictionary, Word word){
	if(!insideDictionary(dictionary, word)){
		return dictionary;
	}
	en_minus(word);
	Dictionary node = NULL;

	if (emptyDictionary(dictionary)) {
		// no delete needed
		dictionary = NULL;
	} else if (dictionary->car == word[0]) {
		// delete subword
		dictionary->leftChild = deleteWord(dictionary->leftChild, word+1);
		// if no subword
		if (dictionary->leftChild == NULL) {
			// delete character
			node = dictionary;
			dictionary = dictionary->rightBrother;
			free(node);
		}
	} else if (dictionary->car < word[0]) {
		// find subword
		dictionary->rightBrother = deleteWord(dictionary->rightBrother, word);
	} else {
		// Do nothing, word is not in dictionary
	}
	return dictionary;
}

Boolean insideDictionary(Dictionary dictionary, Word word){
	en_minus(word);
	if (emptyDictionary(dictionary)) {
		// if end of word found
		return word[0] == '\0';
	} else if (dictionary->car == word[0]) {
		// if subword found
		return insideDictionary(dictionary->leftChild, word+1);
	} else if (dictionary->car < word[0]) {
		// if subword found
		return insideDictionary(dictionary->rightBrother, word);
	} else {
		return 0;
	}
}

Dictionary freeDictionary(Dictionary dico){
	if(!emptyDictionary(dico)){
		freeDictionary(dico->leftChild);
		freeDictionary(dico->rightBrother);
		free(dico);
	}
	return NULL;
}

Boolean emptyDictionary(Dictionary dictionary){
	return dictionary == NULL;
}

Dictionary makeLetters(Word word){
	Dictionary node = malloc(sizeof(struct node));
	if (word[0] == '\0') {
		// add end of string character
		#ifdef DEBUG
		printf("Fin du mot ajouté \n");
		#endif
		node->car = '\0';
		node->leftChild = NULL;
		node->rightBrother = NULL;
	} else {
		// add character
		#ifdef DEBUG
		printf("Lettre ajouté : %c\n", word[0]);
		#endif
		node->car = word[0];
		node->leftChild = makeLetters(word+1);
		node->rightBrother = NULL;
	}

	return node;
}

char* displayDictionary(Dictionary dictionary){
	Word word = malloc(WORD_LENGTH_MAX * sizeof(char));
	char* display = malloc(WORD_MAX * WORD_LENGTH_MAX * sizeof(char));
	// actual display
	displaySubDictionary(dictionary, word, 0, display);
	return display;
}

void displaySubDictionary(Dictionary dictionary, Word word, int offset, char* display){
	//printf("%s\n", word);
	if (emptyDictionary(dictionary)) {
		return;
	} else if(dictionary->car == '\0') {
		// add word to display
		word[offset] = '\0';
		display = strcat(display, word);
		display = strcat(display, "\n");
		displaySubDictionary(dictionary->rightBrother, word, offset, display);
		return;
	} else {
		// add character to word
		word[offset] = dictionary->car;
		displaySubDictionary(dictionary->leftChild, word, offset+1, display);
		displaySubDictionary(dictionary->rightBrother, word, offset, display);
		return;
	}
}

int saveDictionary(Dictionary dictionary, char* fileName){
	FILE* file = fopen(fileName, "w");

	if(file == NULL){
		return FILE_DONT_OPEN;
	}

	fputs(displayDictionary(dictionary), file);

	fclose(file);
	return 0;
}

Dictionary loadDictionary(Dictionary dictionary, char* fileName){
	FILE* file = fopen(fileName, "r");
	if(file == NULL){
		return NULL;
	}

	Word word = malloc(WORD_LENGTH_MAX * sizeof(char));
	memset(word, '\0', WORD_LENGTH_MAX);
	int position = 0;

	char c = fgetc(file);

	// add each word
	while(!feof(file)){
		if(c == '\n'){
			// add word
			dictionary = addWord(dictionary, word);
			memset(word, '\0', position);
			position = 0;
		} else{

			word[position] = c;
			position++;
		}
		c = fgetc(file);
	}

	// add last word
	dictionary = addWord(dictionary, word);

	fclose(file);

	return dictionary;
}

int numberOfWords(Dictionary dictionary){
	if (emptyDictionary(dictionary)) {
		// no words
		return 0;
	} else if (dictionary->car == '\0') {
		// sum of word and brothers
		return 1 + numberOfWords(dictionary->rightBrother);
	} else {
		// sum of childs and brothers
		return numberOfWords(dictionary->leftChild) + numberOfWords(dictionary->rightBrother);
	}
}

void en_minus(Word string){
	int i;
	for(i = 0; i < strlen(string); i++){
		string[i] = tolower(string[i]);
	}
}
