#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//*********************************\\
//Mitchell Miller		   \\
//PHYS 240 			   \\
//Final Project 3/30/10		   \\
//2 Dimensional Molecular Dynamics \\	**Currently 2 Dimensional Version as of 5/3/10**
//*********************************\\	

//Declare global constants
#define nAtoms 100
#define nMax 513
#define Pi 3.1415926535897932384626433832795028841971693993751058209749
#define argonRadius 1.1225
#define drand48 1.0/RAND_MAX*rand
#define srand48 srand

double forces(int time, double potentialEnergy, double x[nAtoms], double forceX[nAtoms][2], double y[nAtoms], double forceY[nAtoms][2]){

	//Intialize Variables
	int counter1,counter2,length,nDimensions=2;
	double deltaForceX, deltaForceY, deltaForce, radiusSquared, inverseRadiusSquared=0, radiusSquaredCutoff=9, radius, dx, dy,theta;

	if(floor(pow(1.0*nAtoms, 1.0/nDimensions)) == pow(1.0*nAtoms, 1.0/nDimensions))	length = 2*pow(1.0*nAtoms, 1.0/nDimensions);
	else	length = 2*floor(pow(1.0*nAtoms, 1.0/nDimensions))+1;

	double sign(double a, double b);

	//Intialize Forces
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
			//printf("First dx = %lf, dy = %lf\n", dx,dy);


			if(fabs(dx) > 0.5*length){
		
				dx = dx - sign(length,dx);

			}

			if(fabs(dy) > 0.5*length){
		
				dy = dy - sign(length,dy);

			}

		
			/*if(dx == 0)	radius = sqrt(dy*dy);
			else if(dy == 0)	radius = sqrt(dx*dx);
			else radius = sqrt(dx*dx + dy*dy);
			if(dx == 0 && dy > 0)	theta = Pi/2;
			else if(dx == 0 && dy < 0)	theta = -Pi/2;
			else if(dx == -1 && dy ==0)	theta = Pi;
			else if(dx < 0 )	theta = atan(dy/dx) + Pi;
			else theta = atan(dy/dx);
			//printf("R = %lf, dx = %lf, dy = %lf ,%d,%d, theta = %lf\n",radius,dx,dy,counter1,counter2,theta);
			radiusSquared = pow(radius,2);
			//printf("X_%d = %lf, X_%d = %lf\n",counter1,*(x+counter1),counter2,*(x+counter2));
			//printf("dx = %lf, dy = %lf\n", dx,dy);
			//getchar();*/

			//Check for cutoff distance
			if(radiusSquared < radiusSquaredCutoff){

				radiusSquared = dx*dx + dy*dy;
				radius = sqrt(radiusSquared);

				if(radiusSquared == 0.0){

					dx = dx * radius * cos(drand48());
					dy = dy * radius * cos(drand48());
					radiusSquared = argonRadius;

				}
				else{

					dx = dx * sqrt(argonRadius/radiusSquared);         
					dy = dy * sqrt(argonRadius/radiusSquared);         
					radiusSquared = argonRadius;

				}

				inverseRadiusSquared = 1.0 / radiusSquared;

				//deltaForce = (48.0 * (pow(inverseRadiusSquared,3) - 0.5) * pow(inverseRadiusSquared,3)) * 1/radius;
				deltaForceX = 48.0 * (pow(inverseRadiusSquared,3) - 0.5) * pow(inverseRadiusSquared,4) * dx;
				deltaForceY = 48.0 * (pow(inverseRadiusSquared,3) - 0.5) * pow(inverseRadiusSquared,4) * dy;
				//printf("theta = %lf, deltaforce = %lf\n",theta,deltaForce);
				forceX[counter1][time] = forceX[counter1][time] + deltaForceX;
				forceX[counter2][time] = forceX[counter2][time] - deltaForceX;
				forceY[counter1][time] = forceY[counter1][time] + deltaForceY;
				forceY[counter2][time] = forceY[counter2][time] - deltaForceY;
				potentialEnergy += 4 * pow(inverseRadiusSquared,3) * (pow(inverseRadiusSquared,3) - 1);
				//printf("Force X_%d = %lf\tForce Y_%d = %lf\tTheta = %lf\t%d",counter1,*(forceX+counter1+time*nAtoms),counter1,*(forceY+counter1+time*nAtoms),theta,counter2);
				//printf("DForceX = %lf\tDForceY = %lf\tTheta = %lf\t%d %d",deltaForceX,deltaForceY,theta,counter1,counter2);
				//getchar();
				//printf("PE = %lf, 1 = %d, 2 = %d, R = %lf\n", potentialEnergy, counter1,counter2,radius);
		
			}

		}

		//printf("Force X_%d = %lf\tForce Y_%d = %lf\n",counter1,*(forceX+counter1+time*nAtoms),counter1,*(forceY+counter1+time*nAtoms));

	}
	//getchar();
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
	double timeStep=0.004, stepOver2=(timeStep/2.0), potentialEnergy=0, kineticEnergy=0, temp, initialTemp=100;
	int counter=0, xCounter, yCounter, time1=0, time2=1, dummy, timeMain=0, numberOfSteps=100000, stepsBetweenPrint=1000, nDimensions=2, length, stop=0;

	if(floor(pow(1.0*nAtoms, 1.0/nDimensions)) == pow(1.0*nAtoms, 1.0/nDimensions))	length = 2*pow(1.0*nAtoms, 1.0/nDimensions);
	else	length = 2*floor(pow(1.0*nAtoms, 1.0/nDimensions))+1;

	srand48(123456);

	FILE *outfile;
	outfile = fopen("final.2.0.txt","w");

	
	printf("nAtoms = %d\tLength = %d\n", nAtoms, length);

	
	for(xCounter=0; xCounter<length; xCounter+=2){
		
		for(yCounter=0; yCounter<length; yCounter+=2){

			//Set initial positions
			positionX[counter] = xCounter;
			positionY[counter] = yCounter;
			printf("Intial X_%d = %f, Inital Y_%d = %f\n", counter, positionX[counter], counter, positionY[counter]);

			//Set initial velocities with temperature scaling
			velocityX[counter] =((drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48())/(12.0))-0.5;
			velocityX[counter] = velocityX[counter]*sqrt(initialTemp);
			//velocityX[counter] = 1;
			printf("Initial X Velocity %d = %f\n", counter, velocityX[counter]);

			velocityY[counter] =((drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48()+drand48())/(12.0))-0.5;
			velocityY[counter] = velocityY[counter]*sqrt(initialTemp);
			//velocityY[counter] = 1;
			printf("Initial Y Velocity %d = %f\n", counter, velocityY[counter]);
			
			velocityTotal[counter] = sqrt(velocityX[counter]*velocityX[counter]+velocityY[counter]*velocityY[counter]);

			counter++;
			if(counter>=nAtoms){
				stop = 1;
				break;
			}
	
		}

		if(stop==1)	break;
	}

	//Calculate inital Potential and Kinetic Energy
	potentialEnergy = forces(time1, potentialEnergy, positionX, forceXMain, positionY, forceYMain);
	//getchar();
	for(counter=0; counter<nAtoms; counter++){

		velocityTotal[counter] = sqrt(velocityX[counter]*velocityX[counter]+velocityY[counter]*velocityY[counter]);
		kineticEnergy += (velocityTotal[counter]*velocityTotal[counter]) * 0.5;

	}
	
	printf("Time:   0\tPE = %f\tKE = %f\tTE = %f\n", potentialEnergy, kineticEnergy, potentialEnergy+kineticEnergy);

	//Main Loop
	for(timeMain=1;timeMain<numberOfSteps;timeMain++){

		//potentialEnergy = forces(time1, potentialEnergy, positionX, forceXMain, positionY, forceYMain);

		//Check for collisions
		for(xCounter=0;xCounter<nAtoms;xCounter++){

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

		}

		//Change position
		for(counter=0;counter<nAtoms;counter++){

			//potentialEnergy = forces(time1, potentialEnergy, positionX, forceXMain, positionY, forceYMain);
			//getchar();
			//printf("PE = %lf\n",potentialEnergy);
			//printf("X = %lf, Y = %lf\n",*(positionX+counter),*(positionY+counter));
			positionX[counter] = positionX[counter] + timeStep * (velocityX[counter] + stepOver2*(forceXMain[counter][time1]));
			positionY[counter] = positionY[counter] + timeStep * (velocityY[counter] + stepOver2*(forceYMain[counter][time1]));
			//printf("Next X = %lf\n",*(positionX+counter));
			if (positionX[counter] < 0.)		positionX[counter] = positionX[counter] + length;
      			if (positionX[counter] >= length)	positionX[counter] = positionX[counter] - length;
			if (positionY[counter] < 0.)		positionY[counter] = positionY[counter] + length;
      			if (positionY[counter] >= length)	positionY[counter] = positionY[counter] - length;
	
		}


		potentialEnergy = forces(time2, potentialEnergy, positionX, forceXMain, positionY, forceYMain);
		kineticEnergy = 0;
		
		//Change velocity
		for(counter=0;counter<nAtoms;counter++){

			velocityX[counter] = velocityX[counter] + stepOver2 * (forceXMain[counter][time1]+forceXMain[counter][time2]);
			velocityY[counter] = velocityY[counter] + stepOver2 * (forceYMain[counter][time1]+forceYMain[counter][time2]);
			velocityTotal[counter] = sqrt(velocityX[counter]*velocityX[counter]+velocityY[counter]*velocityY[counter]);
			//printf("Force X_%d = %lf, Force Y_%d = %lf\n",counter,*(forceXMain+counter+time1*nAtoms),counter,*(forceYMain+counter+time1*nAtoms));
			//printf("X Velocity_%d = %lf, Y Velocity_%d = %lf, Total = %lf, Time = %d\n",counter,velocityX[counter],counter,velocityY[counter], velocityTotal[counter],timeMain);
			kineticEnergy += (velocityX[counter]*velocityX[counter]+velocityY[counter]*velocityY[counter]) * 0.5;

		}
		//getchar();

		temp = 2*kineticEnergy / (3*nAtoms);
	
		//Troubleshoot print loop
		//if(timeMain<100)	printf("Time: %3.d\tPE = %lf\tKE = %lf\tPE+KE = %lf\n",timeMain,potentialEnergy,kineticEnergy,potentialEnergy+kineticEnergy);
		
		if(timeMain%stepsBetweenPrint == 0)	printf("Time: %d\tPE = %lf\tKE = %lf\tPE+KE = %lf\n",timeMain,potentialEnergy,kineticEnergy,potentialEnergy+kineticEnergy);

		dummy = time1;
		time1 = time2;
		time2 = dummy;


	}
	
	printf("Final Temp = %lf\n",temp);
	
	fclose(outfile);
	//getchar();	
	
}
