
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARS 10

int debug=1;
int readFromFile = 0;


int isWordsEqualsSpaces(char **p, int rows, int cols, int totalChars, int *wordMap){
	int i=0, j=0;
	int totalCounter = 0, wordCounter = 0;
	int myWordMap[MAX_CHARS] = {0};

	// Go horizontaly
	for(i=0;i<rows;i++){							// <-- each lines
		for(int j=0;j<cols-1;j++){		// <-- each character

			if(p[i][j]=='#' && p[i][j+1]=='#'){
				// now found a #, lets look right for how many # points
				wordCounter = 0;

				while (p[i][j] == '#'){
					wordCounter++;
					j++;
				}

				myWordMap[wordCounter]++;
			}
		}
	}

	// Go vertically
	for(i=0;i<cols;i++){					
		for(int j=0;j<rows-1;j++){	

			if(p[j][i]=='#' && p[j+1][i]=='#'){
				// now found a #, lets look right for how many # points
				wordCounter = 0;

				while (p[j][i] == '#'){
					wordCounter++;
					j++;
				}

				myWordMap[wordCounter]++;
			}
		}
	}

	for(i=0;i<MAX_CHARS;i++){
		if(debug) printf(">> %d %d\n", wordMap[i], myWordMap[i]);

		if(wordMap[i]!=myWordMap[i]){
			return 0;
		}
	}
	return 1;
}

void printPuzzle(char **p, int rows, int cols){
	int i,j;

	for(i=0;i<rows;i++){
		printf(" ");
		for(j=0;j<cols;j++){
			printf("%c", p[i][j]);
		}	
		printf("\n");
	}	
	return;
}


int main(){
	FILE *fp;
	char buffer[100][100] = {};			// Assumption
	char word[100];							// Assumption
	int mode = 0, i=0, j=0;
	int rows = 0, cols;
	int wordCount = 0, wordsSuccess=0;
	int len=0;

	if(debug) printf("Enter Puzzle:\n");

	if(readFromFile){
		fp = fopen("test01.inp", "r");
	}

	while(mode!=2){

		if(readFromFile){
			fscanf(fp, "%c", &buffer[i][j]);
		}else{
			scanf("%c", &buffer[i][j]);
		}

		if(buffer[i][j]=='\n'){	// Newline
			
			if((buffer[i][0]=='\n')){
				// Empty line		
				mode++;
				if(mode==1){
					if(debug) printf(">> Enter words:\n");
				}

			}else{
				// Not an empty line
				buffer[i][j] = '\0';

				if(mode==0) {									// mode0 = puzzle
					rows++;
					len = strlen(buffer[i]);
					cols = (len>cols) ? len : cols ;
				}
				if(mode==1) wordCount++;					// mode1=words
			}
			i++;j=0;

		}else{
			j++;
		}
	}
	
	if(debug) printf("puzzle=%d word=%d cols=%d\n\n", rows, wordCount, cols);

	//format puzzle for best view
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
				if( !(buffer[i][j]=='*' || buffer[i][j]=='#')){
				buffer[i][j]='*';
			}
		}
	}
	
	/***********************************************************************************/

	char **p, **w;

	// for any number of rows & columns this will work
	p = (char **)malloc(rows*sizeof(char *));
	for(i=0;i<rows;i++){
		 *(p+i) = (char *)malloc(cols*sizeof(char));
	}

	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			p[i][j] = buffer[i][j];
		}	
	}	

	// for any number of rows & columns this will work
	w = (char **)malloc(wordCount*sizeof(char *));
	for(i=0;i<wordCount;i++){
		 *(w+i) = (char *)malloc(strlen(buffer[rows + 1 + i])*sizeof(char));
	}

	for(i=0;i<wordCount;i++){
		strcpy(w[i],buffer[rows + 1 + i]);
	}

	/***********************************************************************************/

	if(debug){

		// print puzzle
		printf("Puzzle:\n");
		printPuzzle(p,rows,cols);

		// print words
		printf("Words:\n");
		for(i=0;i<wordCount;i++){
			printf(" %s\n", w[i]);
		}

		printf("\n");

	}

	/***********************************************************************************/

	int totalChars = 0;
	int wordMap[MAX_CHARS] = {0};

	for(i=0;i<wordCount;i++){
		int len = strlen(buffer[rows + 1 + i]);
		wordMap[len]++;
		totalChars += len;
	}

	if(debug){
		printf("Word Map\n");
		for(int i=0;i<MAX_CHARS;i++){
			printf(" %d %d\n", i, wordMap[i]);
		}

		printf("\n Sum: %d\n", totalChars);
	}

	if (isWordsEqualsSpaces(p,rows,cols, totalChars, wordMap)==0){
		printf("IMPOSSIBLE\n");
	}else{
		printf("POSSIBLE\n");
	}


	/*
	// print words
	printf("\nWords:\n");
	for(i=0;i<wordCount;i++){
		printf("%s\n", buffer[rows + 1 + i]);
	}
	*/

	
	// Try to fix words horizontly
	for(w=0;w<wordCount;w++){							//<-- words

		strcpy(word, buffer[rows + 1 + w]);
		len = strlen(word);
		printf("word=%s length=%d\n", word, len);

		for(i=0;i<rows;i++){						// <-- each lines
			for(int j=0;j<=(cols-len);j++){		// <-- each character

				if(buffer[i][j]=='#'){
					// now find a *, lets look right for how many * points
					int wordCounter = 0;

					while (buffer[i][j] == '#'){
						wordCounter++;
						j++;
					}

					//printf("len=%d wordCounter=%d\n", len, wordCounter);
					j = j - wordCounter;

					if(len==wordCounter){
						// Can fit into matrix
						wordsSuccess++;


						while (buffer[i][j] == '#'){
							//printf("%c", word[len-wordCounter]);
							buffer[i][j] = word[len-wordCounter];
							j++;
							wordCounter--;
						}	
					}

					//printf("line=%s j=%d empty slots=%d\n", buffer[i], j,  wordCounter);
				}
			}
		}
	}


/*
	// print puzzle
	printf("\n\n\nPuzzle:\n");
	for(i=0;i<rows;i++){
		printf("%s\n", buffer[i]);
	}	

	if(wordsSuccess != wordsSuccess){
		printf("\nINCOMPLETE\n");
	}

	isAllFilled(&buffer, rows, cols);
*/
	return 0;
}


