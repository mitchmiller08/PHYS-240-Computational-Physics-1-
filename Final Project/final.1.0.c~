#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//*********************************\\
//Mitchell Miller		   \\
//PHYS 240 			   \\
//Final Project 3/30/10		   \\
//2 Dimensional Molecular Dynamics \\	**Currently 1 Dimensional Version as of 3/30/10**
//*********************************\\

//Declare global constants
#define nAtoms 8
#define nMax 513

double forces(int time, double potentialEnergy,double x[nAtoms], double forceX[nAtoms][2]){

	//Intialize Variables
	int counter1,counter2,length,nDimensions=1;
	double functionCounter, radiusSquared, inverseRadiusSquared=0, radiusSquaredCutoff=9, dx;
	length = floor(pow(1.0*nAtoms, 1.0/nDimensions));
	double sign(double a, double b);

	//Intialize Forces
	potentialEnergy = 0.0;
	for(counter1=0;counter1<nAtoms;counter1++){

		forceX[counter1][time]=0;

	}

	//Calculate Forces
	for(counter1=0;counter1<nAtoms;counter1++){
		
		for(counter2=counter1+1; counter2<nAtoms; counter2++){

			dx = x[counter1] - x[counter2];


			if(fabs(dx) > 0.5*length){
		
				dx = dx - sign(length,dx);

			}

			radiusSquared = pow(dx,2);

			//Check for cutoff distance
			if(radiusSquared < radiusSquaredCutoff){

				if(radiusSquared == 0.0)	radiusSquared = 0.0000000001;
				inverseRadiusSquared = 1.0 / radiusSquared;
				functionCounter = (48.0 * (pow(inverseRadiusSquared,3) - 0.5) * pow(inverseRadiusSquared,3)) * inverseRadiusSquared * dx;
				forceX[counter1][time] = forceX[counter1][time] + functionCounter;
				forceX[counter2][time] = forceX[counter2][time] + functionCounter;
				potentialEnergy += 4 * pow(inverseRadiusSquared,3) * (pow(inverseRadiusSquared,3) - 1);
		
			}

		}

	}

	return potentialEnergy;

}

double sign(double a, double b){

	if(b >= 0.0)	return fabs(a);
	else	return -fabs(a);

}	

int main(){

	//Intialize variables
	double x[nAtoms], forceX[nAtoms][2], velocityX[nAtoms];
	double timeStep=0.004, stepOver2=timeStep/2.0, potentialEnergy=0, kineticEnergy=0, temp, initialTemp=10;
	int counter=0, xCounter, time1=0, time2=1, dummyTemp, time=0, numberOfSteps=10000, stepsBetweenPrint=100, nDimensions=1, length;
	length = floor(pow(1.0*nAtoms, 1.0/nDimensions));
	double forces(int time, double potentialEnergy, double x[nAtoms], double forceX[nAtoms][2]);
	
	printf("nAtoms = %d\tLength = %d\n", nAtoms, length);

	
	for(xCounter=0; xCounter<length; xCounter++){

		//Set initial positions
		x[counter] = xCounter;
		printf("Intial X_%d = %f\n", counter, x[counter]);

		//Set initial velocities with temperature scaling
		velocityX[counter] = (((rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()) / (12 * RAND_MAX)) - 0.5) * sqrt(initialTemp);
		printf("Initial X Velocity %d = %f\n", counter, velocityX[counter]);

		counter++;

	}

	//Calculate inital Potential Energy
	potentialEnergy = forces(time1, potentialEnergy, x, forceX);
	for(counter=0; counter<nAtoms; counter++){

		kineticEnergy += (velocityX[counter]*velocityX[counter]) * 0.5;

	}
	
	printf("%d\tPE = %f\tKE = %f\tTE = %f\n", time, potentialEnergy,kineticEnergy, potentialEnergy+kineticEnergy);

	
	
	
}
