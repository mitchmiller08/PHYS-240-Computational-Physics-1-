#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535897932384626433832

//Mitchell Miller
//Assignment 5
//PHYS 240 4/2/10

int main(){

	//Intialize variables
	double randomCurrent,randomPrevious,area,location;
	int counter, nIn=0, nOut=0;
	srand48(213548);
	randomPrevious = (drand48() - 0.5) * 2;

	for(counter=0;counter<150000;counter++){

		//Calculate first random number
		randomCurrent = (drand48() - 0.5) * 2;
		location = randomCurrent*randomCurrent + randomPrevious*randomPrevious;
		
		//Test if point is in circle
		if(location<1)	nIn++;
		else		nOut++;
		randomPrevious = randomCurrent;

	}

	area = 4 * (double)(nIn) / ((double)nIn + (double)nOut);
	printf("Area = %lf\tnIn = %d\n", area, nIn);
	printf("Error = %lf\n", (area-PI)/PI);

}