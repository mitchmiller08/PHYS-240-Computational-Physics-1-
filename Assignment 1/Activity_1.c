#include <stdio.h>

//Exercise 1.5.2 #2
//Mitchell Miller
int main() {
	//Setting variables
	float underFloat=1;
	float overFloat=1;
	double underDouble=2.072262e-317;
	double overDouble=5.357543e+300;
	int underInt=-2147483500;
	int overInt=2147483500;
	int loopCount=1;
	int numberOfLoops=200;
	int numberOfLoopsDouble=30;
	int numberOfLoopsInt=160;

	//Test for underflow and overflow limits on float
	printf("Testing underflow and overflow limits for a floating point number \n");
	printf("Count, Under, Over \n");
	for(loopCount=1; loopCount<numberOfLoops; loopCount++){
		overFloat = overFloat*2;
		underFloat = underFloat/2;
		printf("%d %e %e \n", loopCount, underFloat, overFloat);
	}	
	
	//Test for under and overflow limits on double
	printf("Testing underflow and overflow limits for a double \n");
	printf("Count, Under, Over \n");
	//Reset values
	loopCount=1;
	for(loopCount=1; loopCount<numberOfLoopsDouble; loopCount++){
		overDouble = overDouble*2;		
		underDouble = underDouble/2;
		printf("%d %e %e \n", loopCount, underDouble, overDouble);
	}

	//Test for under and overflow limits on integer
	printf("Testing underflow and overflow limits for a floating point number \n");
	printf("Count, Smallest, Largest \n");
	//Reset count
	loopCount=1;
	for(loopCount=1; loopCount<numberOfLoopsInt; loopCount++){
		overInt = overInt + 1;		
		underInt = underInt - 1;
		printf("%d %i %i \n", loopCount, underInt, overInt);
	}
	getchar();
	return 0;
}
