
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CHARS 10

int debug=0;
int readFromFile = 0;


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
	char buffer[20][20] = {};			// Assumption
	char word[100];							// Assumption
	int mode = 0, i=0, j=0, w1=0;
	int rows = 0, cols=0;
	int wordCount = 0, wordsSuccess=0;
	int len=0;

	if(debug) printf(">>Enter Puzzle:\n");

	if(readFromFile){
		fp = fopen("test01.inp", "r");
	}

	while(mode!=2){

		if(readFromFile){
			fscanf(fp, "%c", &buffer[i][j]);
		}else{
			scanf("%c", &buffer[i][j]);
		}

      buffer[i][j] = toupper(buffer[i][j]);
        
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
	/*for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
				if( !(buffer[i][j]=='*' || buffer[i][j]=='#')){
				buffer[i][j]='*';
			}
		}
	}*/
	
	/***********************************************************************************/

	char **p, **w;
	int totalChars = 0,wordCounter = 0;
	int wordMap[MAX_CHARS] = {0};
	int myWordMap[MAX_CHARS] = {0};

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
		wordMap[strlen(w[i])]++;
	}

	/***********************************************************************************/

	// Go horizontaly
	for(i=0;i<rows;i++){
		for(int j=0;j<cols-1;j++){

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

	/*for(i=0;i<MAX_CHARS;i++){
		if(debug) printf(">> %d %d\n", wordMap[i], myWordMap[i]);

		if(wordMap[i]!=myWordMap[i]){
			//return 0;
		}
	}*/

	//printf("Word Map\n");
	for(int i=0;i<MAX_CHARS;i++){
		//printf(" %d %d %d\n", i, wordMap[i], myWordMap[i]);

		if(wordMap[i]>1){
			// impossible according to hackerrank,,REM:
			for(i=0;i<rows;i++){
				printf("%s\n", buffer[i]);
			}	
			return 0;

		}else if (wordMap[i] != myWordMap[i]){
			printf("IMPOSSIBLE\n");
			return 0;
		}
	}

	/***********************************************************************************/




	// Try to fix words horizontly
	for(w1=0;w1<wordCount;w1++){							//<-- words
        int used=0;
		strcpy(word, buffer[rows + 1 + w1]);
		len = strlen(word);
		//printf("word=%s length=%d\n", word, len);

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

					if(len==wordCounter && used == 0){
						// Can fit into matrix
						wordsSuccess++;
                        used = 1;

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

	//printf("\n\n\nPuzzle:\n");
	for(i=0;i<rows;i++){
		printf("%s\n", buffer[i]);
	}	


	//printPuzzle(p, rows, cols);


	return 0;
}

