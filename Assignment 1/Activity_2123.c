#include <stdio.h>
#include <math.h>

//Exerciese 2.1.2 #3
//Mitchell Miller
int main() {
    //Initialize variables
    float loopCount=1;
    float sUp=0;
    float sDown=0;
    float numberOfLoops=1;
    float N=1;
    int totalLoopCount=0;
    int totalNumberOfLoops=10000000;
    float Error=1;
    FILE *file;
    
    file = fopen("2123.txt", "w");                                                  //Open file for data plotting
    
    for(numberOfLoops=1; numberOfLoops<=totalNumberOfLoops; numberOfLoops+=1000){
        sUp=0;
        sDown=0;
        
        //Begin summing
        for(N=1; N<=(numberOfLoops); N++){                                          //Upward counting sum
             sUp = sUp + (1 / N);
        }
        for(N=numberOfLoops; N>0; N--){                                             //Downward counting sum
            sDown = sDown + (1 / N);
        }
        Error = ((sUp-sDown) / (sUp+sDown));
        printf("%.15e, %.15lf \n", Error, numberOfLoops);
        fprintf(file, "{%lf,%e},", numberOfLoops, Error);                           //Write data to txt file
    }
    fclose(file);                                                                   //Close file
    printf("Press Enter to exit");
    getchar();
} 
