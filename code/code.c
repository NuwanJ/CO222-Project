
#include <stdio.h>
#include <string.h>


int main(){

	char buffer[100][100] = {};
	int mode = 0, i=0, j=0;
	int puzCount = 0;
	int wordlCount = 0;


	while(mode!=2){

		scanf("%c", &buffer[i][j]);

		if(buffer[i][j]==10){	// Newline
			if((buffer[i][0]==10)){
				mode++;
				printf(">> mode=%d\n", mode);
			}
			i++;j=0;

		}else{
			j++;
		}
	}
	

	return 0;
}
