#include <stdio.h>
#include <math.h>

//Exerciese 1.6
//Mitchell Miller
int main() {
	//Intitialize variables
	double value=0;
	double term=1;
	double sum=1;
	double eps=1E-8;                                                             //Set to either 1E-8 or 1E-15
	int loopCount=1;
	int numberOfLoops=240;
	int n=2;
	double x=0;
	double relativeError=0;

	//Begin summing
	printf("x,\t imax,\t sum,\t |sum-sin(x)|/sin(x) \n");
	for(loopCount=1; loopCount<numberOfLoops; loopCount++){
	term = x;
	sum = x;
	n=2;
		do{
			term = (-term*x*x)/((2*n-1)*(2*n-2));			                     //Calculate next term
			sum = sum + term;					                                 //Add to total
			n = n + 1;
		} while(abs(term/sum)>eps);
	relativeError = abs(sum - sin(x)) / sin(x);				                     //Calculate relative error
	printf("%.5g,\t %.3i,\t %.12g,\t %.9e \n", x, n, sum, relativeError);	     //Display results
	x = x + 0.261799167;                                                         //0.261799167 to increase by 1/12 pi, 3.141592654 to increase by pi
	}
	printf("Press any key to exit");
    getchar();
	return 0;
}
