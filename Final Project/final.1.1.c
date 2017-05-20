#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//*********************************\\
//Mitchell Miller		   \\
//PHYS 240 			   \\
//Final Project 3/30/10		   \\
//2 Dimensional Molecular Dynamics \\	**Currently 1 Dimensional Version as of 4/25/10**
//*********************************\\

//Declare global constants
#define nAtoms 8
#define nMax 513
#define drand48 1.0/RAND_MAX*rand
#define srand48 srand

double forces(int time, double potentialEnergy,double *x, double *forceX){

	//Intialize Variables
	int counter1,counter2,length,nDimensions=1;
	double deltaForce, radiusSquared, inverseRadiusSquared=0, radiusSquaredCutoff=9, dx;
	length = floor(pow(1.0*nAtoms, 1.0/nDimensions));
	double sign(double a, double b);

	//Intialize Forces
	potentialEnergy = 0.0;
	for(counter1=0;counter1<nAtoms;counter1++){

		*(forceX+counter1+nAtoms*time)=0;

	}

	//Calculate Forces
	for(counter1=0;counter1<nAtoms;counter1++){
		
		for(counter2=counter1+1; counter2<nAtoms; counter2++){

			dx = *(x+counter1) - *(x+counter2);


			if(fabs(dx) > 0.5*length){
		
				dx = dx - sign(length,dx);

			}

			radiusSquared = pow(dx,2);

			//Check for cutoff distance
			if(radiusSquared < radiusSquaredCutoff){

				if(radiusSquared == 0.0)	radiusSquared = 0.0001;
				inverseRadiusSquared = 1.0 / radiusSquared;
				deltaForce = (48.0 * (pow(inverseRadiusSquared,3) - 0.5) * pow(inverseRadiusSquared,3)) * inverseRadiusSquared * dx;
				*(forceX+counter1+time*nAtoms) = *(forceX+counter1+time*nAtoms) + deltaForce;
				*(forceX+counter2+time*nAtoms) = *(forceX+counter2+time*nAtoms) - deltaForce;
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
	double *positionX, *forceXMain, velocityX[nAtoms];
	double timeStep=0.004, stepOver2=(timeStep/2.0), potentialEnergy=0, kineticEnergy=0, temp, initialTemp=10;
	int counter=0, xCounter, time1=0, time2=1, dummyTime, timeMain=0, numberOfSteps=10000, stepsBetweenPrint=100, nDimensions=1, length;
	length = floor(pow(1.0*nAtoms, 1.0/nDimensions));
	srand48(123456);
	FILE *outfile;
	outfile = fopen("final.1.1.txt","w");

	positionX = calloc(nAtoms,sizeof(double));
	forceXMain = calloc(nAtoms*2,sizeof(double));
	
	printf("nAtoms = %d\tLength = %d\n", nAtoms, length);

	
	for(xCounter=0; xCounter<length; xCounter++){

		//Set initial positions
		*(positionX+counter) = xCounter;
		printf("Intial X_%d = %f\n", counter, *(positionX+counter));

		//Set initial velocities with temperature scaling
		velocityX[counter] =((drand48()+drand48()+drand48()+
                   drand48()+drand48()+drand48()+
                   drand48()+drand48()+drand48()+
                   drand48()+drand48()+drand48())/(12.0))-0.5;
		velocityX[counter] = velocityX[counter]*sqrt(initialTemp);
		//velocityX[counter] = (((rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()) / (12 * RAND_MAX)) - 0.5) * sqrt(initialTemp);
		printf("Initial X Velocity %d = %f\n", counter, velocityX[counter]);

		counter++;

	}

	//Calculate inital Potential Energy
	potentialEnergy = forces(time1, potentialEnergy, positionX, forceXMain);
	for(counter=0; counter<nAtoms; counter++){

		kineticEnergy += (velocityX[counter]*velocityX[counter]) * 0.5;

	}
	
	printf("Time: %d\tPE = %f\tKE = %f\tTE = %f\n", timeMain, potentialEnergy,kineticEnergy, potentialEnergy+kineticEnergy);

	//Main Loop
	for(timeMain=1;timeMain<numberOfSteps;timeMain++){

		for(counter=0;counter<nAtoms;counter++){

			potentialEnergy = forces(time1, potentialEnergy, positionX, forceXMain);
			//printf("PE = %lf\n",potentialEnergy);
			//printf("X = %lf\n",*(positionX+counter));
			*(positionX+counter) = *(positionX+counter) + timeStep * (velocityX[counter] + stepOver2*(*(forceXMain+counter+time1*nAtoms)));
			//printf("Next X = %lf\n",*(positionX+counter));
			if (*(positionX+counter) <= 0.)	*(positionX+counter) = *(positionX+counter) + length;
      			if (*(positionX+counter) >= length)	*(positionX+counter) = *(positionX+counter) - length;
	
		}

		potentialEnergy = forces(time2, potentialEnergy, positionX, forceXMain);
		kineticEnergy = 0;
		
		for(counter=0;counter<nAtoms;counter++){

			velocityX[counter] = velocityX[counter] + stepOver2 * ((*(forceXMain+counter+time1*nAtoms))+(*(forceXMain+counter+time2*nAtoms)));
			//printf("Velocity_%d = %lf\n",counter,velocityX[counter]);
			kineticEnergy = kineticEnergy + (velocityX[counter]*velocityX[counter]/2);

		}

		temp = 2*kineticEnergy / (3*nAtoms);
	
		if(timeMain<100)	printf("Time: %d\tPE = %lf\tKE = %lf\tPE+KE = %lf\n",timeMain,potentialEnergy,kineticEnergy,potentialEnergy+kineticEnergy);
		
		if(timeMain%stepsBetweenPrint == 0)	printf("Time: %d\tPE = %lf\tKE = %lf\tPE+KE = %lf\n",timeMain,potentialEnergy,kineticEnergy,potentialEnergy+kineticEnergy);

		dummyTime = time1;
		time1 = time2;
		time2 = dummyTime;


	}
	for(counter=0;counter<nAtoms;counter++) printf("Final X_%d = %lf\n",counter,*(positionX+counter));
	
	free(positionX);
	free(forceXMain);
	fclose(outfile);
    getchar();	
	
}
