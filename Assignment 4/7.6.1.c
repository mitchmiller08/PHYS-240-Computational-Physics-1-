#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749

//Mitchell Miller
//Assignment 4
//PHYS 240 3/19/10

double function(double x){
	//Specify your desired function
	return(cos(x));
}

//Calculate the central difference second order differential

//	    f(x + h) + f(x - h) + 2f(x)
// f''(x) = ----------------------------
//		      h * h

double centralDiff(double xValue, double stepSize){
	double differentiatedValue;

	differentiatedValue = (function(xValue+stepSize)+function(xValue-stepSize)-2*function(xValue)) / (stepSize*stepSize);
	return(differentiatedValue);

}

int main(){
	//Initialize variables
	double loops;
	double cenSolution;
	double cenError;
	double xValue;
	FILE *outfile;
	outfile=fopen("7.6.1.error.txt","w");
	fprintf(outfile,"X Value\th\teps\n");

	//Calculate values
	for(xValue=0;xValue<=8*PI;xValue=xValue+PI/10){

		for(loops=PI/10;loops>=5e-16;loops=loops*0.75){
			cenSolution = centralDiff(xValue,loops);

			//Calculate error
			cenError = fabs((-cos(xValue)-cenSolution) / -cos(xValue));
		
			//Print results
			printf("h = %e\t", loops);
			printf("x = %lf\t", xValue);
			printf("Central Error = %e\n", cenError);
			fprintf(outfile,"%.20lf\t%.20lf\t%.20lf\n",xValue,loops,cenError);
		}

	}

	fclose(outfile);

}
