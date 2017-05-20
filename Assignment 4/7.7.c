#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749

//Mitchell Miller
//Assignment 4
//PHYS 240 3/19/10

double function(double x){
	//Specify your desired function
	return(sqrt(10-x)*tan(sqrt(10-x))-sqrt(x));
}

//Bisection method
double bisectionMethod(double xMin,double xMax){
	//Initialize variables
	double xMid=0,eps=1e-14;
	int counter;

	//Calculate zero
	for(counter=0;counter<100;counter++){

		//Find midpoint of segment
		xMid = (xMax + xMin) / 2.;
		printf("%d\t%.20lf\t%.20lf\n",counter,xMid,function(xMid)); 
      		
		//Check sign of result
		if ( function(xMax)*function(xMid) > 0. )
			xMax = xMid;
      		else xMin = xMid;
      
		//Test for convergence
		if ( fabs(function(xMid)) < eps){
        		printf("Root = %.20lf\n",xMid);
        		break;
		}

	}

}

//Newton-Raphson Algorithm using central difference approximation with backtracking
double newtonMethod(double xGuess){
	//Initialize variables
	double derivative,stepSize=1e-2,eps=1e-14,functionAtX=function(xGuess),addedElement=stepSize;
	int counter,flag=0;

	//Calculate zero
	for(counter=0;counter<=100;counter++){

		flag=0;
		printf("%d\t%.20lf\t%.20lf\n",counter,xGuess,functionAtX);
		//Find central difference approximation
		derivative = (function(xGuess+stepSize/2)-function(xGuess-stepSize))/stepSize;
		//Change step size
		stepSize = -functionAtX/derivative;
		addedElement = stepSize;
		//Test for divergence and change guess
		while(flag==0){
			if(pow(fabs(function(xGuess+addedElement)),2)>pow(fabs(function(xGuess)),2)){
				addedElement = addedElement/2;
				printf("FAIL,%e\n",addedElement);}
			else{ 
				xGuess+=addedElement;
				flag=1;
			}
		}		

		functionAtX=function(xGuess);
		flag=0;
		addedElement = stepSize;

		//Test for convergence
		if ( fabs(functionAtX)<eps){
			printf("Root = %.20lf\n",xGuess);
			break;
		}

	}

}		

double main(){
	//bisectionMethod(8,9);
	newtonMethod(8.59278527522983814890);
}
