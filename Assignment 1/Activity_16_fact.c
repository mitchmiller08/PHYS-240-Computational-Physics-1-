#include <stdio.h>
#include <math.h>

//Exerciese 1.6 (factorial method)
//Mitchell Miller

//Define factorial() as a function
int factorial(int N){
	double total=1.;
	int count=1;
	for(count=N; count>0; --count){
       total = total * count;
    }
    return total;
}

int main() {
	//Intitialize variables
	double value=0;
	double term=1;
	double sum=1;
	double eps=1E-8;
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
			term = pow(-1,n-1)*pow(x,2*n-1)/factorial(2*n-1);		                //Calculate next term
			sum = sum + term;					                                //Add to total
			n = n + 1;
		} while(abs(term/sum)>eps);
	relativeError = abs(sum - sin(x)) / sin(x);				                    //Calculate relative error
	printf("%.5g,\t %.3i,\t %.6g,\t %e \n", x, n, sum, relativeError);	        //Display results
	x = x + 0.261799167;							                            //change to 0.261799167 to increase by 1/12 pi, 3.141592654 to increase by pi
	}
	printf("Press Enter to Exit");
    getchar();
	return 0;
}
