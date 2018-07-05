
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CHARS 50

int worker(int rows, int cols, char **buffer, char *word, int len, int round);

int debug=0;
int readFromFile = 0;

int main(){

	FILE *fp;
	char buffer[MAX_CHARS][50] = {};			// Assumption
	char word[MAX_CHARS];									// Assumption
	int mode = 0, i=0, j=0, w1=0,rows = 0, cols=0,wordCount = 0,len=0;

	if(debug) printf(">>Enter Puzzle:\n");

	if(readFromFile==1){
		fp = fopen("test06.inp", "r");
	}

	while(mode!=2){
		if(readFromFile==1){
			fscanf(fp, "%c", &buffer[i][j]);
		}else{
			scanf("%c", &buffer[i][j]);
		}

    buffer[i][j] = toupper(buffer[i][j]);

		if(buffer[i][j]=='\n'){
			if((buffer[i][0]=='\n')){
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
					cols = (len>cols) ? len : cols;
				}
				if(mode==1) wordCount++;					// mode1 = words
			}
			i++;j=0;

		}else{
			j++;
		}
	}

	if(debug) printf("puzzle=%d word=%d cols=%d\n\n", rows, wordCount, cols);

	/***********************************************************************************/
	char **p, **w;
	int *wLen;

	int wordCounter = 0;
	int wordMap[MAX_CHARS] = {0};
	int myWordMap[MAX_CHARS] = {0};

	p = (char **)malloc(rows*sizeof(char *));
	for(i=0;i<rows;i++){
		 *(p+i) = (char *)malloc(cols*sizeof(char));
	}

	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			p[i][j] = buffer[i][j];
		}
	}

	w = (char **)malloc(wordCount*sizeof(char *));
	wLen = (int *)malloc(wordCount*sizeof(int));

	for(i=0;i<wordCount;i++){
		 *(w+i) = (char *)malloc((strlen(buffer[rows + 1 + i]) + 1)*sizeof(char));
	}

	// Adding words to an array according to increasing length
	int index=0;
	for(int j=0;j<MAX_CHARS;j++){
		for(i=0;i<wordCount;i++){
			if(strlen(buffer[rows + 1 + i])==j){
				strcpy(w[index],buffer[rows + 1 + i]);
				wordMap[j]++;
				wLen[index] = j;
				index++;
			}
		}
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

				while (j<rows && p[j][i] == '#'){
					wordCounter++;
					j++;
				}
				myWordMap[wordCounter]++;
			}
		}
	}

	// Count individual #
	for(i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int ok=0;

			if(p[i][j]=='#'){
				if (j>0 && p[i][j-1]!='#') ok++; 		// <
				if (j<cols-1 && p[i][j+1]!='#') ok++; 	// >
				if (i>0 && p[i-1][j]!='#') ok++; 		// ^
				if (i<rows-1 && p[i+1][j]!='#') ok++; 	// V

				if(ok==4){
					myWordMap[1]++;
					if(debug) printf(">> %d %d\n", i, j);
				}
			}

		}
	}

	for(int i=0;i<MAX_CHARS;i++){
		//if (debug) printf(" %d - %d %d\n", i, wordMap[i], myWordMap[i]);

		if(wordMap[i]>1){
			// impossible according to hackerrank
			/*for(i=0;i<rows;i++){
				printf("%s\n", buffer[i]);
			}
			return 0;*/

		}else if (wordMap[i] > myWordMap[i] && i>1){
			printf("IMPOSSIBLE\n");
			return 0;
		}
	}

	/***********************************************************************************/

	for(w1=wordCount-1;w1>=0;w1--){
		int len  = wLen[w1];
		char word[MAX_CHARS];

		strcpy(word, w[w1]);
		if (debug) printf("\n%s (%d)> \n", word, len);

		if(wordMap[len]>1){

		}else{
			// Fill undoubt words in first round
			worker(rows, cols, p, word, len, 0);
		}

	}

	// second round filling
	for(w1=wordCount-1;w1>=0;w1--){
		int len  = wLen[w1];
		char word[MAX_CHARS];

		strcpy(word, w[w1]);
		if (debug) printf("\n%s (%d)> \n", word, len);

		if(wordMap[len]>1){
				//printf(">>%s\n", word);
				worker(rows, cols, p, word, len, 1);
		}
	}

	if(debug) printf("\n");

	//printf("\n\n\nPuzzle:\n");
	for(i=0;i<rows;i++){
		printf("%s\n", p[i]);
	}

	return 0;
}

int worker(int rows, int cols, char **buffer, char *word, int len, int round){

	int i,j,used=0, linkedLetters=0;

	for(i=0;i<rows;i++){							// <-- each row

		if(used)break;

		for(int j=0;j<=cols;j++){				// <-- each col
			if ((buffer[i][j] == '#' || buffer[i][j]== word[0]) && len>1){

				if (debug) printf("  %d %d right >> ", i, j);

				// try to fit it on horizontal axis
				int j2=j,possible=1;

				if(j+len>cols) possible=0;					// impossible if not enough cols

				while (j2<(len+j) && possible==1){	// try to increase and check word can be fit or not

					if (buffer[i][j2] == word[j2-j]){
						linkedLetters++;		// Find is there any linked leters
						//printf(">> %d %d (%d)\n", i, j, linkedLetters);
					}

					if(!(buffer[i][j2] == '#' || buffer[i][j2] == word[j2-j])){
						possible = 0;
						break;														// Stop further checking
					}
					if(debug) printf(" (%c)", buffer[i][j2]);
					j2++;
				}

				// round=0 > fill it. round==1 > fill only if exist a linked letter
				if (possible==1 && ((j+len)>=cols || (buffer[i][j+len] == '*' || buffer[i][j+len] == 0)) && (j==0 || buffer[i][j-1]!='#') && (round==0 || (round==1 && linkedLetters>0))){
					if(debug) printf(" Possible >\n");

					for (int j2=0;j2<len;j2++){
						buffer[i][j + j2] = word[j2];
					}
					used = 1;
					break;
				}

				if (debug) printf("\n  %d %d down  >> ", i, j);

				// Try to fix it on verticle axis
				int i2=i; possible = 1;linkedLetters=0;

				if(i+len>rows) possible=0;						// impossible if not enough rows
				if(used==1) possible = 0; 						// Because already used

				while (i2<(len+i) && possible==1){		// try to increase and check work can be fit or not

					if (buffer[i][j2] == word[j2-j]) {
						linkedLetters++;		// Find is there any linked leters
						//printf(">> %d %d (%d)\n", i, j, linkedLetters);
					}

					if(!(buffer[i2][j] == '#' || buffer[i2][j] == word[i2-i])){
						possible = 0;
						break;														// Stop further checking
					}
					if(debug) printf(" (%c)", buffer[i2][j]);
					i2++;
				}

				// round=0 > fill it. round==1 > fill only if exist a linked letter
				if (possible==1 && ( (i+len >= rows) || (buffer[i+len][j] == '*' || buffer[i+len][j] == 0)) && (i==0 || buffer[i-1][j]!='#') && (round==0 || (round==1 && linkedLetters>0))){
					if(debug) printf(" Possible v\n");

					for (int i2=0;i2<len;i2++){
						buffer[i + i2][j] = word[i2];
					}
					used = 1;
					break;
				}
				if(debug) printf("\n");

			} else if (buffer[i][j]=='#' && len==1){
				// Single character word

				int ok=0;
				if (j>0 && buffer[i][j-1]=='*') ok++; 		// <
				if (j<cols-1 && buffer[i][j+1]=='*') ok++; 	// >
				if (i>0 && buffer[i-1][j]=='*') ok++; 		// ^
				if (i<rows-1 && buffer[i+1][j]=='*') ok++; 	// V

				if(ok==4){
					if (debug) printf("  >> %d %d\n\n", i, j);
					buffer[i][j] = word[0];
				}


			}
		}
	}

	return 0;
}
