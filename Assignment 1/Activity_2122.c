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
    float n=1;
    float test=0;
    float error=0;
    float logError=0;
    float logN=0;
    int totalLoopCount=1;
    int totalNumberOfLoops=1000000;
    FILE *file;
    
    file = fopen("2122.txt", "w");                                              //Opens txt file to output data for plotting
    
    for(totalLoopCount=1; totalLoopCount<=totalNumberOfLoops; totalLoopCount+=1000){//Increase number of terms in sum by 1
        //Reset variables to begin new loop
        s1 = 0;                                                                 
        s2 = 0;
        s2Positive = 0;
        s2Negative = 0;
        s3 = 0;
        
        //Calculate S(1)
        for(n=1; n<=(2*totalLoopCount); n++){
             s1 += pow(-1, n)*(n/(n+1)); ;
        }
        
        //Calculate S(2)
        n=1;
        loopCount = 1;
        for(n=1; n<=totalLoopCount; n++){
             s2Negative = (2*n-1)/(2*n) + s2Negative;
             s2Positive = (2*n)/(2*n+1) + s2Positive;
        }
        s2 = s2Positive - s2Negative;
        
        //Calculate S(3)
        n=1;
        loopCount = 1;
        for(n=1; n<=totalLoopCount; n++){
             
             s3 += 1/((2*n)*(2*n+1));
             //n = n+1;
        }
        
        //Calculate and display output
        error = fabs(s1-s3)/s3;
        logError = log10f(error);
        logN = log10f(totalLoopCount);
        printf("%f, %f, %f, %d \n", s1, s2, s3, totalLoopCount);
        fprintf(file, "{%lf,%lf}, ", logN, logError);                           //Writes data to txt file
    }
    fclose(file);                                                               //Closes file
    printf("Press Enter to Exit");

    getchar();
}
