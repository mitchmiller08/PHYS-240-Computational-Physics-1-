#include <stdio.h>
#include <math.h>

//Exerciese 2.3.1
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
	const double pi=3.141592654;
	double value=0;
	double term=1;
	double sum=1;
	double eps=1E-8;
	int loopCount=1;
	int numberOfLoops=12;
	int n=2;
	double x=0;
	double relativeError=0;
	int m=0;
	int numberOfPi=5;

	//Begin summing
	printf("x,\t imax,\t sum,\t |sum-sin(x)|/sin(x) \n");
	for(m=0; m<numberOfPi; m++){
    if(m==0){
        x=0;
    }
    else{
         x=0.261799167;
    }
    	for(loopCount=1; loopCount<=numberOfLoops; loopCount++){
    	term = x;
    	sum = x;
    	n=2;
    		do{
    			term = pow(-1,n-1)*pow(x,2*n-1)/factorial(2*n-1);		            //Calculate next term
    			sum = sum + term;					                                //Add to total
    			n = n + 1;
    		} while(abs(term/sum)>eps);
   		sum = sum * pow(-1,m);
    	relativeError = abs(sum - sin(x+m*pi)) / sin(x+m*pi);				        //Calculate relative error
    	printf("%.5g,\t %.3i,\t %.6g,\t %e \n", x+m*pi, n, sum, relativeError);	    //Display results
    	x = x + 0.261799167;							                            //change to 0.261799167 to increase by 1/12 pi, 3.141592654 to increase by pi
    	}
    }
	printf("Press any key to exit");
    getchar();
	return 0;
}
