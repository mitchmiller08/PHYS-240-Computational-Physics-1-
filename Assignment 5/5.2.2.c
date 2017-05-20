#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Mitchell Miller
//Assignment 5
//PHYS 240 4/2/10

int linearCongruent(int constant1, int constant2, int modulus, long seed){

	//Initialize variables
	int randomCurrent, randomPrevious=seed;
	int *list;
	int counter;
	list = calloc(modulus,sizeof(int));
	list[0]=seed;
	FILE *outfile;
	outfile = fopen("5.2.2.txt","w");

	//Calculate random values
	for(counter=1;counter<=modulus;counter++){

		randomCurrent = (constant1*randomPrevious+constant2) % modulus;
		list[counter] = randomCurrent;
		//fprintf(outfile,"%d\t%d\n",randomPrevious,randomCurrent);
		randomPrevious = randomCurrent;

	}

	for(counter=1;counter<=modulus;counter++){

	printf("Random # %d = %d\n",counter,list[counter-1]);
	fprintf(outfile,"%d\t%d\n",counter,list[counter-1]);

	}

}

int main(){
	//Intialize variables
	int *list,counter;
	FILE *outfile;
	outfile = fopen("5.2.2.rand.txt","w");
	list = calloc(112233,sizeof(int));

	//Calculate random values using built in function
	for(counter=0;counter<112233;counter++){
		
		list[counter] = rand() % 112233;
		fprintf(outfile,"%d\t%d\n",counter,list[counter]);

	}

	linearCongruent(9999,11,112233,10);

}
