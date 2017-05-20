#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 2.71828182845

//Mitchell Miller
//Assignment 4
//PHYS 240 3/19/10

double function(double x){
	//Specify your desired function
	//return(pow(e,x));
	return(cos(x));
}

//Calculate the forward difference differential

//	    f(x + h) - f(x)
// f'(x) = -----------------
//		   h

double forwardDiff(double xValue, double stepSize){
	double differentiatedValue;

	differentiatedValue = (function(xValue+stepSize) - function(xValue)) / stepSize;
	return(differentiatedValue);

}

//Calculate the central difference differential

//	    f(x + h/2) - f(x - h/2)
// f'(x) = ------------------------
//		       h

double centralDiff(double xValue, double stepSize){
	double differentiatedValue;

	differentiatedValue = (function(xValue+stepSize/2)-function(xValue-stepSize/2)) / stepSize;
	return(differentiatedValue);

}

//Calculate the extrapolated difference differential

//	    f(x + h/4) - f(x - h/4)
// f'(x) = ------------------------
//		      h/2

double extrapolatedDiff(double xValue, double stepSize){
	double differentiatedValue;

	differentiatedValue = (8*(function(xValue+stepSize/4)-function(xValue-stepSize/4)) - (function(xValue+stepSize/2)-function(xValue-stepSize/2))) / (3*stepSize);
	return(differentiatedValue);

}

int main(){
	//Initialize variables
	double loops;
	double forSolution,cenSolution,extSolution;
	double forError,cenError,extError;
	double analyticSolution = -sin(100);
	FILE *outfile;
	outfile=fopen("7.5.1.cos.error_10e1.txt","w");
	fprintf(outfile,"N\teps_F\teps_C\teps_E\n");

	//Calculate values
	for(loops=8;loops>=1e-15;loops=loops*0.75){
		forSolution = forwardDiff(100,loops);
		cenSolution = centralDiff(100,loops);
		extSolution = extrapolatedDiff(100,loops);

		//Calculate error
		forError = fabs((analyticSolution-forSolution) / analyticSolution);
		cenError = fabs((analyticSolution-cenSolution) / analyticSolution);
		extError = fabs((analyticSolution-extSolution) / analyticSolution);
		
		//Print results
		printf("h = %e\n", loops);
		printf("Forward Error = %e\n", forError);
		printf("Central Error = %e\n", cenError);
		printf("Extrapolated Error = %e\n", extError);
		fprintf(outfile,"%.20lf\t%.20lf\t%.20lf\t%.20lf\n",loops,forError,cenError,extError);
	}

	fclose(outfile);

}
