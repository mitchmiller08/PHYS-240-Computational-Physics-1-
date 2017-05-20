#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535897932384626433832

//Mitchell Miller
//Assignment 5
//PHYS 240 4/2/10

int main(){

	//Intialize variables
	double x,y,average=0,counter=1;
	int counter1,counter2,counter3;
	FILE *outfile;
	outfile = fopen("6.6.3.txt","w");
	
	for(counter1=0;counter1<16;counter1++){

		//Reset variables
		y = 0;
		counter2 = 0;
		counter3 = 0;
		counter = 0;

		printf("********* Trial # %d *********\n",counter1+1);

		for(counter2=1;counter2<70000;counter2++){

			//Reset X
			x = 0;
			
			//Add to X
			for(counter3=0;counter3<10;counter3++)	x += drand48();

			//Calculate Y
			y += x * x;
			
			if(counter2%(int)pow(2,counter) == 0){

				counter++;
				printf("Loops = %d\tIntegral = %lf\tError = %lf\n",counter2,y/counter2,fabs((y/counter2)-155/6)/(155/6));
				fprintf(outfile,"%lf\t%lf\n",1/sqrt((double)counter2),fabs((y/counter2)-155/6)/(155/6));
			}

		}

		average += y/counter2;
	
	}

	printf("Average = %lf\n", average/16);

}
