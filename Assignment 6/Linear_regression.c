#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Mitchell Miller
//Assignment 6
//PHYS 240 4/16/10

int main(){

	//Intialize variables
	//double xMatrix[11] = {15, 25, 35, 45, 55, 65, 75, 85, 105, 115}; //T **EXPONENTIAL DECAY 8.7.2
	double xMatrix[9] = {1,2,3,4,5,6,7,8,9};    //X **HEAT FLOW 8.7.3
	//double yMatrix[11] = {3.2,-1.8,2.1,-0.7,0.8,0.6,0.5,0.2,0.3,0.5,0.1};	//dN/dt	**EXPONENTIAL DECAY 8.7.2
	//double yMatrix2[11] = {3.47,2.89,3.04,1.95,2.08,1.79,1.61,0.69,1.1,1.61,0};	//ln(dN/dt) **EXPONENTIAL DECAY 8.7.2
	double yMatrix2[9] = {14.6,18.5,36.6,30.8,59.2,60.1,62.2,79.4,99.9};	//T_i **HEAT FLOW 8.7.3
	double errorMatrix[11] = {.05,.05,.05,.05,.05,.05,.05,.05,.05,.05,.05};
	double slope, yIntercept, xAvg=0, yAvg=0, sXX=0, sXY=0;
	double varianceA,varianceB,s=0,sX=0,delta;
	//int nPoints=11;		//**EXPONENTIAL DECAY 8.7.2
	int nPoints=9;		//**HEAT FLOW 8.7.3
	int counter;

	//Calculate Averages
	for(counter=0;counter<nPoints;counter++)	xAvg += xMatrix[counter]*(1/(double)nPoints);
	for(counter=0;counter<nPoints;counter++)	yAvg += yMatrix2[counter]*(1/(double)nPoints);

	//Calculate sXX and sXY
	for(counter=0;counter<nPoints;counter++){

		sXX += pow((xMatrix[counter]-xAvg),2) / pow(errorMatrix[counter],2);
		sXY += (xMatrix[counter]-xAvg)*(yMatrix2[counter]-yAvg) / pow(errorMatrix[counter],2);

	}

	slope = sXY/sXX;
	yIntercept = yAvg - slope*xAvg;
	printf("Y = %lfx + %lf\n",slope,yIntercept);

	//Calculate variance
	for(counter=0;counter<nPoints;counter++){

		s += 1 / pow(errorMatrix[counter],2);
		sX += xMatrix[counter] / pow(errorMatrix[counter],2);

	}

	delta = s*sXX-pow(sX,2);
	varianceA = sXX / delta;
	varianceB = s / delta;
	printf("Variance A = %e, Variance B = %e\n",varianceA,varianceB);
   getchar();

}
