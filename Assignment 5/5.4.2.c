#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Mitchell Miller
//Assignment 5
//PHYS 240 4/2/10

int main(){

	//Intialize Variables
	double dx,dy,x=0,y=0,meanSquare=0;
	double dxAverage,dyAverage,Average,trialAverage=0;
	int counter1,counter2,counter3;
	FILE *outfile;
	outfile = fopen("5.4.2.6.txt","w");
	//outfile = fopen("5.4.2.txt","w");
	//fprintf(outfile,"Run 1\n");

	for(counter3=1;counter3<10000;counter3+=10){

	meanSquare = 0;

		for(counter1=0;counter1<100;counter1++){

			//Set seed and start value
			srand48(495236*cos(counter1));
			x=0;
			y=0;
			dxAverage=0;
			dyAverage=0;

			for(counter2=0;counter2<counter3;counter2++){

				dx = (drand48() - 0.5) * 2;
				dy = (drand48() - 0.5) * 2;
				x = x + dx;
				y = y + dy;
				dxAverage = dxAverage + dx * 1/10000;
				dyAverage = dyAverage + dy * 1/10000;
				//fprintf(outfile, "%lf\t%lf\n",x,y);

			}

			//Compute Average values for R^2 and (dx*dy)/R^2
			Average = dxAverage * dyAverage / (x*x + y*y);
			trialAverage = trialAverage + Average * 0.01;
			meanSquare = meanSquare + (x*x + y*y) * 0.01;
			//printf("(dx*dy)/R^2 = %e\n",Average);

			//fprintf(outfile,"\n\n\nRun %d\n",counter1+2);

		}

	printf("Mean Square Distance = %lf\n",meanSquare);
	printf("<(dx*dy)/R^2> = %e\n",trialAverage);
	fprintf(outfile, "%lf\t%lf\n",sqrt(counter3),sqrt(meanSquare));

	}
	
	fclose(outfile);

}
