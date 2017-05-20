#include <stdio.h>
#include <math.h>

//Exerciese 2.1.2 #2
//Mitchell Miller
int main() {
    //Initialize variables
    float s1=0;
    float s2Negative=0;
    float s2Positive=0;
    float s2=0;
    float s3=0;
    int loopCount=1;
    int numberOfLoops=1000000;
    float n=1;
    float test=0;
    float error=0;
    float logError=0;
    float logN=0;
    
    
    //Calculate S(1)
    for(loopCount=1; loopCount<=(2*numberOfLoops); loopCount++){
         s1 = s1 + (pow(-1,n)*n / (n+1));
         n = n+1;
    }
    
    //Calculate S(2)
    n=1;
    loopCount = 1;
    for(loopCount=1; loopCount<=numberOfLoops; loopCount++){
         s2Negative = (2*n-1)/(2*n) + s2Negative;
         s2Positive = (2*n)/(2*n+1) + s2Positive;
         n = n+1;
    }
    s2 = s2Positive - s2Negative;
    
    //Calculate S(3)
    n=1;
    loopCount = 1;
    for(loopCount=1; loopCount<=numberOfLoops; loopCount++){
         s3 = (1 / (2*n*(2*n+1))) + s3;
         n = n+1;
    }
    error = fabs(s1-s3)/s3;
    logError = log10f(error);
    logN = log10f(numberOfLoops);
    printf("%f, %f, %f, %f \n", s1, s2, s3, logError);
    printf("Press enter to exit \n");
    getchar();
}
