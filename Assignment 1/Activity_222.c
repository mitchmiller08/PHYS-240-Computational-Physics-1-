#include <stdio.h>
#include <math.h>

//Exerciese 2.2.2
//Mitchell Miller

//Define factorial() as a function
double factorial(int N){
	double total=1.0;
	double count=1.0;
	for(count=N; count>0; --count){
       total = total * count;
    }
    return total;
}

int main() {
    //Intialize variables
    int L=0;
    double X=0.1;
    int LloopCount=1;
    int LnumberOfLoops=26;
    int XloopCount=1;
    int XnumberOfLoops=3;
    int loopCount=1;
    int numberOfLoops=200;
    double JUp=0;
    double JDown=0;
    double N=0;
    
    printf("%lf \n", factorial(5.));
    //Begin sum
    for(LloopCount=1; LloopCount<=LnumberOfLoops; LloopCount++){                //Increase value for l from 0 to 25
        X = 0.1;
        N = 0;
        JUp = 0;
        JDown = 0;
        for(XloopCount=1; XloopCount<=XnumberOfLoops; XloopCount++){            //Increase value for x from .01 to 10
            for(loopCount=1; loopCount<=numberOfLoops; loopCount++){            //Perform sum with upward recursion
                JUp += pow(-1,N) * pow(X/2,(2*N)+L) / (factorial(N) * factorial(N+L));
                N = N + 1;
            }
            for(loopCount=1; loopCount<=numberOfLoops; loopCount++){            //Perform sum with downward recursion
                JDown += pow(-1,N) * pow(X/2,(2*N)+L) / (factorial(N) * factorial(N+L));
                N = N - 1;
            }
            printf("J_%i(%lf)_Up = %e \n", L, X, JUp);
            printf("J_%i(%lf)_Down = %e \n", L, X, JDown);
        X = X * 10;
        }
    L = L + 1;
    }
    printf("Press Enter to Exit");
    getchar();
}
//Very large error,  wrong summing method?  yes
