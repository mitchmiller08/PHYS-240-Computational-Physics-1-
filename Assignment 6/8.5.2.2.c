#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Mitchell Miller
//Assignment 6
//PHYS 240 4/16/10

double lagrangeInterpolation(int numberPoints, double *positionMatrix, double *valueMatrix, double interpolationPoint){

	int counter1,counter2;
	double product,sum=0;
	int shift = (int)interpolationPoint/25 - 1;

	for(counter1=0;counter1<numberPoints;counter1++){

		product = 1;
		for(counter2=0;counter2<numberPoints;counter2++){

			if(counter1!=counter2){

				//Calculate lambda
				product = product * ((interpolationPoint - positionMatrix[counter2+shift]) / (positionMatrix[counter1+shift] - positionMatrix[counter2+shift]));

			}
			
		}

		//Calcualte g(x)
		sum += product*valueMatrix[counter1+shift];

	}

	printf("g(x) = %lf, shift = %d\n",sum,shift);
	return sum;

}

int main(){

	int numberPoints = 3;
	int counter1;
	double positionMatrix[9] = {0.,25.,50.,75.,100.,125.,150.,175.,200.};
	double valueMatrix[9] = {10.6,16.0,45.0,83.5,52.8,19.9,10.8,8.25,4.7};
	double pointValue;
	FILE *outfile;
	outfile = fopen("8.5.2.2.txt","w");

	//Calculate interpolation at points between 25 and 200
	for(counter1=25;counter1<200;counter1+=5){
	
		pointValue = lagrangeInterpolation(numberPoints,positionMatrix,valueMatrix,(double)counter1);
		fprintf(outfile,"%d\t%lf\n",counter1,pointValue);

	}
	fclose(outfile);

}

