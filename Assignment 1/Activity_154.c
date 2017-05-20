#include <stdio.h>

//Exercise 1.5.4 
//Mitchell Miller
int main() {
	//Initialize variables	
	float epsFloat=1;
	float oneFloat=1;
	double epsDouble=1;
	double oneDouble=1;
	int loopCount=1;
	int numberOfLoops=100;
	
	//Begin precision test for floating point
	for(loopCount=1; loopCount<numberOfLoops; loopCount++){
		epsFloat = epsFloat / 2;
		oneFloat = 1. + epsFloat;
		printf("%d %.15f \n", loopCount, oneFloat);
	}
	
	//Begin precision test for double
	for(loopCount=1; loopCount<numberOfLoops; loopCount++){
		epsDouble = epsDouble / 2;
		oneDouble = 1. + epsDouble;
		printf("%d %.20f \n", loopCount, oneDouble);
	}
	getchar();
	return 0;
}
