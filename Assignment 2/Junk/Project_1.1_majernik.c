#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define hbar 0.1e-9
#define m 9.109534e-31
#define e_0 1.602189e-19


main() {
	
	/****************
	 File formatting should be:
	 double,double
	 double,double
	 ...
	 
	 Where the first value is the position in angstroms and the second is the potential in eV divided by e_0 (this is reintroduced later in the code)
	****************/
	
	FILE *inputfile;
	inputfile = fopen("Input_1.1.txt", "r");
	int numLines=100;					//Number of lines to read from input
	double position[numLines];			//Position array for potential function. z
	double potential[numLines];			//Potential. V(z)
	char contents[100];					//Arbitrary length character array to store each line of file
	int line=0;							//Which line in the file is being read
	
	
	while(fgets(contents, sizeof(contents), inputfile) != NULL){
		//strtok tokenizes the string based on the comma delimiter and returns one of the tokens
		//atof converts the string into a double
		position[line] = atof(strtok(contents, ","));	//Stuff before comma
		potential[line] = atof(strtok(NULL, ","));		//Stuff after comma
		printf("z_i = %f, V(z)_i = %f\n", position[line], potential[line]);
		line++;
	}
	
	//Now we're done reading the file and are left with two arrays
	//Much of this code comes directly from pg23
	double energy;
	double dEnergy=1e-3*e_0;
	//This is an important difference from the pg23 code. 
	//Instead of defining the change in position per step, this is now based on the information from the file
	double dPosition=position[1]-position[0];
	double psi0,psi1,psi2;
	int index;
	FILE *outputfile;
	outputfile = fopen("P1.1_out.txt", "w");
	
	for(energy=0;energy<e_0;energy=energy+dEnergy){
		psi0=0;
		psi1=1; //Initial values for odd parity
		for(index=0;index<numLines;index++) { //Going through the arrays
			psi2=(2*m*(dPosition/hbar)*(dPosition/hbar)*(e_0*potential[index]-energy)+2)*psi1-psi0;
			psi0=psi1;
			psi1=psi2;
		}
		fprintf(outputfile,"%f,%e\n",energy/(1e-3*e_0),psi2);
	}
	
	
	
}
