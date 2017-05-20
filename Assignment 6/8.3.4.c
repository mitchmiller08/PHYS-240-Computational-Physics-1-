#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "/usr/include/clapack.h"
#include <cblas.h>

//Mitchell Miller
//Assignment 6
//PHYS 240 4/16/10

//http://www.netlib.org/lapack/double/


static long
calldgetrf(long M, long N, double *matrixA, long lda, long *matrixPivot){

  long info;

  dgetrf_(&M, &N, matrixA, &lda, matrixPivot, &info);
  return info;

}

static long
calldgetri(long N, double *matrixA, long lda, long *matrixPivot, double *matrixWork, long lwork){

	long info;
	
	dgetri_(&N, matrixA, &lda, matrixPivot, matrixWork, &lwork, &info);
	return info;
	
}

static long
calldgesv(long N, long NRHS, double *matrixA, long lda, long *matrixPivot, double *matrixB, long ldb){

	long info;

	dgesv_(&N, &NRHS, matrixA, &lda, matrixPivot, matrixB, &ldb, &info);
	return info;

}

static long
calldgeev(char jobL, char jobR, long N, double *matrixA, long lda, double *eigenvalueRealArray, double *eigenvalueImaginaryArray, double *eigenvectorL, long ldvl, double *eigenvectorR, long ldvr, double *matrixWork, long lwork){

	long info;

	dgeev_(&jobL,&jobR,&N,matrixA,&lda,eigenvalueRealArray,eigenvalueImaginaryArray,eigenvectorL,&ldvl,eigenvectorR,&ldvr,matrixWork,&lwork,info);
	return info;

}

int main(){

	//Initialize Variables
	double matrixATranspose[] = { 4, 3, 2,
			     -2, 6, 1,
			     1, -4, 8};
	double matrixAInverse[] = { 4,-2, 1,
			     3, 6,-4,
			     2, 1, 8};
	double matrixAEigen[] = {-2,2,-3,
				  2,1,-6,
				 -1,-2,0};
	double eigenvalueRealArray[3];
	double eigenvalueImaginaryArray[3];
	double eigenvectorArrayL[9];
	double eigenvectorArrayR[9];
	long matrixPivot[9];
	int counter1,counter2;
	int three=3,info=0,stupid=12;
	double matrixWork[3];
	
	//Calculate inverse of A
	info = calldgetrf(3,3,matrixAInverse,3,matrixPivot);
	printf("INFO: %d\n", info);
	info = calldgetri(3,matrixAInverse,3,matrixPivot,matrixWork,3);
	printf("INFO: %d\n", info);

	//Prinf inverse of A
	printf("****A INVERSE SOLUTION****\n");
	for(counter1=0;counter1<3;counter1++){

		for(counter2=0;counter2<3;counter2++) printf("%lf\t",matrixAInverse[3*counter1+counter2]);
		printf("\n");

	}

	//Initialize Matricies for part 2
	double matrixB[] = {12.,-25.,32.};
	//double matrixB[] = {4,-10,22};
	//double matrixB[] = {20,-30,40};

	//Calculate solutions for A*x = B
	info = calldgesv(3,1,matrixATranspose,3,matrixPivot,matrixB,3);

	//Print solutions
	printf("****X MATRIX SOLUTION****\n");
	printf("INFO: %d\n", info);
	for(counter1=0;counter1<3;counter1++)	printf("%lf\n", matrixB[counter1]);
	
	//Calculate eignevalues and eigenvectors
	calldgeev('V','V',3,matrixAEigen,3,eigenvalueRealArray,eigenvalueImaginaryArray,eigenvectorArrayL,3,eigenvectorArrayR,3,matrixWork,12);
	
	//Print soluionts	
	printf("****EIGENVALUE SOLUTIONS****\n");
	printf("INFO: %d\n", info);

	for(counter1=0;counter1<3;counter1++)	printf("%lf %lf\n", eigenvalueRealArray[counter1],eigenvalueImaginaryArray[counter1]);
	
	for(counter2=0;counter2<3;counter2++){
	
		printf("****EIGENVECTOR %d SOLUTIONS****\n",counter2+1);
		for(counter1=0;counter1<3;counter1++){

			printf("%lf %lf\n",eigenvectorArrayL[counter1+3*counter2],eigenvectorArrayR[counter1+3*counter2]);

		}
	
	}

	//Initialize Hilbert matrix
	double matrixHilbert[10000];
	double matrixBHilbert[100];
	for(counter1=1;counter1<101;counter1++){

		for(counter2=1;counter2<101;counter2++){

			matrixHilbert[100*(counter1-1)+(counter2-1)] = 1/((double)counter1+(double)counter2-1.);
			//printf("Position = %d, %lf\n",100*(counter1-1)+counter2,matrixHilbert[100*(counter1-1)+counter2]);

		}
		matrixBHilbert[counter1-1] = (1/(double)counter1);
		//printf("%lf\n",matrixBHilbert[counter1-1]);

	}

	//Compute solution for Hilbert Matrix
	info = calldgesv(100,1,matrixHilbert,100,matrixPivot,matrixBHilbert,100);
	printf("****HILBERT MATRIX SOLUTION****\n");
	printf("INFO: %d\n",info);
	for(counter1=0;counter1<100;counter1++) printf("%d\t%lf\n",counter1,matrixBHilbert[counter1]);
}



