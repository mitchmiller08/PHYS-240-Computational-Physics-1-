#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Mitchell Miller
//Assignment 5
//PHYS 240 4/2/10

int main(){

	//Intialize variables
	double lambda = 0.1;
	double decay;
	int time, numberOfAtoms=1000, counter, dummyVariable=1000;
	FILE *outfile;
	outfile = fopen("5.5.3.txt","w");
	srand48(68111);			//Set seed value
	fprintf(outfile,"0\t1\t%.20lf\t%.20lf\n",log(1000),log(1));

	for(time=1;time<=500;time++){

		//Decay loop
		for(counter=1;counter<=numberOfAtoms;counter++){

			//Set random decay value
			decay = drand48();
			if(decay<lambda) dummyVariable--;	//Decreases number of particles

		}

		numberOfAtoms = dummyVariable;
		fprintf(outfile, "%d\t%.20lf\t%.20lf\t%.20lf\t%.20lf\n",time, (double)numberOfAtoms/1000,log((double)numberOfAtoms),log((double)numberOfAtoms/1000),decay);

	}

	fclose(outfile);

}