#include <stdio.h>
#include <math.h>

//Task 1.1
//Mitchell Miller PHYS240 2/12/10

//**                 2     2
//**               n  *  h
//**        E = -------------
//**                        2
//**              8 * m * L 
//*************************************************
//**              ________     0.5
//**             |   2             (  n * Pi      )
//**   Psi(x) =  | -----    *   sin(---------- * x)
//**            \|   L             (    L         )


int main(){
	//Initialize variables
	double eigenvalue[7]={0,0,0,0,0,0,0}, planck=6.62606896e-34, hBar=1.054571628e-34, mass=0, length=0;
    double state=1, internalCoefficient=1, externalCoefficient=1, m=9.10938215e-31, dx=0, x=0;
	int count=1;
	FILE *file;
    
    file = fopen("Task 11.txt", "w");
	printf("Length = ");
	scanf("%lf",&length);
	printf("Mass = ");
	scanf("%lf",&mass);
	//Calculate eigenvalues
	do{
		dx = 0;
        eigenvalue[count] = (state*state*planck*planck) / (8*mass*length*length);
		printf("Eigenvalue %i = %lf \n", count, eigenvalue[count]*(6.24150974e18));
    //Calculate coefficients and display wave function
		internalCoefficient = state*3.141592653589793/length;
		externalCoefficient = sqrt(2/length);
		while(dx<length){
                    x = externalCoefficient*sin(internalCoefficient*dx);
                    dx = dx + length/500;
                    fprintf(file, "{%e,%e},", dx, x);
        }
        printf("Normalized Wave Function %i = %lf*sin[%lf*x] \n", count, externalCoefficient, internalCoefficient);
		fprintf(file, "\n\n\n");
		state ++;
		count ++;
	}while(state<7);
	
	printf("Press Enter to Exit");
	getchar();
	getchar();
	fclose(file);
}
