#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.c"
#define e 2.71828182845
#define pi 3.1415926535897932385

//Assignment 3
//Ch. 6.2.5 #1
//Mitchell Miller
//PHYS 240 2/26/10


double function(double x){
	//Specify your desired function
	return(pow(e,-x));
}

//		**TRAPEZOID METHOD**
//	|\ b	      h				  h
//	|   f(x)dx = ---f  + hf  + ... + hf    + ---f
//     \| a           2  1     2	   N-1    2  N
//

double trapezoidIntegration(int loops,double start,double end){

	//Initialize function variables	
	double sum=0,h=0,weight=0;
	int counter=0;

	h = (end-start)/(loops-1);

	//Perform trapezoid method integration sum	
	for(counter=1; counter<=loops; counter++){

		if(counter==1 || counter==loops){
			weight=h/2;
		}
		else{
			weight=h;
		}

		sum += weight*function(start+(counter-1)*h);
	}

	return(sum);
}

//			**SIMPSON METHOD**
//	|\ b	      h	      4h       2h             4h        h
//	|   f(x)dx = ---f  + ----f  + ----f  + ... + ----f   + ---f
//     \| a           3  1     3  2     3  3           3  N-1   3  N
//

double simpsonIntegration(int loops,double start,double end){
	
	//Initialize function variables	
	double sum=0,h=0,weight=0;
	int counter=0;

	h = (end-start)/(loops-1);

	//Perform simpson method integration sum	
	for(counter=1; counter<=loops; counter++){

		if(counter==1 || counter==loops){
			weight = h/3;
		}
		if(counter!=1 && counter!=loops && counter%2==0){
			weight = 4*h/3;
		}
		if(counter!=1 && counter!=loops && counter%2==1){
			weight = 2*h/3;
		}
		
		sum += weight*function(start+(counter-1)*h);
	}

	return(sum);
}

//			**GAUSSIAN QUADRATURE METHOD**
//		       N
//		      ---
//	|\ b	      \	  W * g( x )
//	|   f(x)dx =  /    i      i
//     \| a           ---
//                    i=1

double quadtratureIntegration(int loops, double start, double end){

	//Initialize variables	
	int counter=0;	
	double sum=0,*x,*weight;
	x=calloc(1100000,sizeof(double));
	weight=calloc(1100000,sizeof(double));

	//Generate points and weights with code provided
	gauss(loops,0,start,end,x,weight);
	
	//Sum integral with Gaussian Quadrature method
	for(counter=0; counter<loops; counter++){
		sum= sum + function(x[counter])*weight[counter];
	}

	return(sum);
}


int main(){
	//Initialize variables
	int loops;
	double trapSolution,simpSolution,quadSolution;
	double analyticSolution=(1-pow(e,-1));
	double trapError,simpError,quadError;
	FILE *outfile;
	outfile=fopen("625.2.error.txt","w");
	fprintf(outfile,"N\teps_T\teps_s\teps_Q\n");

	//Calculate integral for different numbers of loops
	for(loops=1;loops<5002;loops+=2){
		trapSolution = trapezoidIntegration(loops,0,1);
		simpSolution = simpsonIntegration(loops,0,1);
		quadSolution = quadtratureIntegration(loops,0,1);

		//Calculate error for given number of loops
		trapError=fabs((trapSolution-analyticSolution)/analyticSolution);
		simpError=fabs((simpSolution-analyticSolution)/analyticSolution);
		quadError=fabs((quadSolution-analyticSolution)/analyticSolution);

		//Print results
		printf("Trapezoid Method Solution: %.20lf\n",trapSolution);
		printf("Simpson Method Solution: %.20lf\n",simpSolution);
		printf("Quatrature Method Solution: %.20lf\n",quadSolution);
		printf("Analytic Solution: %.20lf\n",analyticSolution);
		printf("# of Loops = %d\n",loops);
		fprintf(outfile,"%i\t%.20lf\t%.20lf\t%.20lf\n",loops,trapError,simpError,quadError);
	}

	fclose(outfile);
}
