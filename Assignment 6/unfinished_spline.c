#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Mitchell Miller
//Assignment 6
//PHYS 240 4/16/10

int main(){

	//Intialize variables
	double timeMatrix[12] = {5,15,25,35,45,55,65,75,85,95,105,115};		/****FILL DATA POINTS****/
	double valueMatrix[12] = {32,18,21,7,8,6,5,3,4,0,5,1};
	double valueMatrix2[12];
	double dummyMatrix[12],dummyVariable,dummyVariable2;
	double timeOut,valueOut;
	double yPrimeFirst,yPrimeLast;
	double difference,aCoefficient,bCoefficient;
	double p,qn,sig,un;	//*****TEMP NAMES*****//
	int nPointsToFit=2000;
	int nPoints=12;
	int counter,midpoint;
	int lowLimit=0,highLimit=nPoints;
	FILE *outfile
	outfile = fopen("8.7.2.txt","w");

	//Print input data to file
	fprintf(outfile,"****INPUT DATA****\n");
	for(counter=0;counter<nPoints;counter++)	fprintf("%lf\t%lf\n",timeMatrix[counter],valueMatrix[counter]);

	//Calculate first derivative at endpoints
	yPrimeFirst = (valueMatrix[1]-valueMatrix[0])/(timeMatrix[1]-timeMatrix[0]) - (valueMatrix[2]-valueMatrix[1])/(timeMatrix[2]-timeMatrix[1]) + (valueMatrix[2]-valueMatrix[0])/(timeMatrix[2]-timeMatrix[0]);
	yPrimeLast = (valueMatrix[nPoints-1]-valueMatrix[nPoints-2])/(timeMatrix[nPoints-1]-timeMatrix[nPoints-2]) - (valueMatrix[nPoints-2]-valueMatrix[nPoints-3])/(timeMatrix[nPoints-2]-timeMatrix[nPoints-3]) + (valueMatrix[nPoints-1]-valueMatrix[nPoints-3])/(timeMatrix[nPoints-1]-timeMatrix[nPoints-3]);

	//Perform natural spline test @ first point
	if(yPrimeFirst > 0.99e30)	valueMatrix2[0] = dummyMatrix[0] = 0;
	else{

		valueMatrix2[0] = -0.5;
		dummyMatrix[0] = (3 / (timeMatrix[1]-timeMatrix[0])) * ((valueMatrix[1]-valueMatrix[0])/(timeMatrix[1]-timeMatrix[0])-yPrimeFirst);

	}

	//Decomposition loop	****FIX VARIABLE NAMES****
	for(counter=1,counter<n-1;counter++){
		
		sig = (timeMatrix[counter] - timeMatrix[counter-1]) / (timeMatrix[counter+1] - timeMatrix[counter-1]);
		p = sig * valueMatrix2[counter-1] + 2;
		valueMatrix2[counter] = (sig - 1) / p;
		dummyMatrix[counter] = ((valueMatrix[counter+1]-valueMatrix[counter]) / (timeMatrix[counter+1]-timeMatrix[counter])) - ((valueMatrix[counter]-valueMatrix[counter-1]) / (timeMatrix[counter]-timeMatrix[counter-1]));
		dummyMatrix[counter] = (6*dummyMatrix[counter] / (timeMatrix[counter+1]-timeMatrix[counter-1])) - sig*dummyMatrix[counter-1]/p;
		
	}

	//Perform natural spline test @ last point	****FIX VARIABLE NAMES****
	if(yPrimeLast > 0.99e30)	valueMatrix2[0] = dummyMatrix[0] = 0;
	else{

		qn = 0.5;
		un = (3/(timeMatrix[nPoints-1]-timeMatrix[nPoints-2])) * (yPrimeLast-(valueMatrix[nPoints-1]-valueMatrix[nPoints-2])/(timeMatrix[nPoints-1]-timeMatrix[nPoints-2]));

	}

	valueMatrix2[nPoints-1] = (un-qn*dummyMatrix[nPoints-2]) / (qn*valueMatrix2[nPoints-2]+1);
	for(counter=nPoints-2;counter>=0;counter--)	valueMatrix2[counter] = valueMatrix2[counter]*valueMatrix[counter+1]+dummyMatrix[counter];

	//Begin spline
	for(counter=0;counter<nPointsToFit;counter++){

		timeOut = timeMatrix[0] + (timeMatrix[nPoints-1]-timeMatrix[0])*counter/nPointsToFit;
		lowLimit=0;
		highLimit=nPoints;
		while(highLimit-lowLimit>1){

			dummyVariable2 = 
		
	
	
	
	fclose(outfile);	
}
