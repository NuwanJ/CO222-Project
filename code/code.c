
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//int isAllFilled(**puzzle, int p, int k);

void printPuzzle(char **p, int rows, int cols){
	int i,j;

	printf("\n\n");
	for(i=0;i<rows;i++){
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
	int mode = 0, i=0, j=0, w=0;
	int rows = 0, cols;
	int wordCount = 0, wordsSuccess=0;
	int len=0;

	int readFromFile = 1;

	printf("Enter Puzzle:\n");

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
				if(mode==1)printf(">> Enter words:\n");

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
	
	printf("puzzle=%d word=%d cols=%d\n\n", rows, wordCount, cols);

	//format puzzle for best view
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
				if( !(buffer[i][j]=='*' || buffer[i][j]=='#')){
				buffer[i][j]='*';
			}
		}
	}
	
	// print puzzle
	printf("Puzzle:\n");
	for(i=0;i<rows;i++){
		printf("%s\n", buffer[i]);
	}	

	/***********************************************************************************/

	char **p;

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

	printPuzzle(p,rows,cols);






	/*
	// print words
	printf("\nWords:\n");
	for(i=0;i<wordCount;i++){
		printf("%s\n", buffer[rows + 1 + i]);
	}
	*/

	/*
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


