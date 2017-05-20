#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//*********************************\\
//Mitchell Miller		   \\
//PHYS 240 			   \\
//Final Project 3/30/10		   \\
//2 Dimensional Molecular Dynamics \\
//*********************************\\	

//Declare global constants
#define nAtoms 500
#define nMax 513
#define Pi 3.1415926535897932384626433832795028841971693993751058209749
#define argonRadius 1.1225
#define nDimensions 2
#define drand48 1.0/RAND_MAX*rand
#define srand48 srand

//Forces function for calculating forces and 
//potential energy with Lennard-Jones Potential

//
//	       [  1       1  ]
//  U(r) = 4 * | ---  -  --- |
//	       [ r^12    r^6 ]
//

double forces(int time, double length, double potentialEnergy, double x[nAtoms], double forceX[nAtoms][2], double y[nAtoms], double forceY[nAtoms][2]){

	//Intialize Variables
	int counter1,counter2;
	double deltaForceX, deltaForceY, radiusSquared, inverseRadiusSquared=0, radiusSquaredCutoff=20, radius, dx, dy;

	double sign(double a, double b);

	//Intialize Potential Energy and Forces
	potentialEnergy = 0.0;
	for(counter1=0;counter1<nAtoms;counter1++){

		forceX[counter1][time]=0;
		forceY[counter1][time]=0;

	}

	//Calculate Forces
	for(counter1=0;counter1<nAtoms;counter1++){
		
		for(counter2=counter1+1; counter2<nAtoms; counter2++){

			dx = x[counter2] - x[counter1];
			dy = y[counter2] - y[counter1];

			//Minimum image condition
            if(fabs(dx) > 0.5*length){
		
				dx = dx - sign(length,dx);

			}

			if(fabs(dy) > 0.5*length){
		
				dy = dy - sign(length,dy);

			}


			radiusSquared = dx*dx + dy*dy;
			radius = sqrt(radiusSquared);

			//Check for cutoff distance
			if(radiusSquared < radiusSquaredCutoff){

				//Check for overlapping atoms
                if(radiusSquared == 0.0){

					dx = dx * argonRadius * cos(drand48());
					dy = dy * argonRadius * cos(drand48());
					radiusSquared = argonRadius;

				}
				else{

					dx = dx * sqrt(argonRadius/radiusSquared);         
					dy = dy * sqrt(argonRadius/radiusSquared);         
					radiusSquared = argonRadius;

				}

				inverseRadiusSquared = 1.0 / radiusSquared;

				//Calculate change in force based on Lennard - Jones Potential derivative
                deltaForceX = 48.0 * (pow(inverseRadiusSquared,3) - 0.5) * pow(inverseRadiusSquared,3) * dx;
				deltaForceY = 48.0 * (pow(inverseRadiusSquared,3) - 0.5) * pow(inverseRadiusSquared,3) * dy;

				forceX[counter1][time] = forceX[counter1][time] + deltaForceX;
				forceX[counter2][time] = forceX[counter2][time] - deltaForceX;
				forceY[counter1][time] = forceY[counter1][time] + deltaForceY;
				forceY[counter2][time] = forceY[counter2][time] - deltaForceY;

				//Lennard - Jones Potential
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
	double positionX[nAtoms], forceXMain[nAtoms][2], velocityX[nAtoms];
	double positionY[nAtoms], forceYMain[nAtoms][2], velocityY[nAtoms];
	double velocityTotal[nAtoms];
	double timeStep=0.004, stepOver2=(timeStep/2.0), potentialEnergy=0, kineticEnergy=0, temp, initialTemp=15, length;
	int counter=0, xCounter, yCounter, time1=0, time2=1, dummy, timeMain=0, numberOfSteps=100000, stepsBetweenPrint=100, stop=0;

	if(floor(pow(1.0*nAtoms, 1.0/nDimensions)) == pow(1.0*nAtoms, 1.0/nDimensions))	length = 2*pow(1.0*nAtoms, 1.0/nDimensions);
	else	length = 2*floor(pow(1.0*nAtoms, 1.0/nDimensions))+1;

	srand48(123456);

	FILE *outfile1;
	FILE *outfile2;
	outfile1 = fopen("final.2.2.txt","w");
	outfile2 = fopen("final.2.2.path.txt","w");

	
	printf("nAtoms = %d\tLength = %lf\n", nAtoms, length);

	
	for(xCounter=0; xCounter<length; xCounter+=2){
		
		for(yCounter=0; yCounter<length; yCounter+=2){

			//Set initial positions
			positionX[counter] = xCounter;
			positionY[counter] = yCounter;
			
			printf("Intial X_%d = %f, Inital Y_%d = %f\n", counter, positionX[counter], counter, positionY[counter]);

			//Set initial velocities with temperature scaling
			velocityX[counter] =((drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48())/(12.0))-0.5;
			velocityX[counter] = velocityX[counter]*sqrt(initialTemp);
			printf("Initial X Velocity %d = %f\n", counter, velocityX[counter]);

			velocityY[counter] =((drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48())/(12.0))-0.5;
			velocityY[counter] = velocityY[counter]*sqrt(initialTemp);
			printf("Initial Y Velocity %d = %f\n", counter, velocityY[counter]);
			
			velocityTotal[counter] = sqrt(velocityX[counter]*velocityX[counter]+velocityY[counter]*velocityY[counter]);

			fprintf(outfile1, "%lf\t%lf\n", positionX[counter],positionY[counter]);

			counter++;
			if(counter>=nAtoms-1){
				stop = 1;
				break;
			}
	
		}

		if(stop==1)	break;
	}
	
	fprintf(outfile1,"\n\n\n");

	//Calculate inital Potential and Kinetic Energy
	potentialEnergy = forces(time1, length, potentialEnergy, positionX, forceXMain, positionY, forceYMain);

	for(counter=0; counter<nAtoms; counter++){

		velocityTotal[counter] = sqrt(velocityX[counter]*velocityX[counter]+velocityY[counter]*velocityY[counter]);
		kineticEnergy += (velocityTotal[counter]*velocityTotal[counter]) * 0.5;

	}
	
	printf("Time:   0\tPE = %f\tKE = %f\tTE = %f\n", potentialEnergy, kineticEnergy, potentialEnergy+kineticEnergy);
	fprintf(outfile1, "%d\t%lf\t%lf\t%lf\t%lf\n", timeMain, initialTemp, kineticEnergy, potentialEnergy, kineticEnergy+potentialEnergy);
	fprintf(outfile2, "%lf\t%lf\n", positionX[250], positionY[250]);

	//Main Loop
	for(timeMain=1;timeMain<numberOfSteps;timeMain++){

		//Check for collisions
		/*for(xCounter=0;xCounter<nAtoms;xCounter++){

			for(yCounter=xCounter+1;yCounter<nAtoms;yCounter++){

				if(*(positionX+xCounter)==*(positionX+yCounter) && *(positionY+xCounter)==*(positionY+yCounter)){

					dummy = velocityX[xCounter];
					velocityX[xCounter] = velocityX[yCounter];
					velocityX[yCounter] = dummy;

					dummy = velocityY[xCounter];
					velocityY[xCounter] = velocityY[yCounter];
					velocityY[yCounter] = dummy;

				}

			}

		}*/

		//Change position
		for(counter=0;counter<nAtoms;counter++){

			positionX[counter] = positionX[counter] + timeStep * (velocityX[counter] + stepOver2*(forceXMain[counter][time1]));
			positionY[counter] = positionY[counter] + timeStep * (velocityY[counter] + stepOver2*(forceYMain[counter][time1]));

			if (positionX[counter] <= 0.)		positionX[counter] = positionX[counter] + length;
      			if (positionX[counter] >= length)	positionX[counter] = positionX[counter] - length;
			if (positionY[counter] <= 0.)		positionY[counter] = positionY[counter] + length;
      			if (positionY[counter] >= length)	positionY[counter] = positionY[counter] - length;
	
		}


		potentialEnergy = forces(time2, length, potentialEnergy, positionX, forceXMain, positionY, forceYMain);
		kineticEnergy = 0;
		
		//Change velocity
		for(counter=0;counter<nAtoms;counter++){

			velocityX[counter] = velocityX[counter] + stepOver2 * (forceXMain[counter][time1]+forceXMain[counter][time2]);
			velocityY[counter] = velocityY[counter] + stepOver2 * (forceYMain[counter][time1]+forceYMain[counter][time2]);

			velocityTotal[counter] = sqrt(velocityX[counter]*velocityX[counter]+velocityY[counter]*velocityY[counter]);

			kineticEnergy += (velocityX[counter]*velocityX[counter]+velocityY[counter]*velocityY[counter]) * 0.5;

		}

		temp = 2*kineticEnergy / (3*nAtoms);
	
		//Troubleshoot print loop
		//if(timeMain<100)	printf("Time: %3.d\tPE = %lf\tKE = %lf\tPE+KE = %lf\n",timeMain,potentialEnergy,kineticEnergy,potentialEnergy+kineticEnergy);
		
		//Main print loop
		if(timeMain%stepsBetweenPrint == 0){

			printf("Time: %d\tPE = %lf\tKE = %lf\tPE+KE = %lf\n",timeMain,potentialEnergy,kineticEnergy,potentialEnergy+kineticEnergy);
			fprintf(outfile1, "%d\t%lf\t%lf\t%lf\t%lf\n",timeMain, temp, kineticEnergy, potentialEnergy, kineticEnergy+potentialEnergy);

		}

		//Trajectory print loop
		if(timeMain%10 == 0)	fprintf(outfile2, "%lf\t%lf\n", positionX[250], positionY[250]);

		dummy = time1;
		time1 = time2;
		time2 = dummy;


	}

	fprintf(outfile1, "\n\n\n");

	for(counter=0;counter<nAtoms;counter++)	fprintf(outfile1, "%lf\t%lf\n",positionX[counter],positionY[counter]);
	
	printf("Final Temp = %lf\n",temp);
	
	fclose(outfile1);
	
}
