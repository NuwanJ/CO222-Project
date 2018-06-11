
#include <stdio.h>
#include <string.h>


int main(){

	char buffer[100][100] = {};
	int mode = 0, i=0, j=0;
	int puzCount = 0, maxPuzzle;
	int wordCount = 0;
	int len=0;

	printf("Enter Puzzle:\n");


	while(mode!=2){
		scanf("%c", &buffer[i][j]);

		if(buffer[i][j]==10){	// Newline
			
			if((buffer[i][0]==10)){
				// Empty line		
				mode++;
				if(mode==1)printf(">> Enter words:\n");

			}else{
				// Not an empty line
				buffer[i][j] = '\0';

				if(mode==0) {
					puzCount++;
					len = strlen(buffer[i])-1;
					maxPuzzle = (len>maxPuzzle) ? len : maxPuzzle ;
				}
				if(mode==1) wordCount++;
			}
			i++;j=0;

		}else{
			j++;
		}
	}
	
	printf("puzzle=%d word=%d maxPuzzle=%d\n\n", puzCount, wordCount, maxPuzzle);
		
	// print puzzle
	printf("Puzzle:\n");
	for(i=0;i<puzCount;i++){
		printf("%s\n", buffer[i]);
	}


	// print words
	printf("\nWords:\n");
	for(i=0;i<wordCount;i++){
		printf("%s\n", buffer[puzCount + 1 + i]);
	}

	//complete 
	

	return 0;
}
