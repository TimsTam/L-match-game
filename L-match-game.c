#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//--------------------------------------------------------
// Get the sum of a word, if (H=5, E=3, Y=2) then HEY=532
//--------------------------------------------------------
int getWordSum(char *word, char letters[100], int digits[100]){
    int sum=0, i=0, j=0, num=0;
    for(i=0; i < strlen(word); i++){
        for(j=0; j < strlen(letters); j++){
            if(word[i] == letters[j]){
                num = digits[j];
            }
        }
        sum += (pow(10, (strlen(word) - (i+1)))) * num;
    }
    return sum;
}

void assignDigits(char letters[100], int digits[100], char notAllowed[100]){
    int i=0, pos=0, exists=0;
    for (i=0; i < strlen(letters); i++){
        int ranNo = (rand() % 10);
        exists = 0;
        if (ranNo == 0) {
            for (int e=0; e < strlen(notAllowed); e++) {
                if (letters[pos] == notAllowed[e]) {
                    exists = 1;
                    i++;
                }
            }
            exists = 1;
        }
        for(int a=0; a < pos; a++){
            if (ranNo == digits[a]){
                exists = 1;
            }
        }
        if (exists == 0) {
            digits[pos] = ranNo;
            pos++;
        }else{
            i--;
        }
    }
}

int main (){
    char wordsum[100] = "send more money";
    char *wordList[100];
    char notAllowed[100];
    char letters[100];
    int digits[100] = {};
    int pos=0, index=0, wordNum=0, sum=0, sumLHS=1, sumRHS=0, repeatedLetter=0;

    
    FILE *inputFile = NULL;

    inputFile = fopen("dictionary.txt", "r");

    char theWord;
    fscanf(inputFile, "%s", theWord);
    if (inputFile == NULL){
        printf("Unable to open file.");
    }


//--------------------------------------------------------
// Separate each word in wordsum and add words to an array
//--------------------------------------------------------
    char *token = strtok(wordsum, " ");
    while (token != NULL){
        wordList[pos] = token;
        notAllowed[pos] = token[0];
        wordNum++;
        for (int a=0; a < strlen(token); a++){
            repeatedLetter = 0;
            for(int i=0; i < index; i++){ // Create a unique array of letters that are in wordsum
                if (token[a] == letters[i]){
                    repeatedLetter = 1;
                }
            }
            if (repeatedLetter == 0){
                letters[index] = token[a];
                index++;
            }
        }
        pos++;
        token = strtok(NULL, " ");
    }

    fclose(inputFile);

    while (sumLHS != sumRHS) {
        sumLHS = 0;
        sumRHS = 0;
        assignDigits(letters, digits, notAllowed);
        for (int i=0; i < (wordNum-1); i++) {
            sum = getWordSum(wordList[i], letters, digits);
            sumLHS += sum;
        }
        sumRHS = getWordSum(wordList[wordNum-1], letters, digits);
        printf("\n%i = %i", sumLHS, sumRHS);
    }

//-----------------------------------------------------
// Print out letters with digits
//-----------------------------------------------------
    printf("Problem: %s", wordList[0]);
    for (int w=1; w < (wordNum-1); w++){
        printf(" + %s", wordList[w]);
    }
    printf(" = %s", wordList[wordNum-1]);

    for (int a=0; a < (strlen(letters)-1); a++){
        printf("\n%c = %i", letters[a], digits[a]);
    }
}